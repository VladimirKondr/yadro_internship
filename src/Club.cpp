#include "Club.h"

#include "Client.h"
#include "ClientPool.h"
#include "TablePool.h"
#include "events/ClientArrivalEvent.h"
#include "events/ClientChangedSeatingEvent.h"
#include "events/ClientLeftInvoluntarilyEvent.h"
#include "events/ClientLeftVoluntarilyEvent.h"
#include "events/ClientSeatingEvent.h"
#include "events/ClientWaitingEvent.h"
#include "events/ErrorEvent.h"

#include <algorithm>
#include <memory>

namespace computer_club {

std::unique_ptr<Club> Club::instance = nullptr;

Club::Club(TimePoint open_time, TimePoint close_time, double hourly_rate)
    : open_time_(open_time), close_time_(close_time), hourly_rate_(hourly_rate) {
}

Club& Club::GetInstance(TimePoint open_time, TimePoint close_time, double hourly_rate) {
    if (!instance) {
        instance = std::unique_ptr<Club>(new Club(open_time, close_time, hourly_rate));
    }
    
    return *instance;
}

void Club::ProcessEvent(const std::shared_ptr<Event>& event) {
    all_events_.push_back(event);

    const TimePoint& time = event->Time();

    if (time < open_time_ || time > close_time_) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "NotOpenYet", event));
        return;
    }

    switch (event->Id()) {
        case 1:
            HandleClientArrival(event);
            break;
        case 2:
            HandleClientSeating(event);
            break;
        case 3:
            HandleClientWaiting(event);
            break;
        case 4:
            HandleClientLeaving(event);
            break;
        default:
            all_events_.push_back(std::make_shared<ErrorEvent>(time, "UnknownEvent", event));
            break;
    }
}

void Club::HandleClientArrival(const std::shared_ptr<Event>& event) {
    auto arrival_event = std::dynamic_pointer_cast<ClientArrivalEvent>(event);

    const TimePoint& time = arrival_event->Time();
    const std::shared_ptr<Client>& client = arrival_event->GetClient();
    
    if (client->IsInClub()) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "ClientAlreadyInClub", event));
    }
    client->SetInClub(true);
}

void Club::HandleClientSeating(const std::shared_ptr<Event>& event) {
    auto seating_event = std::dynamic_pointer_cast<ClientChangedSeatingEvent>(event);

    const TimePoint& time = seating_event->Time();
    const std::shared_ptr<Client>& client = seating_event->GetClient();
    const std::string& client_name = client->Name();
    const std::shared_ptr<Table>& table = seating_event->GetTable();

    if (client == nullptr || !client->IsInClub()) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "ClientUnknown", event));
        return;
    }

    if (table->IsOccupied()) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "PlaceIsBusy", event));
        return;
    }

    const std::shared_ptr<Table>& current_table = client->GetTable();
    if (current_table) {
        current_table->Free(time);
    }
    table->Occupy(time);
    client->ChangeTable(table);
}

void Club::HandleClientWaiting(const std::shared_ptr<Event>& event) {
    auto waiting_event = std::dynamic_pointer_cast<ClientWaitingEvent>(event);

    const std::shared_ptr<Client>& client = waiting_event->GetClient();
    const TimePoint& time = waiting_event->Time();
    std::vector<std::shared_ptr<Table>> free_tables = TablePool::GetFreeTables();

    if (!free_tables.empty()) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "ICanWaitNoLonger!", event));
        return;
    }

    if (waiting_clients_.size() >= TablePool::TableCount()) {
        all_events_.push_back(std::make_shared<ClientLeftInvoluntarilyEvent>(time, client));
        client->SetInClub(false);
        return;
    }

    waiting_clients_.push(client);
}

void Club::HandleClientLeaving(const std::shared_ptr<Event>& event) {
    auto leaving_event = std::dynamic_pointer_cast<ClientLeftVoluntarilyEvent>(event);

    const TimePoint& time = leaving_event->Time();
    const std::shared_ptr<Client>& client = leaving_event->GetClient();

    if (client == nullptr || !client->IsInClub()) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "ClientUnknown", event));
        return;
    }

    if (client->GetTable() != nullptr) {
        std::shared_ptr<Table> table_to_free = client->GetTable();
        table_to_free->Free(time);
        client->ChangeTable(nullptr);
        SeatClientFromQueue(time, table_to_free);
    }
    client->SetInClub(false);
}

void Club::SeatClientFromQueue(const TimePoint& time, const std::shared_ptr<Table>& table) {
    if (waiting_clients_.empty()) {
        return;
    }

    std::shared_ptr<Client> next_client = waiting_clients_.front();
    waiting_clients_.pop();

    all_events_.push_back(std::make_shared<ClientSeatingEvent>(time, next_client, table));

    table->Occupy(time);
    next_client->ChangeTable(table);
}

void Club::ClosingTime() {
    std::vector<std::shared_ptr<Client>> remaining_clients;

    for (const auto& [client_name, client] : ClientPool::Clients()) {
        if (!client->IsInClub()) {
            continue;
        }
        remaining_clients.push_back(client);
    }

    std::sort(
        remaining_clients.begin(), remaining_clients.end(),
        [](const std::shared_ptr<Client>& a, const std::shared_ptr<Client>& b) { return a->Name() < b->Name(); });

    for (const auto& client : remaining_clients) {
        all_events_.push_back(std::make_shared<ClientLeftInvoluntarilyEvent>(close_time_, client));

        if (client->GetTable() != nullptr) {
            client->GetTable()->Free(close_time_);
            client->ChangeTable(nullptr);
        }
        client->SetInClub(false);
        
    }

    waiting_clients_ = std::queue<std::shared_ptr<Client>>();
}

const std::vector<std::shared_ptr<Event>>& Club::GetAllEvents() const {
    return all_events_;
}

TimePoint Club::GetOpenTime() const {
    return open_time_;
}

TimePoint Club::GetCloseTime() const {
    return close_time_;
}

double Club::GetHourlyRate() const {
    return hourly_rate_;
}
}  // namespace computer_club

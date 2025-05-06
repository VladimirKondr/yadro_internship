#include "Club.h"

#include "Client.h"
#include "Logger.h"
#include "events/ClientChangedSeatingEvent.h"
#include "events/ClientLeftInvoluntarilyEvent.h"
#include "events/ClientLeftVoluntarilyEvent.h"
#include "events/ClientSeatingEvent.h"
#include "events/ClientWaitingEvent.h"
#include "events/ErrorEvent.h"
#include "events/IncomingEvent.h"

#include <algorithm>
#include <stdexcept>

namespace computer_club {

Club::Club(int table_count, TimePoint open_time, TimePoint close_time, double hourly_rate)
    : table_count_(table_count)
    , open_time_(open_time)
    , close_time_(close_time)
    , hourly_rate_(hourly_rate) {
    for (int i = 1; i <= table_count_; ++i) {
        tables_.emplace_back(i);
    }
}

bool Club::IsTableIdValid(int table_id) const {
    return table_id >= 1 && table_id <= table_count_;
}

bool Club::IsClientInClub(const std::string& client_name) const {
    return clients_.find(client_name) != clients_.end();
}

bool Club::HasFreeTable() const {
    return std::ranges::any_of(tables_, [](const Table& table) {
        return !table.IsOccupied();
    });
}

Table* Club::GetTable(int table_id) {
    if (!IsTableIdValid(table_id)) {
        return nullptr;
    }
    return &tables_[table_id - 1];
}

void Club::ProcessEvent(const std::shared_ptr<Event>& event) {
    all_events_.push_back(event);

    const TimePoint& time = event->Time();

    if (time < open_time_) {
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
    auto arrival_event = std::dynamic_pointer_cast<IncomingEvent>(event);
    if (!arrival_event) {
        return;
    }

    const TimePoint& time = arrival_event->Time();
    const std::string& client_name = arrival_event->ClientName();

    if (IsClientInClub(client_name)) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "YouShallNotPass", event));
        return;
    }

    clients_.insert({client_name, Client(client_name)});
}

void Club::HandleClientSeating(const std::shared_ptr<Event>& event) {
    auto seating_event = std::dynamic_pointer_cast<ClientChangedSeatingEvent>(event);
    if (!seating_event) {
        return;
    }

    const TimePoint& time = seating_event->Time();
    const std::string& client_name = seating_event->ClientName();
    int table_id = seating_event->TableNumber();

    if (!IsClientInClub(client_name)) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "ClientUnknown", event));
        return;
    }

    if (!IsTableIdValid(table_id)) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "InvalidTable", event));
        return;
    }

    Table* table = GetTable(table_id);

    if (table->IsOccupied()) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "PlaceIsBusy", event));
        return;
    }

    int current_table_id = clients_[client_name].TableNumber();
    if (current_table_id > 0 && current_table_id != table_id) {
        Table* current_table = GetTable(current_table_id);
        current_table->Free(time, hourly_rate_);
    }

    table->Occupy(time);
    clients_[client_name].SetTableNumber(table_id);
}

void Club::HandleClientWaiting(const std::shared_ptr<Event>& event) {
    auto waiting_event = std::dynamic_pointer_cast<ClientWaitingEvent>(event);
    if (!waiting_event) {
        return;
    }

    const TimePoint& time = waiting_event->Time();
    const std::string& client_name = waiting_event->ClientName();

    if (!IsClientInClub(client_name)) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "ClientUnknown", event));
        return;
    }

    if (HasFreeTable()) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "ICanWaitNoLonger!", event));
        return;
    }

    if (waiting_clients_.size() >= static_cast<size_t>(table_count_)) {
        all_events_.push_back(std::make_shared<ClientLeftInvoluntarilyEvent>(time, client_name));
        clients_.erase(client_name);
        return;
    }

    waiting_clients_.push(client_name);
}

void Club::HandleClientLeaving(const std::shared_ptr<Event>& event) {
    auto leaving_event = std::dynamic_pointer_cast<ClientLeftVoluntarilyEvent>(event);
    if (!leaving_event) {
        return;
    }

    const TimePoint& time = leaving_event->Time();
    const std::string& client_name = leaving_event->ClientName();

    if (!IsClientInClub(client_name)) {
        all_events_.push_back(std::make_shared<ErrorEvent>(time, "ClientUnknown", event));
        return;
    }

    int table_id = clients_[client_name].TableNumber();
    if (table_id > 0) {
        Table* table = GetTable(table_id);
        table->Free(time, hourly_rate_);

        SeatClientFromQueue(time, table_id);
    }

    clients_.erase(client_name);
}

void Club::SeatClientFromQueue(const TimePoint& time, int table_id) {
    if (waiting_clients_.empty()) {
        return;
    }

    std::string next_client_name = waiting_clients_.front();
    waiting_clients_.pop();

    all_events_.push_back(std::make_shared<ClientSeatingEvent>(time, next_client_name, table_id));

    Table* table = GetTable(table_id);
    table->Occupy(time);
    clients_[next_client_name].SetTableNumber(table_id);
}

void Club::ClosingTime() {
    std::vector<std::string> remaining_clients;

    for (const auto& [client_name, client] : clients_) {
        remaining_clients.push_back(client_name);
    }

    std::sort(remaining_clients.begin(), remaining_clients.end());

    for (const auto& client_name : remaining_clients) {
        all_events_.push_back(
            std::make_shared<ClientLeftInvoluntarilyEvent>(close_time_, client_name));

        int table_id = clients_[client_name].TableNumber();
        if (table_id > 0) {
            Table* table = GetTable(table_id);
            table->Free(close_time_, hourly_rate_);
        }
    }

    clients_.clear();
    waiting_clients_ = std::queue<std::string>();
}

const std::vector<std::shared_ptr<Event>>& Club::GetAllEvents() const {
    return all_events_;
}

const std::vector<Table>& Club::GetTables() const {
    return tables_;
}

TimePoint Club::GetOpenTime() const {
    return open_time_;
}

TimePoint Club::GetCloseTime() const {
    return close_time_;
}

}  // namespace computer_club
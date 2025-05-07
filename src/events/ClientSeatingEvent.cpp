#include "events/ClientSeatingEvent.h"
#include "ClientPool.h"
#include "TablePool.h"

#include <sstream>

namespace computer_club {

ClientSeatingEvent::ClientSeatingEvent(const TimePoint& t, const std::shared_ptr<Client>& client, const std::shared_ptr<Table>& table)
    : OutgoingEvent(t, 12, client->Name() + " " + table->ToString()), client_(client)
    , table_(table) {
}

std::shared_ptr<Table> ClientSeatingEvent::GetTable() const {
    return table_;
}

std::shared_ptr<Client> ClientSeatingEvent::GetClient() const {
    return client_;
}

std::string ClientSeatingEvent::ToString() const {
    return Time().ToString() + " 12 " + GetClient()->Name() + " " +
           GetTable()->ToString();
}

std::shared_ptr<ClientSeatingEvent> ClientSeatingEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    int table_number = -1;
    iss >> client_name >> table_number;
    return std::make_shared<ClientSeatingEvent>(time, ClientPool::GetClient(client_name), TablePool::GetTable(table_number));
}

}  // namespace computer_club
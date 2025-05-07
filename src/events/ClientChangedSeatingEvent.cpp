#include "events/ClientChangedSeatingEvent.h"

#include "ClientPool.h"
#include "TablePool.h"

#include <sstream>

namespace computer_club {

ClientChangedSeatingEvent::ClientChangedSeatingEvent(
    const TimePoint& t, const std::shared_ptr<Client>& client, const std::shared_ptr<Table>& table)
    : IncomingEvent(t, 2, client), table_(table) {
}

std::shared_ptr<Table> ClientChangedSeatingEvent::GetTable() const {
    return table_;
}

std::string ClientChangedSeatingEvent::ToString() const {
    return Time().ToString() + " 2 " + GetClient()->Name() + " " + table_->ToString();
}

std::shared_ptr<ClientChangedSeatingEvent> ClientChangedSeatingEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    int table_number = -1;
    iss >> client_name >> table_number;
    return std::make_shared<ClientChangedSeatingEvent>(
        time, ClientPool::GetClient(client_name), TablePool::GetTable(table_number));
}

}  // namespace computer_club
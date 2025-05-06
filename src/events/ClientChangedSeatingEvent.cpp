#include "events/ClientChangedSeatingEvent.h"

#include <sstream>

namespace computer_club {

ClientChangedSeatingEvent::ClientChangedSeatingEvent(
    const TimePoint& t, std::string client, int table)
    : IncomingEvent(t, 2, std::move(client)), table_number_(table) {
}

int ClientChangedSeatingEvent::TableNumber() const {
    return table_number_;
}

std::string ClientChangedSeatingEvent::ToString() const {
    return Time().ToString() + " 2 (ClientChangedSeating) " + ClientName() + " " +
           std::to_string(TableNumber());
}

std::shared_ptr<ClientChangedSeatingEvent> ClientChangedSeatingEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    int table_number = -1;
    iss >> client_name >> table_number;
    return std::make_unique<ClientChangedSeatingEvent>(time, client_name, table_number);
}

}  // namespace computer_club
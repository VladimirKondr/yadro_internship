#include "ClientSeatingEvent.h"

#include <sstream>

namespace computer_club {

ClientSeatingEvent::ClientSeatingEvent(const TimePoint& t, std::string client_name, int table)
    : OutgoingEvent(t, 12, client_name + " " + std::to_string(table))
    , table_number_(table)
    , client_name_(std::move(client_name)) {
}

int ClientSeatingEvent::TableNumber() const {
    return table_number_;
}

std::string ClientSeatingEvent::ClientName() const {
    return client_name_;
}

std::string ClientSeatingEvent::ToString() const {
    return Time().ToString() + " 12 (ClientSeating) " + ClientName() + " " +
           std::to_string(TableNumber());
}

std::unique_ptr<ClientSeatingEvent> ClientSeatingEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    int table_number = -1;
    iss >> client_name >> table_number;
    return std::make_unique<ClientSeatingEvent>(time, client_name, table_number);
}

}  // namespace computer_club
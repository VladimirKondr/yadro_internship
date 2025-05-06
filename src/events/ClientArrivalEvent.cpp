#include "ClientArrivalEvent.h"

#include <sstream>

namespace computer_club {

ClientArrivalEvent::ClientArrivalEvent(const TimePoint& t, std::string client)
    : IncomingEvent(t, 1, std::move(client)) {
}

std::string ClientArrivalEvent::ToString() const {
    return Time().ToString() + " 1 (ClientArrival) " + ClientName();
}

std::unique_ptr<ClientArrivalEvent> ClientArrivalEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    return std::make_unique<ClientArrivalEvent>(time, client_name);
}

}  // namespace computer_club
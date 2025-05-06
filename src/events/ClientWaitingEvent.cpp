#include "events/ClientWaitingEvent.h"

#include <sstream>

namespace computer_club {

ClientWaitingEvent::ClientWaitingEvent(const TimePoint& t, std::string client)
    : IncomingEvent(t, 3, std::move(client)) {
}

std::string ClientWaitingEvent::ToString() const {
    return Time().ToString() + " 3 " + ClientName();
}

std::shared_ptr<ClientWaitingEvent> ClientWaitingEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    return std::make_unique<ClientWaitingEvent>(time, client_name);
}

}  // namespace computer_club
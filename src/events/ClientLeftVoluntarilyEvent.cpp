#include "events/ClientLeftVoluntarilyEvent.h"

#include <sstream>

namespace computer_club {

ClientLeftVoluntarilyEvent::ClientLeftVoluntarilyEvent(const TimePoint& t, std::string client)
    : IncomingEvent(t, 4, std::move(client)) {
}

std::string ClientLeftVoluntarilyEvent::ToString() const {
    return Time().ToString() + " 4 (ClientLeftVoluntarily) " + ClientName();
}

std::shared_ptr<ClientLeftVoluntarilyEvent> ClientLeftVoluntarilyEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    return std::make_unique<ClientLeftVoluntarilyEvent>(time, client_name);
}

}  // namespace computer_club
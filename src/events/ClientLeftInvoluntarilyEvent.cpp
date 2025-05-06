#include "ClientLeftInvoluntarilyEvent.h"

#include <sstream>

namespace computer_club {

ClientLeftInvoluntarilyEvent::ClientLeftInvoluntarilyEvent(const TimePoint& t, std::string client)
    : OutgoingEvent(t, 11, std::move(client)) {
}

std::string ClientLeftInvoluntarilyEvent::ClientName() const {
    return client_name_;
}

std::string ClientLeftInvoluntarilyEvent::ToString() const {
    return Time().ToString() + " 11 (ClientLeftInvoluntarily) " + ClientName();
}

std::unique_ptr<ClientLeftInvoluntarilyEvent> ClientLeftInvoluntarilyEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    return std::make_unique<ClientLeftInvoluntarilyEvent>(time, client_name);
}

}  // namespace computer_club
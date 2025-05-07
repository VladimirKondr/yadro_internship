#include "events/ClientLeftInvoluntarilyEvent.h"

#include "ClientPool.h"

#include <sstream>

namespace computer_club {

ClientLeftInvoluntarilyEvent::ClientLeftInvoluntarilyEvent(
    const TimePoint& t, const std::shared_ptr<Client>& client)
    : OutgoingEvent(t, 11, ""), client_(client) {
}

std::shared_ptr<Client> ClientLeftInvoluntarilyEvent::GetClient() const {
    return client_;
}

std::string ClientLeftInvoluntarilyEvent::ToString() const {
    return Time().ToString() + " 11 " + GetClient()->Name();
}

std::shared_ptr<ClientLeftInvoluntarilyEvent> ClientLeftInvoluntarilyEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    return std::make_shared<ClientLeftInvoluntarilyEvent>(time, ClientPool::GetClient(client_name));
}

}  // namespace computer_club
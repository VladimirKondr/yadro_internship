#include "events/ClientLeftVoluntarilyEvent.h"

#include "ClientPool.h"

#include <sstream>

namespace computer_club {

ClientLeftVoluntarilyEvent::ClientLeftVoluntarilyEvent(
    const TimePoint& t, const std::shared_ptr<Client>& client)
    : IncomingEvent(t, 4, client) {
}

std::string ClientLeftVoluntarilyEvent::ToString() const {
    return Time().ToString() + " 4 " + GetClient()->Name();
}

std::shared_ptr<ClientLeftVoluntarilyEvent> ClientLeftVoluntarilyEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    return std::make_shared<ClientLeftVoluntarilyEvent>(time, ClientPool::GetClient(client_name));
}

}  // namespace computer_club
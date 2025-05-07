#include "events/ClientWaitingEvent.h"

#include "ClientPool.h"

#include <sstream>

namespace computer_club {

ClientWaitingEvent::ClientWaitingEvent(const TimePoint& t, const std::shared_ptr<Client>& client)
    : IncomingEvent(t, 3, client) {
}

std::string ClientWaitingEvent::ToString() const {
    return Time().ToString() + " 3 " + GetClient()->Name();
}

std::shared_ptr<ClientWaitingEvent> ClientWaitingEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    return std::make_shared<ClientWaitingEvent>(time, ClientPool::GetClient(client_name));
}

}  // namespace computer_club
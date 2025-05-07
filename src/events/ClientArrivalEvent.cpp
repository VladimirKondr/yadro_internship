#include "events/ClientArrivalEvent.h"
#include "ClientPool.h"
#include "Client.h"

#include <sstream>

namespace computer_club {

ClientArrivalEvent::ClientArrivalEvent(const TimePoint& t, const std::shared_ptr<Client>& client)
    : IncomingEvent(t, 1, client) {
}
std::string ClientArrivalEvent::ToString() const {
    return Time().ToString() + " 1 " + GetClient()->Name();
}

std::shared_ptr<ClientArrivalEvent> ClientArrivalEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    ClientPool::AddClient(client_name);
    return std::make_shared<ClientArrivalEvent>(time, ClientPool::GetClient(client_name));
}

}  // namespace computer_club
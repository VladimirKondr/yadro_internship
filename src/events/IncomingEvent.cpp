#include "events/IncomingEvent.h"
#include <Client.h>

namespace computer_club {

IncomingEvent::IncomingEvent(const TimePoint& t, int i, const std::shared_ptr<Client>& client)
    : Event(t, i), client_(client) {
}

std::shared_ptr<Client> IncomingEvent::GetClient() const {
    return client_;
}

}  // namespace computer_club
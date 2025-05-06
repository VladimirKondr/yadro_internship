#include "events/IncomingEvent.h"

#include <utility>

namespace computer_club {

IncomingEvent::IncomingEvent(const TimePoint& t, int i, std::string client)
    : Event(t, i), client_name_(std::move(client)) {
}

std::string IncomingEvent::ClientName() const {
    return client_name_;
}

}  // namespace computer_club
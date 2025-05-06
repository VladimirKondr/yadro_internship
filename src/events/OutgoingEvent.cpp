#include "OutgoingEvent.h"

#include <utility>

namespace computer_club {

OutgoingEvent::OutgoingEvent(const TimePoint& t, int i, std::string msg)
    : Event(t, i), message_(std::move(msg)) {
}

std::string OutgoingEvent::Message() const {
    return message_;
}

}  // namespace computer_club
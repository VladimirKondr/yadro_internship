#include "events/ErrorEvent.h"

#include <sstream>
#include <utility>

namespace computer_club {

ErrorEvent::ErrorEvent(const TimePoint& t, std::string error, std::shared_ptr<Event> cause_event)
    : OutgoingEvent(t, 13, std::move(error)), cause_event_(std::move(cause_event)) {
}

std::string ErrorEvent::ToString() const {
    return Time().ToString() + " 13 (Error) " + Message();
}

std::shared_ptr<ErrorEvent> ErrorEvent::Parse(std::istringstream& iss, const TimePoint& time) {
    std::string error_message;
    std::getline(iss, error_message);
    if (error_message.empty()) {
        return nullptr;
    }
    return std::make_unique<ErrorEvent>(time, error_message);
}

std::shared_ptr<Event> ErrorEvent::CauseEvent() const {
    return cause_event_;

}

}  // namespace computer_club
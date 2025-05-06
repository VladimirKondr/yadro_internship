#include "ErrorEvent.h"

#include <sstream>
#include <utility>

namespace computer_club {

ErrorEvent::ErrorEvent(const TimePoint& t, std::string error)
    : OutgoingEvent(t, 13, std::move(error)) {
}

std::string ErrorEvent::ToString() const {
    return Time().ToString() + " 13 (Error) " + Message();
}

std::unique_ptr<ErrorEvent> ErrorEvent::Parse(std::istringstream& iss, const TimePoint& time) {
    std::string error_message;
    std::getline(iss, error_message);
    if (error_message.empty()) {
        return nullptr;
    }
    return std::make_unique<ErrorEvent>(time, error_message);
}

}  // namespace computer_club
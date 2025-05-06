#ifndef ERROREVENT_H
#define ERROREVENT_H

#include "OutgoingEvent.h"
#include "TimePoint.h"

#include <memory>
#include <string>

namespace computer_club {

class ErrorEvent : public OutgoingEvent {
   public:
    ErrorEvent(const TimePoint& t, std::string error);
    [[nodiscard]] std::string ToString() const override;
    static std::unique_ptr<ErrorEvent> Parse(std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // ERROREVENT_H
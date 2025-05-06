#ifndef ERROREVENT_H
#define ERROREVENT_H

#include "OutgoingEvent.h"
#include "TimePoint.h"

#include <memory>
#include <string>

namespace computer_club {

class ErrorEvent : public OutgoingEvent {
    private:
    std::shared_ptr<Event> cause_event_;
   public:
    ErrorEvent(const TimePoint& t, std::string error_message, std::shared_ptr<Event> cause_event = nullptr);
    [[nodiscard]] std::string ToString() const override;
    static std::shared_ptr<ErrorEvent> Parse(std::istringstream& iss, const TimePoint& time);
    [[nodiscard]] std::shared_ptr<Event> CauseEvent() const;
};

}  // namespace computer_club

#endif  // ERROREVENT_H
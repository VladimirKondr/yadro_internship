#ifndef OUTGOINGEVENT_H
#define OUTGOINGEVENT_H

#include "Client.h"
#include "EventBase.h"

#include <optional>
#include <string>

namespace computer_club {

class OutgoingEvent : public Event {
   private:
    std::string message_;

   public:
    OutgoingEvent(const TimePoint& t, int i, std::string msg);
    [[nodiscard]] std::string Message() const;
};

}  // namespace computer_club

#endif  // OUTGOINGEVENT_H
#ifndef INCOMINGEVENT_H
#define INCOMINGEVENT_H

#include "EventBase.h"

#include <string>

namespace computer_club {

class IncomingEvent : public Event {
   private:
    std::string client_name_;

   public:
    IncomingEvent(const TimePoint& t, int i, std::string client);
    [[nodiscard]] std::string ClientName() const;
};

}  // namespace computer_club

#endif  // INCOMINGEVENT_H
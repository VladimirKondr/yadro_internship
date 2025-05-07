#ifndef INCOMINGEVENT_H
#define INCOMINGEVENT_H

#include "EventBase.h"
#include "Client.h"

#include <string>

namespace computer_club {

class IncomingEvent : public Event {
   private:
    std::shared_ptr<Client> client_;

   public:
    IncomingEvent(const TimePoint& t, int i, const std::shared_ptr<Client>& client);
    [[nodiscard]] std::shared_ptr<Client> GetClient() const;
};

}  // namespace computer_club

#endif  // INCOMINGEVENT_H
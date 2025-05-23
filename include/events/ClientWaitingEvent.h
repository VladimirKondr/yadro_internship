#ifndef CLIENTWAITINGEVENT_H
#define CLIENTWAITINGEVENT_H

#include "Client.h"
#include "IncomingEvent.h"

#include <memory>
#include <sstream>
#include <string>

namespace computer_club {

class ClientWaitingEvent : public IncomingEvent {
   public:
    ClientWaitingEvent(const TimePoint& t, const std::shared_ptr<Client>& client);
    [[nodiscard]] std::string ToString() const override;
    static std::shared_ptr<ClientWaitingEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // CLIENTWAITINGEVENT_H
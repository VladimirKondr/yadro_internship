#ifndef CLIENTARRIVALEVENT_H
#define CLIENTARRIVALEVENT_H

#include "IncomingEvent.h"

#include <memory>
#include <sstream>
#include <string>

namespace computer_club {

class ClientArrivalEvent : public IncomingEvent {
   public:
    ClientArrivalEvent(const TimePoint& t, std::string client);
    [[nodiscard]] std::string ToString() const override;
    static std::shared_ptr<ClientArrivalEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // CLIENTARRIVALEVENT_H
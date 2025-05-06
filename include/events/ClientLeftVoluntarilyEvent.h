#ifndef CLIENTLEFTVOLUNTARILYEVENT_H
#define CLIENTLEFTVOLUNTARILYEVENT_H

#include "IncomingEvent.h"

#include <memory>
#include <sstream>
#include <string>

namespace computer_club {

class ClientLeftVoluntarilyEvent : public IncomingEvent {
   public:
    ClientLeftVoluntarilyEvent(const TimePoint& t, std::string client);
    [[nodiscard]] std::string ToString() const override;
    static std::shared_ptr<ClientLeftVoluntarilyEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // CLIENTLEFTVOLUNTARILYEVENT_H
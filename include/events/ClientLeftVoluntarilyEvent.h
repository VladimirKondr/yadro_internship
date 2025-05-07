#ifndef CLIENTLEFTVOLUNTARILYEVENT_H
#define CLIENTLEFTVOLUNTARILYEVENT_H

#include "Client.h"
#include "IncomingEvent.h"

#include <memory>
#include <sstream>
#include <string>

namespace computer_club {

class ClientLeftVoluntarilyEvent : public IncomingEvent {
   public:
    ClientLeftVoluntarilyEvent(const TimePoint& t, const std::shared_ptr<Client>& client);
    [[nodiscard]] std::string ToString() const override;
    static std::shared_ptr<ClientLeftVoluntarilyEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // CLIENTLEFTVOLUNTARILYEVENT_H
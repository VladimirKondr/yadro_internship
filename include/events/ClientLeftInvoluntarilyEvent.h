#ifndef CLIENTLEFTINVOLUNTARILYEVENT_H
#define CLIENTLEFTINVOLUNTARILYEVENT_H

#include "OutgoingEvent.h"

#include <memory>
#include <sstream>
#include <string>

namespace computer_club {

class ClientLeftInvoluntarilyEvent : public OutgoingEvent {
   private:
    std::string client_name_;

   public:
    ClientLeftInvoluntarilyEvent(const TimePoint& t, std::string client);
    [[nodiscard]] std::string ToString() const override;
    [[nodiscard]] std::string ClientName() const;
    static std::shared_ptr<ClientLeftInvoluntarilyEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // CLIENTLEFTINVOLUNTARILYEVENT_H
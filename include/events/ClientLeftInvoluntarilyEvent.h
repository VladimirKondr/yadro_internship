#ifndef CLIENTLEFTINVOLUNTARILYEVENT_H
#define CLIENTLEFTINVOLUNTARILYEVENT_H

#include "Client.h"
#include "OutgoingEvent.h"

#include <memory>
#include <sstream>
#include <string>

namespace computer_club {

class ClientLeftInvoluntarilyEvent : public OutgoingEvent {
   private:
    std::shared_ptr<Client> client_;

   public:
    ClientLeftInvoluntarilyEvent(const TimePoint& t, const std::shared_ptr<Client>& client);
    [[nodiscard]] std::shared_ptr<Client> GetClient() const;
    [[nodiscard]] std::string ToString() const override;
    static std::shared_ptr<ClientLeftInvoluntarilyEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // CLIENTLEFTINVOLUNTARILYEVENT_H
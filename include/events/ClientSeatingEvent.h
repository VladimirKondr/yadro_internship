#ifndef CLIENTSEATINGEVENT_H
#define CLIENTSEATINGEVENT_H

#include "Client.h"
#include "OutgoingEvent.h"

#include <memory>
#include <sstream>
#include <string>

namespace computer_club {

class ClientSeatingEvent : public OutgoingEvent {
   private:
    std::shared_ptr<Table> table_;
    std::shared_ptr<Client> client_;

   public:
    ClientSeatingEvent(
        const TimePoint& t, const std::shared_ptr<Client>& client,
        const std::shared_ptr<Table>& table);
    [[nodiscard]] std::shared_ptr<Table> GetTable() const;
    [[nodiscard]] std::shared_ptr<Client> GetClient() const;
    [[nodiscard]] std::string ToString() const override;
    static std::shared_ptr<ClientSeatingEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // CLIENTSEATINGEVENT_H
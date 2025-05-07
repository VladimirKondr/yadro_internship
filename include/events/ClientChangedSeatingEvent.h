#ifndef CLIENTCHANGEDSEATINGEVENT_H
#define CLIENTCHANGEDSEATINGEVENT_H

#include "Client.h"
#include "IncomingEvent.h"

#include <memory>
#include <sstream>
#include <string>

namespace computer_club {

class ClientChangedSeatingEvent : public IncomingEvent {
   private:
    std::shared_ptr<Table> table_;

   public:
    ClientChangedSeatingEvent(
        const TimePoint& t, const std::shared_ptr<Client>& client,
        const std::shared_ptr<Table>& table);
    [[nodiscard]] std::shared_ptr<Table> GetTable() const;
    [[nodiscard]] std::string ToString() const override;
    static std::shared_ptr<ClientChangedSeatingEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // CLIENTCHANGEDSEATINGEVENT_H
#ifndef CLIENTCHANGEDSEATINGEVENT_H
#define CLIENTCHANGEDSEATINGEVENT_H

#include "IncomingEvent.h"

#include <memory>
#include <sstream>
#include <string>

namespace computer_club {

class ClientChangedSeatingEvent : public IncomingEvent {
   private:
    int table_number_;

   public:
    ClientChangedSeatingEvent(const TimePoint& t, std::string client, int table);
    [[nodiscard]] int TableNumber() const;
    [[nodiscard]] std::string ToString() const override;
    static std::unique_ptr<ClientChangedSeatingEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // CLIENTCHANGEDSEATINGEVENT_H
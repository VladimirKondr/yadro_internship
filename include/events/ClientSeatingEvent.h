#ifndef CLIENTSEATINGEVENT_H
#define CLIENTSEATINGEVENT_H

#include "OutgoingEvent.h"

#include <memory>
#include <sstream>
#include <string>

namespace computer_club {

class ClientSeatingEvent : public OutgoingEvent {
   private:
    int table_number_;
    std::string client_name_;

   public:
    ClientSeatingEvent(const TimePoint& t, std::string client_name, int table);
    [[nodiscard]] int TableNumber() const;
    [[nodiscard]] std::string ToString() const override;
    [[nodiscard]] std::string ClientName() const;
    static std::shared_ptr<ClientSeatingEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // CLIENTSEATINGEVENT_H
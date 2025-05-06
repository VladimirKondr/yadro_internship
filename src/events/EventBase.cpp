#include "events/ClientArrivalEvent.h"
#include "events/ClientChangedSeatingEvent.h"
#include "events/ClientLeftInvoluntarilyEvent.h"
#include "events/ClientLeftVoluntarilyEvent.h"
#include "events/ClientSeatingEvent.h"
#include "events/ClientWaitingEvent.h"
#include "events/ErrorEvent.h"
#include "events/TimePoint.h"

#include <sstream>
#include <stdexcept>

namespace computer_club {

Event::Event(const TimePoint& t, int i) : time_(t), id_(i) {
}

const TimePoint& Event::Time() const {
    return time_;
}

int Event::Id() const {
    return id_;
}

std::shared_ptr<Event> Event::Parse(const std::string& event_str) {
    std::istringstream iss(event_str);
    std::string time_str;
    int event_id = -1;
    iss >> time_str >> event_id;

    TimePoint time = TimePoint::Parse(time_str);

    switch (event_id) {
        case 1:
            return ClientArrivalEvent::Parse(iss, time);
        case 2:
            return ClientChangedSeatingEvent::Parse(iss, time);
        case 3:
            return ClientWaitingEvent::Parse(iss, time);
        case 4:
            return ClientLeftVoluntarilyEvent::Parse(iss, time);
        case 11:
            return ClientLeftInvoluntarilyEvent::Parse(iss, time);
        case 12:
            return ClientSeatingEvent::Parse(iss, time);
        case 13:
            return ErrorEvent::Parse(iss, time);
        default:
            throw std::invalid_argument("Unknown event ID: " + std::to_string(event_id));
    }
}

}  // namespace computer_club
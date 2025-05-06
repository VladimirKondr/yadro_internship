#ifndef EVENTBASE_H
#define EVENTBASE_H

#include "TimePoint.h"

#include <memory>
#include <string>

namespace computer_club {

class Event {
   private:
    TimePoint time_;
    int id_;

   public:
    Event(const TimePoint& t, int i);

    Event(const Event&) = default;
    Event(Event&&) noexcept = default;
    Event& operator=(const Event&) = default;
    Event& operator=(Event&&) noexcept = default;

    virtual ~Event() = default;
    [[nodiscard]] virtual std::string ToString() const = 0;

    [[nodiscard]] const TimePoint& Time() const;
    [[nodiscard]] int Id() const;

    static std::shared_ptr<Event> Parse(const std::string& event_str);
};

}  // namespace computer_club

#endif  // EVENTBASE_H
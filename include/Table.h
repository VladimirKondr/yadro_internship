#ifndef TABLE_H
#define TABLE_H

#include "events/TimePoint.h"

#include <string>

namespace computer_club {

class Table {
   private:
    int id_;
    bool occupied_ = false;
    TimePoint occupation_start_;
    int total_busy_hours_ = 0;
    TimePoint total_busy_time_;

   public:
    explicit Table(int id);

    [[nodiscard]] int Id() const;
    [[nodiscard]] bool IsOccupied() const;
    [[nodiscard]] int TotalBusyHours() const;
    [[nodiscard]] TimePoint TotalBusyTime() const;

    void Occupy(const TimePoint& time);
    void Free(const TimePoint& time);

    [[nodiscard]] double Revenue(double hourly_rate) const;

    [[nodiscard]] std::string ToString() const;
};

}  // namespace computer_club

#endif  // TABLE_H
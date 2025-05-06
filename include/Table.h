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
    int total_busy_minutes_ = 0;
    double revenue_ = 0.0;

public:
    explicit Table(int id);

    [[nodiscard]] int Id() const;
    [[nodiscard]] bool IsOccupied() const;
    [[nodiscard]] int TotalBusyMinutes() const;
    [[nodiscard]] double Revenue() const;
    [[nodiscard]] std::string FormatBusyTime() const;

    void Occupy(const TimePoint& time);
    void Free(const TimePoint& time, double hourly_rate);
};

} // namespace computer_club

#endif // TABLE_H
#include "Table.h"
#include <cmath>
#include <iomanip>
#include <sstream>

namespace computer_club {

Table::Table(int id) : id_(id) {}

int Table::Id() const {
    return id_;
}

bool Table::IsOccupied() const {
    return occupied_;
}

int Table::TotalBusyHours() const {
    return total_busy_hours_;
}

void Table::Occupy(const TimePoint& time) {
    if (!occupied_) {
        occupation_start_ = time;
        occupied_ = true;
    }
}

void Table::Free(const TimePoint& time) {
    if (occupied_) {
        int minutes_occupied = time - occupation_start_;
        total_busy_hours_ += std::ceil(minutes_occupied / 60.0);
        total_busy_time_ += minutes_occupied;
        occupied_ = false;
    }
}

double Table::Revenue(double hourly_rate) const {
    return total_busy_hours_ * hourly_rate;
}

TimePoint Table::TotalBusyTime() const {
    return total_busy_time_;
}

std::string Table::ToString() const {
    std::ostringstream oss;
    oss << id_;
    return oss.str();
}

} // namespace computer_club
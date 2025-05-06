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

int Table::TotalBusyMinutes() const {
    return total_busy_minutes_;
}

double Table::Revenue() const {
    return revenue_;
}

std::string Table::FormatBusyTime() const {
    int hours = total_busy_minutes_ / 60;
    int minutes = total_busy_minutes_ % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":" 
        << std::setfill('0') << std::setw(2) << minutes;
    return oss.str();
}

void Table::Occupy(const TimePoint& time) {
    if (!occupied_) {
        occupation_start_ = time;
        occupied_ = true;
    }
}

void Table::Free(const TimePoint& time, double hourly_rate) {
    if (occupied_) {
        int minutes_occupied = time - occupation_start_;
        total_busy_minutes_ += minutes_occupied;
        
        double hours = std::ceil(minutes_occupied / 60.0);
        revenue_ += hours * hourly_rate;
        
        occupied_ = false;
    }
}

} // namespace computer_club
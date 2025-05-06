#include "events/TimePoint.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace computer_club {

TimePoint::TimePoint() : hours_(0), minutes_(0) {
}

TimePoint::TimePoint(int h, int m) {
    if (h < 0 || h > 23 || m < 0 || m > 59) {
        throw std::invalid_argument("Time must be in 24-hour format between 00:00 and 23:59");
    }
    hours_ = h;
    minutes_ = m;
}

TimePoint TimePoint::Parse(const std::string& time_str) {
    int h = std::stoi(time_str.substr(0, 2));
    int m = std::stoi(time_str.substr(3, 2));
    return {h, m};
}

TimePoint TimePoint::Parse(std::istream& is) {
    int h = 0;
    int m = 0;
    is >> h;
    is.ignore(1);
    is >> m;
    return {h, m};
}

int TimePoint::Hours() const {
    return hours_;
}

int TimePoint::Minutes() const {
    return minutes_;
}

std::string TimePoint::ToString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours_ << ":" << std::setfill('0') << std::setw(2)
        << minutes_;
    return oss.str();
}

bool TimePoint::operator<(const TimePoint& other) const {
    return (hours_ * 60 + minutes_) < (other.hours_ * 60 + other.minutes_);
}

bool TimePoint::operator>(const TimePoint& other) const {
    return other < *this;
}

bool TimePoint::operator==(const TimePoint& other) const {
    return hours_ == other.hours_ && minutes_ == other.minutes_;
}

bool TimePoint::operator!=(const TimePoint& other) const {
    return !(*this == other);
}

bool TimePoint::operator<=(const TimePoint& other) const {
    return !(*this > other);
}

bool TimePoint::operator>=(const TimePoint& other) const {
    return !(*this < other);
}

TimePoint& TimePoint::operator+=(int minutes) {
    int total = (hours_ * 60) + minutes_ + minutes;
    if (total < 0 || total > 1439) {
        throw std::invalid_argument("Can't add time to make it less than 00:00 or more than 23:59");
    }
    hours_ = total / 60;
    minutes_ = total % 60;
    return *this;
}

TimePoint TimePoint::operator+(int minutes) const {
    TimePoint result = *this;
    result += minutes;
    return result;
}

TimePoint& TimePoint::operator-=(int minutes) {
    return *this += -minutes;
}

TimePoint TimePoint::operator-(int minutes) const {
    return *this + (-minutes);
}

int TimePoint::operator-(const TimePoint& other) const {
    return (hours_ * 60 + minutes_) - (other.hours_ * 60 + other.minutes_);
}

}  // namespace computer_club
#ifndef TIMEPOINT_H
#define TIMEPOINT_H

#include <istream>
#include <string>

namespace computer_club {

class TimePoint {
   private:
    int hours_;
    int minutes_;

   public:
    TimePoint();

    TimePoint(int h, int m);

    TimePoint(const TimePoint& other) = default;
    TimePoint(TimePoint&& other) noexcept = default;
    TimePoint& operator=(const TimePoint& other) = default;
    TimePoint& operator=(TimePoint&& other) noexcept = default;

    static TimePoint Parse(const std::string& time_str);

    static TimePoint Parse(std::istream& is);

    [[nodiscard]] int Hours() const;

    [[nodiscard]] int Minutes() const;

    [[nodiscard]] std::string ToString() const;

    bool operator<(const TimePoint& other) const;

    bool operator>(const TimePoint& other) const;

    bool operator==(const TimePoint& other) const;

    bool operator!=(const TimePoint& other) const;

    bool operator<=(const TimePoint& other) const;

    bool operator>=(const TimePoint& other) const;

    TimePoint& operator+=(int minutes_to_add);

    TimePoint operator+(int minutes_to_add) const;

    TimePoint& operator-=(int minutes_to_add);

    TimePoint operator-(int minutes_to_add) const;

    [[nodiscard]] int operator-(const TimePoint& other) const;
};

}  // namespace computer_club

#endif  // TIMEPOINT_H
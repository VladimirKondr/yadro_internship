#include "Event.h"

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

Event::Event(const TimePoint& t, int i) : time_(t), id_(i) {
}

const TimePoint& Event::Time() const {
    return time_;
}

int Event::Id() const {
    return id_;
}

IncomingEvent::IncomingEvent(const TimePoint& t, int i, std::string client)
    : Event(t, i), client_name_(std::move(client)) {
}

std::string IncomingEvent::ClientName() const {
    return client_name_;
}

OutgoingEvent::OutgoingEvent(const TimePoint& t, int i, std::string msg)
    : Event(t, i), message_(std::move(msg)) {
}

std::string OutgoingEvent::Message() const {
    return message_;
}

ClientArrivalEvent::ClientArrivalEvent(const TimePoint& t, std::string client)
    : IncomingEvent(t, 1, std::move(client)) {
}

std::string ClientArrivalEvent::ToString() const {
    return Time().ToString() + " 1 (ClientArrival) " + ClientName();
}

ClientChangedSeatingEvent::ClientChangedSeatingEvent(
    const TimePoint& t, std::string client, int table)
    : IncomingEvent(t, 2, std::move(client)), table_number_(table) {
}

int ClientChangedSeatingEvent::TableNumber() const {
    return table_number_;
}

std::string ClientChangedSeatingEvent::ToString() const {
    return Time().ToString() + " 2 (ClientChangedSeating) " + ClientName() + " " +
           std::to_string(TableNumber());
}

ClientWaitingEvent::ClientWaitingEvent(const TimePoint& t, std::string client)
    : IncomingEvent(t, 3, std::move(client)) {
}

std::string ClientWaitingEvent::ToString() const {
    return Time().ToString() + " 3 (ClientWaiting) " + ClientName();
}

ClientLeftVoluntarilyEvent::ClientLeftVoluntarilyEvent(const TimePoint& t, std::string client)
    : IncomingEvent(t, 4, std::move(client)) {
}

std::string ClientLeftVoluntarilyEvent::ToString() const {
    return Time().ToString() + " 4 (ClientLeftVoluntarily) " + ClientName();
}

ClientLeftInvoluntarilyEvent::ClientLeftInvoluntarilyEvent(const TimePoint& t, std::string client)
    : OutgoingEvent(t, 11, std::move(client)) {
}

std::string ClientLeftInvoluntarilyEvent::ClientName() const {
    return client_name_;
}

std::string ClientLeftInvoluntarilyEvent::ToString() const {
    return Time().ToString() + " 11 (ClientLeftInvoluntarily) " + ClientName();
}

ClientSeatingEvent::ClientSeatingEvent(const TimePoint& t, std::string client_name, int table)
    : OutgoingEvent(t, 12, client_name + " " + std::to_string(table))
    , table_number_(table)
    , client_name_(std::move(client_name)) {
}

int ClientSeatingEvent::TableNumber() const {
    return table_number_;
}

std::string ClientSeatingEvent::ClientName() const {
    return client_name_;
}

std::string ClientSeatingEvent::ToString() const {
    return Time().ToString() + " 12 (ClientSeating) " + ClientName() + " " +
           std::to_string(TableNumber());
}

ErrorEvent::ErrorEvent(const TimePoint& t, std::string error)
    : OutgoingEvent(t, 13, std::move(error)) {
}

std::string ErrorEvent::ToString() const {
    return Time().ToString() + " 13 (Error) " + Message();
}

}  // namespace computer_club
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

Event::Event(const TimePoint& t, int i) : time_(t), id_(i) {
}

const TimePoint& Event::Time() const {
    return time_;
}

int Event::Id() const {
    return id_;
}

std::unique_ptr<Event> Event::Parse(const std::string& event_str) {
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

std::unique_ptr<ClientArrivalEvent> ClientArrivalEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    return std::make_unique<ClientArrivalEvent>(time, client_name);
}

std::unique_ptr<ClientChangedSeatingEvent> ClientChangedSeatingEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    int table_number = -1;
    iss >> client_name >> table_number;
    return std::make_unique<ClientChangedSeatingEvent>(time, client_name, table_number);
}

std::unique_ptr<ClientWaitingEvent> ClientWaitingEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    return std::make_unique<ClientWaitingEvent>(time, client_name);
}

std::unique_ptr<ClientLeftVoluntarilyEvent> ClientLeftVoluntarilyEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    return std::make_unique<ClientLeftVoluntarilyEvent>(time, client_name);
}

std::unique_ptr<ClientLeftInvoluntarilyEvent> ClientLeftInvoluntarilyEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    iss >> client_name;
    return std::make_unique<ClientLeftInvoluntarilyEvent>(time, client_name);
}

std::unique_ptr<ClientSeatingEvent> ClientSeatingEvent::Parse(
    std::istringstream& iss, const TimePoint& time) {
    std::string client_name;
    int table_number = -1;
    iss >> client_name >> table_number;
    return std::make_unique<ClientSeatingEvent>(time, client_name, table_number);
}

std::unique_ptr<ErrorEvent> ErrorEvent::Parse(std::istringstream& iss, const TimePoint& time) {
    std::string error_message;
    std::getline(iss, error_message);
    return std::make_unique<ErrorEvent>(time, error_message);
}

}  // namespace computer_club
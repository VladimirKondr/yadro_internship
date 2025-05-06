#ifndef EVENT_H
#define EVENT_H

#include <fstream>
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

class Event {
   private:
    TimePoint time_;
    int id_;

   public:
    Event(const TimePoint& t, int i);

    Event(const Event&) = default;
    Event(Event&&) = default;
    Event& operator=(const Event&) = default;
    Event& operator=(Event&&) = default;

    virtual ~Event() = default;
    [[nodiscard]] virtual std::string ToString() const = 0;

    [[nodiscard]] const TimePoint& Time() const;
    [[nodiscard]] int Id() const;

    static std::unique_ptr<Event> Parse(const std::string& event_str);
};

class IncomingEvent : public Event {
   private:
    std::string client_name_;

   public:
    IncomingEvent(const TimePoint& t, int i, std::string client);
    [[nodiscard]] std::string ClientName() const;
};

class OutgoingEvent : public Event {
   private:
    std::string message_;

   public:
    OutgoingEvent(const TimePoint& t, int i, std::string msg);
    [[nodiscard]] std::string Message() const;
};

class ClientArrivalEvent : public IncomingEvent {
   public:
    ClientArrivalEvent(const TimePoint& t, std::string client);
    [[nodiscard]] std::string ToString() const override;
    static std::unique_ptr<ClientArrivalEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

class ClientChangedSeatingEvent : public IncomingEvent {
   private:
    int table_number_;

   public:
    ClientChangedSeatingEvent(const TimePoint& t, std::string client, int table);
    [[nodiscard]] int TableNumber() const;
    [[nodiscard]] std::string ToString() const override;
    static std::unique_ptr<ClientChangedSeatingEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

class ClientWaitingEvent : public IncomingEvent {
   public:
    ClientWaitingEvent(const TimePoint& t, std::string client);
    [[nodiscard]] std::string ToString() const override;
    static std::unique_ptr<ClientWaitingEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

class ClientLeftVoluntarilyEvent : public IncomingEvent {
   public:
    ClientLeftVoluntarilyEvent(const TimePoint& t, std::string client);
    [[nodiscard]] std::string ToString() const override;
    static std::unique_ptr<ClientLeftVoluntarilyEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

class ClientLeftInvoluntarilyEvent : public OutgoingEvent {
   private:
    std::string client_name_;

   public:
    ClientLeftInvoluntarilyEvent(const TimePoint& t, std::string client);
    [[nodiscard]] std::string ToString() const override;
    [[nodiscard]] std::string ClientName() const;
    static std::unique_ptr<ClientLeftInvoluntarilyEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

class ClientSeatingEvent : public OutgoingEvent {
   private:
    int table_number_;
    std::string client_name_;

   public:
    ClientSeatingEvent(const TimePoint& t, std::string client_name, int table);
    [[nodiscard]] int TableNumber() const;
    [[nodiscard]] std::string ToString() const override;
    [[nodiscard]] std::string ClientName() const;
    static std::unique_ptr<ClientSeatingEvent> Parse(
        std::istringstream& iss, const TimePoint& time);
};

class ErrorEvent : public OutgoingEvent {
   public:
    ErrorEvent(const TimePoint& t, std::string error);
    [[nodiscard]] std::string ToString() const override;
    static std::unique_ptr<ErrorEvent> Parse(std::istringstream& iss, const TimePoint& time);
};

}  // namespace computer_club

#endif  // EVENT_H
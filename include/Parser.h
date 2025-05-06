#ifndef PARSER_H
#define PARSER_H

#include "events/EventBase.h"
#include "events/TimePoint.h"

namespace computer_club {

class FormatError : public std::exception {};

class Parser {
   private:
    Parser() = default;
    static std::unique_ptr<Parser> instance;
    int table_count_{};
    TimePoint open_time_;
    TimePoint close_time_;
    double hourly_rate_{};
    std::vector<std::shared_ptr<Event>> events_;

    static void ValidateTableCount(const std::string& line);
    static void ValidateTimeRange(const std::string& line);
    static void ValidateHourlyRate(const std::string& line);
    void ValidateEventFormat(const std::string& line) const;
    static void ValidateClientNameFormat(std::istringstream& iss);
    void ValidateClientAndTableFormat(std::istringstream& iss) const ;
    void ValidateEventSequence() const;

   public:
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) noexcept = default;
    Parser& operator=(Parser&&) noexcept = default;
    ~Parser() = default;

    static Parser& GetInstance();

    void ParseFile(const std::string& filename);

    [[nodiscard]] int TableCount() const;

    [[nodiscard]] TimePoint OpenTime() const;

    [[nodiscard]] TimePoint CloseTime() const;

    [[nodiscard]] double HourlyRate() const;

    [[nodiscard]] const std::vector<std::shared_ptr<Event>>& Events() const;

    [[nodiscard]] std::string ToString() const;
};

}  // namespace computer_club

#endif  // PARSER_H
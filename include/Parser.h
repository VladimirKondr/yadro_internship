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
    static int table_count;
    static TimePoint open_time;
    static TimePoint close_time;
    static double hourly_rate;
    static std::vector<std::shared_ptr<Event>> events;

    static void ValidateTableCount(const std::string& line);
    static void ValidateTimeRange(const std::string& line);
    static void ValidateHourlyRate(const std::string& line);
    static void ValidateEventFormat(const std::string& line);
    static void ValidateClientNameFormat(std::istringstream& iss);
    static void ValidateClientAndTableFormat(std::istringstream& iss);
    static void ValidateEventSequence();

   public:
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) noexcept = default;
    Parser& operator=(Parser&&) noexcept = default;
    ~Parser() = default;

    static Parser& GetInstance();

    static void ParseFile(const std::string& filename);

    [[nodiscard]] static int TableCount();

    [[nodiscard]] static TimePoint OpenTime();

    [[nodiscard]] static TimePoint CloseTime();

    [[nodiscard]] static double HourlyRate();

    [[nodiscard]] const static std::vector<std::shared_ptr<Event>>& Events();

    [[nodiscard]] static std::string ToString();

    static void Reset();
};

}  // namespace computer_club

#endif  // PARSER_H
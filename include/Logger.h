#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace computer_club {

enum class LogDestination : std::uint8_t { STDOUT, FILE, CUSTOM_STREAM, BOTH_STDOUT_AND_FILE };

class Logger {
   private:
    static std::unique_ptr<Logger> instance;
    static std::ostream* output_stream;
    static std::ofstream file_stream;
    static LogDestination destination;

    Logger();

   public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    ~Logger();

    Logger(Logger&&) noexcept = default;
    Logger& operator=(Logger&&) noexcept = default;

    static Logger& GetInstance();

    static void Log(const std::string& message);

    static void SetOutputToStdout();
    static void SetOutputToFile(const std::string& filename);
    static void SetOutputToCustomStream(std::ostream* stream);
    static void SetOutputToBoth(const std::string& filename);

    static void SetOutputStream(std::ostream* stream);
    static void SetOutputFile(const std::string& filename);
    static void EnableStdout(bool enable);

    static void Info(const std::string& message);
    static void Error(const std::string& message);
    static void Debug(const std::string& message);

    static void Reset();
};

}  // namespace computer_club

#endif  // LOGGER_H
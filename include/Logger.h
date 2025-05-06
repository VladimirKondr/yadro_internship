#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <memory>
#include <fstream>
#include <iostream>

namespace computer_club {

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    std::ostream* output_stream_{&std::cout};
    std::ofstream file_stream_;
    bool enable_stdout_{true};
    
    Logger() = default;
    
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    ~Logger();
    
    Logger(Logger&&) noexcept = default;
    Logger& operator=(Logger&&) noexcept = default;

    static Logger& GetInstance();
    
    void Log(const std::string& message);
    void SetOutputStream(std::ostream* stream);
    void SetOutputFile(const std::string& filename);
    void EnableStdout(bool enable);
    
    static void Info(const std::string& message);
    static void Error(const std::string& message);
    static void Debug(const std::string& message);
};

} // namespace computer_club

#endif // LOGGER_H
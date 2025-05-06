#include "Logger.h"

namespace computer_club {

std::unique_ptr<Logger> Logger::instance = nullptr;

Logger::~Logger() {
    if (file_stream_.is_open()) {
        file_stream_.close();
    }
}

Logger& Logger::GetInstance() {
    if (!instance) {
        instance = std::unique_ptr<Logger>(new Logger());
    }
    return *instance;
}

void Logger::Log(const std::string& message) {
    if (enable_stdout_ && (output_stream_ != nullptr)) {
        *output_stream_ << message << '\n';
    }
    
    if (file_stream_.is_open()) {
        file_stream_ << message << '\n';
    }
}

void Logger::SetOutputStream(std::ostream* stream) {
    output_stream_ = stream;
}

void Logger::SetOutputFile(const std::string& filename) {
    if (file_stream_.is_open()) {
        file_stream_.close();
    }
    
    file_stream_.open(filename);
    if (!file_stream_.is_open()) {
        if (output_stream_ != nullptr) {
            *output_stream_ << "Failed to open log file: " << filename << '\n';
        }
    }
}

void Logger::EnableStdout(bool enable) {
    enable_stdout_ = enable;
}

void Logger::Info(const std::string& message) {
    GetInstance().Log(message);
}

void Logger::Error(const std::string& message) {
    GetInstance().Log("ERROR: " + message);
}

void Logger::Debug(const std::string& message) {
#ifdef DEBUG
    GetInstance().Log("DEBUG: " + message);
#endif
}

} // namespace computer_club
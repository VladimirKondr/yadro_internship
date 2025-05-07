#include "Logger.h"

namespace computer_club {

std::ofstream Logger::file_stream;
std::ostream* Logger::output_stream = &std::cout;
LogDestination Logger::destination =
    LogDestination::STDOUT;
std::unique_ptr<Logger> Logger::instance = nullptr;

Logger::Logger() {
    output_stream = &std::cout;
    destination = LogDestination::STDOUT;
}

Logger::~Logger() {
    if (file_stream.is_open()) {
        file_stream.close();
    }
}

Logger& Logger::GetInstance() {
    if (!instance) {
        instance = std::unique_ptr<Logger>(new Logger());
    }
    return *instance;
}

void Logger::Log(const std::string& message) {
    switch (destination) {
        case LogDestination::STDOUT:
            std::cout << message << '\n';
            break;

        case LogDestination::FILE:
            if (file_stream.is_open()) {
                file_stream << message << '\n';
                file_stream.flush();
            }
            break;

        case LogDestination::CUSTOM_STREAM:
            if (output_stream != nullptr) {
                *output_stream << message << '\n';
                output_stream->flush();
            }
            break;

        case LogDestination::BOTH_STDOUT_AND_FILE:
            std::cout << message << '\n';
            if (file_stream.is_open()) {
                file_stream << message << '\n';
                file_stream.flush();
            }
            break;
    }
}

void Logger::SetOutputToStdout() {
    destination = LogDestination::STDOUT;
    if (file_stream.is_open()) {
        file_stream.close();
    }
}

void Logger::SetOutputToFile(const std::string& filename) {
    if (file_stream.is_open()) {
        file_stream.close();
    }

    file_stream.open(filename);
    if (!file_stream.is_open()) {
        std::cerr << "Failed to open log file: " << filename << '\n';
        destination = LogDestination::STDOUT;
    } else {
        destination = LogDestination::FILE;
    }
}

void Logger::SetOutputToCustomStream(std::ostream* stream) {
    if (stream != nullptr) {
        output_stream = stream;
        destination = LogDestination::CUSTOM_STREAM;

        if (file_stream.is_open()) {
            file_stream.close();
        }
    } else {
        destination = LogDestination::STDOUT;
    }
}

void Logger::SetOutputToBoth(const std::string& filename) {
    if (file_stream.is_open()) {
        file_stream.close();
    }

    file_stream.open(filename);
    if (!file_stream.is_open()) {
        std::cerr << "Failed to open log file: " << filename << '\n';
        destination = LogDestination::STDOUT;
    } else {
        destination = LogDestination::BOTH_STDOUT_AND_FILE;
    }
}

void Logger::SetOutputStream(std::ostream* stream) {
    SetOutputToCustomStream(stream);
}

void Logger::SetOutputFile(const std::string& filename) {
    SetOutputToFile(filename);
}

void Logger::EnableStdout(bool enable) {
    if (enable) {
        if (destination == LogDestination::FILE) {
            destination = LogDestination::BOTH_STDOUT_AND_FILE;
        } else {
            destination = LogDestination::STDOUT;
        }
    } else {
        if (destination == LogDestination::BOTH_STDOUT_AND_FILE) {
            destination = LogDestination::FILE;
        } else if (destination == LogDestination::STDOUT) {
            destination = LogDestination::CUSTOM_STREAM;
            output_stream = nullptr;
        }
    }
}

void Logger::Info(const std::string& message) {
    Log(message);
}

void Logger::Error(const std::string& message) {
    Log("ERROR: " + message);
}

void Logger::Debug(const std::string& message) {
#ifdef DEBUG
    Log("DEBUG: " + message);
#endif
}

}  // namespace computer_club
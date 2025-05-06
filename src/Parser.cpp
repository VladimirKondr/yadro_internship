#include "Parser.h"

#include <fstream>
#include <sstream>

namespace computer_club {

std::unique_ptr<Parser> Parser::instance = nullptr;

Parser& Parser::GetInstance() {
    if (!instance) {
        instance = std::unique_ptr<Parser>(new Parser());
    }
    return *instance;
}

void Parser::ParseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    file >> table_count_;
    open_time_ = TimePoint::Parse(file);
    close_time_ = TimePoint::Parse(file);
    file >> hourly_rate_;
    std::string line;
    while (std::getline(file, line)) {
        events_.push_back(Event::Parse(line));
    }
}

int Parser::TableCount() const {
    return table_count_;
}

[[nodiscard]] TimePoint Parser::OpenTime() const {
    return open_time_;
}

[[nodiscard]] TimePoint Parser::CloseTime() const {
    return close_time_;
}

[[nodiscard]] double Parser::HourlyRate() const {
    return hourly_rate_;
}

[[nodiscard]] const std::vector<std::unique_ptr<Event>>& Parser::Events() const {
    return events_;
}

std::string Parser::ToString() const {
    std::ostringstream oss;
    oss << "Table Count: " << table_count_ << "\n";
    oss << "Open Time: " << open_time_.ToString() << "\n";
    oss << "Close Time: " << close_time_.ToString() << "\n";
    oss << "Hourly Rate: " << hourly_rate_ << "\n";
    oss << "Events:\n";
    for (const auto& event : events_) {
        oss << (*event).ToString() << "\n";
    }
    return oss.str();
}

}  // namespace computer_club
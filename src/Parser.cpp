#include "Parser.h"
#include "TablePool.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

namespace computer_club {

int Parser::table_count = 0;
double Parser::hourly_rate = 0.0;
TimePoint Parser::open_time;
TimePoint Parser::close_time;
std::vector<std::shared_ptr<Event>> Parser::events;
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

    std::string line;
    if (!std::getline(file, line)) {
        throw std::runtime_error("Empty input file");
    }

    try {
        ValidateTableCount(line);
    } catch (const FormatError&) {
        std::cout << line << '\n';
        throw;
    }
    table_count = std::stoi(line);

    if (!std::getline(file, line)) {
        throw std::runtime_error("Missing opening and closing times");
    }

    try {
        ValidateTimeRange(line);
    } catch (const FormatError&) {
        std::cout << line << '\n';
        throw;
    }

    std::istringstream time_stream(line);
    std::string open_time_str;
    std::string close_time_str;
    time_stream >> open_time_str >> close_time_str;

    try {
        open_time = TimePoint::Parse(open_time_str);
        close_time = TimePoint::Parse(close_time_str);
    } catch (const std::exception&) {
        std::cout << line << '\n';
        throw FormatError();
    }

    if (!std::getline(file, line)) {
        throw std::runtime_error("Missing hourly rate");
    }

    try {
        ValidateHourlyRate(line);
    } catch (const FormatError&) {
        std::cout << line << '\n';
        throw;
    }
    hourly_rate = std::stod(line);

    TablePool::Initialize(Parser::TableCount(), 
                                             Parser::HourlyRate());
                    

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        try {
            ValidateEventFormat(line);
            events.push_back(Event::Parse(line));
        } catch (const std::exception&) {
            std::cout << line << '\n';
            throw FormatError();
        }
    }

    try {
        ValidateEventSequence();
    } catch (const std::exception&) {
        throw FormatError();
    }
}

void Parser::ValidateTableCount(const std::string& line) {
    std::regex pattern(R"(^\s*[1-9]\d*\s*$)");
    if (!std::regex_match(line, pattern)) {
        throw FormatError();
    }
}

void Parser::ValidateTimeRange(const std::string& line) {
    std::regex pattern(
        R"(^\s*([0-1][0-9]|2[0-3]):[0-5][0-9]\s+([0-1][0-9]|2[0-3]):[0-5][0-9]\s*$)");
    if (!std::regex_match(line, pattern)) {
        throw FormatError();
    }
}

void Parser::ValidateHourlyRate(const std::string& line) {
    std::regex pattern(R"(^\s*[1-9]\d*\s*$)");
    if (!std::regex_match(line, pattern)) {
        throw FormatError();
    }
}

void Parser::ValidateEventFormat(const std::string& line) {
    std::regex time_pattern("([0-1][0-9]|2[0-3]):[0-5][0-9]");

    if (!std::regex_search(line, time_pattern)) {
        throw FormatError();
    }

    std::istringstream iss(line);
    std::string time_str;
    int event_id = -1;
    iss >> time_str >> event_id;

    if (event_id < 1 || event_id > 13) {
        throw FormatError();
    }

    switch (event_id) {
        case 1:
            ValidateClientNameFormat(iss);
            break;
        case 2:
            ValidateClientAndTableFormat(iss);
            break;
        case 3:
            ValidateClientNameFormat(iss);
            break;
        case 4:
            ValidateClientNameFormat(iss);
            break;
        default:
            if (event_id == 11 || event_id == 12 || event_id == 13) {
                throw FormatError();
            }
    }
}

void Parser::ValidateClientNameFormat(std::istringstream& iss) {
    std::string client_name;
    iss >> client_name;

    if (client_name.empty()) {
        throw std::runtime_error("Missing client name");
    }

    std::regex name_pattern("^[a-z0-9_-]+$");
    if (!std::regex_match(client_name, name_pattern)) {
        throw std::runtime_error("Invalid client name format. Only a-z, 0-9, _, - are allowed");
    }
}

void Parser::ValidateClientAndTableFormat(std::istringstream& iss) {
    std::string client_name;
    int table_id = -1;

    iss >> client_name >> table_id;

    if (client_name.empty()) {
        throw std::runtime_error("Missing client name");
    }

    std::regex name_pattern("^[a-z0-9_-]+$");
    if (!std::regex_match(client_name, name_pattern)) {
        throw std::runtime_error("Invalid client name format. Only a-z, 0-9, _, - are allowed");
    }

    if (table_id <= 0 || table_id > table_count) {
        throw std::runtime_error(
            "Invalid table ID: " + std::to_string(table_id) + ". Must be between 1 and " +
            std::to_string(table_count));
    }
}

void Parser::ValidateEventSequence() {
    if (events.empty()) {
        return;
    }

    TimePoint last_time = events[0]->Time();

    for (size_t i = 1; i < events.size(); ++i) {
        TimePoint current_time = events[i]->Time();

        if (current_time < last_time) {
            throw std::runtime_error(
                "Events are not in chronological order at event " + std::to_string(i + 1) + ": " +
                events[i]->ToString());
        }

        last_time = current_time;
    }
}

int Parser::TableCount() {
    return table_count;
}

TimePoint Parser::OpenTime() {
    return open_time;
}

TimePoint Parser::CloseTime() {
    return close_time;
}

double Parser::HourlyRate() {
    return hourly_rate;
}

const std::vector<std::shared_ptr<Event>>& Parser::Events() {
    return events;
}

std::string Parser::ToString() {
    std::ostringstream oss;
    oss << "Table Count: " << table_count << "\n";
    oss << "Open Time: " << open_time.ToString() << "\n";
    oss << "Close Time: " << close_time.ToString() << "\n";
    oss << "Hourly Rate: " << hourly_rate << "\n";
    oss << "Events:\n";
    for (const auto& event : events) {
        oss << (*event).ToString() << "\n";
    }
    return oss.str();
}

}  // namespace computer_club
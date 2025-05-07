#include "ClientPool.h"
#include "Parser.h"
#include "Club.h"
#include "Logger.h"
#include "TablePool.h"
#include "events/EventBase.h"
#include <iostream>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << '\n';
        return 1;
    }
    
    try {
        computer_club::Logger::SetOutputToBoth("logs.txt");
        computer_club::Parser::ParseFile(argv[1]);

        computer_club::Club& club = computer_club::Club::GetInstance(
            computer_club::Parser::OpenTime(),
            computer_club::Parser::CloseTime(),
            computer_club::Parser::HourlyRate()
        );
        
        for (const auto& event : computer_club::Parser::Events()) {
            club.ProcessEvent(event);
        }
        
        club.ClosingTime();
        
        computer_club::Logger::Info(club.GetOpenTime().ToString());
        
        for (const auto& event : club.GetAllEvents()) {
            computer_club::Logger::Info(event->ToString());
        }
        
        computer_club::Logger::Info(club.GetCloseTime().ToString());
        
        for (const auto& table : computer_club::TablePool::Tables()) {
            if (table->Id() == 0) {
                continue;
            }
            computer_club::Logger::Info(std::to_string(table->Id()) + " " 
                      + std::to_string(static_cast<int>(table->Revenue(club.GetHourlyRate()))) + " " 
                      + table->TotalBusyTime().ToString());
        }
        
    } catch (const computer_club::FormatError&) {
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
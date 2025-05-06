#include "Parser.h"
#include "Club.h"
#include "Logger.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << '\n';
        return 1;
    }
    
    try {

        computer_club::Logger& logger = computer_club::Logger::GetInstance();
        logger.SetOutputFile("log.txt");
        
        computer_club::Parser& parser = computer_club::Parser::GetInstance();
        parser.ParseFile(argv[1]);
        
        computer_club::Club club(
            parser.TableCount(),
            parser.OpenTime(),
            parser.CloseTime(),
            parser.HourlyRate()
        );
        
        for (const auto& event : parser.Events()) {
            club.ProcessEvent(event);
        }
        
        club.ClosingTime();
        
        
        std::cout << parser.OpenTime().ToString() << '\n';
        
        for (const auto& event : club.GetAllEvents()) {
            std::cout << event->ToString() << '\n';
        }
        
        std::cout << parser.CloseTime().ToString() << '\n';
        
        for (const auto& table : club.GetTables()) {
            std::cout << std::to_string(table.Id()) << " " 
                      << static_cast<int>(table.Revenue()) << " " 
                      << table.FormatBusyTime() << '\n';
        }
        
    } catch (const computer_club::FormatError&) {
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
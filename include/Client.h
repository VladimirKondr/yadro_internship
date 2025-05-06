#ifndef CLIENT_H
#define CLIENT_H

#include <string>

namespace computer_club {

class Client {
private:
    std::string name_;
    int table_number_;

public:
    Client() : name_(""), table_number_(-1) {}
    
    explicit Client(std::string n) : name_(std::move(n)), table_number_(-1) {}
    
    [[nodiscard]] const std::string& Name();
    [[nodiscard]] int TableNumber() const;
    void SetTableNumber(int table_number);
};

} // namespace computer_club

#endif // CLIENT_H
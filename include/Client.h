#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <utility>

namespace computer_club {

class Client {
   private:
    std::string name_;
    std::optional<int> table_number_;

   public:
    explicit Client(std::string n) : name_(std::move(n)), table_number_(0) {
    }

    [[nodiscard]] bool InClub() const;

    [[nodiscard]] int TableNumber() const;

    [[nodiscard]] std::string Name() const;
};

}  // namespace computer_club

#endif  // CLIENT_H
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <utility>

class Client {
   private:
    std::string name_;
    std::optional<int> table_number_;

   public:
    explicit Client(std::string n) : name_(std::move(n)), table_number_(0) {}

    [[nodiscard]] bool InClub() const;

    [[nodiscard]] int TableNumber() const;

    [[nodiscard]] std::string Name() const;
};

#endif  // CLIENT_H
#ifndef CLIENT_H
#define CLIENT_H

#include "Table.h"

#include <memory>
#include <string>

namespace computer_club {

class Client {
   private:
    std::string name_;
    std::shared_ptr<Table> table_;
    bool in_club_ = false;

   public:
    Client() = default;
    explicit Client(std::string name, const std::shared_ptr<Table>& t);

    [[nodiscard]] const std::string& Name() const;
    [[nodiscard]] std::shared_ptr<Table> GetTable() const;
    [[nodiscard]] bool IsInClub() const;
    void SetInClub(bool in_club);
    void ChangeTable(const std::shared_ptr<Table>& new_table);

    bool operator==(const Client& other) const;
    bool operator!=(const Client& other) const;

    [[nodiscard]] std::string ToString() const;
};

}  // namespace computer_club

#endif  // CLIENT_H
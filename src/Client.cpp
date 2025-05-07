#include "Client.h"

namespace computer_club {

Client::Client(std::string name, const std::shared_ptr<Table>& t)
    : name_(std::move(name)), table_(t) {
}

const std::string& Client::Name() const {
    return name_;
}

std::shared_ptr<Table> Client::GetTable() const {
    return table_;
}

bool Client::IsInClub() const {
    return in_club_;
}

void Client::SetInClub(bool in_club) {
    in_club_ = in_club;
}

void Client::ChangeTable(const std::shared_ptr<Table>& new_table) {
    table_ = new_table;
}

bool Client::operator==(const Client& other) const {
    return name_ == other.name_;
}

bool Client::operator!=(const Client& other) const {
    return !(*this == other);
}

std::string Client::ToString() const {
    return "Client: " + name_ + ", Table: " + (table_ ? table_->ToString() : "None");
}
}  // namespace computer_club
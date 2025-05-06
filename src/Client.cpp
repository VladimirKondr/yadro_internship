#include "Client.h"

namespace computer_club {

const std::string& Client::Name() {
    return name_;
}

int Client::TableNumber() const {
    return table_number_;
}

void Client::SetTableNumber(int table_number) {
    table_number_ = table_number;
}
}  // namespace computer_club
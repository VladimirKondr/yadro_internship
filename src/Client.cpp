#include "Client.h"

bool Client::InClub() const {
    return table_number_.has_value();
}

int Client::TableNumber() const {
    if (InClub()) {
        return table_number_.value();
    }
    throw std::logic_error("Client is not in the club");
}

std::string Client::Name() const {
    return name_;
}

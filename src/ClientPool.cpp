#include "ClientPool.h"

namespace computer_club {

std::unique_ptr<ClientPool> ClientPool::instance = nullptr;
std::unordered_map<std::string, std::shared_ptr<Client>> ClientPool::clients;

ClientPool& ClientPool::GetInstance() {
    if (!instance) {
        instance = std::unique_ptr<ClientPool>(new ClientPool());
    }
    return *instance;
}

std::unordered_map<std::string, std::shared_ptr<Client>> ClientPool::Clients() {
    return clients;
}

std::shared_ptr<Client> ClientPool::GetClient(const std::string& client_name) {
    if (!clients.contains(client_name)) {
        return nullptr;
    }
    return clients[client_name];
}

void ClientPool::AddClient(const std::string& name) {
    clients[name] = std::make_shared<Client>(name, nullptr);
}

bool ClientPool::Contains(const std::string& name) {
    return clients.find(name) != clients.end();
}

std::string ClientPool::ToString() {
    std::string result;
    for (const auto& [name, client] : clients) {
        result += client->ToString() + "\n";
    }
    return result;
}

void ClientPool::Reset() {
    instance.reset();
    clients.clear();
}

}  // namespace computer_club

#ifndef CLIENTPOOL_H
#define CLIENTPOOL_H

#include "Client.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace computer_club {

class ClientPool {
   private:
    static std::unordered_map<std::string, std::shared_ptr<Client>> clients;
    static std::unique_ptr<ClientPool> instance;

    ClientPool() = default;

   public:
    ClientPool(const ClientPool&) = delete;
    ClientPool& operator=(const ClientPool&) = delete;
    ClientPool(ClientPool&&) = default;
    ClientPool& operator=(ClientPool&&) = default;
    ~ClientPool() = default;

    static ClientPool& GetInstance();

    [[nodiscard]] static std::unordered_map<std::string, std::shared_ptr<Client>> Clients();

    static std::shared_ptr<Client> GetClient(const std::string& client_name);

    static void AddClient(const std::string& name);

    static bool Contains(const std::string& name);

    [[nodiscard]] static std::string ToString();
};

}  // namespace computer_club

#endif  // CLIENTPOOL_H
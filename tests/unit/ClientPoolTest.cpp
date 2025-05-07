#include "ClientPool.h"

#include <gtest/gtest.h>

namespace computer_club {

class ClientPoolTest : public ::testing::Test {
   protected:
    void SetUp() override {
        ClientPool::Reset();
    }

    void TearDown() override {
        ClientPool::Reset();
    }
};

TEST_F(ClientPoolTest, AddAndGetClient) {
    ClientPool::AddClient("test_client");

    auto client = ClientPool::GetClient("test_client");
    EXPECT_EQ("test_client", client->Name());
    EXPECT_FALSE(client->IsInClub());
    EXPECT_EQ(nullptr, client->GetTable());
}

TEST_F(ClientPoolTest, GetNonexistentClient) {
    EXPECT_EQ(ClientPool::GetClient("non_existing_client"), nullptr);
}

TEST_F(ClientPoolTest, AddClientTwice) {
    ClientPool::AddClient("test_client");
    ClientPool::AddClient("test_client");

    auto client = ClientPool::GetClient("test_client");
    EXPECT_EQ("test_client", client->Name());
}

TEST_F(ClientPoolTest, AllClients) {
    ClientPool::AddClient("client1");
    ClientPool::AddClient("client2");

    auto clients = ClientPool::Clients();
    EXPECT_EQ(2, clients.size());
    EXPECT_NE(clients.end(), clients.find("client1"));
    EXPECT_NE(clients.end(), clients.find("client2"));
}

}  // namespace computer_club
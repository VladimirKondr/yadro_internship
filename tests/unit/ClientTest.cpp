#include "Client.h"
#include "Table.h"

#include <gtest/gtest.h>
#include <memory>

namespace computer_club {

class ClientTest : public ::testing::Test {
   protected:
    void SetUp() override {
        table = std::make_shared<Table>(1);
        client = std::make_unique<Client>("test_client", table);
    }

    std::shared_ptr<Table> table;
    std::unique_ptr<Client> client;
};

TEST_F(ClientTest, InitialState) {
    EXPECT_EQ("test_client", client->Name());
    EXPECT_EQ(table, client->GetTable());
    EXPECT_FALSE(client->IsInClub());
}

TEST_F(ClientTest, SetInClub) {
    client->SetInClub(true);
    EXPECT_TRUE(client->IsInClub());

    client->SetInClub(false);
    EXPECT_FALSE(client->IsInClub());
}

TEST_F(ClientTest, ChangeTable) {
    auto new_table = std::make_shared<Table>(2);
    client->ChangeTable(new_table);
    EXPECT_EQ(new_table, client->GetTable());
}

TEST_F(ClientTest, ChangeTableToNull) {
    client->ChangeTable(nullptr);
    EXPECT_EQ(nullptr, client->GetTable());
}

TEST_F(ClientTest, ClientEquality) {
    Client client1("test_client", table);
    Client client2("test_client", std::make_shared<Table>(2));
    Client client3("other_client", table);

    EXPECT_TRUE(client1 == client2);
    EXPECT_FALSE(client1 == client3);
}

TEST_F(ClientTest, ClientInequality) {
    Client client1("test_client", table);
    Client client2("test_client", std::make_shared<Table>(2));
    Client client3("other_client", table);

    EXPECT_FALSE(client1 != client2);
    EXPECT_TRUE(client1 != client3);
}

TEST_F(ClientTest, ToStringWithTable) {
    std::string expected = "Client: test_client, Table: 1";
    EXPECT_EQ(expected, client->ToString());
}

TEST_F(ClientTest, ToStringWithoutTable) {
    client->ChangeTable(nullptr);
    std::string expected = "Client: test_client, Table: None";
    EXPECT_EQ(expected, client->ToString());
}

TEST_F(ClientTest, ConstructWithNullTable) {
    Client nullTableClient("null_table_client", nullptr);
    EXPECT_EQ("null_table_client", nullTableClient.Name());
    EXPECT_EQ(nullptr, nullTableClient.GetTable());
    EXPECT_FALSE(nullTableClient.IsInClub());
}

}  // namespace computer_club
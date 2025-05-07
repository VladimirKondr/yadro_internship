#include "Client.h"
#include "ClientPool.h"
#include "TablePool.h"
#include "events/ClientArrivalEvent.h"
#include "events/ClientChangedSeatingEvent.h"
#include "events/ClientLeftInvoluntarilyEvent.h"
#include "events/ClientLeftVoluntarilyEvent.h"
#include "events/ClientSeatingEvent.h"
#include "events/ClientWaitingEvent.h"
#include "events/ErrorEvent.h"

#include <gtest/gtest.h>
#include <sstream>

namespace computer_club {

class ConcreteEventsTest : public ::testing::Test {
   protected:
    void SetUp() override {
        ClientPool::Reset();
        TablePool::Reset();
        TablePool::Initialize(3, 10.0);
    }

    void TearDown() override {
        ClientPool::Reset();
        TablePool::Reset();
    }
};

TEST_F(ConcreteEventsTest, ClientArrivalEvent) {
    TimePoint time(10, 0);
    ClientPool::AddClient("test_client");
    auto client = ClientPool::GetClient("test_client");

    ClientArrivalEvent event(time, client);
    EXPECT_EQ("10:00 1 test_client", event.ToString());
    EXPECT_EQ(client, event.GetClient());
    EXPECT_EQ(1, event.Id());
    EXPECT_EQ(time, event.Time());
}

TEST_F(ConcreteEventsTest, ClientChangedSeatingEvent) {
    TimePoint time(10, 15);
    ClientPool::AddClient("test_client");
    auto client = ClientPool::GetClient("test_client");
    auto table = TablePool::GetTable(2);

    ClientChangedSeatingEvent event(time, client, table);
    EXPECT_EQ("10:15 2 test_client 2", event.ToString());
    EXPECT_EQ(client, event.GetClient());
    EXPECT_EQ(table, event.GetTable());
    EXPECT_EQ(2, event.Id());
    EXPECT_EQ(time, event.Time());
}

TEST_F(ConcreteEventsTest, ClientWaitingEvent) {
    TimePoint time(11, 30);
    ClientPool::AddClient("test_client");
    auto client = ClientPool::GetClient("test_client");

    ClientWaitingEvent event(time, client);
    EXPECT_EQ("11:30 3 test_client", event.ToString());
    EXPECT_EQ(client, event.GetClient());
    EXPECT_EQ(3, event.Id());
    EXPECT_EQ(time, event.Time());
}

TEST_F(ConcreteEventsTest, ClientLeftVoluntarilyEvent) {
    TimePoint time(12, 45);
    ClientPool::AddClient("test_client");
    auto client = ClientPool::GetClient("test_client");

    ClientLeftVoluntarilyEvent event(time, client);
    EXPECT_EQ("12:45 4 test_client", event.ToString());
    EXPECT_EQ(client, event.GetClient());
    EXPECT_EQ(4, event.Id());
    EXPECT_EQ(time, event.Time());
}

TEST_F(ConcreteEventsTest, ErrorEvent) {
    TimePoint time(13, 0);
    std::string error_message = "TestError";

    ClientPool::AddClient("test_client");
    auto client = ClientPool::GetClient("test_client");
    auto original_event = std::make_shared<ClientArrivalEvent>(time, client);

    ErrorEvent event(time, error_message, original_event);
    EXPECT_EQ("13:00 13 TestError", event.ToString());
    EXPECT_EQ(13, event.Id());
    EXPECT_EQ(time, event.Time());
    EXPECT_EQ("TestError", event.Message());
    EXPECT_EQ(original_event, event.CauseEvent());
}

TEST_F(ConcreteEventsTest, ClientLeftInvoluntarilyEvent) {
    TimePoint time(14, 15);
    ClientPool::AddClient("test_client");
    auto client = ClientPool::GetClient("test_client");

    ClientLeftInvoluntarilyEvent event(time, client);
    EXPECT_EQ("14:15 11 test_client", event.ToString());
    EXPECT_EQ(client, event.GetClient());
    EXPECT_EQ(11, event.Id());
    EXPECT_EQ(time, event.Time());
}

TEST_F(ConcreteEventsTest, ClientSeatingEvent) {
    TimePoint time(15, 30);
    ClientPool::AddClient("test_client");
    auto client = ClientPool::GetClient("test_client");
    auto table = TablePool::GetTable(3);

    ClientSeatingEvent event(time, client, table);
    EXPECT_EQ("15:30 12 test_client 3", event.ToString());
    EXPECT_EQ(client, event.GetClient());
    EXPECT_EQ(table, event.GetTable());
    EXPECT_EQ(12, event.Id());
    EXPECT_EQ(time, event.Time());
}

}  // namespace computer_club
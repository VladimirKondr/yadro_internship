#include "ClientPool.h"
#include "Parser.h"
#include "TablePool.h"
#include "events/ClientArrivalEvent.h"
#include "events/ClientChangedSeatingEvent.h"
#include "events/ClientLeftVoluntarilyEvent.h"
#include "events/ClientWaitingEvent.h"

#include <fstream>
#include <gtest/gtest.h>

namespace computer_club {

class ParserTest : public ::testing::Test {
   protected:
    void SetUp() override {
        Parser::Reset();
        TablePool::Reset();
        ClientPool::Reset();
    }

    void TearDown() override {
        Parser::Reset();
        TablePool::Reset();
        ClientPool::Reset();
    }

    std::string CreateTempFile(const std::string& content) {
        std::string filename = "parser_test_temp.txt";
        std::ofstream file(filename);
        file << content;
        file.close();
        return filename;
    }
};

TEST_F(ParserTest, ParseValidFile) {
    std::string content =
        "3\n"
        "09:00 19:00\n"
        "100\n"
        "09:41 1 client1\n"
        "09:48 1 client2\n"
        "09:52 3 client1\n"
        "09:54 2 client1 1\n"
        "10:25 2 client2 2\n";
    std::string filename = CreateTempFile(content);

    Parser::ParseFile(filename);

    EXPECT_EQ(5, Parser::Events().size());
    EXPECT_EQ(3, Parser::TableCount());
    EXPECT_EQ(100.0, Parser::HourlyRate());
    EXPECT_EQ("09:00", Parser::OpenTime().ToString());
    EXPECT_EQ("19:00", Parser::CloseTime().ToString());

    auto event0 = std::dynamic_pointer_cast<ClientArrivalEvent>(Parser::Events()[0]);
    ASSERT_NE(nullptr, event0);
    EXPECT_EQ("09:41", event0->Time().ToString());
    EXPECT_EQ("client1", event0->GetClient()->Name());

    auto event1 = std::dynamic_pointer_cast<ClientArrivalEvent>(Parser::Events()[1]);
    ASSERT_NE(nullptr, event1);
    EXPECT_EQ("09:48", event1->Time().ToString());
    EXPECT_EQ("client2", event1->GetClient()->Name());

    auto event2 = std::dynamic_pointer_cast<ClientWaitingEvent>(Parser::Events()[2]);
    ASSERT_NE(nullptr, event2);
    EXPECT_EQ("09:52", event2->Time().ToString());
    EXPECT_EQ("client1", event2->GetClient()->Name());

    std::remove(filename.c_str());
}

TEST_F(ParserTest, ParseFileWithInvalidHeader) {
    std::string content =
        "not_a_number\n"
        "09:00 19:00\n"
        "100\n";
    std::string filename = CreateTempFile(content);

    EXPECT_THROW(Parser::ParseFile(filename), FormatError);

    std::remove(filename.c_str());
}

TEST_F(ParserTest, ParseFileWithInvalidTimeFormat) {
    std::string content =
        "3\n"
        "9:00 19:00\n"
        "100\n";
    std::string filename = CreateTempFile(content);

    EXPECT_THROW(Parser::ParseFile(filename), FormatError);

    std::remove(filename.c_str());
}

TEST_F(ParserTest, ParseFileWithInvalidHourlyRate) {
    std::string content =
        "3\n"
        "09:00 19:00\n"
        "abc\n";
    std::string filename = CreateTempFile(content);

    EXPECT_THROW(Parser::ParseFile(filename), FormatError);

    std::remove(filename.c_str());
}

TEST_F(ParserTest, ParseFileWithInvalidEventFormat) {
    std::string content =
        "3\n"
        "09:00 19:00\n"
        "100\n"
        "09:41 1 client1\n"
        "09:48 abc client2\n";
    std::string filename = CreateTempFile(content);

    EXPECT_THROW(Parser::ParseFile(filename), FormatError);

    std::remove(filename.c_str());
}

TEST_F(ParserTest, ParseFileWithInvalidEventID) {
    std::string content =
        "3\n"
        "09:00 19:00\n"
        "100\n"
        "09:41 1 client1\n"
        "09:48 99 client2\n";
    std::string filename = CreateTempFile(content);

    EXPECT_THROW(Parser::ParseFile(filename), FormatError);

    std::remove(filename.c_str());
}

}  // namespace computer_club
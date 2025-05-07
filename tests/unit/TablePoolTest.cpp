#include "TablePool.h"

#include <gtest/gtest.h>

namespace computer_club {

class TablePoolTest : public ::testing::Test {
   protected:
    void SetUp() override {
        TablePool::Reset();
        TablePool::Initialize(3, 10.0);
    }

    void TearDown() override {
        TablePool::Reset();
    }
};

TEST_F(TablePoolTest, Initialize) {
    auto tables = TablePool::Tables();
    EXPECT_EQ(4, tables.size());

    for (int i = 1; i <= 3; ++i) {
        auto table = TablePool::GetTable(i);
        EXPECT_EQ(i, table->Id());
        EXPECT_FALSE(table->IsOccupied());
    }
}

TEST_F(TablePoolTest, GetFreeTables) {
    auto free_tables = TablePool::GetFreeTables();
    EXPECT_EQ(3, free_tables.size());

    auto table = TablePool::GetTable(1);
    table->Occupy(TimePoint(10, 0));

    free_tables = TablePool::GetFreeTables();
    EXPECT_EQ(2, free_tables.size());
}

TEST_F(TablePoolTest, GetTableOutOfRange) {
    auto result = [&]() {
        try {
            TablePool::GetTable(0);
            return false;
        } catch (const std::out_of_range&) {
            return true;
        }
    }();
    EXPECT_TRUE(result);

    result = [&]() {
        try {
            TablePool::GetTable(4);
            return false;
        } catch (const std::out_of_range&) {
            return true;
        }
    }();
    EXPECT_TRUE(result);
}

TEST_F(TablePoolTest, TableCount) {
    EXPECT_EQ(3, TablePool::TableCount());
}

}  // namespace computer_club
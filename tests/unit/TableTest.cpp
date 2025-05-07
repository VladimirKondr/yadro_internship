#include "Table.h"

#include <gtest/gtest.h>

namespace computer_club {

class TableTest : public ::testing::Test {
   protected:
    void SetUp() override {
        table = std::make_unique<Table>(1);
    }

    std::unique_ptr<Table> table;
};

TEST_F(TableTest, InitialState) {
    EXPECT_EQ(1, table->Id());
    EXPECT_FALSE(table->IsOccupied());
    EXPECT_EQ(0, table->TotalBusyHours());
    EXPECT_EQ("00:00", table->TotalBusyTime().ToString());
    EXPECT_EQ(0, table->Revenue(100.0));
    EXPECT_EQ("1", table->ToString());
}

TEST_F(TableTest, OccupyTable) {
    TimePoint start_time(10, 0);
    table->Occupy(start_time);
    EXPECT_TRUE(table->IsOccupied());
}

TEST_F(TableTest, OccupyAlreadyOccupied) {
    TimePoint start_time(10, 0);
    table->Occupy(start_time);
    table->Occupy(TimePoint(11, 0));

    TimePoint end_time(12, 0);
    table->Free(end_time);

    EXPECT_EQ(2, table->TotalBusyHours());
    EXPECT_EQ("02:00", table->TotalBusyTime().ToString());
}

TEST_F(TableTest, FreeUnoccupiedTable) {
    TimePoint end_time(10, 0);
    table->Free(end_time);
    EXPECT_EQ(0, table->TotalBusyHours());
}

TEST_F(TableTest, OccupyAndFree) {
    TimePoint start_time(10, 0);
    TimePoint end_time(11, 30);

    table->Occupy(start_time);
    table->Free(end_time);

    EXPECT_FALSE(table->IsOccupied());
    EXPECT_EQ(2, table->TotalBusyHours());
    EXPECT_EQ("01:30", table->TotalBusyTime().ToString());
}

TEST_F(TableTest, CalculateRevenue) {
    double hourly_rate = 100.0;
    TimePoint start_time(10, 0);
    TimePoint end_time(11, 30);

    table->Occupy(start_time);
    table->Free(end_time);

    EXPECT_EQ(200.0, table->Revenue(hourly_rate));
}

TEST_F(TableTest, MultipleOccupationPeriods) {
    table->Occupy(TimePoint(10, 0));
    table->Free(TimePoint(11, 30));

    table->Occupy(TimePoint(13, 0));
    table->Free(TimePoint(14, 15));

    EXPECT_EQ(4, table->TotalBusyHours());
    EXPECT_EQ("02:45", table->TotalBusyTime().ToString());
    EXPECT_EQ(400.0, table->Revenue(100.0));
}

TEST_F(TableTest, ZeroOccupationPeriod) {
    table->Occupy(TimePoint(10, 0));
    table->Free(TimePoint(10, 0));

    EXPECT_EQ(0, table->TotalBusyHours());
    EXPECT_EQ("00:00", table->TotalBusyTime().ToString());
}

}  // namespace computer_club
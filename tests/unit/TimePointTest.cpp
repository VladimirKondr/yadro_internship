#include "events/TimePoint.h"
#include <gtest/gtest.h>

namespace computer_club {

TEST(TimePointTest, DefaultConstructor) {
    TimePoint time;
    EXPECT_EQ(0, time.Hours());
    EXPECT_EQ(0, time.Minutes());
    EXPECT_EQ("00:00", time.ToString());
}

TEST(TimePointTest, ParameterizedConstructor) {
    TimePoint time(12, 30);
    EXPECT_EQ(12, time.Hours());
    EXPECT_EQ(30, time.Minutes());
    EXPECT_EQ("12:30", time.ToString());
}

TEST(TimePointTest, ParameterizedConstructorThrowsOnInvalidTime) {
    EXPECT_THROW(TimePoint(-1, 0), std::invalid_argument);
    EXPECT_THROW(TimePoint(24, 0), std::invalid_argument);
    EXPECT_THROW(TimePoint(0, -1), std::invalid_argument);
    EXPECT_THROW(TimePoint(0, 60), std::invalid_argument);
}

TEST(TimePointTest, ParseFromString) {
    TimePoint time = TimePoint::Parse("14:45");
    EXPECT_EQ(14, time.Hours());
    EXPECT_EQ(45, time.Minutes());
}

TEST(TimePointTest, CompareLessThan) {
    TimePoint earlier(9, 0);
    TimePoint later(10, 0);
    EXPECT_TRUE(earlier < later);
    EXPECT_FALSE(later < earlier);
    EXPECT_FALSE(earlier < earlier);
    
    TimePoint t1(9, 0);
    TimePoint t2(9, 1);
    EXPECT_TRUE(t1 < t2);
}

TEST(TimePointTest, CompareLessThanOrEqual) {
    TimePoint earlier(9, 0);
    TimePoint later(10, 0);
    TimePoint same(9, 0);
    
    EXPECT_TRUE(earlier <= later);
    EXPECT_TRUE(earlier <= same);
    EXPECT_FALSE(later <= earlier);
}

TEST(TimePointTest, CompareGreaterThan) {
    TimePoint earlier(9, 0);
    TimePoint later(10, 0);
    EXPECT_TRUE(later > earlier);
    EXPECT_FALSE(earlier > later);
    EXPECT_FALSE(earlier > earlier);
}

TEST(TimePointTest, CompareGreaterThanOrEqual) {
    TimePoint earlier(9, 0);
    TimePoint later(10, 0);
    TimePoint same(9, 0);
    
    EXPECT_TRUE(later >= earlier);
    EXPECT_TRUE(same >= earlier);
    EXPECT_FALSE(earlier >= later);
}

TEST(TimePointTest, CompareEqual) {
    TimePoint t1(9, 0);
    TimePoint t2(9, 0);
    TimePoint t3(10, 0);
    
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
}

TEST(TimePointTest, CompareNotEqual) {
    TimePoint t1(9, 0);
    TimePoint t2(9, 0);
    TimePoint t3(10, 0);
    
    EXPECT_FALSE(t1 != t2);
    EXPECT_TRUE(t1 != t3);
}

TEST(TimePointTest, AddMinutes) {
    TimePoint time(9, 30);
    TimePoint result = time + 45;
    EXPECT_EQ(10, result.Hours());
    EXPECT_EQ(15, result.Minutes());
}

TEST(TimePointTest, AddMinutesSelfAssign) {
    TimePoint time(9, 30);
    time += 45;
    EXPECT_EQ(10, time.Hours());
    EXPECT_EQ(15, time.Minutes());
}

TEST(TimePointTest, SubtractMinutes) {
    TimePoint time(9, 30);
    TimePoint result = time - 45;
    EXPECT_EQ(8, result.Hours());
    EXPECT_EQ(45, result.Minutes());
}

TEST(TimePointTest, SubtractMinutesSelfAssign) {
    TimePoint time(9, 30);
    time -= 45;
    EXPECT_EQ(8, time.Hours());
    EXPECT_EQ(45, time.Minutes());
}

TEST(TimePointTest, SubtractTimePoint) {
    TimePoint earlier(9, 0);
    TimePoint later(10, 30);
    int diff = later - earlier;
    EXPECT_EQ(90, diff);
}

TEST(TimePointTest, AddThrowsOnInvalidTime) {
    TimePoint time(23, 59);
    EXPECT_THROW(time + 1, std::invalid_argument);
    
    TimePoint time2(0, 0);
    EXPECT_THROW(time2 - 1, std::invalid_argument);
}

}  // namespace computer_club
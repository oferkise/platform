#include "gtest/gtest.h"
#include "DateTime.h"
#include <ctime>

TEST(DateTimeTest, DefaultConstructor) {
    platform::DateTime obj(1, 1, 2023, 0, 0, 0);
    // Validate initial values
    EXPECT_EQ(obj.getDay(), 1);
    EXPECT_EQ(obj.getMonth(), 1);
    EXPECT_EQ(obj.getYear(), 2023);   
    EXPECT_EQ(obj.getHour(), 0);
    EXPECT_EQ(obj.getMinute(), 0);
    EXPECT_EQ(obj.getSecond(), 0);
}
TEST(DateTimeTest, EpochConstructor) {
    time_t epochTime = 1672531200; // Corresponds to 2023-01-01 00:00:00 UTC
    // DateTime(epochTime) uses localtime(), so compute expected values from localtime
    std::tm* lt = std::localtime(&epochTime);
    
    platform::DateTime obj(epochTime);
    EXPECT_EQ(obj.getDay(), lt->tm_mday);
    EXPECT_EQ(obj.getMonth(), lt->tm_mon + 1);
    EXPECT_EQ(obj.getYear(), lt->tm_year + 1900);   
    EXPECT_EQ(obj.getHour(), lt->tm_hour);
    EXPECT_EQ(obj.getMinute(), lt->tm_min);
    EXPECT_EQ(obj.getSecond(), lt->tm_sec);
}

TEST(DateTimeTest, TimestampConstructor) {
    unsigned long timestamp = 1672531200000; // Corresponds to 2023-01-01 00:00:00
    // DateTime(epochTime) uses localtime(), so compute expected values from localtime
    std::time_t ts_seconds = timestamp / 1000;
    std::tm* lt = std::localtime(&ts_seconds);
    platform::DateTime obj(timestamp);
    EXPECT_EQ(obj.getDay(), lt->tm_mday);
    EXPECT_EQ(obj.getMonth(), lt->tm_mon + 1);
    EXPECT_EQ(obj.getYear(), lt->tm_year + 1900);   
    EXPECT_EQ(obj.getHour(), lt->tm_hour);
    EXPECT_EQ(obj.getMinute(), lt->tm_min);
    EXPECT_EQ(obj.getSecond(), lt->tm_sec);
}

TEST(DateTimeTest, CurrentDateTimeString) {
    std::string dateTimeStr = platform::DateTime::getCurrentDateTimeString();
    // Basic validation of format "YYYY-MM-DD HH:MM:SS"
    EXPECT_EQ(dateTimeStr.length(), 19);
    EXPECT_EQ(dateTimeStr[4], '-');
    EXPECT_EQ(dateTimeStr[7], '-');
    EXPECT_EQ(dateTimeStr[10], ' ');
    EXPECT_EQ(dateTimeStr[13], ':');
    EXPECT_EQ(dateTimeStr[16], ':');
}

TEST(DateTimeTest, AdditionOperator) {
    platform::DateTime obj(1, 1, 2023, 0, 0, 0);
    platform::DateTime newObj = obj + 3600; // Add one hour
    EXPECT_EQ(newObj.getDay(), 1);
    EXPECT_EQ(newObj.getMonth(), 1);
    EXPECT_EQ(newObj.getYear(), 2023);   
    EXPECT_EQ(newObj.getHour(), 1);
    EXPECT_EQ(newObj.getMinute(), 0);
    EXPECT_EQ(newObj.getSecond(), 0);
}

TEST(DateTimeTest, SubtractionOperator) {
    platform::DateTime obj1(1, 1, 2023, 1, 0, 0);
    platform::DateTime obj2(1, 1, 2023, 0, 0, 0);
    long diff = obj1 - obj2; // Difference in seconds
    EXPECT_EQ(diff, 3600); // One hour difference
}

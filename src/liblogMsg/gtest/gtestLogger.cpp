#include "gtest/gtest.h"
#include "Logger.h"

TEST(LoggerTest, DefaultConstructor) {
    platform::Logger obj("TestCategory");
}

TEST(LoggerTest, LogMessage) {
    RecordProperty("Description", "Test logging messages at different levels");
    platform::Logger logger("TestCategory");
    LOGGER_INFO(logger, "This is an info message");
    LOGGER_ERROR(logger, "This is an error message");

    logger.disableLevel(platform::LogLevel::DEBUG);
    LOGGER_DEBUG(logger, "This debug message should not appear");

    EXPECT_EQ(logger.getCategory(), "TestCategory");
    EXPECT_TRUE(logger.isLevelEnabled(platform::LogLevel::INFO));
    EXPECT_TRUE(logger.isLevelEnabled(platform::LogLevel::ERROR));
    EXPECT_FALSE(logger.isLevelEnabled(platform::LogLevel::DEBUG));
}

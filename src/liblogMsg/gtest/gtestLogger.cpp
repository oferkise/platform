#include "gtest/gtest.h"
#include "Logger.h"

TEST(LoggerTest, DefaultConstructor) {
    platform::Logger obj("TestCategory");
}

TEST(LoggerTest, LogMessage) {
    platform::Logger logger("TestCategory");
    LOGGER_INFO(logger, "This is an info message");
    LOGGER_ERROR(logger, "This is an error message");
}

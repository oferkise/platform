#include "gtest/gtest.h"
#include "Logger.h"
#include "LoggerCfg.h"
#include "CfgFile.h"

class LoggerCfgTest : public ::testing::Test {
protected:
    void SetUp() override {
        // invent a testLogger.cfg using the CfgFile class
        platform::CfgFile cfg;
        cfg.setValue("category1EnableInfo", "true");
        cfg.setValue("category1EnableDebug", "false");
        cfg.setValue("category1EnableError", "true");
        cfg.setValue("category2EnableDebug", "true");
        cfg.setValue("category2EnableInfo", "false");

        bool written = cfg.write("testLogger.cfg");
        ASSERT_TRUE(written);
        SLOG_INFO("LoggerCfgTest", "Wrote file testLogger.cfg");
    }
    void TearDown() override {
        // delete the testLogger.cfg file
        std::remove("testLogger.cfg");
    }
};

TEST_F(LoggerCfgTest, LoadConfigAndGetLogger) {
    RecordProperty("Description", "Test loading logger configuration and retrieving loggers");
    platform::LoggerCfg loggerCfg;
    loggerCfg.loadConfig("testLogger.cfg");

    platform::Logger logger1 = loggerCfg.getLogger("category1");
    platform::Logger logger2 = loggerCfg.getLogger("category2");

    LOGGER_INFO(logger1, "Info message from category1");
    LOGGER_DEBUG(logger2, "Debug message from category2");

    EXPECT_EQ(logger1.getCategory(), "category1");
    EXPECT_EQ(logger2.getCategory() , "category2");
    EXPECT_TRUE(logger1.isLevelEnabled(platform::LogLevel::INFO));
    EXPECT_FALSE(logger1.isLevelEnabled(platform::LogLevel::DEBUG));
    EXPECT_TRUE(logger2.isLevelEnabled(platform::LogLevel::DEBUG));
    EXPECT_FALSE(logger2.isLevelEnabled(platform::LogLevel::INFO));
}

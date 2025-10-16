#pragma once
#include <string>

#define LOGGER_TRACE(logger, message) logger.log(platform::LogLevel::TRACE, __func__, __LINE__, message)
#define LOGGER_DEBUG(logger, message) logger.log(platform::LogLevel::DEBUG, __func__, __LINE__, message)
#define LOGGER_INFO(logger, message)  logger.log(platform::LogLevel::INFO,  __func__, __LINE__, message)
#define LOGGER_WARN(logger, message)  logger.log(platform::LogLevel::WARN,  __func__, __LINE__, message)
#define LOGGER_ERROR(logger, message) logger.log(platform::LogLevel::ERROR, __func__, __LINE__, message)

#define GLOG_TRACE(message) LOGGER.log(platform::LogLevel::TRACE, __func__, __LINE__, message)
#define GLOG_DEBUG(message) LOGGER.log(platform::LogLevel::DEBUG, __func__, __LINE__, message)
#define GLOG_INFO(message)  LOGGER.log(platform::LogLevel::INFO,  __func__, __LINE__, message)
#define GLOG_WARN(message)  LOGGER.log(platform::LogLevel::WARN,  __func__, __LINE__, message)
#define GLOG_ERROR(message) LOGGER.log(platform::LogLevel::ERROR, __func__, __LINE__, message)

#define SLOG_TRACE(message) logger.logStatic(platform::LogLevel::TRACE, "", __func__, __LINE__, message)
#define SLOG_DEBUG(message) logger.logStatic(platform::LogLevel::DEBUG, "", __func__, __LINE__, message)
#define SLOG_INFO(message)  logger.logStatic(platform::LogLevel::INFO,  "", __func__, __LINE__, message)
#define SLOG_WARN(message)  logger.logStatic(platform::LogLevel::WARN,  "", __func__, __LINE__, message)
#define SLOG_ERROR(message) logger.logStatic(platform::LogLevel::ERROR, "", __func__, __LINE__, message)

namespace platform {
    enum class LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR
    };
    // class for managing log messages. An instance is expected for each category
    class Logger {
    public:
        Logger(std::string category) : m_category(std::move(category)) 
        {
            // Enable all levels by default
            m_enabledLevels = (1 << static_cast<int>(LogLevel::TRACE)) |
                              (1 << static_cast<int>(LogLevel::DEBUG)) |
                              (1 << static_cast<int>(LogLevel::INFO))  |
                              (1 << static_cast<int>(LogLevel::WARN))  |
                              (1 << static_cast<int>(LogLevel::ERROR));
        };
        ~Logger() = default;
        void log(LogLevel level, const std::string& func, const unsigned int line, const std::string& message);
        void enableLevel(LogLevel level);
        static void logStatic(LogLevel level, const std::string& category, const std::string& func, const unsigned int line, const std::string& message);

    protected:
        std::string m_category;
        int m_enabledLevels = 0; // bitmask of enabled levels
    };
}

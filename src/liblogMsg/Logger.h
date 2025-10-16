#pragma once
#include <string>

#define LOGGER_TRACE(logger, message) (logger).log(platform::LogLevel::TRACE, __func__, __LINE__, (message))
#define LOGGER_DEBUG(logger, message) (logger).log(platform::LogLevel::DEBUG, __func__, __LINE__, (message))
#define LOGGER_INFO(logger, message)  (logger).log(platform::LogLevel::INFO,  __func__, __LINE__, (message))
#define LOGGER_WARN(logger, message)  (logger).log(platform::LogLevel::WARN,  __func__, __LINE__, (message))
#define LOGGER_ERROR(logger, message) (logger).log(platform::LogLevel::ERROR, __func__, __LINE__, (message))

#define GLOG_TRACE(message) LOGGER.log(platform::LogLevel::TRACE, __func__, __LINE__, (message))
#define GLOG_DEBUG(message) LOGGER.log(platform::LogLevel::DEBUG, __func__, __LINE__, (message))
#define GLOG_INFO(message)  LOGGER.log(platform::LogLevel::INFO,  __func__, __LINE__, (message))
#define GLOG_WARN(message)  LOGGER.log(platform::LogLevel::WARN,  __func__, __LINE__, (message))
#define GLOG_ERROR(message) LOGGER.log(platform::LogLevel::ERROR, __func__, __LINE__, (message))

#define SLOG_TRACE(category, message) platform::Logger::logStatic(platform::LogLevel::TRACE, (category), __func__, __LINE__, (message))
#define SLOG_DEBUG(category, message) platform::Logger::logStatic(platform::LogLevel::DEBUG, (category), __func__, __LINE__, (message))
#define SLOG_INFO(category, message)  platform::Logger::logStatic(platform::LogLevel::INFO,  (category), __func__, __LINE__, (message))
#define SLOG_WARN(category, message)  platform::Logger::logStatic(platform::LogLevel::WARN,  (category), __func__, __LINE__, (message))
#define SLOG_ERROR(category, message) platform::Logger::logStatic(platform::LogLevel::ERROR, (category), __func__, __LINE__, (message))
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
        /**
         * Constructor that initializes the logger with a specific category.
         */
        Logger(std::string category) : m_category(std::move(category)) 
        {
            // Enable all levels by default
            m_enabledLevels = (1 << static_cast<int>(LogLevel::TRACE)) |
                              (1 << static_cast<int>(LogLevel::DEBUG)) |
                              (1 << static_cast<int>(LogLevel::INFO))  |
                              (1 << static_cast<int>(LogLevel::WARN))  |
                              (1 << static_cast<int>(LogLevel::ERROR));
        };
        /**
         * Destructor
         */
        ~Logger() = default;
        /**
         * Logs a message with the specified log level, function name, line number, and message.
         * @param level The log level (TRACE, DEBUG, INFO, WARN, ERROR)
         * @param func The function name where the log is generated.
         * @param line The line number where the log is generated.
         * @param message The log message.
         */
        void log(LogLevel level, const std::string& func, const unsigned int line, const std::string& message);
        /**
         * Enables logging for the specified log level.
         * @param level The log level to enable.
         */
        void enableLevel(LogLevel level);
        /**
         * Disables logging for the specified log level.
         * @param level The log level to disable.
         */
        void disableLevel(LogLevel level);
        /**
         * @return the category of the logger.
         */
        std::string getCategory() const { return m_category; }
        /**
         * Checks if the specified log level is enabled.
         * @param level The log level to check.
         * @return true if the log level is enabled, false otherwise.
         */
        bool isLevelEnabled(LogLevel level) const;
        /** 
         * Static logging method that does not require a Logger instance 
         * @param level The log level (TRACE, DEBUG, INFO, WARN, ERROR)
         * @param category The category of the log message.
         * @param func The function name where the log is generated.
         * @param line The line number where the log is generated.
         * @param message The log message.
         */
        static void logStatic(LogLevel level, const std::string& category, const std::string& func, const unsigned int line, const std::string& message);

    protected:
        std::string m_category;
        int m_enabledLevels = 0; // bitmask of enabled levels
    };
}

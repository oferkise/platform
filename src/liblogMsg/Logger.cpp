#include "Logger.h"
#include "DateTime.h"
#include <iostream>

static std::string levelStrings[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR" };

namespace platform {
    void Logger::log(LogLevel level, const std::string& func, const unsigned int line, const std::string& message) {
        // Simple console logging implementation
        if (m_enabledLevels & (1 << static_cast<int>(level))) 
        {
            std::cout << "{\"time\":\"" << DateTime::getCurrentDateTimeString()
                      << "\",\"lvl\":\"" << levelStrings[static_cast<int>(level)] << "\""
                      << ",\"cat\":\"" << m_category << "\""
                      << ",\"loc\":\"" << func << ":" << line << "\""
                      << ",\"msg\":\"" << message << "\"}" << std::endl;
        }
    }

    void Logger::logStatic(LogLevel level, const std::string& category, const std::string& func, const unsigned int line, const std::string& message) 
    {
        // Simple console logging implementation
        std::cout << "{\"time\":\"" << DateTime::getCurrentDateTimeString()
                  << "\",\"lvl\":\"" << levelStrings[static_cast<int>(level)] << "\""
                  << ",\"cat\":\"" << category << "\""
                  << ",\"loc\":\"" << func << ":" << line << "\""
                  << ",\"msg\":\"" << message << "\"}" << std::endl;
    }

    void Logger::enableLevel(LogLevel level) {
        m_enabledLevels |= (1 << static_cast<int>(level));
    }

    void Logger::disableLevel(LogLevel level) {
        m_enabledLevels &= ~(1 << static_cast<int>(level));
    }

    bool Logger::isLevelEnabled(LogLevel level) const {
        return (m_enabledLevels & (1 << static_cast<int>(level))) != 0;
    }
}

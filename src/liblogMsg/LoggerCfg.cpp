#include "LoggerCfg.h"
#include "CfgFile.h"
#include <algorithm>


namespace platform {
    void LoggerCfg::loadConfig(const std::string& configFilePath) {
        CfgFile cfg;
        if (cfg.load(configFilePath)) {
            // For simplicity, assume config file has lines like:
            // category1EnableInfo=true
            // category2EnableDebug=false
            std::list<std::string> keys = cfg.getAllKeys();
            for (const auto& categoryAndLevel : keys) {
                // parse the line
                std::string enableStr = cfg.getValue(categoryAndLevel, "false");
                std::transform(enableStr.begin(), enableStr.end(), enableStr.begin(),
                    [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                const std::string category = categoryAndLevel.substr(0, categoryAndLevel.find("Enable"));
                const std::string levelStr = categoryAndLevel.substr(categoryAndLevel.find("Enable") + 6);
                bool enabled = (enableStr == "true" || enableStr == "1");
   
                // get or create the logger for this category
                if (m_loggers.find(category) == m_loggers.end()) {
                    m_loggers[category] = std::make_shared<Logger>(category);
                }
                // enable or disable the specified level
                Logger& logger = *m_loggers[category];
                std::string levelUpper = levelStr;
                std::transform(levelUpper.begin(), levelUpper.end(), levelUpper.begin(),
                               [](unsigned char c) { return static_cast<char>(std::toupper(c)); });

                auto level = LogLevel::INFO; // default
                if (levelUpper == "TRACE") {
                    level = LogLevel::TRACE;
                } else if (levelUpper == "DEBUG") {
                    level = LogLevel::DEBUG;
                } else if (levelUpper == "INFO") {
                    level = LogLevel::INFO;
                } else if (levelUpper == "WARN") {
                    level = LogLevel::WARN;
                } else if (levelUpper == "ERROR") {
                    level = LogLevel::ERROR;
                }
                if (enabled) {
                    logger.enableLevel(level);
                } else {
                    logger.disableLevel(level);
                }
            }
        }
        else 
        {
            // Could not load config file, do nothing
            SLOG_WARN("LoggerCfg", "Failed to load config file: " + configFilePath);
        }
    }

    Logger& LoggerCfg::getLogger(const std::string& category) {
        auto it = m_loggers.find(category);
        if (it != m_loggers.end()) {
            return *it->second;
        }
        // if a logger is not found create one
        m_loggers[category] = std::make_shared<Logger>(category);
        return *m_loggers[category];
    }
}
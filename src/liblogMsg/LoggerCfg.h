#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Logger.h"


namespace platform {
    // class to manage the loggers instances from configuration
    class LoggerCfg {
    public:
        /**     
         * Default constructor
         */
        LoggerCfg() = default;
        /**
         * Destructor
         */
        ~LoggerCfg() = default;

        /**
         * Loads the logger configuration from a file.
         * @param configFilePath Path to the configuration file.
         * The configuration file is expected to have lines like:
         * category1EnableInfo=true
         * category2EnableDebug=false
         * This will enable or disable specific log levels for each category.
         * If a category is not found, a new logger instance will be created with default settings.
         * If a log level is not specified for a category, it will be enabled by default.
         * If the configuration file cannot be loaded, no changes will be made.
         */
        void loadConfig(const std::string& configFilePath);
        /**
         * Gets the logger instance for a specific category.
         * If the logger does not exist, it will be created with default settings.
         * @param category The category name.
         * @return Reference to the logger instance.
         */
        Logger& getLogger(const std::string& category);

    private:
        // Internal storage for logger instances
        std::unordered_map<std::string, std::shared_ptr<Logger>> m_loggers;
    };
}  // namespace platform
#pragma once
#include <string>
#include <list>
#include <unordered_map>

namespace platform {
    // class for reading simple configuration files with key=value pairs
    class CfgFile {
    public:
        /**
         * Default constructor
         */
        CfgFile() = default;
        /**
         * Destructor
         */
        ~CfgFile() = default;
        /**
         * Loads the configuration from a file.
         * @param filePath Path to the configuration file.
         * @return true if the file was successfully loaded, false otherwise.
         */
        bool load(const std::string& filePath);
        /**
         * Gets the value associated with a key.
         * @param key The key to look up.
         * @param defaultValue The value to return if the key is not found (default is an empty string).
         * @return The value associated with the key, or defaultValue if the key is not found.
         */
        std::string getValue(const std::string& key, const std::string& defaultValue = "") const;
        /**
         * Sets the value for a key.
         * @param key The key to set.
         * @param value The value to associate with the key.
         */
        void setValue(const std::string& key, const std::string& value);
        /**
         * Writes the current configuration to a file.
         * @param filePath Path to the output configuration file.
         * @return true if the file was successfully written, false otherwise.
         */
        bool write(const std::string& filePath) const;
        /**
         * Gets a list of all keys in the configuration.
         * @return A list of all keys.
         */
        std::list<std::string> getAllKeys() const { return m_keyList; }

    private:
        std::unordered_map<std::string, std::string> m_configMap; // key-value pairs of the configuration
        std::list<std::string> m_keyList; // to maintain the list of keys
    };
}  // namespace platform
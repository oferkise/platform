#include "CfgFile.h"
#include <fstream>

namespace platform {
    const char COMMENT_CHAR = '#';
    const char DELIMITER_CHAR = '=';

    bool CfgFile::load(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            // trim whitespace at beginning
            line.erase(0, line.find_first_not_of(" \t\n\r"));
            // trim whitespace or comments at end
            size_t commentPos = line.find(COMMENT_CHAR);
            if (commentPos != std::string::npos) {
                line = line.substr(0, commentPos);
            }
            line.erase(line.find_last_not_of(" \t\n\r") + 1);
            
            // ignore empty
            if (line.empty()) {
                continue;
            }
            size_t delimiterPos = line.find(DELIMITER_CHAR);
            if (delimiterPos != std::string::npos) {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                m_configMap[key] = value;
                m_keyList.push_back(key);
            }
        }
        file.close();
        return true;
    }

    std::string CfgFile::getValue(const std::string& key, const std::string& defaultValue) const {
        // look for the key
        auto it = m_configMap.find(key);
        if (it != m_configMap.end()) {
            return it->second;
        }
        return defaultValue;
    }

    void CfgFile::setValue(const std::string& key, const std::string& value) {
        // if key is new, add to key list
        if (m_configMap.find(key) == m_configMap.end())
            m_keyList.push_back(key);
        m_configMap[key] = value;
    }

    bool CfgFile::write(const std::string& filePath) const {
        // open the desired file for writing
        std::ofstream file(filePath);
        if (!file.is_open()) {
            return false;
        }
        // write all key-value pairs
        for (const auto& pair : m_configMap) {
            file << pair.first << DELIMITER_CHAR << pair.second << std::endl;
        }
        // close the file
        file.close();
        return true;
    }
}  // namespace platform

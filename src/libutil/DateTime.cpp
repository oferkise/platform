#include "DateTime.h"

namespace platform {
    DateTime::DateTime(time_t epochTime) {
        struct tm* timeinfo = localtime(&epochTime);
        m_year = timeinfo->tm_year + 1900;
        m_month = timeinfo->tm_mon + 1;
        m_day = timeinfo->tm_mday;
        m_hour = timeinfo->tm_hour;
        m_minute = timeinfo->tm_min;
        m_second = timeinfo->tm_sec;
    }

    DateTime::DateTime(unsigned long timestamp) {
        time_t seconds = timestamp / 1000;
        unsigned int milliseconds = timestamp % 1000;
        struct tm* timeinfo = localtime(&seconds);
        m_year = timeinfo->tm_year + 1900;
        m_month = timeinfo->tm_mon + 1;
        m_day = timeinfo->tm_mday;
        m_hour = timeinfo->tm_hour;
        m_minute = timeinfo->tm_min;
        m_second = timeinfo->tm_sec;
        // Note: milliseconds are not stored in this implementation
    }

    std::string DateTime::getCurrentDateTimeString() {
        time_t now = time(0);
        struct tm* timeinfo = localtime(&now);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return std::string(buffer);
    }

    DateTime DateTime::getCurrentDateTime()
    {
        time_t now = time(0);
        return DateTime(now);
    }

    DateTime DateTime::operator+(const unsigned int seconds) const {
        struct tm timeinfo = {};
        timeinfo.tm_year = m_year - 1900;
        timeinfo.tm_mon = m_month - 1;
        timeinfo.tm_mday = m_day;
        timeinfo.tm_hour = m_hour;
        timeinfo.tm_min = m_minute;
        timeinfo.tm_sec = m_second + seconds;

        time_t newTime = mktime(&timeinfo);
        return DateTime(newTime);
    }

    long DateTime::operator-(const DateTime& other) const {
        struct tm timeinfo1 = {};
        timeinfo1.tm_year = m_year - 1900;
        timeinfo1.tm_mon = m_month - 1;
        timeinfo1.tm_mday = m_day;
        timeinfo1.tm_hour = m_hour;
        timeinfo1.tm_min = m_minute;
        timeinfo1.tm_sec = m_second;

        struct tm timeinfo2 = {};
        timeinfo2.tm_year = other.m_year - 1900;
        timeinfo2.tm_mon = other.m_month - 1;
        timeinfo2.tm_mday = other.m_day;
        timeinfo2.tm_hour = other.m_hour;
        timeinfo2.tm_min = other.m_minute;
        timeinfo2.tm_sec = other.m_second;

        time_t t1 = mktime(&timeinfo1);
        time_t t2 = mktime(&timeinfo2);
        long diffSeconds = difftime(t1, t2);

        return diffSeconds;
    }
} // namespace platform

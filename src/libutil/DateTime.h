#pragma once
#include <string>
#include <ctime>

namespace platform {
    // Utility class representing a date and a time
    class DateTime {
    public:
        /**
         * Constructs a DateTime object with the specified date and time components.
         */
        DateTime(const unsigned int day, const unsigned int month, const unsigned int year, 
                 const unsigned int hour, const unsigned int minute, const unsigned int second)
            : m_day(day), m_month(month), m_year(year), m_hour(hour), m_minute(minute), m_second(second) {} 
        /**
         * Copy constructor
         */
        DateTime(const DateTime&) = default;
        /**
         * Copy assignment operator
         */
        DateTime& operator=(const DateTime&) = default;
        /**
         * Constructs a DateTime object from epoch time or timestamp.
         * @param epochTime Time in seconds since epoch (1970-01-01 00:00:00 UTC)
         */
        DateTime(time_t epochTime);
        /**
         * Constructs a DateTime object from a timestamp in milliseconds since epoch.
         * @param timestamp Time in milliseconds since epoch (1970-01-01 00:00:00 UTC)
         */
        DateTime(unsigned long timestamp);
        /**
         * Destructor
         */
        ~DateTime() = default;
        /**
         * Returns the current date and time as a string.
         * Format: "YYYY-MM-DD HH:MM:SS"
         */
        static std::string getCurrentDateTimeString();
        static DateTime getCurrentDateTime();
        DateTime operator+(const unsigned int seconds) const;
        long operator-(const DateTime& other) const;

        // getters
        unsigned int getDay() const { return m_day; }
        unsigned int getMonth() const { return m_month; }
        unsigned int getYear() const { return m_year; }
        unsigned int getHour() const { return m_hour; }
        unsigned int getMinute() const { return m_minute; }
        unsigned int getSecond() const { return m_second; }
    private:
        unsigned int m_day;
        unsigned int m_month;
        unsigned int m_year;
        unsigned int m_hour;    
        unsigned int m_minute;
        unsigned int m_second;
    };
} // namespace platform

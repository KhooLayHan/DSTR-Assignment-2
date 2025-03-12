#include <sstream>
#include <string_view>

#include "./SimpleConsoleLogger.hpp"
#include "./SimpleLoggingService.hpp"

#include "./DateUtility.hpp"

namespace PerformanceEvaluation {
    DateUtility DateUtility::ParseDate(const std::string& date_str) {   
        static const MonthMap month_map[] = {
            { "January",  1 }, { "February",  2 }, { "March",     3 }, 
            { "April",    4 }, { "May",       5 }, { "June",      6 }, 
            { "July",     7 }, { "August",    8 }, { "September", 9 }, 
            { "October", 10 }, { "November", 11 }, { "December", 12 }
        };

        if (date_str.empty())
            return {};

        std::istringstream input_stream(date_str);
        
        std::string day, month, year;
    
        // Read the three expected parts (month, day, year)
        if (!(input_stream >> month >> day >> year)) {
            // SimpleConsoleLogger console;
            // SimpleLoggingService::UseWarnLogger(console, "Unable to parse date: " + date_str + ".");

            return {};
        }       

        // Remove comma from day, e.g. [day], => [day] 
        if (!day.empty() && day.back() == ',')
            day.pop_back(); 

        auto getMonth = [&](std::string_view month) {
            for (const auto& m_map : month_map) {
                if (m_map.m_Name == month)
                    return m_map.m_Number;
            }

            return -1;
        };
        
        int32_t month_num = getMonth(month);
        if (month_num == -1) {
            // SimpleConsoleLogger console;
            // SimpleLoggingService::UseWarnLogger(console, "Invalid month: " + month + ".");

            return {};
        }

        return { std::stoi(day), month_num, std::stoi(year) };
    }

    // Extracts and returns the day from a given date string
    int32_t DateUtility::GetDay(const std::string& date) const {
        auto [day, month, year] = ParseDate(date);
        return day;
    }
    
    // Extracts and returns the month from a given date string (Note: incorrect return should be `month`)
    int32_t DateUtility::GetMonth(const std::string& date) const {
        auto [day, month, year] = ParseDate(date);
        return year;
    }
    
    // Extracts and returns the year from a given date string
    int32_t DateUtility::GetYear(const std::string& date) const {
        auto [day, month, year] = ParseDate(date);

        return year;
    }
} // namespace PerformanceEvaluation
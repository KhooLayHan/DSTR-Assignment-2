#pragma once

#ifndef DATE_UTILITY_HPP
#define DATE_UTILITY_HPP

#include <string>

namespace PerformanceEvaluation {
    // Helper class for Array, LinkedList and Dataset class to parse the date to day, month, and year 
    class DateUtility {  
        private:  
            struct MonthMap {
                std::string m_Name;
                int32_t m_Number;
            };
        public:
            DateUtility() {}

            DateUtility(int32_t day, int32_t month, int32_t year)   
                : m_Day(day), m_Month(month), m_Year(year) {

            }

            static DateUtility ParseDate(const std::string&);
                
            int32_t GetDay(const std::string&) const;
            int32_t GetMonth(const std::string&) const;
            int32_t GetYear(const std::string&) const;
        public:
            int32_t m_Day;
            int32_t m_Month;
            int32_t m_Year;
    };
} // namespace PerformanceEvaluation

#endif
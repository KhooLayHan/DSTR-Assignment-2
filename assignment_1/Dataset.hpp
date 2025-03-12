#pragma once

#ifndef DATASET_HPP
#define DATASET_HPP

#include <iostream>
#include <string>
#include <string_view>

namespace PerformanceEvaluation
{   
    enum class Criteria {
        TEXT = 0,
        TITLE = 1,
        SUBJECT = 2,
        DATE = 3, // Publication year
    };

    class Dataset {
        public:
            int32_t m_Id;
            std::string m_Title;
            std::string m_Text;
            std::string m_Subject;
            std::string m_Date; 

            Dataset() {}

            Dataset(int32_t id, std::string_view title, std::string_view text, std::string_view subject, std::string_view date) 
                : m_Id(id), m_Title(title), m_Text(text), m_Subject(subject), m_Date(date) {

            }

            bool operator==(const Dataset& other) {
                return 
                    m_Id        == other.m_Id       &&
                    m_Title     == other.m_Title    &&
                    m_Text      == other.m_Text     &&
                    m_Subject   == other.m_Subject  &&
                    m_Date      == other.m_Date
                ;
            }

            void Display() const {
                std::cout << "\n\033[34;1mID:\033[0m "       << m_Id      << "\n";
                std::cout << "\033[34;1mTITLE:\033[0m "      << m_Title   << "\n";
                std::cout << "\033[34;1mTEXT:\033[0m "       << m_Text    << "\n";
                std::cout << "\033[34;1mSUBJECT:\033[0m "    << m_Subject << "\n";
                std::cout << "\033[34;1mDATE:\033[0m "       << m_Date    << "\n";
                
                std::cout << "\n-----------\n";
            }
            
            std::string ReadAll() const {
                return { ReadTitle() + ReadWord() + ReadSubject() + ReadDate() };
            }

            std::string ReadTitle() const {
                return m_Title;
            }
            
            std::string ReadWord() const {
                return m_Text;
            }
            
            std::string ReadSubject() const {
                return m_Subject;
            }
            
            std::string ReadDate() const {
                return m_Date;
            }
    };
} // namespace PerformanceEvaluation


#endif
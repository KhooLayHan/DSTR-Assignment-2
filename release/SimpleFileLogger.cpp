#include <sstream>

#include "./FileHandling.hpp"
#include "./SimpleFileLogger.hpp"

namespace PerformanceEvaluation {
    #ifdef SOURCE_LOCATION_SUPPORTED
        void SimpleFileLogger::Log(std::string_view message, LogLevel level, const Location& location) const {
            WriteFile(message, level, location);
        }
                
        void SimpleFileLogger::Debug(std::string_view message, const Location& location) const {
            WriteFile(message, LogLevel::DEBUG, location);    
        }
                
        void SimpleFileLogger::Info(std::string_view message, const Location& location) const {
            WriteFile(message, LogLevel::INFO, location);
        }
                
        void SimpleFileLogger::Warn(std::string_view message, const Location& location) const {
            WriteFile(message, LogLevel::WARN, location);
        }
                
        void SimpleFileLogger::Error(std::string_view message, const Location& location) const {
            WriteFile(message, LogLevel::ERROR, location);
        }
                
        void SimpleFileLogger::Fatal(std::string_view message, const Location& location) const {
            WriteFile(message, LogLevel::FATAL, location);
        }

        void SimpleFileLogger::WriteFile(std::string_view message, LogLevel level, const Location& location) const {
            std::stringstream output_stream;

            output_stream 
                << "[" 
                << __DATE__ << "|"
                << __TIME__ << "|"
                << location.file_name() << "|" 
                << "Line " << location.line() << "|"
                << location.function_name() << "|"
                << "Column " << location.column() 
                << "]\n"
                << SetLogLevel(level) << ": " << message 
                << "\n\n"
            ;

            if (level == LogLevel::INFO || level == LogLevel::DEBUG) 
                FileHandling::AppendFile("./Logs/log.txt", output_stream.str());
            else
                FileHandling::AppendFile("./Logs/error_log.txt", output_stream.str());    
        }
    #else
        void SimpleFileLogger::Log(std::string_view message, const char* file, int32_t line, LogLevel level) const {
            printConsole(message, file, line, level);
        }

        void SimpleLogger::WriteFile(std::string_view message, const char* file, int32_t line, LogLevel level) const {
            std::stringstream output_stream;

            output_stream 
                << "[" 
                << __DATE__ << "|"
                << __TIME__ << "|"
                << file << "|" // __FILE__
                << "Line " << line << "|" // __LINE__
                // * Note: __FUNCTION__ is not standard C++ 
                // * Note: __COLUMN__ predefined macro does not exist 
                << "]\n"
                << SetLogLevel(level) << ": " << message 
                << "\n\n"
            ;
            
            if (level == LogLevel::INFO || level == LogLevel::DEBUG) 
                FileHandling::AppendFile("./Logs/log.txt", output_stream.str());
            else
                FileHandling::AppendFile("./Logs/error_log.txt", output_stream.str());  
        }
    #endif
}

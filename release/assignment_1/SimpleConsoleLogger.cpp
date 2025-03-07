#include <iostream>

#include "./SimpleConsoleLogger.hpp"

namespace PerformanceEvaluation {
    #ifdef SOURCE_LOCATION_SUPPORTED
        void SimpleConsoleLogger::Log(std::string_view message, LogLevel level, const Location& location) const {
            PrintConsole(message, level, location);
        }
                
        void SimpleConsoleLogger::Debug(std::string_view message, const Location& location) const {
            PrintConsole(message, LogLevel::DEBUG, location);    
        }
                
        void SimpleConsoleLogger::Info(std::string_view message, const Location& location) const {
            PrintConsole(message, LogLevel::INFO, location);
        }
                
        void SimpleConsoleLogger::Warn(std::string_view message, const Location& location) const {
            PrintConsole(message, LogLevel::WARN, location);
        }
                
        void SimpleConsoleLogger::Error(std::string_view message, const Location& location) const {
            PrintConsole(message, LogLevel::ERROR, location);
        }
                
        void SimpleConsoleLogger::Fatal(std::string_view message, const Location& location) const {
            PrintConsole(message, LogLevel::FATAL, location);
        }

        void SimpleConsoleLogger::PrintConsole(std::string_view message, LogLevel level, const Location& location) const {
            static int32_t id;

            if (level == LogLevel::DEBUG || level == LogLevel::INFO) {
                std::cout 
                    << ++id << " ["
                    << __DATE__ << "|"
                    << __TIME__ 
                    << "]"
                    << SetLogLevel(level) << ": " << message
                    << "\n\n"
                ;
            } else {
                std::cerr 
                    << ++id << " [" 
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
            }
        }
    #else
        void SimpleConsoleLogger::Log(std::string_view message, const char* file, int32_t line, LogLevel level) const {
            printConsole(message, file, line, level);
        }

        void SimpleLogger::PrintConsole(std::string_view message, const char* file, int32_t line, LogLevel level) const {
            static int32_t id;

            if (level == LogLevel::DEBUG || level == LogLevel::INFO) {
                std::cout 
                    << ++id << " ["
                    << __DATE__ << "|"
                    << __TIME__ 
                    << "]"
                    << SetLogLevel(level) << ": " << message
                    << "\n\n"
                ;
            } else {
                std::cerr 
                    << ++id << " [" 
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
            }
        }
    #endif
}

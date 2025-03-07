#pragma once

#define SOURCE_LOCATION_SUPPORTED 1 
#ifdef SOURCE_LOCATION_SUPPORTED
    #include <source_location>
#endif

#include <string>
#include <string_view>

namespace PerformanceEvaluation {
    enum class LogLevel {
      DEBUG = 0,
      INFO = 1,
      WARN = 2,
      ERROR = 3,
      FATAL = 4,
    };

    using Location = std::source_location;
    class SimpleLogger {   
        public: 
            #ifdef SOURCE_LOCATION_SUPPORTED
                virtual void Log    (std::string_view, LogLevel, const Location& location) const = 0;
                virtual void Debug  (std::string_view, const Location& location) const = 0;
                virtual void Info   (std::string_view, const Location& location) const = 0;
                virtual void Warn   (std::string_view, const Location& location) const = 0;
                virtual void Error  (std::string_view, const Location& location) const = 0;
                virtual void Fatal  (std::string_view, const Location& location) const = 0;
            #else
                virtual void Log    (std::string_view, const char*, int32_t, LogLevel) const = 0;            
            #endif

            SimpleLogger() {}

            virtual ~SimpleLogger() = default;
        protected: 
            static const std::string SetLogLevel(LogLevel log_level) {
                switch (log_level) {
                    case LogLevel::DEBUG:   return "DEBUG";
                    case LogLevel::INFO:    return "INFO";
                    case LogLevel::WARN:    return "WARN";
                    case LogLevel::ERROR:   return "ERROR";
                    case LogLevel::FATAL:   return "FATAL";
                    default:                return "LOG_LEVEL_UNKNOWN";
                }
            }
        private:            
            SimpleLogger(const SimpleLogger&) = delete;
            SimpleLogger(SimpleLogger&&) = delete;
            
            SimpleLogger& operator=(const SimpleLogger&) = delete; 
            SimpleLogger& operator=(SimpleLogger&&) = delete; 
    };
}
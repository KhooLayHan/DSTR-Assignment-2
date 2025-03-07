#include "./SimpleLoggingService.hpp"

namespace PerformanceEvaluation {
    void SimpleLoggingService::UseLogger(const SimpleLogger& logger, std::string_view message, LogLevel level, const Location& location) {
        logger.Log(message, level, location);
    }
    
    void SimpleLoggingService::UseDebugLogger(const SimpleLogger& logger, std::string_view message, const Location& location) {
        logger.Debug(message, location);
    }
    
    void SimpleLoggingService::UseInfoLogger(const SimpleLogger& logger, std::string_view message, const Location& location) {
        logger.Info(message, location);
    }
    
    void SimpleLoggingService::UseWarnLogger(const SimpleLogger& logger, std::string_view message, const Location& location) {
        logger.Warn(message, location);
    }
    
    void SimpleLoggingService::UseErrorLogger(const SimpleLogger& logger, std::string_view message, const Location& location) {
        logger.Error(message, location);
    }

    void SimpleLoggingService::UseFatalLogger(const SimpleLogger& logger, std::string_view message, const Location& location) {
        logger.Fatal(message, location);
    }
}
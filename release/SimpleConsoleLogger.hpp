#pragma once

#include "./SimpleLogger.hpp"

namespace PerformanceEvaluation {
    class SimpleConsoleLogger final : public SimpleLogger {        
      public: 
          #ifdef SOURCE_LOCATION_SUPPORTED
              void Log    (std::string_view, LogLevel, const Location& location) const override;
              void Debug  (std::string_view, const Location& location) const override;
              void Info   (std::string_view, const Location& location) const override;
              void Warn   (std::string_view, const Location& location) const override;
              void Error  (std::string_view, const Location& location) const override;
              void Fatal  (std::string_view, const Location& location) const override;
              
              void PrintConsole(std::string_view, LogLevel, const Location&) const;
          #else
              void Log(std::string_view, const char*, int32_t, LogLevel) const override;            
              void PrintConsole(std::string_view, const char*, int32_t, LogLevel) const;
          #endif
    };
}
#pragma once

#include "./SimpleLogger.hpp"

namespace PerformanceEvaluation {
    class SimpleLoggingService {
        public:
            static void UseLogger      (const SimpleLogger&, std::string_view, LogLevel, const Location& location = Location::current());
            static void UseDebugLogger (const SimpleLogger&, std::string_view, const Location& location = Location::current());
            static void UseInfoLogger  (const SimpleLogger&, std::string_view, const Location& location = Location::current());
            static void UseWarnLogger  (const SimpleLogger&, std::string_view, const Location& location = Location::current());
            static void UseErrorLogger (const SimpleLogger&, std::string_view, const Location& location = Location::current());
            static void UseFatalLogger (const SimpleLogger&, std::string_view, const Location& location = Location::current());
    };
}
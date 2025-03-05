#pragma once

#include <chrono>

#include "./SimpleLogger.hpp"

namespace PerformanceEvaluation {
    enum class TimeUnit {
        SECONDS = 0,
        MICROSECONDS = 1,
        MILLISECONDS = 2,
        NANOSECONDS = 3,
    };
    
    class Benchmark {
        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = std::chrono::time_point<Clock>;
        using Seconds = std::chrono::seconds;
        using Microseconds = std::chrono::microseconds;
        using Milliseconds = std::chrono::milliseconds;
        using Nanoseconds = std::chrono::nanoseconds;

        public:
            Benchmark() 
                : m_IsRunning(false) {
                // StartTimer();
            }

            ~Benchmark() {
                // EndTimer();
            }
           
            void StartTimer();    
            void EndTimer();
            void Duration(TimeUnit time_unit = TimeUnit::MICROSECONDS) const;
            
            void DurationSeconds() const;
            void DurationMicroseconds() const;
            void DurationMilliseconds() const;
            void DurationNanoseconds() const;

            template<typename Func>
            void MeasureDuration(Func func) {
                StartTimer();
                func();
                EndTimer(); 
            }
        protected:
            void CheckBenchmarkIsRunning() const;
            
            static const std::string SetTimeUnit(TimeUnit time_unit) {
                switch (time_unit) {
                    case TimeUnit::SECONDS:         return "s";
                    case TimeUnit::MICROSECONDS:    return "μs";
                    case TimeUnit::MILLISECONDS:    return "ms";
                    case TimeUnit::NANOSECONDS:     return "ns";
                    default:                        return "TIME_UNIT_UNKNOWN";
                }
            } 
        private:
            TimePoint m_StartTime;
            TimePoint m_EndTime;
            bool m_IsRunning;
    }; 
} // namespace PerformanceEvaluation
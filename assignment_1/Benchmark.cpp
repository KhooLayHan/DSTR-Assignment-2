#include <iostream>
#include <string>

#include "./Benchmark.hpp"

#include "./SimpleConsoleLogger.hpp"
#include "./SimpleLoggingService.hpp"

namespace PerformanceEvaluation {
    void Benchmark::StartTimer() {
        m_StartTime = Clock::now();
        m_IsRunning = true;
    }

    void Benchmark::EndTimer() {
        if (m_IsRunning == false) {
            SimpleConsoleLogger console;
            SimpleLoggingService::UseWarnLogger(console, "System has not started benchmarking the program.");

            return;
        }   

        m_EndTime = Clock::now();
        m_IsRunning = false;

        Duration();
    }            

    void Benchmark::Duration(TimeUnit time_unit) const {
        using std::chrono::duration_cast;
        
        CheckBenchmarkIsRunning();

        // By default, it should be set to microseconds
        auto duration = duration_cast<Microseconds>(m_EndTime - m_StartTime).count();
        
        // Otherwise,check what unit is preferred and set it accordingly
        switch (time_unit) {
            case TimeUnit::SECONDS:
                duration = duration_cast<Seconds>(m_EndTime - m_StartTime).count(); 
                break;
            case TimeUnit::MICROSECONDS:
                break;
            case TimeUnit::MILLISECONDS:
                duration = duration_cast<Milliseconds>(m_EndTime - m_StartTime).count(); 
                break;
            case TimeUnit::NANOSECONDS:
                duration = duration_cast<Nanoseconds>(m_EndTime - m_StartTime).count(); 
                break;
        }

        std::cout << "\nDuration taken: " << duration << SetTimeUnit(time_unit) << ".\n";
    }

    void Benchmark::DurationSeconds() const {
        CheckBenchmarkIsRunning();  

        auto duration = std::chrono::duration_cast<Seconds>(m_EndTime - m_StartTime).count();
        std::cout << "\nDuration taken: " << duration << "s\n";
    }

    void Benchmark::DurationMicroseconds() const {
        CheckBenchmarkIsRunning();

        auto duration = std::chrono::duration_cast<Microseconds>(m_EndTime - m_StartTime).count();
        std::cout << "\nDuration taken: " << duration << "μs\n";
    }

    void Benchmark::DurationMilliseconds() const {
        CheckBenchmarkIsRunning();

        auto duration = std::chrono::duration_cast<Milliseconds>(m_EndTime - m_StartTime).count();
        std::cout << "\nDuration taken: " << duration << "ms\n";
    }

    void Benchmark::DurationNanoseconds() const {
        CheckBenchmarkIsRunning();

        auto duration = std::chrono::duration_cast<Nanoseconds>(m_EndTime - m_StartTime).count();
        std::cout << "\nDuration taken: " << duration << "ns\n";
    }

    void Benchmark::CheckBenchmarkIsRunning() const {
        if (m_IsRunning == false) 
            return;

        SimpleConsoleLogger console;
        SimpleLoggingService::UseWarnLogger(console, "The benchmark is still running. Stop it to get the duration.");
    }
} // namespace PerformanceEvaluation
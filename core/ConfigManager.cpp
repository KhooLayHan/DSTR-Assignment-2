#include "./ConfigManager.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

// #include "./SimpleConsoleLogger.hpp"

#include "../utils/SimpleFileLogger.hpp"
#include "../utils/SimpleLoggingService.hpp"

#define RESET   "\033[0m"  // Reset color
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

namespace TCMS {
    ConfigManager::ConfigManager() {
        config["DEBUG"] = "0"; // Default: Debugging disabled
        config["LOG_LEVEL"] = "2"; // Default: Set log level to 2
        config["SOURCE_LOCATION_SUPPORTED"] = "1"; // Default: std::source_location is supported 
        config["FILE_SIZE_LIMIT"] = "1048576"; // Default: 1MB in bytes
        config["PLATFORM"] = detectPlatform();
        config["CPP_STANDARD"] = detectCppVersion();

        // Override with environment variables if they exist (only applicable in MacOS or Linux) 
        if (const char* env_debug = std::getenv("DEBUG"))
            config["DEBUG"] = env_debug;
        if (const char* env_log_level = std::getenv("LOG_LEVEL"))
            config["LOG_LEVEL"] = env_log_level;
        if (const char* env_source_location_supported = std::getenv("SOURCE_LOCATION_SUPPORTED"))
            config["SOURCE_LOCATION_SUPPORTED"] = env_source_location_supported;
        if (const char* env_file_size_limit = std::getenv("FILE_SIZE_LIMIT"))
            config["FILE_SIZE_LIMIT"] = env_file_size_limit;
        if (const char* env_platform = std::getenv("PLATFORM"))
            config["PLATFORM"] = env_platform;
        if (const char* env_cpp_standard = std::getenv("CPP_STANDARD"))
            config["CPP_STANDARD"] = env_cpp_standard;
    };

    // Parse command-line arguments of argv 
    void ConfigManager::loadFromArgs(int argc, char** argv) {
        for (int i = 0; i != argc; i++) {
            std::string arg = argv[i];

            // Expect format: [--key=value]
            if (arg.rfind("--", 0) == 0) { // Starts with "--"
                size_t position = arg.find('=');
                
                if (position != std::string::npos) {
                    std::string key = arg.substr(2, position - 2);
                    std::string value = arg.substr(position + 1);

                    config[key] = value;
                }
            }
        }
    };

    void ConfigManager::printConfig() {
        std::cout << "\nSystem is starting.";
        std::cout << "\n[CONFIGURATION SETTINGS]\n";
        
        // std::cout << RED    << "DEBUG: " << RESET << config.get("DEBUG") << "\n";
        // std::cout << GREEN  << "LOG_LEVEL: " << RESET << config.get("LOG_LEVEL") << "\n";
        // std::cout << YELLOW << "SOURCE_LOCATION_SUPPORTED: " << RESET << config.get("SOURCE_LOCATION_SUPPORTED") << "\n";
        // std::cout << BLUE   << "FILE_SIZE_LIMIT: " << RESET << config.get("FILE_SIZE_LIMIT") << "\n";
        std::cout << CYAN   << "PLATFORM: " << RESET << config.get("PLATFORM") << "\n";
        std::cout << GREEN  << "CPP_STANDARD: " << RESET << config.get("CPP_STANDARD") << "\n\n";
    }

    std::string ConfigManager::get(const std::string& key, const std::string& placeholder) {        
        auto it = config.find(key);
        return it ? *it : placeholder;
    };

    int32_t ConfigManager::getInt(const std::string& key, int32_t placeholder) {
        auto it = config.find(key);
        return it ? std::stoi(*it) : placeholder;
    };
    
    bool ConfigManager::getBool(const std::string& key) {
        auto it = config.find(key);
        return it && (*it == "1" || *it == "true");
    }

    void ConfigManager::set(const std::string& key, const std::string& value) {
        config[key] = value;
    };

    void ConfigManager::ensureFileSizeLimit(const std::string& filename) {
        size_t file_size_limit = getInt("FILE_SIZE_LIMIT", 1048576);
        
        if (std::filesystem::exists(filename) && std::filesystem::file_size(filename) > file_size_limit) {
            SimpleFileLogger file;            
            SimpleLoggingService::UseInfoLogger(file, "File " + filename + " exceeds size limit. Deleting and recreating it.");
            
            std::filesystem::remove(filename);
        }
        
        std::ofstream newFile(filename, std::ios::app); // Creates a new file if deleted
    }

    void ConfigManager::destroyFileOnShutdown(const std::string& filename) {
        if (std::filesystem::exists(filename)) {
            SimpleFileLogger file;
            SimpleLoggingService::UseInfoLogger(file, "Deleting file on shutdown: " + filename + ".");
            
            std::filesystem::remove(filename);
        }
    }

    void ConfigManager::createFileOnStartup(const std::string& filename) {
        if (!std::filesystem::exists(filename)) {
            SimpleFileLogger file;            
            SimpleLoggingService::UseInfoLogger(file, "Creating file on startup: " + filename + ".");
            
            std::ofstream newFile(filename);
        }
    }

    std::string ConfigManager::detectPlatform() {
        #if defined(_WIN32)
            return "Windows";
        #elif defined(__linux__)
            return "Linux";
        #elif defined(__APPLE__)
            return "MacOS";
        #else   
            return "Unknown";
        #endif
    }

    std::string ConfigManager::detectCppVersion() {
        #if __cplusplus >= 202002L
            return "C++20";
        #elif __cplusplus >= 201703L
            return "C++17";
        #elif __cplusplus >= 201402L
            return "C++14";
        #elif __cplusplus >= 201103L
            return "C++11";
        #else
            return "Pre-C++11";
        #endif
    }
} // namespace TCMS

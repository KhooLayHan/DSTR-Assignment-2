#pragma once

#include <string>

#include "./HashMap.hpp"
namespace PerformanceEvaluation {    
    class ConfigManager {
        public:
            ConfigManager();

            void LoadFromArgs(int argc, char** argv);

            std::string Get     (const std::string& key, const std::string& placeholder = "");
            int32_t     GetInt  (const std::string& key, int32_t placeholder = 0);
            bool        GetBool (const std::string& key);

            void        Set     (const std::string& key, const std::string& value);
            
            void EnsureFileSizeLimit(const std::string& filename);
        
            void DestroyFileOnShutdown(const std::string& filename);
        
            void CreateFileOnStartup(const std::string& filename);
        
            void PrintConfig();
        private:
            static std::string DetectPlatform();
            static std::string DetectCppVersion();

            HashMap<std::string, std::string> config;
    };
} // namespace PerformanceEvaluation
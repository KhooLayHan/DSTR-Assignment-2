#pragma once

#include <string>

#include "../data_structures/hash_map/HashMap.hpp"

namespace TCMS {    
    class ConfigManager {
        public:
            ConfigManager();

            void loadFromArgs(int argc, char** argv);

            std::string get     (const std::string& key, const std::string& placeholder = "");
            int32_t     getInt  (const std::string& key, int32_t placeholder = 0);
            bool        getBool (const std::string& key);

            void        set     (const std::string& key, const std::string& value);
            
            void ensureFileSizeLimit(const std::string& filename);
        
            void destroyFileOnShutdown(const std::string& filename);
        
            void createFileOnStartup(const std::string& filename);
        
            void printConfig();
        private:
            static std::string detectPlatform();
            static std::string detectCppVersion();

            HashMap<std::string, std::string> config;
    };
} // namespace PerformanceEvaluation
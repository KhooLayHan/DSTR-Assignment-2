#pragma once

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

#include "../data_structures/Vector.hpp"
#include "../models/Player.hpp"

namespace TCMS {
    using FilePath = std::filesystem::path;
    
    class FileHandling {
        public:
            // Default constructor for FileHandling
            FileHandling() {}
        
            // Constructor that initializes the file path
            FileHandling(const FilePath& filePath)
                : m_FilePath(filePath) {}

            // Constructor that moves the file path
            FileHandling(FilePath&& filePath)
                : m_FilePath(std::move(filePath)) {}

            static void readPlayerFile(const FilePath&, Vector<Players>& playersVec);
            
            static void writeFile(const FilePath&, const std::string&);
            
            static void appendFile(const FilePath&, const std::string&);
            static void appendFileNewline(const FilePath&, const std::string&);
            static void appendPlayerFileNewline(const FilePath&, Players players);

            static void checkReadFileValidity(const FilePath&, const std::ifstream&);
            static void checkWriteFileValidity(const FilePath&, const std::ofstream&);
            static void checkAppendFileValidity(const FilePath&, const std::ofstream&);
        protected:
        private:
            FilePath m_FilePath; // Stores the file path associated with this object
    };
} // namespace TCMS
#pragma once

#include <array>
#include <filesystem>
#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

#include "./Array.hpp"
#include "./Dataset.hpp"
#include "./LinkedList.hpp"
#include "./DynamicArray.hpp"

namespace PerformanceEvaluation {
    using FilePath = std::filesystem::path;
    using FilePath = std::filesystem::path;
    class FileHandling {
        public:
            // Default constructor for FileHandling
            FileHandling() {}
        
            // Constructor that initializes the file path
            FileHandling(const FilePath& file_path)
                : m_FilePath(file_path) {}

            // Constructor that moves the file path
            FileHandling(FilePath&& file_path)
                : m_FilePath(std::move(file_path)) {}

            static void ReadFile(const FilePath&, LinkedList&);
            static void ReadFile(const FilePath&, Array<Dataset>&);
            static void ReadFile(const FilePath&, DynamicArray<Dataset>&);
            
            static void WriteFile(const FilePath&, const std::string&);
            
            static void AppendFile(const FilePath&, const std::string&);
            static void AppendFileNewline(const FilePath&, const std::string&);
            
            static void AppendFileContent(const FilePath&, const FilePath&);

            static void CheckReadFileValidity(const FilePath&, const std::ifstream&);
            static void CheckWriteFileValidity(const FilePath&, const std::ofstream&);
            static void CheckAppendFileValidity(const FilePath&, const std::ofstream&);
        protected:
            static Dataset CleanParseAndMoreClean(const std::string&);

            static const std::string CleanField(const std::string&, const std::string&);

            static std::array<std::string, 4> ParseCSVLine(const std::string&);
        private:
            FilePath m_FilePath; // Stores the file path associated with this object
    };
} // namespace PerformanceEvaluation
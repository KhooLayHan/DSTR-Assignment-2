#include <iostream>
#include <string_view>
#include <sstream>

#include "./FileHandling.hpp"

#include "./SimpleFileLogger.hpp"
#include "./SimpleConsoleLogger.hpp"
#include "./SimpleLoggingService.hpp"

namespace PerformanceEvaluation {

    void FileHandling::ReadFile(const FilePath& file_path, LinkedList& linked_list) {
        std::ifstream file(file_path);
        
        CheckReadFileValidity(file_path, file);

        std::string line;

        while (std::getline(file, line)) {
            if (line == "title,text,subject,date" || line == "title,text,subject,date\r") 
                continue;

            const auto& [id, title, text, subject, date] = CleanParseAndMoreClean(line);

            linked_list.InsertEnd({ id, title, text, subject, date });
        }

        file.close();
    }

    void FileHandling::ReadFile(const FilePath& file_path, Array<Dataset>& array) {
        std::ifstream file(file_path);
        
        CheckReadFileValidity(file_path, file);

        std::string line;
        
        while (std::getline(file, line)) {
            if (line == "title,text,subject,date" || line == "title,text,subject,date\r") 
                continue;

            // Parse the line into dataset fields
            const auto& [id, title, text, subject, date] = CleanParseAndMoreClean(line);
            
            // Insert parsed data into the array
            array.InsertEnd({ id, title, text, subject, date });
        }

        file.close();
    }
    
    void FileHandling::ReadFile(const FilePath& file_path, DynamicArray<Dataset>& array) {
        std::ifstream file(file_path);
        
        CheckReadFileValidity(file_path, file);

        std::string line;
        
        while (std::getline(file, line)) {
            if (line == "title,text,subject,date" || line == "title,text,subject,date\r") 
                continue;

            const auto& [id, title, text, subject, date] = CleanParseAndMoreClean(line);

            /// Ensure the array has sufficient capacity
            if (static_cast<size_t>(id) >= array.GetCapacity()) {
                array.Resize(id * 2); // Resize dynamically
            }

            // Insert parsed data into the array
            array.Insert(id, { id, title, text, subject, date });
        }

        file.close();
    }

    void FileHandling::WriteFile(const FilePath& file_path, const std::string& message) {
        std::ofstream file(file_path);
        
        CheckWriteFileValidity(file_path, file);

        file << message;                
        file.close();

        const std::string& ref_file_path = file_path; 

        // SimpleFileLogger file_logger;
        // SimpleLoggingService::UseInfoLogger(file_logger, "Successfully written to file " + ref_file_path + " with message: " + message + ".");
    }
    
    void FileHandling::AppendFile(const FilePath& file_path, const std::string& message) {
        std::ofstream file(file_path, std::ios::app);
        
        CheckAppendFileValidity(file_path, file);

        file << message;                
        file.close();
        
        const std::string& ref_file_path = file_path; 

        // SimpleFileLogger file_logger;
        // SimpleLoggingService::UseInfoLogger(file_logger, "Successfully appended to file " + ref_file_path + " with message: " + message + ".");
    }
    
    void FileHandling::AppendFileNewline(const FilePath& file_path, const std::string& message) {
        std::ofstream file(file_path, std::ios::app);
        
        CheckAppendFileValidity(file_path, file);

        file << message << "\n";                
        file.close();
        
        const std::string& ref_file_path = file_path; 

        // SimpleFileLogger file_logger;
        // SimpleLoggingService::UseInfoLogger(file_logger, "Successfully appended to file " + ref_file_path + " with message: " + message + ".");
    }

    void FileHandling::AppendFileContent(const FilePath& src_file_path, const FilePath& dest_file_path) {
        std::ifstream input_file(src_file_path);
        std::ofstream output_file(dest_file_path, std::ios::app);

        CheckReadFileValidity(src_file_path, input_file);
        CheckWriteFileValidity(dest_file_path, output_file);

        if (std::string line; std::getline(input_file, line)) {
            while (std::getline(input_file, line)) 
                output_file << line << "\n";
        }
        
        const std::string& source = src_file_path;
        const std::string& destination = dest_file_path;

        // SimpleFileLogger file_logger;
        // SimpleLoggingService::UseInfoLogger(file_logger, "Contents of file " + source + " was successfully appended to file " + destination + ".");
        
        input_file.close();
        output_file.close();
    }

    void FileHandling::CheckReadFileValidity(const FilePath& file_path, const std::ifstream& file) {
        const std::string& ref_file_path = file_path;
        
        if (!file) { 
            SimpleConsoleLogger console_logger;
            SimpleLoggingService::UseWarnLogger(console_logger, "Reading file " + ref_file_path + " is not found.");
            
            return; 
        }
    }

    void FileHandling::CheckWriteFileValidity(const FilePath& file_path, const std::ofstream& file) {
        const std::string& ref_file_path = file_path;
        
        if (!file) { 
            SimpleConsoleLogger console_logger;
            SimpleLoggingService::UseWarnLogger(console_logger, "Writing file " + ref_file_path + " is not found.");

            return; 
        }
    }

    void FileHandling::CheckAppendFileValidity(const FilePath& file_path, const std::ofstream& file) {
        const std::string& ref_file_path = file_path;
        
        if (!file) { 
            SimpleConsoleLogger console_logger;
            SimpleLoggingService::UseWarnLogger(console_logger, "Appending file " + ref_file_path + " is not found.");

            return; 
        }
    }

    Dataset FileHandling::CleanParseAndMoreClean(const std::string& line) {        
        const auto& [title, text, subject, date] = ParseCSVLine(line);
        
        Dataset dataset;
        
        dataset.m_Id++;
        dataset.m_Title = CleanField(title, "No Title");
        dataset.m_Text = CleanField(text, "No Text");
        dataset.m_Subject = CleanField(subject, "No Subject");
        dataset.m_Date = CleanField(date, "No Date");

        return dataset;
    }

    const std::string FileHandling::CleanField(const std::string& field, const std::string& placeholder) {
        if (field.empty()) 
            return placeholder;
            
        std::string cleaned;
        for (char character : field) {
            // Keep only non-control characters (e.g., skip \r, \n)
            if (!std::iscntrl(character) || character == '\n') { // Preserve newlines if needed
                cleaned += character;
            }
        }

        // Trim whitespace, carriage returns ('\r'), and newlines ('\n') characters trailing '\r' characters
        cleaned.erase(0, cleaned.find_first_not_of(" \t\r\n")); // Trim leading
        cleaned.erase(cleaned.find_last_not_of(" \t\r\n") + 1); // Trim trailing
        
        return cleaned;
    }


    std::array<std::string, 4> FileHandling::ParseCSVLine(const std::string& line) {
        static constexpr size_t MAX_FIELD_SIZE = 4;
        
        std::array<std::string, 4> fields;

        size_t field_index = 0;
        std::string token;
        bool in_quotes = false;
        bool escape_next = false;

        for (size_t i = 0; i < line.size(); ++i) {
            char character = line[i];
    
            if (escape_next) {
                token += character;
                escape_next = false;
            } else if (character == '\\') {
                escape_next = true;
            } else if (character == '"') {
                in_quotes = !in_quotes;
            } else if (character == ',' && !in_quotes) {
                if (field_index < MAX_FIELD_SIZE)
                    fields[field_index++] = token;
                token.clear();
            } else {
                token += character;
            }
        }
    
        // If there are more than 4 fields, then error!
        if (field_index > MAX_FIELD_SIZE - 1) {
            // std::cout << token << "\n";
            // SimpleConsoleLogger console;
            // SimpleLoggingService::UseFatalLogger(console, "Unexpected number of fields in line; field_index == " + field_index + '.');
        }
        
        // Add the last field
        if (field_index < MAX_FIELD_SIZE)
            fields[field_index] = token;
        
        return { fields };
    }
}
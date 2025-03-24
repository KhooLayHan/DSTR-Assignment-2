#include <iostream>
#include <string_view>
#include <sstream>

#include "./FileHandling.hpp"
#include "../controllers/PlayerManager.hpp"

#include "../utils/SimpleFileLogger.hpp"
#include "../utils/SimpleLoggingService.hpp"

namespace TCMS {

    // Load players from file
    void FileHandling::readPlayerFile(const FilePath& filePath, Vector<Players>& playersVec) {
        std::ifstream file(filePath);

        if (!file)
        {
            SimpleFileLogger fileLogger;
            SimpleLoggingService::UseWarnLogger(fileLogger, "Reading file " + filePath.string() + " is not found.");
            return;
        }

        std::string line;
        std::getline(file, line); // Skip the header

        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string uid, name, skillLevelStr, nationality, ageStr, gender, rankingStr;

            std::getline(ss, uid, ',');
            std::getline(ss, name, ',');
            std::getline(ss, skillLevelStr, ',');
            std::getline(ss, nationality, ',');
            std::getline(ss, ageStr, ',');
            std::getline(ss, gender, ',');
            std::getline(ss, rankingStr, ',');

            int32_t skillLevel = std::stoi(skillLevelStr);
            int32_t age = std::stoi(ageStr);
            int32_t ranking = std::stoi(rankingStr);

            // Create a new Player object and add it to the playersVec
            auto player = std::make_shared<Player>(name, skillLevel, nationality, age, gender, ranking);
            playersVec.emplaceBack(player); // Add the player to the vector
        }

        file.close();

        SimpleFileLogger fileLogger;
        SimpleLoggingService::UseInfoLogger(fileLogger, "Player data loaded from " + filePath.string() + "\n");
    }

    void FileHandling::writeFile(const FilePath& filePath, const std::string& message) {
        std::ofstream file(filePath);
        
        checkWriteFileValidity(filePath, file);

        file << message;                
        file.close();

        const std::string& refFilePath = filePath; 

        // SimpleFileLogger file_logger;
        // SimpleLoggingService::UseInfoLogger(file_logger, "Successfully written to file " + refFilePath + " with message: " + message + ".");
    }
    
    void FileHandling::appendFile(const FilePath& filePath, const std::string& message) {
        std::ofstream file(filePath, std::ios::app);
        
        checkAppendFileValidity(filePath, file);

        file << message;                
        file.close();
        
        const std::string& refFilePath = filePath; 

        // SimpleFileLogger file_logger;
        // SimpleLoggingService::UseInfoLogger(file_logger, "Successfully appended to file " + refFilePath + " with message: " + message + ".");
    }
    
    void FileHandling::appendFileNewline(const FilePath& filePath, const std::string& message) {
        std::ofstream file(filePath, std::ios::app);
        
        checkAppendFileValidity(filePath, file);

        file << message << "\n";                
        file.close();
        
        const std::string& refFilePath = filePath; 

        // SimpleFileLogger file_logger;
        // SimpleLoggingService::UseInfoLogger(file_logger, "Successfully appended to file " + refFilePath + " with message: " + message + ".");
    }
    
    void FileHandling::appendPlayerFileNewline(const FilePath& filePath, Players players) {
        std::ofstream file(filePath, std::ios::app);
        
        checkAppendFileValidity(filePath, file);

        // UID,Name,SkillLevel,Nationality,Age,Gender,Ranking

        file << players->getUID() << "," << players->getName() << "," << std::to_string(players->getSkillLevel()) << "," << 
            players->getNationality() << "," << std::to_string(players->getAge()) << "," << players->getGender() << "," <<
            std::to_string(players->getRanking()) << "\n";                
        
            file.close();
        
        const std::string& refFilePath = filePath; 

        // SimpleFileLogger file_logger;
        // SimpleLoggingService::UseInfoLogger(file_logger, "Successfully appended to file " + refFilePath + " with message: " + message + ".");
    }

    void FileHandling::checkReadFileValidity(const FilePath& filePath, const std::ifstream& file) {
        const std::string& refFilePath = filePath;
        
        if (!file) { 
            SimpleFileLogger fileLogger;
            SimpleLoggingService::UseWarnLogger(fileLogger, "Reading file " + refFilePath + " is not found.");
            
            return; 
        }
    }

    void FileHandling::checkWriteFileValidity(const FilePath& filePath, const std::ofstream& file) {
        const std::string& refFilePath = filePath;
        
        if (!file) { 
            SimpleFileLogger fileLogger;
            SimpleLoggingService::UseWarnLogger(fileLogger, "Writing file " + refFilePath + " is not found.");

            return; 
        }
    }

    void FileHandling::checkAppendFileValidity(const FilePath& filePath, const std::ofstream& file) {
        const std::string& refFilePath = filePath;
        
        if (!file) { 
            SimpleFileLogger fileLogger;
            SimpleLoggingService::UseWarnLogger(fileLogger, "Appending file " + refFilePath + " is not found.");

            return; 
        }
    }
} // namespace TCMS
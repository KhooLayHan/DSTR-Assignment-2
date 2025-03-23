#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "../LinkedLists/SinglyLinkedList.hpp"
#include "../DataStructures/Queue.hpp"
#include "../DataStructures/Stack.hpp"
#include "../models/MatchRecord.hpp"
#include "../models/Player.hpp" // From Task 1

namespace TCMS
{
    class MatchHistoryTracker
    {
    public:
        MatchHistoryTracker()
        {
            loadMatchHistory();
        }

        void addMatchHistory(const std::string &player1, const std::string &player2, int score1, int score2)
        {
            auto match = std::make_shared<MatchRecord>(player1, player2, score1, score2);
            m_HistoryQueue.enqueue(match);
            m_HistoryStack.push(match);
            m_HistoryList.insertEnd(match); // Store in Linked List

            saveMatchHistoryToFile();
        }

        // Integration with Task 1: Record match using Player objects
        void addMatchFromPlayers(const Player &player1, const Player &player2)
        {
            auto match = std::make_shared<MatchRecord>(player1, player2);
            m_HistoryQueue.enqueue(match);
            m_HistoryStack.push(match);
            m_HistoryList.insertEnd(match);

            std::ofstream file("match_history.txt", std::ios::app);
            if (file.is_open())
            {
                file << match->toFileString() << "\n";
                file.close();
            }
        }

        void displayAllHistory()
        {
            if (m_HistoryList.isEmpty())
            {
                std::cout << "\033[1;31m❌ No match history available.\033[0m\n";
                return;
            }

            std::cout << "\n----- Match History -----\n";
            int matchCount = 1;
            auto current = m_HistoryList.getHead();
            while (current)
            {
                std::cout << "Match " << matchCount++ << ": " << current->getData()->getMatchDetails() << "\n";
                current = current->getNext();
            }
        }

        std::string retrieveHistory(int position)
        {
            if (m_HistoryList.isEmpty() || position <= 0)
            {
                return "\033[1;31m❌ No match history available.\033[0m";
            }

            auto current = m_HistoryList.getHead();
            int index = 1;
            while (current)
            {
                if (index == position)
                {
                    return current->getData()->getMatchDetails();
                }
                current = current->getNext();
                index++;
            }

            return "\033[1;31m❌ Error: Match not found!\033[0m";
        }

        void updateMatch(int position, const std::string &player1, const std::string &player2, int score1, int score2)
        {
            if (m_HistoryList.isEmpty() || position <= 0)
            {
                std::cout << "\033[1;31m❌ No match history available or invalid position.\033[0m\n";
                return;
            }

            auto current = m_HistoryList.getHead();
            int index = 1;
            std::shared_ptr<MatchRecord> matchToUpdate = nullptr;

            // Find the match to update
            while (current)
            {
                if (index == position)
                {
                    matchToUpdate = current->getData();
                    break;
                }
                current = current->getNext();
                index++;
            }

            if (!matchToUpdate)
            {
                std::cout << "\033[1;31m❌ Error: Match not found!\033[0m\n";
                return;
            }

            // Update match details
            matchToUpdate->setPlayer1(player1);
            matchToUpdate->setPlayer2(player2);
            matchToUpdate->setScore1(score1);
            matchToUpdate->setScore2(score2);

            // Update the file
            saveMatchHistoryToFile();

            std::cout << "\033[1;33m🔄 Match updated: " << matchToUpdate->getMatchDetails() << "\033[0m\n";
        }

        void undoLastMatch()
        {
            if (m_HistoryStack.isEmpty() || m_HistoryList.isEmpty())
            {
                std::cout << "\033[1;31m❌ No match to undo!\033[0m\n";
                return;
            }

            auto lastMatch = m_HistoryStack.pop(); // Remove from stack
            m_HistoryQueue.dequeue();              // Remove from queue
            m_HistoryList.removeEnd();             // Remove from linked list

            // Remove last line from the file
            std::ifstream file("match_history.txt");
            std::ofstream tempFile("temp.txt");

            std::string line;
            int totalLines = 0;
            while (std::getline(file, line))
                totalLines++; // Count lines

            file.clear();
            file.seekg(0);
            int index = 0;
            while (std::getline(file, line))
            {
                if (++index < totalLines) // Write all lines except the last one
                    tempFile << line << "\n";
            }

            file.close();
            tempFile.close();
            std::remove("match_history.txt");
            std::rename("temp.txt", "match_history.txt");

            std::cout << "\033[1;33m🔄 Match undone: " << lastMatch->getMatchDetails() << "\033[0m\n";
            std::cout << "\033[1;33m🔄 Last match undone successfully.\033[0m\n";
        }

        void deleteMatch(int position)
        {
            if (m_HistoryList.isEmpty() || position <= 0)
            {
                std::cout << "\033[1;31m❌ No match history available or invalid position.\033[0m\n";
                return;
            }

            auto current = m_HistoryList.getHead();
            int index = 1;
            std::shared_ptr<MatchRecord> matchToDelete = nullptr;

            // Find the match to delete
            while (current)
            {
                if (index == position)
                {
                    matchToDelete = current->getData();
                    break;
                }
                current = current->getNext();
                index++;
            }

            if (!matchToDelete)
            {
                std::cout << "\033[1;31m❌ Error: Match not found!\033[0m\n";
                return;
            }

            // Remove from stack
            Stack<std::shared_ptr<MatchRecord>> tempStack;
            while (!m_HistoryStack.isEmpty())
            {
                auto lastMatch = m_HistoryStack.pop();
                if (lastMatch != matchToDelete)
                {
                    tempStack.push(lastMatch);
                }
            }
            // Restore the stack without the deleted match
            while (!tempStack.isEmpty())
            {
                m_HistoryStack.push(tempStack.pop());
            }

            // Remove from queue
            Queue<std::shared_ptr<MatchRecord>> tempQueue;
            while (!m_HistoryQueue.isEmpty())
            {
                auto lastMatch = m_HistoryQueue.dequeue();
                if (lastMatch != matchToDelete)
                {
                    tempQueue.enqueue(lastMatch);
                }
            }
            // Restore the queue without the deleted match
            while (!tempQueue.isEmpty())
            {
                m_HistoryQueue.enqueue(tempQueue.dequeue());
            }

            // Remove from linked list
            m_HistoryList.remove(matchToDelete);

            // Update the file
            saveMatchHistoryToFile();

            std::cout << "\033[1;33m🔄 Match deleted: " << matchToDelete->getMatchDetails() << "\033[0m\n";
        }

        std::shared_ptr<MatchRecord> retrieveMatch(int position)
        {
            if (m_HistoryList.isEmpty() || position <= 0)
            {
                return nullptr; // Return nullptr if the list is empty or position is invalid
            }

            auto current = m_HistoryList.getHead(); // Get the head of the linked list
            int index = 1;                          // Start indexing from 1

            // Traverse the linked list to find the match at the specified position
            while (current)
            {
                if (index == position)
                {
                    return current->getData(); // Return the match record at the specified position
                }
                current = current->getNext(); // Move to the next node
                index++;
            }

            return nullptr; // Return nullptr if the position is out of bounds
        }

    private:
        Queue<std::shared_ptr<MatchRecord>> m_HistoryQueue;
        Stack<std::shared_ptr<MatchRecord>> m_HistoryStack;
        SinglyLinkedList<std::shared_ptr<MatchRecord>> m_HistoryList;

        void loadMatchHistory()
        {
            std::ifstream file("match_history.txt");
            if (!file.is_open())
                return;

            std::string line;
            while (std::getline(file, line))
            {
                auto match = MatchRecord::fromFileString(line);
                m_HistoryQueue.enqueue(match);
                m_HistoryStack.push(match);
                m_HistoryList.insertEnd(match);
            }
            file.close();
        }

        void saveMatchHistoryToFile()
        {
            std::ofstream file("match_history.txt");
            if (!file.is_open())
                return;

            auto current = m_HistoryList.getHead();
            while (current)
            {
                file << current->getData()->toFileString() << "\n";
                current = current->getNext();
            }
            file.close();
        }
    };
} // namespace TCMS

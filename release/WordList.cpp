#include <iostream>

#include "./SimpleConsoleLogger.hpp"
#include "./SimpleFileLogger.hpp"
#include "./SimpleLoggingService.hpp"

#include "./WordList.hpp"

namespace PerformanceEvaluation {
    
    void WordList::InsertBegin(const std::string& data) {
        WordListNode* node = new WordListNode(data);
        node->m_Next = m_Head;
        m_Head = node;
        
        IncrementLength();
    }
            
    void WordList::InsertEnd(const std::string& data) {
        WordListNode* node = new WordListNode(data);

        if (m_Head == nullptr) {
            m_Head = node;
            
            IncrementLength();

            return;
        }

        WordListNode* temp = m_Head;
        
        while (temp->m_Next != nullptr) {
            temp = temp->m_Next;
        }

        temp->m_Next = node;

        IncrementLength();
    }

    void WordList::InsertPosition(const std::string& data, size_t position) {
        WordListNode* node = new WordListNode(data);
    
        if (position == 0) {
            InsertBegin(std::move(data));
            return;
        }

        WordListNode* temp = m_Head;
        for (size_t i = 0; temp != nullptr && i < position - i; i++) 
            temp = temp->m_Next;

        if (temp == nullptr) {
            
            // SimpleFileLogger file_logger;
            // SimpleLoggingService::
            // SimpleLogger::Fatal("Position is out of bounds.", LogHandler::FILE);
            
            delete node;
            node = nullptr;

            return;
        }

        node->m_Next = temp->m_Next;
        temp->m_Next = node;

        IncrementLength();
    }
        
    void WordList::DisplayAll() const {
        IsHeadEmpty();

        WordListNode* temp = m_Head;

        while (temp != nullptr) {
            std::cout << "\n" << temp->m_Data << "\n";
            
            std::cout << "\n-----------\n";
            temp = temp->m_Next;
        } 

        std::cout << "\n";
    }
    
    size_t WordList::GetLength() const {
        size_t length = 0;
        WordListNode* temp = m_Head;
        
        while (temp) {
            length++;
            temp = temp->m_Next;
        }
        
        return length;
    }

    void WordList::DeleteNode(const std::string& dataset) {
        if (m_Head == nullptr) {
            // SimpleLogger::Warn("List is empty.", LogHandler::FILE);
            return;
        }

        // Deleting m_Head node scenario
        if (m_Head->m_Data == dataset) {
            WordListNode* temp = m_Head;
            m_Head = m_Head->m_Next;
            
            delete temp;
            temp = nullptr;

            // assert(temp != nullptr && "Attempted to delete from a linked list.");

            DecrementLength();

            return;
        }

        // Deleting middle or end node scenario
        WordListNode* temp = m_Head;
        
        while (temp->m_Next != nullptr && !(temp->m_Next->m_Data == dataset)) {
            temp = temp->m_Next;
        }

        if (temp->m_Next == nullptr) { 
            // SimpleLogger::Warn("Value cannot be found in the list.", LogHandler::FILE);
            return;
        }

        // Node to be deleted
        WordListNode* node = temp->m_Next;
        temp->m_Next = temp->m_Next->m_Next;
        
        delete node;
        node = nullptr;

        DecrementLength();
    }

    void WordList::DeleteAll() {
        WordListNode* current = m_Head;

        while (current != nullptr) {
            WordListNode* temp = current;
            current = current->m_Next;
            
            // SimpleLogger::Info("Node has been deleted." + temp->m_Data.title, LogHandler::CONSOLE);
            delete temp;
            temp = nullptr;

            DecrementLength();
        }

        m_Head = nullptr;
        // SimpleLogger::Info("All nodes has been deleted.", LogHandler::FILE);
    }

    WordListNode* WordList::GetHead() const {
        return m_Head;
    }

    void WordList::SetHead(WordListNode* new_head) {
        m_Head = new_head;
    }

    void WordList::DecrementLength() {
        if (m_Length > 0)
            m_Length--;
    }

    void WordList::IncrementLength() {
        m_Length++;
    }

    bool WordList::Contains(const std::string& m_Data, std::string_view target) const {
        return m_Data.find(target) != std::string::npos;
    }

    void WordList::IsHeadEmpty() const {
        if (m_Head == nullptr) {
            // SimpleLogger::Warn("The linked list is empty.", LogHandler::FILE);
            return;
        }
    }

    void WordList::IsHeadOrNextEmpty() const {
        if (m_Head == nullptr || m_Head->m_Next == nullptr) {
            // SimpleLogger::Warn("The linked list is empty.", LogHandler::FILE);
            return;
        }
    }
} // namespace PerformanceEvaluation
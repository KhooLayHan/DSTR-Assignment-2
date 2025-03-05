#include <iostream>
#include <string>
#include <string_view>
#include <memory>

#include "./DateUtility.hpp"
#include "./SimpleLogger.hpp"

#include "./SimpleConsoleLogger.hpp"
#include "./SimpleFileLogger.hpp"
#include "./SimpleLoggingService.hpp"

#include "./LinkedList.hpp"

namespace PerformanceEvaluation {
    
    // Insert a new node at the beginning of the linked list.
    void LinkedList::InsertBegin(const Dataset& data) {
        LinkedListNode* node = new LinkedListNode(data);
        node->m_Next = m_Head;
        m_Head = node;
        
        IncrementLength();
    }
            
    // Insert a new node at the end of the linked list.
    void LinkedList::InsertEnd(const Dataset& data) {
        LinkedListNode* node = new LinkedListNode(data);

        if (m_Head == nullptr) {
            m_Head = node;
            
            IncrementLength();

            return;
        }

        LinkedListNode* temp = m_Head;
        
        while (temp->m_Next != nullptr) {
            temp = temp->m_Next;
        }

        temp->m_Next = node;

        IncrementLength();
    }

    // Insert a node at a specific position in the linked list.
    void LinkedList::InsertPosition(const Dataset& data, size_t position) {
        LinkedListNode* node = new LinkedListNode(data);

        if (position == 0) {
            InsertBegin(std::move(data));
            return;
        }

        LinkedListNode* temp = m_Head;
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
        
    // Display all nodes in the linked list.
    void LinkedList::DisplayAll() const {
        IsHeadEmpty();

        LinkedListNode* temp = m_Head;

        while (temp != nullptr) {
            std::cout << "\n\033[34;1mID:\033[0m "       << temp->m_Data.m_Id      << "\n";
            std::cout << "\033[34;1mTITLE:\033[0m "      << temp->m_Data.m_Title   << "\n";
            std::cout << "\033[34;1mTEXT:\033[0m "       << temp->m_Data.m_Text    << "\n";
            std::cout << "\033[34;1mSUBJECT:\033[0m "    << temp->m_Data.m_Subject << "\n";
            std::cout << "\033[34;1mDATE:\033[0m "       << temp->m_Data.m_Date    << "\n";
            
            std::cout << "\n-----------\n";

            temp = temp->m_Next;
        } 

        std::cout << "\n";
    }
    
    // Display the first 'count' nodes in the linked list.
    void LinkedList::DisplayFirst(int32_t count) const {
        IsHeadEmpty();

        LinkedListNode* temp = m_Head;

        int32_t line = 0;

        while (temp != nullptr && line != count) {
            std::cout << "\n\033[34;1mID:\033[0m "       << temp->m_Data.m_Id      << "\n";
            std::cout << "\033[34;1mTITLE:\033[0m "      << temp->m_Data.m_Title   << "\n";
            std::cout << "\033[34;1mTEXT:\033[0m "       << temp->m_Data.m_Text    << "\n";
            std::cout << "\033[34;1mSUBJECT:\033[0m "    << temp->m_Data.m_Subject << "\n";
            std::cout << "\033[34;1mDATE:\033[0m "       << temp->m_Data.m_Date    << "\n";
            
            std::cout << "\n-----------\n";

            temp = temp->m_Next;

            line++;
        } 

        std::cout << "\n";
    }

    // Display only the titles of all nodes.
    void LinkedList::DisplayTitle() const {
        IsHeadEmpty();

        LinkedListNode* temp = m_Head;

        std::cout << "TITLE\n-----------\n";
        
        while (temp != nullptr) {
            std::cout << "\n\033[34;1mTITLE:\033[0m "      << temp->m_Data.m_Title   << "\n";
            std::cout << "\n-----------\n";

            temp = temp->m_Next;
        } 
        
        std::cout << "\n";
    }

    // Display only the text of all nodes.
    void LinkedList::DisplayText() const {
        IsHeadEmpty();

        LinkedListNode* temp = m_Head;

        std::cout << "TEXT\n-----------\n";

        while (temp != nullptr) {
            std::cout << "\n\033[34;1mTEXT:\033[0m "      << temp->m_Data.m_Text   << "\n";
            std::cout << "\n-----------\n";

            temp = temp->m_Next;
        } 

        std::cout << "\n";
    }
        
    // Display only the subject of all nodes.
    void LinkedList::DisplaySubject() const {
        IsHeadEmpty();

        LinkedListNode* temp = m_Head;
        
        std::cout << "SUBJECT\n-----------\n";
        
        while (temp != nullptr) {
            std::cout << "\n\033[34;1mSUBJECT:\033[0m "      << temp->m_Data.m_Subject   << "\n";
            std::cout << "\n-----------\n";

            temp = temp->m_Next;
        } 

        std::cout << "\n";
    }

    void LinkedList::DisplayDate() const {
        IsHeadEmpty();

        LinkedListNode* temp = m_Head;

        std::cout << "DATE\n-----------\n";

        while (temp != nullptr) {
            std::cout << "\n\033[34;1mDATE:\033[0m "      << temp->m_Data.m_Date   << "\n";
            std::cout << "\n-----------\n";
            // std::visit(DisplayDateVis{}, temp->m_Data);
            temp = temp->m_Next;
        } 

        std::cout << "\n";
    }

    void LinkedList::DisplayLength(std::string_view file_path) const {
        std::cout << "The total number of articles from the " << file_path << " dataset is "
            << GetLength() << ".\n";
    }

    size_t LinkedList::GetLength() const {
        size_t length = 0;
        LinkedListNode* temp = m_Head;
        
        while (temp) {
            length++;
            temp = temp->m_Next;
        }
        
        return length;
    }

    // Delete a node containing a specific dataset.
    void LinkedList::DeleteNode(const Dataset& dataset) {
        if (m_Head == nullptr) {
            // SimpleLogger::Warn("List is empty.", LogHandler::FILE);
            return;
        }

        // Deleting m_Head node scenario
        if (m_Head->m_Data == dataset) {
            LinkedListNode* temp = m_Head;
            m_Head = m_Head->m_Next;
            
            delete temp;
            temp = nullptr;

            // assert(temp != nullptr && "Attempted to delete from a linked list.");

            DecrementLength();

            return;
        }

        // Deleting middle or end node scenario
        LinkedListNode* temp = m_Head;
        
        while (temp->m_Next != nullptr && !(temp->m_Next->m_Data == dataset)) {
            temp = temp->m_Next;
        }

        if (temp->m_Next == nullptr) { 
            // SimpleLogger::Warn("Value cannot be found in the list.", LogHandler::FILE);
            return;
        }

        // Node to be deleted
        LinkedListNode* node = temp->m_Next;
        temp->m_Next = temp->m_Next->m_Next;
        
        delete node;
        node = nullptr;

        DecrementLength();
    }

    // Delete all nodes in the linked list.
    void LinkedList::DeleteAll() {
        LinkedListNode* current = m_Head;

        while (current != nullptr) {
            LinkedListNode* temp = current;
            current = current->m_Next;
            
            // SimpleLogger::Info("Node has been deleted." + temp->m_Data.title, LogHandler::CONSOLE);
            delete temp;
            temp = nullptr;

            DecrementLength();
        }

        m_Head = nullptr;
        // SimpleLogger::Info("All nodes has been deleted.", LogHandler::FILE);
    }

    // Get the head node of the linked list.
    LinkedListNode* LinkedList::GetHead() const {
        return m_Head;
    }

    // Set a new head node.
    void LinkedList::SetHead(LinkedListNode* new_head) {
        m_Head = new_head;
    }

    // Decrease the length of the linked list.
    void LinkedList::DecrementLength() {
        if (m_Length > 0)
            m_Length--;
    }

     // Increase the length of the linked list.
    void LinkedList::IncrementLength() {
        m_Length++;
    }

    // Check if the given string contains the target substring.
    bool LinkedList::Contains(const std::string& m_Data, std::string_view target) const {
        return m_Data.find(target) != std::string::npos;
    }

    // Check if the head node is empty.
    void LinkedList::IsHeadEmpty() const {
        if (m_Head == nullptr) {
            // SimpleLogger::Warn("The linked list is empty.", LogHandler::FILE);
            return;
        }
    }

    // Check if the head or next node is empty.
    void LinkedList::IsHeadOrNextEmpty() const {
        if (m_Head == nullptr || m_Head->m_Next == nullptr) {
            // SimpleLogger::Warn("The linked list is empty.", LogHandler::FILE);
            return;
        }
    }
} // namespace PerformanceEvaluation
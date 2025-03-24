// model/VenueSection.hpp
#pragma once

#include <iostream>
#include <string>

#include "../data_structures/Vector.hpp"
#include "../core/UUID.hpp"
#include "./Spectator.hpp"

namespace TCMS {
    class VenueSection {
    public:
        VenueSection(const std::string& name, size_t capacity)
            : m_SectionId(UUID().toString()), 
              m_Name(name), 
              m_Capacity(capacity), 
              m_CurrentOccupancy(0) {}
    
        ~VenueSection() {
            // std::cout << "VenueSection " << m_Name << " destroyed.\n";
        }
    
        std::string getSectionId() const { 
            return m_SectionId; 
        }
        
        std::string getName() const { 
            return m_Name; 
        }
        
        size_t getCapacity() const { 
            return m_Capacity; 
        }
        
        size_t getCurrentOccupancy() const { 
            return m_CurrentOccupancy; 
        }
        
        bool isFull() const { 
            return m_CurrentOccupancy >= m_Capacity; 
        }
    
        bool addSpectator(Spectator* spectator) {
            if (isFull()) return false;
            
            m_Spectators.pushBack(spectator);  // Changed from push_back to pushBack
            m_CurrentOccupancy++;
            return true;
        }
    
        bool removeSpectator(const std::string& spectatorId) {
            // Manual iteration since custom Vector doesn't have iterator-based erase
            for (size_t i = 0; i < m_Spectators.getLength(); i++) {
                if (m_Spectators[i]->getSpectatorId() == spectatorId) {
                    // Shift elements to remove the spectator
                    for (size_t j = i; j < m_Spectators.getLength() - 1; j++) {
                        m_Spectators[j] = m_Spectators[j + 1];
                    }
                    m_Spectators.popBack();  // Remove the last element (duplicate)
                    m_CurrentOccupancy--;
                    return true;
                }
            }
            return false;
        }
    
        void displayInfo() const {
            std::cout << "Section " << m_Name << " (ID: " << m_SectionId << ")\n";
            std::cout << "Capacity: " << m_Capacity << "\n";
            std::cout << "Current Occupancy: " << m_CurrentOccupancy << "\n";
            std::cout << "Available Seats: " << (m_Capacity - m_CurrentOccupancy) << "\n";
        }
        
    private:
        std::string m_SectionId;
        std::string m_Name;
        size_t m_Capacity;
        size_t m_CurrentOccupancy;
        Vector<Spectator*> m_Spectators;  // Changed from std::vector to custom Vector
    };
    
} // namespace TCMS
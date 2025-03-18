#include <iostream>
#include "controllers/TicketingMenu.hpp"

int main() {
    try {
        std::cout << "Starting Asia Pacific University Tennis Championship Ticketing System...\n";
        
        // Create and run the ticketing menu
        TCMS::TicketingMenu menu;
        menu.run();
        
        std::cout << "Program terminated successfully.\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return 2;
    }
}
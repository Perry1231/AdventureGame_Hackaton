#include "Header.h"

void Deleter()
{
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│                   DELETE SAVES                  │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    
    std::cout << "Available saves:\n";
    // TODO: List available save files
    
    std::cout << "\nEnter save name to delete: ";
    std::string saveName;
    std::cin >> saveName;
    
    // TODO: Delete save file
    
    std::cout << "Save deleted successfully!\n";
}
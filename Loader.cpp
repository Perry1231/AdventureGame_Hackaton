#include "Header.h"
#include <fstream>

void Loader(Character& hero, MyInventory& inv)
{
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│                  LOAD GAME                      │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    
    std::cout << "Enter save name (without extension): ";
    std::string saveName;
    std::cin >> saveName;
    
    std::ifstream loadFile("saves/" + saveName + ".txt");
    if (!loadFile) {
        std::cout << "Failed to load save file!\n";
        return;
    }
    
    std::string line;
    while (std::getline(loadFile, line)) {
        std::cout << line << std::endl;
    }
    
    loadFile.close();
    std::cout << "Game loaded successfully!\n";
}
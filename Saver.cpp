#include "Header.h"
#include <fstream>

void Saver(Character& hero, MyInventory& inv, GameHard& difficultyLevel)
{
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│                  SAVE GAME                      │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    
    std::cout << "Enter save name (without extension): ";
    std::string saveName;
    std::cin >> saveName;
    
    std::ofstream saveFile("saves/" + saveName + ".txt");
    if (!saveFile) {
        std::cout << "Failed to create save file!\n";
        return;
    }
    
    saveFile << "Character:\n";
    saveFile << "Name: " << hero.GetName() << "\n";
    saveFile << "Health: " << hero.GetHealth() << "\n";
    saveFile << "Gold: " << hero.GetGold() << "\n";
    saveFile << "Level: " << hero.GetLevel() << "\n";
    
    saveFile << "\nInventory:\n";
    for (int i = 0; i < inv.GetCount(); i++)
    {
        Item* item = inv.GetItem(i);
        if (item) {
            saveFile << "Item #" << (i + 1) << ": " << item->GetName() << " [" << item->GetType() << "]\n";
        }
    }
    saveFile << "\nDifficulty: " << difficultyLevel.GetDifficultyLevel() << "\n";
    
    saveFile.close();
    std::cout << "Game saved successfully!\n";

}
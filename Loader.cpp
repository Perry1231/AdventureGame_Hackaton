#include "Header.h"
#include <fstream>
#include <sstream>

void Loader(Character& hero, MyInventory& inv, GameHard& difficultyLevel, Quest& quest)
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
    std::string section = "";
    int health = 0, gold = 0;
    float level = 1.0f;
    int difficulty = 1;
    
    while (std::getline(loadFile, line)) {
        if (line.empty()) continue;
        
        // Detect sections
        if (line.find("Character:") != std::string::npos) {
            section = "Character";
            continue;
        } else if (line.find("Inventory:") != std::string::npos) {
            section = "Inventory";
            continue;
        } else if (line.find("Quests:") != std::string::npos) {
            section = "Quests";
            continue;
        } else if (line.find("Difficulty:") != std::string::npos) {
            section = "Difficulty";
            continue;
        }
        
        // Parse key: value
        size_t colonPos = line.find(": ");
        if (colonPos == std::string::npos) continue;
        
        std::string key = line.substr(0, colonPos);
        std::string value = line.substr(colonPos + 2);
        
        if (section == "Character") {
            if (key == "Health") health = std::stoi(value);
            else if (key == "Gold") gold = std::stoi(value);
            else if (key == "Level") level = std::stof(value);
        } else if (section == "Difficulty") {
            difficulty = std::stoi(value);
        }
    }
    
    // Apply loaded values
    hero.SetHealth(health);
    hero.SetGold(gold);
    hero.SetLevel(level);
    difficultyLevel.SetDifficultyLevel(difficulty);
    
    loadFile.close();
    std::cout << "Game loaded successfully!\n";
    std::cout << "Health: " << health << ", Gold: " << gold 
              << ", Level: " << level << ", Difficulty: " << difficulty << "\n";
}

void ListSaveFilesLoader()
{
    std::cout << "Available saves:\n";
    // This would require filesystem access - simplified for now
    std::cout << "  (Feature requires <filesystem> header)\n";
}
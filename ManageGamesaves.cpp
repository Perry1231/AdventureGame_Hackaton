#include "Header.h"

void ManageGamesaves(Character& hero, MyInventory& inv, GameHard& difficultyLevel)
{
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│                MANAGE GAME SAVES               │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    std::cout << "│  1. Save game                                   │\n";
    std::cout << "│  2. Load game                                   │\n";
    std::cout << "│  0. Back to main menu                           │\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
    std::cout << "Choice: ";
    
    int choice = ChoiceInput_Number();
    
    switch (choice) {
        case 1:
            Saver(hero, inv, difficultyLevel);
            break;
        case 2:
            Loader(hero, inv);
            break;
        case 0:
            break;
        default:
            std::cout << "\n[!] Invalid choice!\n";
            break;
    }
}
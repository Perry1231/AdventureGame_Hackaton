#include "Header.h"
#include <iostream>
#include <string>
#include <limits>


void HelpFunction() 
{
    // ANSI Color Codes
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string CYAN    = "\033[36m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";

    std::cout << "\n" << CYAN << "┌─────────────────────────────────────────────────────────┐\n";
    std::cout << "│ " << BOLD << YELLOW << "                    GAME HELP MENU                       " << RESET << CYAN << "│\n";
    std::cout << "├─────────────────────────────────────────────────────────┤" << RESET << "\n";
    std::cout << "  " << GREEN << "[INFO]" << RESET << " Used to display help information and game instructions.\n";
    std::cout << "  " << GREEN << "[GAME]" << RESET << " Shows how to structure a C++ adventure game.\n";
    std::cout << "  " << GREEN << "[DEV ]" << RESET << " Developed by: " << BOLD << "Vladyslav Vytrykush" << RESET << "\n";
    std::cout << CYAN << "└─────────────────────────────────────────────────────────┘" << RESET << "\n\n";
}


void GameHard::ChoiceHard(Enemy& enemy) 
{
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string CYAN    = "\033[36m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string RED     = "\033[31m";

    std::cout << "\n" << CYAN << "┌───────────────────────────────────────────────────┐\n";
    std::cout << "│ " << BOLD << YELLOW << "             SELECT DIFFICULTY LEVEL               " << RESET << CYAN << "│\n";
    std::cout << "├───────────────────────────────────────────────────┤" << RESET << "\n";
    std::cout << "  " << GREEN  << "1. Easy"   << RESET << "   - Base enemy stats\n";
    std::cout << "  " << YELLOW << "2. Medium" << RESET << " - 1.5x enemy stats\n";
    std::cout << "  " << RED    << "3. Hard"   << RESET << "   - 2.0x enemy stats\n";
    std::cout << CYAN << "└───────────────────────────────────────────────────┘" << RESET << "\n";
    std::cout << "Select option (1-3): ";

    int choice = 0;
    while (!(std::cin >> choice) || choice < 1 || choice > 3) {
        std::cout << RED << "Invalid choice! Enter 1, 2, or 3: " << RESET;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    float multiplier = 1.0f;
    if (choice == 1) {multiplier = 1.0f; difficultyLevel = 1;}
    else if (choice == 2) {multiplier = 1.5f; difficultyLevel = 2;}
    else if (choice == 3) {multiplier = 2.0f; difficultyLevel = 3;}

    enemy.SetHealth(static_cast<int>(enemy.GetHealth() * multiplier));
    enemy.SetStrength(static_cast<int>(enemy.GetStrength() * multiplier));

    std::cout << "\n" << GREEN << "[SUCCESS]" << RESET << " Game difficulty configured!\n\n";
}


void GetInfo()
{
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string CYAN    = "\033[36m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";

    std::cout << "\n" << CYAN << "┌───────────────────────────────────────────────────┐\n";
    std::cout << "│ " << BOLD << YELLOW << "                 GAME INFORMATION                 " << RESET << CYAN << "│\n";
    std::cout << "├───────────────────────────────────────────────────┤" << RESET << "\n";
    std::cout << "  " << GREEN << "[GENRE]" << RESET << " Text-Based C++ Adventure Game\n";
    std::cout << "  " << GREEN << "[FEATURES]" << RESET << " Explore locations, battle foes & gather loot\n";
    std::cout << "  " << GREEN << "[NAVIGATE]" << RESET << " Use the main menu to make your choices\n";
    std::cout << "  " << GREEN << "[AUTHOR]" << RESET << " Developed by " << BOLD << "Vladyslav Vytrykush" << RESET << "\n";
    std::cout << CYAN << "└───────────────────────────────────────────────────┘" << RESET << "\n\n";
}


void Help()
{
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string CYAN    = "\033[36m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string RED     = "\033[31m";

    std::cout << "\n" << CYAN << "┌─────────────────────────────────────────────────────────┐\n";
    std::cout << "│ " << BOLD << YELLOW << "                  COMMAND REFERENCE MENU                 " << RESET << CYAN << "│\n";
    std::cout << "├─────────────────────────────────────────────────────────┤" << RESET << "\n";
    std::cout << "  " << GREEN << "[1]" << RESET << " Character Stats  - View current character statistics\n";
    std::cout << "  " << GREEN << "[2]" << RESET << " View Inventory   - List all items in your bag\n";
    std::cout << "  " << GREEN << "[3]" << RESET << " Manage Inventory - Equip, consume, or drop items\n";
    std::cout << "  " << GREEN << "[4]" << RESET << " Game Info        - Display game overview & author info\n";
    std::cout << "  " << GREEN << "[5]" << RESET << " Help Menu        - Display this menu again\n";
    std::cout << "  " << RED   << "[0]" << RESET << " Exit Game        - Quit the application\n";
    std::cout << CYAN << "└─────────────────────────────────────────────────────────┘" << RESET << "\n\n";
}


void Reseter(Character& hero, MyInventory& inv, GameHard& levelDificulty)
{
    std::cout << "Game reset requested by user.\n";
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│                  GAME RESET                     │\n";
    std::cout << "└───────────────────────────────────────────────────┘\n\n";

    hero = Character(); 
    
    
    hero.EquipWeapon(nullptr);
    hero.EquipArmor(nullptr);
    
    // Clear inventory
    inv.Clear();
    
    levelDificulty.SetDifficultyLevel(1);
    Weapon* weapon_1 = new Weapon();
    weapon_1->RandomizeWeaponStart(hero.GetProfession());
    
    Armory* armor_1 = new Armory();
    armor_1->RandomizeArmorStart();
    
    Weapon* weapon_2 = new Weapon();
    weapon_2->RandomizeWeaponSpeacial();
    
    Potion* p = new Potion();
    p->RandomizePotion();
    
    inv.AddItem(weapon_1);
    inv.AddItem(armor_1);
    inv.AddItem(weapon_2);
    inv.AddItem(p);
    
    std::cout << "Game reset successfully!\n";
    std::cout << "\nPress Enter to continue...\n";
    std::cin.ignore();
}

void ManageGameSaves(Character& hero, MyInventory& inv, GameHard& levelDificulty)
{
    // Placeholder implementation - saves and loads game state
    std::cout << "[MANAGE GAME SAVES] - Function not yet implemented.\n";
    std::cout << "Save/Load game functionality would go here.\n";
}


void Settings(Character& hero, MyInventory& inv, Enemy& enemy, GameHard& difficultyLevel)
{
    difficultyLevel.ChoiceHard(enemy);

    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string CYAN    = "\033[36m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string RED     = "\033[31m";
    const std::string GRAY    = "\033[90m";

    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n" << CYAN << "┌───────────────────────────────────────────────────┐\n";
        std::cout << "│ " << BOLD << YELLOW << "                   GAME SETTINGS                   " << RESET << CYAN << "│\n";
        std::cout << "├───────────────────────────────────────────────────┤" << RESET << "\n";
        std::cout << "  " << GREEN << "[1]" << RESET << " Difficulty Level  - Change enemy scaling\n";
        std::cout << "  " << RED   << "[2]" << RESET << " Reset Progress    - Reset hero & inventory\n";
        std::cout << "  " << YELLOW << "[3]" << RESET << " View Game Info    - Display game overview & author info\n";
        std::cout << "  " << YELLOW << "[4]" << RESET << " Bug Report        - Report issues or glitches\n";
        std::cout << "  " << GREEN << "[0]" << RESET << " Return            - Back to Main Menu\n";
        std::cout << CYAN << "└───────────────────────────────────────────────────┘" << RESET << "\n";
        std::cout << "Select option: ";

        if (!(std::cin >> choice)) {
            std::cout << RED << "\nInvalid input! Enter a valid number." << RESET << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                difficultyLevel.ChoiceHard(enemy);
                break;

            case 2: {
                std::cout << "\n" << RED << "=== RESET GAME PROGRESS ===" << RESET << "\n";
                std::cout << "All current progress will be lost. Confirm? (y/n): ";

                char confirm;
                std::cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    
                    Reseter(hero, inv, difficultyLevel);
                    std::cout << GREEN << "[SUCCESS] Game progress reset to defaults." << RESET << "\n";
                } else {
                    std::cout << YELLOW << "[CANCELLED] Action aborted." << RESET << "\n";
                }
                break;
            }

            case 3:
                GetInfo();
                break;

                case 4:
                BugReportFunction();
                break;
            case 0:
                break;

            default:
                std::cout << RED << "\nInvalid choice. Try again." << RESET << "\n";
                break;
        }
    }
}


void BugReportFunction()
{
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string CYAN    = "\033[36m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";

    std::cout << "\n" << CYAN << "┌───────────────────────────────────────────────────┐\n";
    std::cout << "│ " << BOLD << YELLOW << "                    BUG REPORT                     " << RESET << CYAN << "│\n";
    std::cout << "├───────────────────────────────────────────────────┤" << RESET << "\n";
    std::cout << "  " << GREEN << "[ISSUE]" << RESET << " Found a bug or glitch during gameplay?\n";
    std::cout << "  " << GREEN << "[HELP ]" << RESET << " Please report issues on GitHub to help improve\n";
    std::cout << "           the game for everyone!\n\n";
    std::cout << "  " << GREEN << "[LINK ]" << RESET << " GitHub: " << BOLD << "github.com/VladyslavVytrykush" << RESET << "\n";
    std::cout << CYAN << "└───────────────────────────────────────────────────┘" << RESET << "\n\n";
}

void StartGame(Enemy& enemy, Character& hero, GameHard& levelDificulty, GameEvent& gameEvent, MyInventory& inv1)
{
    std::cout << "[START GAME] - Function not yet implemented.\n";
    std::cout << "Game starting logic would go here.\n";
    std::cout << "Current difficulty: " << levelDificulty.GetDifficultyLevel() << "\n";
    std::cout << "Press Enter to continue...\n";
    std::cin.ignore();
}


void GameHard::DisplayDifficulty() const
{
    std::cout <<"==================================================" << std::endl;
    std::cout << "Current difficulty level: " << difficultyLevel << "\n";
    std::cout <<"==================================================" << std::endl;
}
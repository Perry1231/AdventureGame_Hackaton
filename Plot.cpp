#include "Header.h"
#include <iostream>
//For main events and plot

void Turn(Character& hero, GameHard& levelDificulty, GameEvent& gameEvent, MyInventory& inv1, Quest& quest1)
{
    int choice = 0;
    do {
        std::cout << "\n┌───────────────────────────────────────────────────┐\n";
        std::cout << "│                       TURN                        │\n";
        std::cout << "├───────────────────────────────────────────────────┤\n";
        std::cout << "│  1. Make turn                                     │\n";
        std::cout << "│  2. Look in inventory                             │\n";
        std::cout << "|  3. Look active quest                             |\n";
        std::cout << "│  4. Go to main menu                               │\n";
        std::cout << "└───────────────────────────────────────────────────┘\n";

        std::cout << "Enter choice : ";
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                std::cout << "\nYou make a turn.\n";
                RandomizerEvent(hero, levelDificulty, gameEvent, inv1);
                break;
            case 2:
                std::cout << "\nYou have chosen to look in your inventory.\n";
                if (hero.GetInventory()) {
                    hero.GetInventory()->DisplayInventory();
                } else {
                    std::cout << "Inventory is empty.\n";
                }
                break;
            case 3:
                quest1.DisplayAllQuestInfo();
                break;
            case 4:
                std::cout << "\nReturning to main menu.\n";
                break;
            default:
                std::cout << "\nInvalid choice. Please select a valid option.\n";
                break;
        }
    } while (choice != 3);
    std::cout << "\n\n";
}
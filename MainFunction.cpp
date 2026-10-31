#include <iostream>
#include "Header.h"
void MainFunction() {
//TESTING=======================================  (For user : -> don't about this)
    Character hero;
    hero.RandomizeStats();


    Weapon* weapon_1 = new Weapon();
    weapon_1->RandomizeWeaponStart(hero.GetProfession());

    Armory* armor_1 = new Armory();
    armor_1->RandomizeArmorStart();

    Weapon* weapon_2 = new Weapon();
    weapon_2->RandomizeWeaponSpeacial();

    Potion* potion = new Potion();
    potion->RandomizePotion();

    Artifact* artif = new Artifact();       //Adding artifact for test in inventory
    artif->RandomizeArtifact();

    MyInventory inv1;
    inv1.SetOwner(&hero);
    hero.SetInventory(&inv1);

    inv1.AddItem(weapon_1);             //Added item with ID ---- will be written
    inv1.AddItem(armor_1);
    inv1.AddItem(weapon_2);
    inv1.AddItem(potion);
    inv1.AddItem(artif);
    
    potion->SetOwner(&hero); 
    artif->SetOwner(&hero);
    
    GameHard difficultyLevelObj;       //Creating object of GameHard class to manage difficulty level
    difficultyLevelObj.SetDifficultyLevel(1); 

    Enemy enemy;
    enemy.RandomizeStats();
    GameEvent gameEvent;

    Quest quest1;
    quest1.SetQuestName("The Lost Home");
    quest1.SetQuestDescription("Find the lost home of the ancient civilization.");
    quest1.SetQuestDifficulty(3);
    quest1.DisplayAllQuestInfo();


    Object* object1 = new Object();
    object1->CreateObjectConstructor();
    object1->SetObjectName("Apple");
    object1->SetObjectDescribtion("Big");
    object1->SetOwner(&hero);
    
//====================================================================
  int mainChoice =0;
    while (true) {
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│                     MAIN MENU                     │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    std::cout << "│  1. Start game                                    │\n";
    std::cout << "│  2. Manage game saves                             │\n";
    std::cout << "│  3. Show character stats                          │\n";
    std::cout << "│  4. Manage your Inventory                         │\n";
    std::cout << "│  5. Settings                                      │\n";
    std::cout << "│  6. Help                                          │\n";
    std::cout << "│  7. Report bug                                    │\n";
    std::cout << "│  0. Exit                                          │\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
    std::cout << "Choice: ";
    std::cin >> mainChoice;                                                                                             

    if (mainChoice == 1) {
        StartGame(enemy, hero, difficultyLevelObj, gameEvent, inv1);                                                                                                 //Start game
    } else if (mainChoice == 2) {
        ManageGameSaves(hero, inv1, difficultyLevelObj);                                                                                                 //Load game                                                                                                //Save game
    } else if (mainChoice == 3) {
        hero.DisplayStats();                                                                                               //Display stats
    } else if (mainChoice == 4) {
        std::cout << "\n┌───────────────────────────────────────────────────┐\n";
        std::cout << "│                INVENTORY MANAGEMENT               │\n";
        std::cout << "├───────────────────────────────────────────────────┤\n";
        std::cout << "│  1. Display inventory                             │\n";                                           //Sub-main functions act1 (Manage inventory)
        std::cout << "│  2. Show weapon status                            │\n";
        std::cout << "│  3. Equip weapon                                  │\n";
        std::cout << "│  4. Unequip weapon                                │\n";
        std::cout << "│  5. Show armor stats                              │\n";
        std::cout << "│  6. Equip armor                                   │\n";
        std::cout << "│  7. Unequip armor                                 │\n";
        std::cout << "│  0. Back to main menu                             │\n";
        std::cout << "└───────────────────────────────────────────────────┘\n";
        std::cout << "Choice: ";
        std::cin >> mainChoice;

        if (mainChoice == 1) {
            inv1.DisplayInventory();
        } else if (mainChoice == 2) {
            weapon_1->ShowInfo();
        } else if (mainChoice == 3) {
            weapon_1->Use();
        } else if (mainChoice == 4) {
            weapon_1->Reset();
        } else if (mainChoice == 5) {
            armor_1->ShowInfo();
        } else if (mainChoice == 6) {
            armor_1->Use();
        } else if (mainChoice == 7) {
            armor_1->Reset();
        } else if (mainChoice == 0) {
            break;
        } else {
            std::cout << "\n[!] Invalid choice!\n";
        }
    } else if (mainChoice == 5) {
        Settings(hero , inv1, enemy, difficultyLevelObj);                                                                                             //Settings
    } else if (mainChoice == 6) {
        Help();                                                                                                            //Help
    } else if (mainChoice == 7) {
        BugReportFunction();
    } else if (mainChoice == 0) {
        break;
    } else {
        std::cout << "\n[!] Invalid choice!\n";
    }
}
}
#include <iostream>
#include "Header.h"
#include <map>          
#include <string>
#include <utility> 

// Campus-themed armor/clothing
static std::map<std::string, std::pair<int, int>>& GetArmorDB() {
    static std::map<std::string, std::pair<int, int>> db;
    if (db.empty()) {
        db = {
            // Common - basic clothing
            {"Hoodie", {3, 15}},
            {"Jeans", {2, 10}},
            {"T-Shirt", {1, 5}},
            {"Sweatpants", {2, 8}},
            {"Baseball Cap", {1, 5}},
            {"Sneakers", {2, 20}},
            {"Light Jacket", {4, 30}},
            
            // Uncommon - better gear
            {"Flannel Shirt", {5, 40}},
            {"Denim Jacket", {6, 60}},
            {"Tracksuit", {5, 50}},
            {"Bomber Jacket", {7, 80}},
            {"Combat Boots", {4, 70}},
            {"Raincoat", {5, 55}},
            
            // Rare - quality gear
            {"Leather Jacket", {8, 120}},
            {"Winter Coat", {9, 150}},
            {"Tactical Vest", {10, 180}},
            {"Motorcycle Gear", {12, 200}},
            {"Hazmat Suit (Clean)", {15, 250}},
            
            // Epic - special items
            {"Dean's Blazer", {18, 500}},
            {"Alumni Letterman", {15, 400}},
            {"Graduation Gown", {20, 750}},
            
            // Legacy (for compatibility)
            {"Padded Armor", {3, 15}},
            {"Leather Armor", {5, 30}},
            {"Chainmail Shirt", {7, 80}},
            {"Plate Armor", {15, 300}},
        };
    }
    return db;
}

// Special/Enchanted armor
static std::map<std::string, std::pair<int, int>>& GetSpecialArmorDB() {
    static std::map<std::string, std::pair<int, int>> db;
    if (db.empty()) {
        db = {
            // Enchanted/Cursed items
            {"Lucky Hoodie", {5, 200}},        // +2 Luck
            {"Cursed Sweater", {10, 50}},      // High defense but cursed
            {"Exam Shield", {12, 300}},        // +5 Intelligence during exams
            {"Party Armor", {8, 400}},         // +5 Charisma at parties
            {"Study Cloak", {7, 350}},         // +10 Intelligence while studying
            {"RA Uniform", {15, 500}},         // Authority bonus
            {"Professor's Tweed", {10, 600}},  // +15 Intelligence
            {"Founder's Robe", {25, 2000}},    // Legendary
        };
    }
    return db;
}

std::string Armory::RandomizeArmor()   
{
    auto& db = GetArmorDB();
    int randomIndex = rand() % db.size();
    auto it = db.begin();
    std::advance(it, randomIndex);
    return it->first;
}

std::string Armory::RandomizeArmorStart()                                  // Starter pack armor
{
    auto& db = GetArmorDB();
    int choice = rand() % 3; 
    switch(choice)
    {
        case 0: name_a = "Hoodie"; break;
        case 1: name_a = "Jeans"; break;
        case 2: name_a = "T-Shirt"; break;
    }
    auto it = db.find(name_a);
    if (it != db.end()) {
        value_a = it->second.second; 
        defend_a = it->second.first;
    }
    return name_a;
}

std::string Armory::RandomizeArmorSpecial()                                  // Special/Enchanted armor
{
    auto& db = GetSpecialArmorDB();
    int randomIndex = rand() % db.size();
    auto it = db.begin();
    std::advance(it, randomIndex);
    
    name_a = it->first;
    defend_a = it->second.first;
    value_a = it->second.second;
    isEnchanted_a = true;
    
    return name_a;
}

void Armory::ShowInfo() const
{
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│              ARMOR CHARACTERISTICS                │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    std::cout << "│  Name         : " << name_a << "\n";
    std::cout << "│  Defense      : " << defend_a << "\n";
    std::cout << "│  Durability   : " << durability_a << "\n";
    std::cout << "│  Value        : " << value_a << "\n";
    std::cout << "│  Is Enchanted : " << (isEnchanted_a ? "Yes" : "No") << "\n";
    std::cout << "└───────────────────────────────────────────────────┘\n\n";
}

void Armory::Use() {
    isEquipped_a = true;
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│  " << name_a << " equipped! Defense: +" << defend_a << "\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
}

void Armory::Reset() {
    isEquipped_a = false;
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│  " << name_a << " unequipped.\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
}

void Armory::BrokenArmory()
{
    isBroken_a = true;
    durability_a = 0;
    
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│  Status: " << (IsUsable() ? "Usable" : "Broken") << "\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
}
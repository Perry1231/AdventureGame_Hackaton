#include <iostream>
#include <map>
#include <tuple>
#include "Header.h"
//Here will be functions for objects db and their abillities

//Name -> {price, rarity, isQuestItem, description}
static std::map<std::string, std::tuple<int, std::string, bool, std::string>>& GetObjectDB() {
    static std::map<std::string, std::tuple<int, std::string, bool, std::string>> db;
    if (db.empty()) {
        db = {
            // Common campus items
            {"Energy Drink",           {8,  "Common", false, "Restores 15 HP. Tastes like battery acid and citrus."}},
            {"Instant Noodles",        {5,  "Common", false, "Cheap meal. Restores 10 HP."}},
            {"Lecture Notes",          {12, "Common", false, "Someone's borrowed notes. +5 Intelligence temporarily."}},
            {"Stale Bagel",            {3,  "Common", false, "Hard as a rock. Restores 5 HP."}},
            {"Campus Map",             {10, "Common", false, "Shows all building locations. Useful for navigation."}},
            {"Library Card",           {0,  "Common", false, "Grants access to the university library."}},
            {"Student ID",             {0,  "Common", false, "Your identification. Required for exams and dorm access."}},
            {"Dorm Key",               {0,  "Common", false, "Opens your dorm room. Don't lose it!"}},
            {"Laundry Token",          {2,  "Common", false, "One wash cycle in the dorm laundry room."}},
            {"Vending Machine Snack",  {4,  "Common", false, "Chips or chocolate bar. Restores 8 HP."}},
            
            // Uncommon items
            {"Energy Shot",            {25, "Uncommon", false, "Concentrated caffeine. Restores 30 HP, +2 Agility temporarily."}},
            {"Professor's Handout",    {30, "Uncommon", false, "Extra credit opportunity. +10 Intelligence."}},
            {"Rare Textbook",          {50, "Uncommon", false, "First edition. Can be sold for good gold."}},
            {"Campus Legend Token",    {40, "Uncommon", false, "Collect all 5 for a special reward."}},
            {"Roommate's Snack Stash", {15, "Uncommon", false, "Hidden treats. Restores 20 HP."}},
            {"Lost AirPods",           {60, "Uncommon", false, "Someone's expensive earbuds. Return for karma or sell."}},
            {"Exam Cheat Sheet",       {35, "Uncommon", true, "Risky but effective. Use during exams."}},
            
            // Rare items
            {"Ancient Lecture Notes",  {100, "Rare", false, "Notes from a legendary professor. +15 Intelligence permanently."}},
            {"Dean's List Certificate", {200, "Rare", false, "Proof of academic excellence. Opens special opportunities."}},
            {"Master Key",             {500, "Rare", false, "Opens any dorm room. Use wisely."}},
            {"Secret Society Invite",  {150, "Rare", true, "Invitation to a mysterious campus group."}},
            {"Cursed Textbook",        {75, "Rare", true, "Gives knowledge but drains health. -10 HP, +20 Int."}},
            {"Golden Energy Drink",    {300, "Rare", false, "Legendary beverage. Fully restores HP and all stats."}},
            
            // Epic items
            {"Time-Turner Watch",      {1000, "Epic", false, "Rewind one turn per day. Extremely rare."}},
            {"Professor's Tenure Letter", {500, "Epic", true, "Guarantees passing grade in one class."}},
            
            // Legacy magic items (for compatibility)
            {"Magic Grass",            {8,  "Common", false, "A strange glowing grass."}},
            {"Magic Stone",            {10, "Common", false, "A stone with faint magical aura."}},
            {"Pinecone",               {5,  "Common", false, "A perfectly symmetrical pinecone."}},
        };
    }
    return db;
}

void Object::CreateObjectConstructor()
{
    auto& db = GetObjectDB();
    int randomIndex = rand() % db.size();
    auto it = db.begin();
    std::advance(it, randomIndex);

    name_object = it->first;
    price_object = std::get<0>(it->second);
    rarityType_object = std::get<1>(it->second);
    isQuest = std::get<2>(it->second);
    describtion_object = std::get<3>(it->second);
}


std::string Object::RandomizeObject()
{
    CreateObjectConstructor();
    return name_object;
}


void Object::RecountObject()
{
    if (count_object < 0) count_object = 0;
}


void Object::DisplayObjectStats()
{
std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│              OBJECT CHARACTERISTICS             │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    std::cout << "│  Object : " << name_object << "\n";
    std::cout << "│  Description: " << describtion_object << "\n";
    std::cout << "│  Rarity   : " << rarityType_object << "\n";
    std::cout << "│  Value    : " << price_object << " gold\n";
    std::cout << "└───────────────────────────────────────────────────┘\n\n";
}



void Object::ShowInfo() const {
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│              ARTIFACT CHARACTERISTICS             │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    std::cout << "│  Artifact : " << name_object << "\n";
    std::cout << "│  Description: " << describtion_object << "\n";
    std::cout << "│  Type     : " << GetType() << "\n";
    std::cout << "│  Value    : " << price_object << " gold\n";
    std::cout << "└───────────────────────────────────────────────────┘\n\n";
}


void Object::Use() {
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    if (!owner_p) {
        std::cout << "│  Artifact " << name_object << " has no owner!\n";
        std::cout << "└───────────────────────────────────────────────────┘\n";
        return;
    }

    std::cout << "│  Using artifact: " << name_object << "!\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
}


void Object::Reset() {
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│  " << name_object << " reset.\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
}

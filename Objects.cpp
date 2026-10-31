#include <iostream>
#include <map>
#include <tuple>
#include "Header.h"
//Here will be functions for objects db and their abillities

//Name -> {price, rarity, isQuestItem}
static std::map<std::string, std::tuple<int, std::string, bool>>& GetObjectDB() {
    static std::map<std::string, std::tuple<int, std::string, bool>> db;
    if (db.empty()) {
        db = {
            {"Magic Grass",            {8,  "Common", false}},
            {"Magic Stone",            {10, "Common", false}},
            {"Magic Mushroom",         {12, "Common", false}},
            {"Rare Ore",                {25, "Rare", false}},
            {"Broken Portal Fragment", {35, "Rare", false}},
            {"Festival Ingredient",    {15, "Common", false}},
            {"Magic White Moss",       {14, "Common", false}},
            {"Mandragora Root",        {22, "Rare", false}},
            {"Magic Mirror Shard",     {30, "Rare", false}},
            {"Ancient Book Page",      {28, "Epic", false}},
            {"Pinecone",               {5,  "Common", false}},
            {"Dwarf House Leaves",     {6,  "Common", false}},
            {"Village Elder's Letter", {0,  "Common", true}},
            {"Stolen Goblin Amulet",   {0,  "Rare", true}}
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
    describtion_object = isQuest
        ? ("A quest item: " + name_object + ".")
        : ("A collectible object: " + name_object + ".");
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

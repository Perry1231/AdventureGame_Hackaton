#include <iostream>
#include "Header.h"
#include <map>          //-> for map function 
#include <string>
#include <utility> 

//Also make as is in weapon.cpp
 static std::map<std::string, std::pair<int, int>>& GetWeaponAR() {
    static std::map<std::string, std::pair<int, int>> db;
    if (db.empty()) {
        db = {
    //              suit name defense cost
 
        {"Padded suit", {11 ,5}}, 
        {"Leather suit", {11, 10}}, 
        {"Studded suit", {12, 22}},

  
        {"Hide suit", {12, 10}},
        {"Chain shirt",{ 13, 30}}, 
        {"Scale male", {13, 43}},
        {"Spaiked armor", {15 , 50}},
        {"Breastplate",{17, 70}},
        {"Halfplate",  {19, 110}},

    
        {"Ring mail", {14, 40 }}, 
        {"Chain mail", {15, 55}},
        {"Splint", {20, 140}}, 
        {"Plate", {26, 250}},

        {"Shield", {6, 70}}};
        }
         return db;
}


std::string Armory::RandomizeArmor()   
{
auto& db = GetWeaponAR();
    int randomIndex = rand() % db.size();
    auto it = db.begin();
    std::advance(it, randomIndex);
    return it->first;
}


std::string Armory::RandomizeArmorStart()                                  //Starter pack armor
{
    auto& db = GetWeaponAR();
    int choise = rand ()% 3; 
switch(choise)
{
    case 0:
        name_a = "Padded suit";
        break;
    case 1:
        name_a = "Leather suit";
        break;
    case 2:
        name_a = "Studded suit";
        break;
}
auto it = db.find(name_a);
    if (it != db.end()) {
        value_a  = it->second.second; 
    }
return name_a;
}
    


void Armory::ShowInfo() const                                                                                          //Show armor characteristics
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


void Armory::BrokenArmory()                                                                                                //Count is armor broken
{
    isBroken_a = true;
    durability_a = 0;
    
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│  Status: " << (IsUsable() ? "Usable" : "Broken") << "\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
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





//==================================================================Special_weapon=========================================================================


static std::map<std::string, std::pair<int, int>>& GetWeaponARS() {
    static std::map<std::string, std::pair<int, int>> db;
    if (db.empty()) {
        db = {
            {"Spider suit", {17 ,100}},
            {"Dragon suit", {22, 200}},
            {"Yetti suit", {15, 75}},
            {"Hide suit", {14, 55 }},
            {"Spiked suit", {16, 60}},
            {"Kevlar suit", {20, 140}},
            {"Adamantium suit", {22, 180}},
            {"Plate", {26, 250}}};
    }
    return db;  // ← тепер завжди повертає
}

std::string Armory::RandomizeArmorSpecial()                                  //Starter pack armor
{
    
    auto& db = GetWeaponARS();
auto it = db.find(name_a);
    if (it != db.end()) {
        value_a  = it->second.second; 
    }
return name_a;
}
    
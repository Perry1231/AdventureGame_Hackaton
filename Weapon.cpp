#include "Header.h"
#include <iostream>
#include <map>      //-> for map function for all weapon


//=====================================================Weapom_Randomize=========================================================================================================
 
    static std::map<std::string, std::pair<int, int>>& GetWeaponDB() {
    static std::map<std::string, std::pair<int, int>> db;
    if (db.empty()) {
        db = {

        {"Club", {3 ,2}}, 
        {"Sword", {3 ,2}}, 
        {"Dagger", {5, 3}}, 
        {"Greatclub", {6, 5}},
        {"Handaxe", {5, 5}},
        {"Javelin", {6, 5}},
        {"Light hammer", {6, 5}},
        {"Mace", {6, 5}},
        {"Sickle", {6, 5}},
        {"Quarterstaff", {6, 5}},
        {"Scimitar", {6, 5}},
        {"Shortsword",{17, 70}},
        {"Unarmed strike", {6, 5}},


//Ranged
        {"Light crossbow", {12, 10}},
        {"Dart",{ 13, 30}}, 
        {"Blowgun",{17, 70}},
        {"Longbow",{17, 70}},
        {"Greatsword",{17, 70}},
        {"Net",{17, 70}},

//Heavy male
        {"Battleaxe", {12, 10}},
        {"Flail",{ 13, 30}}, 
        {"Glaive", {13, 43}},
        {"Greataxe", {15 , 50}},
        {"Greatsword",{17, 70}},
        {"Lance",{17, 70}},
        {"Maul",{17, 70}},
        {"Morningstar",{17, 70}},
        {"Pike",{17, 70}},
        {"Rapier",{17, 70}},
        {"Warhammer",{17, 70}},
        {"Halberd",  {19, 110}},

//Magic
{"Rod", {12, 10}},
{"Wand", {12, 10}},
{"Staff", {12, 10}}};
        }
    return db;
}


std::string Weapon::RandomizeWeapon()   //Ready or not = 
{
auto& db = GetWeaponDB();
    int randomIndex = rand() % db.size();
    auto it = db.begin();
    std::advance(it, randomIndex);
    return it->first;
}


std::string Weapon::RandomizeWeaponStart(const std::string& profession_get)                                  //Starter pack weapon
{
    auto& db = GetWeaponDB();
std::string weapon_me[] = {"Sword","Club", "Dagger","Greatclub", "Handaxe","Javelin", "Light hammer", "Mace", "Sickle", "Quarterstaff", "Scimitar", "Shortsword","Unarmed strike"}; //For_Melee == 13
std::string weapon_ra[] = {"Light crossbow","Dart", "Shortbow", "Blowgun","Longbow","Greatsword","Net"};//For_range == 7
std::string weapon_ma[] = {"Rod", "Wand", "Staff"}; //For_magic == 3

if (profession_get == "Warrior")
{
this -> name_w = weapon_me[rand() % 13];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Mage")
{
this -> name_w = weapon_ma[rand() % 3];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Rogue")
{
this -> name_w = weapon_me[rand() % 13];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Peasant")
{
this -> name_w = weapon_me[rand() % 13];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Archer")
{
this -> name_w = weapon_ra[rand() % 7];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Druid")
{
this -> name_w = weapon_ma[rand() % 3];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Ranger")
{
this -> name_w = weapon_ra[rand() % 7];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Blacksmith")
{
this -> name_w = weapon_me[rand() % 13];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Miner")
{
this -> name_w = weapon_me[rand() % 13];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Berserker")
{
this -> name_w = weapon_me[rand() % 13];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Shaman")
{
this -> name_w = weapon_ma[rand() % 3];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Warlord")
{
this -> name_w = weapon_me[rand() % 13];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Thief")
{
this -> name_w = weapon_me[rand() % 13];
        auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }

return name_w;
}

else if (profession_get == "Assassin")
{
this -> name_w = weapon_me[rand() % 13];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else if (profession_get == "Scavenger")
{
this -> name_w = weapon_me[rand() % 13];
auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second; 
    }
return name_w;
}

else {this -> name_w = "Sword"; 
    auto it = db.find(name_w);
    if (it != db.end()) {
        attack_w = it->second.first;  
        value_w  = it->second.second;} return name_w;}
}


//================================================================Other_functions=============================================================================
void Weapon::ShowInfo() const                                                                                          //Show weapon characteristics
{
std::cout << "\n===Your weapon characteristic=== "<< std::endl;
std::cout << "Name : " << name_w << "\nAttack : " << attack_w << "\nDefend : " << defend_w << "\nDurability : " 
            << durability_w << "\nValue : " << value_w << "\nIs enchanted : " << (isEnchanted_w ? "Yes" : "No") << std::endl;
}


void Weapon::BrokenWeapon()                                                                                                   //Count is weapon broken
{
    isBroken_w = true;
    durability_w = 0;
    std::cout << (IsUsable() ? "Usable" : "Broken") << std::endl;
}


void Weapon::Use()
{
    isEquipped_w = true;
    std::cout << name_w << " equipped! Attack +" << attack_w << std::endl;
}

void Weapon::Reset()
{
    isEquipped_w = false;
        std::cout << name_w << " unequipped!" << std::endl;
}


//=================================================================Special_weapon=================================================================================




 static std::map<std::string, std::pair<int, int>>& GetWeaponSpeacialDB() {                 //Speacial weapon list
    static std::map<std::string, std::pair<int, int>> dp;
    if (dp.empty()) {
        dp = {
            //Weapon speacial
            {"Blade of Broken Mirrors", {10, 10}},
            {"Javelin of Backbiting", {10, 10}},
            {"Wand of Orcus", {10, 10}},
            {"Windvane", {10, 10}},
            {"Spear of Heliod", {10, 10}},
            {"Ephixis", {10, 10}},
            {"Two-Birds Sling", {10, 10}},
            {"Axe of the Dwarvish Lords", {10, 10}},
            {"Gambler’s Blade", {10, 10}},
            {"Orcsplitter ", {10, 10}},
            {"Sword of Sharpness", {10, 10}},
            {"Vorpal Sword", {10, 10}},
            {"Acheron Blade", {10, 10}},
            {"Luck Blade", {10, 10}},
            {"Sword of Life Stealing", {10, 10}},
            {"Mind Lash", {10, 10}},
            {"Dragon Slayer", {10, 10}}};
    }
    return dp;
}

//For chest =====================================================================================================================================================================
std::string  Weapon::RandomizeWeaponSpeacial()                                                            
{
    auto& dp = GetWeaponSpeacialDB();
  

std::string weapon_sp[] = {"Blade of Broken Mirrors","Javelin of Backbiting", "Wand of Orcus","Windvane", "Spear of Heliod","Ephixis", 
    "Two-Birds Sling","Axe of the Dwarvish Lords","Gambler's Blade","Orcsplitter ", "Sword of Sharpness","Vorpal Sword", "Acheron Blade",  
    "Luck Blade","Sword of Life Stealing","Mind Lash", "Dragon Slayer"};                                                                     //Special_weapon
    std::string chosen_name; 
        chosen_name = weapon_sp[rand() % 17];
        auto it = dp.find(chosen_name);
        if (it != dp.end()) {
            attack_w = it->second.first;
            value_w = it->second.second;
        }
    
    name_w = chosen_name;
    return name_w;
}

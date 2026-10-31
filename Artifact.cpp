#include "Header.h"
#include <map>

static std::string EffectTypeToString(int type) {
    switch (type) {
        case HEALTH: return "Health"; break;
        case DEFENSE: return "Defense"; break;
        case AGILITY: return "Agility"; break;
        case INTELLIGENCE: return "Intelligence"; break;
        case GOLD: return "Gold"; break;
        case STRENGTH: return "Strength"; break;
        default: return "Unknown"; break;
    }
}
//Name + power + cost
static std::map<std::string, std::pair<int, int>>& GetWeaponArtifactDB() {
    static std::map<std::string, std::pair<int, int>> ar;
    if (ar.empty()) {
        ar = {
    {"Midas arm", {1, 15}},
    {"Orcsplitter ", {1, 12}},
    {"Two-Birds Sling", {1, 10}},

    //Rare
    {"Windvane", {2, 35}},
    {"Spear of Heliod", {2, 40}},
    {"Sword of Sharpness", {2, 45}},
    {"Acheron Blade", {2, 38}},
    {"Mind Lash", {2, 42}},

    //legendary/Epic
    {"Javelin of Backbiting", {3, 70}},
    {"Wand of Orcus", {3, 85}},
    {"Axe of the Dwarvish Lords", {3, 90}},
    {"Gambler's Blade", {3, 100}},
    {"Vorpal Sword", {3, 95}},
    {"Luck Blade", {3, 80}},
    {"Sword of Life Stealing", {3, 75}},
    {"Dragon Slayer", {3, 110}}
        };
    }
    return ar;
}

//Name + Effect -> 
static int GetArtifactEffectType(const std::string& name) {
    static std::map<std::string, int> effects = {
        {"Midas arm", GOLD},
        {"Javelin of Backbiting", STRENGTH},
        {"Wand of Orcus", INTELLIGENCE},
        {"Windvane", AGILITY},
        {"Spear of Heliod", STRENGTH},
        {"Ephixis", DEFENSE},
        {"Two-Birds Sling", AGILITY},
        {"Axe of the Dwarvish Lords", STRENGTH},
        {"Gambler's Blade", GOLD},
        {"Orcsplitter ", DEFENSE},
        {"Sword of Sharpness", STRENGTH},
        {"Vorpal Sword", STRENGTH},
        {"Acheron Blade", INTELLIGENCE},
        {"Luck Blade", GOLD},
        {"Sword of Life Stealing", HEALTH},
        {"Mind Lash", INTELLIGENCE},
        {"Dragon Slayer", STRENGTH}
    };
    auto it = effects.find(name);
    return (it != effects.end()) ? it->second : HEALTH;
}

std::string Artifact::RandomizeArtifact() {
    auto& ar = GetWeaponArtifactDB();

    std::string weapon_ar[] = {
        "Midas arm", "Javelin of Backbiting", "Wand of Orcus", "Windvane",
        "Spear of Heliod", "Ephixis", "Two-Birds Sling", "Axe of the Dwarvish Lords",
        "Gambler's Blade", "Orcsplitter ", "Sword of Sharpness", "Vorpal Sword",
        "Acheron Blade", "Luck Blade", "Sword of Life Stealing", "Mind Lash", "Dragon Slayer"
    };

    std::string chosen_name;
    chosen_name = weapon_ar[rand() % 17];
    auto it = ar.find(chosen_name);
    if (it != ar.end()) {
        power = it->second.first;
        value = it->second.second;
        value = value * power + (rand() % 15);
    }

    effectType = GetArtifactEffectType(chosen_name);

    name = chosen_name;
    return name;
}

void Artifact::ShowInfo() const {
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│              ARTIFACT CHARACTERISTICS             │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    std::cout << "│  Artifact : " << name << "\n";
    std::cout << "│  Description: " << description << "\n";
    std::cout << "│  Rarity   : " << rarityType << "\n";
    std::cout << "│  Type     : " << GetType() << "\n";
    std::cout << "│  Power    : " << power << "\n";
    std::cout << "│  Value    : " << value << " gold\n";
    std::cout << "│  Effect   : " << EffectTypeToString(effectType) << " +" << power << "\n";
    std::cout << "└───────────────────────────────────────────────────┘\n\n";
}

void Artifact::Use() {
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    if (!owner_p) {
        std::cout << "│  Artifact " << name << " has no owner!\n";
        std::cout << "└───────────────────────────────────────────────────┘\n";
        return;
    }

    std::cout << "│  Using artifact: " << name << "!\n";
    owner_p->ApplyPotionEffect(effectType, power);
    std::cout << "│  Effect applied!\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
}

void Artifact::Reset() {
    isEquipped = false;
    owner_p = nullptr;
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│  " << name << " unequipped.\n";
    std::cout << "└───────────────────────────────────────────────────┘\n";
}



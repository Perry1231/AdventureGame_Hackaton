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

// Campus-themed artifacts with rarity
struct ArtifactData {
    std::string name;
    std::string description;
    int effectType;
    int power;
    int value;
    ArtifactRarity rarity;
};

static std::vector<ArtifactData>& GetArtifactDB() {
    static std::vector<ArtifactData> db = {
        // Common artifacts
        {"Lucky Pen", "A pen that never runs out of ink. +2 Intelligence", INTELLIGENCE, 2, 25, COMMON_ARTIFACT},
        {"Comfortable Pillow", "Ensures good rest. +5 Health per rest", HEALTH, 5, 30, COMMON_ARTIFACT},
        {"Noise-Canceling Earbuds", "Blocks dorm noise. +2 Agility (focus)", AGILITY, 2, 35, COMMON_ARTIFACT},
        {"Reusable Water Bottle", "Stay hydrated. +3 Health", HEALTH, 3, 20, COMMON_ARTIFACT},
        {"Highlighter Set", "Color-code your notes. +2 Intelligence", INTELLIGENCE, 2, 15, COMMON_ARTIFACT},
        
        // Uncommon artifacts
        {"Professor's Favorite Mug", "Coffee tastes better. +5 Health, +2 Intelligence", HEALTH, 7, 75, RARE_ARTIFACT},
        {"Campus Legend Hoodie", "Warm and stylish. +10 Health, +3 Defense", DEFENSE, 3, 120, RARE_ARTIFACT},
        {"Smart Watch", "Tracks fitness and schedule. +3 Agility, +2 Intelligence", AGILITY, 5, 150, RARE_ARTIFACT},
        {"Vintage Textbook", "Contains hidden knowledge. +10 Intelligence", INTELLIGENCE, 10, 200, RARE_ARTIFACT},
        {"Energy Drink IV Drip", "Continuous caffeine. +15 Health, +5 Agility", HEALTH, 20, 180, RARE_ARTIFACT},
        {"RA's Master Key", "Opens common areas. +5 Agility (access)", AGILITY, 5, 160, RARE_ARTIFACT},
        
        // Rare artifacts
        {"Dean's Signet Ring", "Authority recognized. +10 Intelligence, +10 Gold find", GOLD, 10, 500, EPIC_ARTIFACT},
        {"Ancient Campus Map", "Reveals secret paths. +15 Intelligence, +5 Agility", INTELLIGENCE, 20, 750, EPIC_ARTIFACT},
        {"Time Management Planner", "Perfect scheduling. +5 to ALL stats", STRENGTH, 5, 1000, EPIC_ARTIFACT},
        {"Alumni Network Badge", "Connections everywhere. +15 Gold find, +5 Intelligence", GOLD, 15, 800, EPIC_ARTIFACT},
        {"Enchanted Laptop", "Never crashes, infinite battery. +10 Intelligence, +10 Agility", INTELLIGENCE, 20, 1200, EPIC_ARTIFACT},
        
        // Legendary artifacts
        {"Graduation Cap of Destiny", "Guarantees success. +20 to ALL stats, auto-pass one exam", STRENGTH, 30, 5000, LEGENDARY_ARTIFACT},
        {"Founder's Diploma", "Legacy of the university. +25 Intelligence, +15 Gold, unique perks", INTELLIGENCE, 35, 10000, LEGENDARY_ARTIFACT},
        {"Infinite Coffee Thermos", "Never empty, perfect temperature. +30 Health, +10 Agility", HEALTH, 40, 7500, LEGENDARY_ARTIFACT},
    };
    return db;
}

std::string Artifact::RandomizeArtifact() {
    auto& db = GetArtifactDB();
    
    // Weighted rarity selection
    int roll = rand() % 100;
    ArtifactRarity targetRarity;
    if (roll < 50) targetRarity = COMMON_ARTIFACT;
    else if (roll < 80) targetRarity = RARE_ARTIFACT;
    else if (roll < 95) targetRarity = EPIC_ARTIFACT;
    else targetRarity = LEGENDARY_ARTIFACT;
    
    // Filter by rarity
    std::vector<ArtifactData*> candidates;
    for (auto& item : db) {
        if (item.rarity == targetRarity) {
            candidates.push_back(&item);
        }
    }
    
    if (candidates.empty()) {
        // Fallback to any
        candidates.reserve(db.size());
        for (auto& item : db) candidates.push_back(&item);
    }
    
    ArtifactData* chosen = candidates[rand() % candidates.size()];
    
    name = chosen->name;
    description = chosen->description;
    effectType = chosen->effectType;
    power = chosen->power;
    value = chosen->value;
    rarityType = chosen->rarity;
    
    return name;
}

void Artifact::ShowInfo() const {
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│              ARTIFACT CHARACTERISTICS             │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    std::cout << "│  Artifact : " << name << "\n";
    std::cout << "│  Description: " << description << "\n";
    std::cout << "│  Rarity   : " << GetArtifactRarityName() << "\n";
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
#include "Header.h"
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

// [ ] Add random potion generation for loot/caves/shops
// [ ] Connect potion effects to Character stats (health, strength, agility, defense, int, gold)
// [ ] Add cooldown system so effects don't stack infinitely
// [ ] Support negative effects (poison, weakness, slowness) as damage-over-time
// [ ] Make Health Potion heal only and remove negative effect logic
// [ ] Refactor ApplyEffect to handle all EffectType enum values

static std::map<std::string, std::tuple<int, int, int, int>>& GetPotionPO() { //For spell list
	static std::map<std::string, std::tuple<int, int, int, int>> pt;
	if (pt.empty()) {
		pt = {
			{"Health Potion", {0, 20, 0, 2}},   //First -- value is efect in "Header.h" , second -- potency , thirs -- price , forth --duartion
			{"Strength Potion", {1, 5, 3, 3}},
			{"Inteligence potion", {3, 5, 3, 1}},
			{"Defense Potion", {2, 5, 3, 0}},
			{"Gold Potion", {4, 10, 3, 0}},
			{"Intelligence Potion", {3, 5, 3, 0}},
			{"Poison Potion", {0, -10, 0, 0}},
			{"Weakness Potion", {5, -5, 3, 0}},
			{"Slowness Potion", {2, -1, 3, 0}},
			{"Agility Potion", {2, 5, 3, 0}}
		};
	}
	return pt;
}

static std::string EffectTypeToString(int type) {
    switch (type) {
        case 0: return "Health"; break;
        case 1: return "Defense";break;
        case 2: return "Agility";break;
        case 3: return "Intelligence";break;
        case 4: return "Gold";break;
        case 5: return "Strength";break;
        default: return "Unknown";break;
    }
}

void Potion::ShowInfo() const //Count is weapon broken
{
	std::cout << "\n===Your potion characteristic=== " << std::endl;
	std::cout << "Name : " << name_p << "\nEffect Type : " << EffectTypeToString(effectType) 
		<< "\nPotency : "<< potency 
		<< "\nDescribtion : " << description_p
		<< "\nValue : " << value_p
		<< "\nDuration : " << std::get<3>(GetPotionPO()[name_p]) 
		<< "\nIs equipped : " << (isEquipped_p ? "Yes" : "No") << std::endl;
	std::cout << "\n\n" << std::endl;
}


void Potion::Use()
{
	isEquipped_p = true;
	ApplyEffect(GetOwner());
}

void Potion::Reset()
{
	isEquipped_p = false;
	std::cout << name_p << " unequipped!" << std::endl;
}

void Potion::ApplyEffect(Character* character) {
	isEquipped_p = true;
	if (!character) {
		std::cout << "No character to apply the potion effect!" << std::endl;
		return;
	}
	else
	{
	character->ApplyPotionEffect(GetEffectType(), GetPotency());
	std::cout << "Used " << GetName() << "." << std::endl;
	}
}



void Potion::RandomizePotion()
{
    auto& db = GetPotionPO();
    int choise = rand() % db.size();
    auto it = db.begin();
    std::advance(it, choise);
    
     name_p = it->first;
    effectType = std::get<0>(it->second);
    potency = std::get<1>(it->second);
    description_p = "Potion of " + EffectTypeToString(effectType);
    value_p = std::get<2>(it->second);							// Set the value based on the potion name
}
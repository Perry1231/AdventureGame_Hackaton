#include "Header.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <limits>

//=============================Main functions=============================
void Character::DisplayStats() 
{
    const int width = 45;

    std::cout << "\n";
    std::cout << "┌" << std::string(width - 2, '─') << "┐\n";
    std::cout << "│ " << std::left << std::setw(width - 4) << "CHARACTER PROFILE" << " │\n";
    std::cout << "├" << std::string(width - 2, '─') << "┤\n";

    // Basic Info
    std::cout << "│ " << std::left << std::setw(15) << "Name:"        << std::setw(width - 19) << name        << " │\n";
    std::cout << "│ " << std::left << std::setw(15) << "Age:"         << std::setw(width - 19) << age         << " │\n";
    std::cout << "│ " << std::left << std::setw(15) << "Race:"        << std::setw(width - 19) << race        << " │\n";
    std::cout << "│ " << std::left << std::setw(15) << "Profession:"  << std::setw(width - 19) << profession  << " │\n";
    std::cout << "│ " << std::left << std::setw(15) << "Level:"       << std::setw(width - 19) << level       << " │\n";
    std::cout << "│ " << std::left << std::setw(15) << "Description:" << std::setw(width - 19) << description << " │\n";

    std::cout << "├" << std::string(width - 2, '─') << "┤\n";
    std::cout << "│ " << std::left << std::setw(width - 4) << "ATTRIBUTES & STATS" << " │\n";
    std::cout << "├" << std::string(width - 2, '─') << "┤\n";

    // Stats
    std::cout << "│ " << std::left << std::setw(15) << "Health:"       << std::setw(width - 19) << health       << " │\n";
    std::cout << "│ " << std::left << std::setw(15) << "Strength:"     << std::setw(width - 19) << strength     << " │\n";
    std::cout << "│ " << std::left << std::setw(15) << "Agility:"      << std::setw(width - 19) << agility      << " │\n";
    std::cout << "│ " << std::left << std::setw(15) << "Intelligence:" << std::setw(width - 19) << intelligence << " │\n";
    std::cout << "│ " << std::left << std::setw(15) << "Defense:"      << std::setw(width - 19) << defense      << " │\n";
    std::cout << "│ " << std::left << std::setw(15) << "Gold:"         << std::setw(width - 19) << gold         << " │\n";

    std::cout << "└" << std::string(width - 2, '─') << "┘\n\n";
}


void Character::RandomizeStats()
{
    race = (rand() % 5 == 0) ? "Human" : (rand() % 4 == 0) ? "Elf" : (rand() % 3 == 0) ? "Dwarf" : (rand() % 2 == 0) ? "Orc" : "Goblin";        // Random race
    

//=============================Professions base===============================================
std::string professions_h[] = {"Warrior", "Mage", "Rogue", "Peasant"}; //For_Human
std::string professions_e[] = { "Archer", "Druid", "Ranger"}; //For_Elf
std::string professions_d[] = {"Blacksmith", "Miner", "Berserker"}; //For_Dwarf
std::string professions_o[] = {"Shaman", "Warlord", "Berserker"}; //For_Orc
std::string professions_g[] = {"Thief", "Assassin", "Scavenger"}; //For_Goblin

//=============================Randomize stats based on profession=============================
   if(race == "Human") profession = professions_h[rand() % 4];
   else if (race == "Elf") profession = professions_e[rand() % 3];
   else if (race == "Dwarf") profession = professions_d[rand() % 3];
   else if (race == "Orc") profession = professions_o[rand() % 3];
   else if (race == "Goblin") profession = professions_g[rand() % 3];
    
//=============================Stats randomizer================================================
if(profession == "Warrior") {
    health = 120;
    Shealth = health;
    level = 1;
    description = "A strong and resilient fighter, skilled in melee combat.";
}
else if (profession == "Mage") {
    health = 70;
    Shealth = health;
    level = 1;
    description = "A master of arcane arts, capable of casting powerful spells.";
}
else if (profession == "Rogue") {
    health = 80;
    Shealth = health;
    level = 1;
    description = "A stealthy and agile character, excelling in sneaking and critical strikes.";
}
else if (profession == "Peasant") {
    health = 70;
    Shealth = health;
    level = 1;
    description = "A simple student with basic study skills, but untapped potential.";
}
else if (profession == "Archer") {
    health = 100;
    Shealth = health;
    level = 1;
    description = "A skilled marksman, proficient with bows and ranged attacks.";
}
else if (profession == "Druid") {
    health = 110;
    Shealth = health;
    level = 1;
    description = "A nature-based spellcaster, able to heal allies and summon creatures.";
}
else if (profession == "Ranger") {
    health = 100;
    Shealth = health;
    level = 1;
    description = "A versatile explorer, adept at navigating campus and surviving exam weeks.";
}
else if (profession == "Blacksmith") {
    health = 120;
    Shealth = health;
    level = 1;
    description = "A master craftsman, able to forge powerful weapons and armor.";
}
else if (profession == "Miner") {
    health = 140;
    Shealth = health;
    level = 1;
    description = "A hardy student, skilled in extracting valuable notes from the library archives.";
}
else if (profession == "Berserker") {
    health = 130;
    Shealth = health;
    level = 1;
    description = "A fierce warrior who thrives in the heat of battle, gaining strength as they fight.";
}
else if (profession == "Shaman") {
    health = 120;
    Shealth = health;
    level = 1;
    description = "A spiritual guide, able to commune with spirits and harness elemental powers.";
}
else if (profession == "Warlord") {
    health = 140;
    Shealth = health;
    level = 1;
    description = "A strategic leader, commanding troops and inspiring allies on the battlefield.";
}
else if (profession == "Thief") {
    health = 80;
    Shealth = health;
    level = 1;
    description = "A cunning and resourceful character, skilled in stealing and deception.";
}
else if (profession == "Assassin") {
    health = 90;
    Shealth = health;
    level = 1;
    description = "A deadly and silent killer, specializing in eliminating targets quickly and efficiently.";
}
else if (profession == "Scavenger") {
    health = 100;
    Shealth = health;
    level = 1;
    description = "A resourceful survivor, adept at finding valuable items and making the most of limited resources.";
}

//=============================Name randomizer=================================================

    std::string firstNames_h[] = {"Arin", "Bryn", "Cora", "Dain", "Eira", "Finn", "Gwen", "Hale", "Iris", "Jax"};
    std::string lastNames_h[] = {"Stormwind", "Shadowbane", "Ironfist", "Silverleaf", "Darkwood", "Brightblade", "Stoneheart", "Moonshadow", "Fireforge", "Duskwhisper"};
   
   std::string firstNames_e[] = {"Elara", "Thalion", "Lirael", "Eldrin", "Sylvara", "Faelar", "Aeris", "Galadriel", "Riven", "Nimriel"};
   std::string lastNames_e[] = {"Starweaver", "Moonwhisper", "Sunblade", "Duskbloom", "Silvermoon", "Shadowdancer", "Windrider", "Nightshade", "Frostfall", "Lightbringer"};
    
   std::string firstNames_d[] = {"Thorin", "Balin", "Dwalin", "Gimli", "Oin", "Gloin", "Dori", "Nori", "Ori", "Bifur"};
   std::string lastNames_d[] = {"Ironforge", "Stonehelm", "Goldbeard", "Hammerfall", "Deepdelve", "Anvilmar", "Bronzebeard", "Fireforge", "Stormhammer", "Frostbeard"};
   

    std::string firstNames_o[] = {"Grommash", "Garrosh", "Thrall", "Durotan", "Orgrim", "Kargathia", "Zul'jin", "Kilrogg", "Nazgrel", "Mok'Nathal"};
    std::string lastNames_o[] = {"Hellscream", "Doomhammer", "Shadowmoon", "Warsong", "Blackrock", "Frostwolf", "Bleeding Hollow", "Shattered Hand", "Burning Blade", "Skullcrusher"};

    std::string firstNames_g[] = {"Loud Larry", "Messy Mike", "Noisy Nick", "Party Paul", "Snoring Sam", "Cluttered Chris", "Chaotic Chad", "Rowdy Ryan", "Boisterous Brad", "Turbulent Tom"};
    std::string lastNames_g[] = {"NoiseMaker", "MessMaster", "ClatterKing", "ChaosLord", "RacketRuler", "DinDuke", "HullabalooHead", "BrouhahaBoss", "UproarUmpire", "TumultTitan"};
  
    if (race == "Human") {
        name = firstNames_h[rand() % 10] + " " + lastNames_h[rand() % 10];
    } 
    else if (race == "Elf") {
        name = firstNames_e[rand() % 10] + " " + lastNames_e[rand() % 10];
    }
    else if (race == "Dwarf") {
        name = firstNames_d[rand() % 10] + " " + lastNames_d[rand() % 10];
    }
    else if (race == "Orc") {
        name = firstNames_o[rand() % 10] + " " + lastNames_o[rand() % 10];
    }
    else if (race == "Goblin") {
        name = firstNames_g[rand() % 10] + " " + lastNames_g[rand() % 10];
    }
//=============================Age randomizer=================================================             
    age = 18 + rand() % 83; // Random age between 18 and 100  



//=============================Stats randomizer based on profession=============================
    if(profession == "Warrior") {
        strength = 25+ rand() % 11; // Random strength between 25 and 35
        agility = 15 + rand() % 11; // Random agility between 15 and 25
        intelligence = 5 + rand() % 6; // Random intelligence between 5 and 10
        defense = 20 + rand() %11; // Random defense between 20 and 28
        gold = 40 + rand() % 21; // Random gold between 40 and 60
    }
    else if (profession == "Mage") {
        strength = 15 + rand() % 6; // Random strength between 15 and 20
        agility = 10 + rand() % 6; // Random agility between 10 and 15
        intelligence =20 + rand() %11; // Random intelligence between 20 and 30
        defense = 8 + rand() % 7; // Random defense between 8 and 15
        gold = 25 + rand() % 21; // Random gold between 25 and 45
    }
    else if (profession == "Rogue") {
        strength = 10 + rand() % 11; // Random strength between 10 and 15
        agility = 15 + rand() % 6; // Random agility between 15 and 20
        intelligence = 10 + rand() % 6; // Random intelligence between 10 and 15
        defense = 10 + rand() % 6; // Random defense between 10 and 15
        gold = 80 + rand() % 21; // Random gold between 80 and 100
    }
    else if (profession == "Peasant") {
        strength = 5 + rand() % 6; // Random strength between 5 and 10
        agility = 8 + rand() % 8; // Random agility between 8 and 15
        intelligence = 8 + rand() % 8; // Random intelligence between 8 and 15
        defense = 5 + rand() % 6; // Random defense between 5 and 10
        gold = 20 + rand() % 11; // Random gold between 20 and 30
    }
    else if (profession == "Archer") {
        strength = 15 + rand() % 11; // Random strength between 15 and 25
        agility = 20 + rand() % 11; // Random agility between 20 and 30
        intelligence = 20 + rand() % 6; // Random intelligence between 20 and 25
        defense = 10 + rand() % 6; // Random defense between 10 and 15
        gold = 50 + rand() % 21; // Random gold between 50 and 70
    }
    else if (profession == "Druid") {
        strength = 5 + rand() % 6; // Random strength between 5 and 10
        agility = 5 + rand() % 5; // Random agility between 5 and 10
        intelligence = 30 + rand() %11; // Random intelligence between 30 and 40
        defense = 12 + rand() % 4; // Random defense between 12 and 15
        gold = 50 + rand() % 21; // Random gold between 50 and 70
    }

    else if (profession == "Ranger") {
        strength = rand() % 15 + 10; // Random strength between 10 and 25
        agility = 20 + rand() % 11; // Random agility between 20 and 30
        intelligence = 15 + rand() % 11; // Random intelligence between 15 and 25
        defense = 15 + rand() % 11; // Random defense between 15 and 25
        gold = 50 + rand() % 21; // Random gold between 50 and 70
    }
    else if (profession == "Blacksmith") {
        strength = 15 + rand() % 11; // Random strength between 15 and 25
        agility = 8 + rand() % 6; // Random agility between 8 and 14
        intelligence = 20 + rand() % 6; // Random intelligence between 20 and 25
        defense = 10 + rand() % 11; // Random defense between 10 and 20
        gold =50 + rand() % 21; // Random gold between 50 and 70
    }
    else if (profession == "Miner") {
        strength = 20 + rand() % 11; // Random strength between 20 and 30
        agility = 5 + rand() % 6; // Random agility between 5 and 10
        intelligence = 15 + rand() % 6; // Random intelligence between 10 and 15
        defense = 15 + rand() % 11; // Random defense between 15 and 25
        gold = 70 + rand() % 21; // Random gold between 70 and 90
    }
    else if (profession == "Berserker") {
        strength = 20 + rand() % 11; // Increased strength for Berserker
        agility = 10 + rand() % 6; // Balanced agility
        intelligence = 5 + rand() % 11; // Lower intelligence for Berserker
        defense = 15 + rand() % 11; // Increased defense for Berserker
        gold = 30 + rand() % 21; // Starting gold for Berserker
    }
    else if (profession == "Shaman") {
        strength = 10 + rand() % 6; // Random strength between 10 and 15
        agility = 8 + rand() % 7; // Random agility between 8 and 15
        intelligence = 25 + rand() % 6; // Random intelligence between 25 and 30
        defense = 12 + rand() % 4; // Random defense between 12 and 15
        gold = 50 + rand() % 21; // Random gold between 50 and 70
    }
    else if (profession == "Warlord") {
        strength = 20 + rand() % 11; // Random strength between 20 and 30
        agility = 15 + rand() % 6; // Random agility between 15 and 20
        intelligence = 15 + rand() % 11; // Random intelligence between 15 and 20
        defense = 15 + rand() % 11; // Random defense between 15 and 25
        gold = 20 + rand() % 21; // Random gold between 20 and 40
    }
    else if (profession == "Thief") {
        strength = 10+ rand() % 6; // Random strength between 10 and 15
        agility = 15 + rand() % 11; // Random agility between 15 and 25
        intelligence = 10 + rand() % 6; // Random intelligence between 10 and 15
        defense = 8 + rand() % 8; // Random defense between 8 and 15
        gold = 80 + rand() % 21; // Random gold between 80 and 100
    }
    else if (profession == "Assassin") {
        strength = 15 + rand() % 6; // Random strength between 12 and 20
        agility = 18 + rand() % 7; // Random agility between 18 and 24
        intelligence = 8 + rand() % 6; // Random intelligence between 8 and 13
        defense = 15 + rand() % 6; // Random defense between 10 and 15
        gold = 70 + rand() % 21; // Random gold between 70 and 90
        age = 18 + rand() % 27; // Random age between 18 and 45 for Assassin
    }
    else if (profession == "Scavenger") {
        strength = 10 + rand() % 6; // Random strength between 10 and 15
        agility = 12 + rand() % 6; // Random agility between 12 and 17
        intelligence = 8 + rand() % 6; // Random intelligence between 8 and 13
        defense = 10 + rand() % 6; // Random defense between 10 and 15
        gold = 80 + rand() % 21; // Random gold between 80 and 100
    }

    //=============================End of randomization=============================
}

std::string GetEffectName(int type) {
    switch (type) {
        case 0: return "Health";break;
        case 1: return "Defense";break;
        case 2: return "Agility";break;
        case 3: return "Intelligence";break;
        case 4: return "Gold";break;
        case 5: return "Strength";break;
        default: return "Unknown";break;
    }
}

void Character::EquipWeapon(Weapon* w)
{
    if (equipped_weapon) {
        equipped_weapon->Reset(); 
    }
    equipped_weapon = w;
    if (equipped_weapon) {
        equipped_weapon->Use(); 
         GetTotalAttack();
        GetTotalDefense();  
    }
}

void Character::EquipArmor(Armory* a)
{
    if (equipped_armor) {
        equipped_armor->Reset(); 
    }
    equipped_armor = a;
    if (equipped_armor) {
        equipped_armor->Use(); 
        GetTotalAttack();
        GetTotalDefense();  
    }
    
}

void Character::UnequipWeapon()
{
 if (equipped_weapon) {
        equipped_weapon->Reset();
        equipped_weapon = nullptr;
    }
}

void Character::UnequipArmor()
{
 if (equipped_armor) {
        equipped_armor->Reset();
        equipped_armor = nullptr;
    }
}


void Character::Usage()
{
    std::cout << "\n" << this->name << " is using their equipment...\n";
    std::cout << "=== Equipped Gear ===\n";
    if (equipped_weapon) {
        std::cout << "Weapon: " << equipped_weapon->GetName() << std::endl;
        equipped_weapon->ShowInfo();
    } else {
        std::cout << "Weapon: None\n";
    }
    if (equipped_armor) {
        std::cout << "Armor: " << equipped_armor->GetName() << std::endl;
        equipped_armor->ShowInfo();
    } else {
        std::cout << "Armor: None\n";
    }
    std::cout << "=== Total Stats ===\n";
    std::cout << "Total Attack: " << GetTotalAttack() << std::endl;
    std::cout << "Total Defense: " << GetTotalDefense() << std::endl;
    if (!activeEffects.empty()) {
        std::cout << "Active Effects:\n";
        for (const auto& eff : activeEffects) {
            std::cout << "- " << GetEffectName(eff.type) << (eff.isDebuff ? " (Debuff)" : " (Buff)") << ": " << eff.potency << std::endl;
        }
    }
    std::cout << "=====================\n";
}


void Character::Take() {
    if (!currentChest) {
        std::cout << "No chest selected!\n";
        return;
    }
    int itemCount = currentChest->GetItemCount();
    if (itemCount == 0) {
        std::cout << "Chest is empty!\n";
        return;
    }
    std::cout << "\n=== Items in chest ===\n";
    for (int i = 0; i < itemCount; ++i) {
        Item* chestItem = currentChest->GetItem(i);
        std::cout << i + 1 << ". ";
        if (chestItem) chestItem->ShowInfo();
    }
    std::cout << "0. Cancel\n";
    std::cout << "Select item to take: ";
    int choice = ChoiceInput_Number();
    if (choice == 0) return;
    if (choice < 1 || choice > itemCount) {
        std::cout << "Invalid choice!\n";
        return;
    }
    Item* selectedItem = currentChest->GetItem(choice - 1);
    if (!selectedItem) {
        std::cout << "Item no longer available!\n";
        return;
    }
    if (inventory) {
        inventory->AddItem(selectedItem);  // <-- use inventory->, not inventory
        currentChest->RemoveItem(choice - 1);
        std::cout << "Successfully taken " << selectedItem->GetName() << "!\n";
    } else {
        std::cout << "Inventory not linked to character!\n";
    }
}

void Character::TakeAll() {
    if (!currentChest) {
        std::cout << "No chest selected!\n";
        return;
    }
    int itemCount = currentChest->GetItemCount();
    if (itemCount == 0) {
        std::cout << "Chest is already empty!\n";
        return;
    }
    std::cout << "\nTaking all items from chest...\n";
    if (!inventory) {
        std::cout << "Inventory not linked to character!\n";
        return;
    }
    for (int i = itemCount - 1; i >= 0; --i) {
        Item* item = currentChest->GetItem(i);
        if (!item) continue;
        inventory->AddItem(item);  // <-- same here: inventory->
        currentChest->RemoveItem(i);
        std::cout << "- Taken " << item->GetName() << std::endl;
    }
    std::cout << "All items transferred to inventory!\n";
}

void Character::ApplyPotionEffect(int effectType, int potency) {
    switch (effectType) {
        case 0: // HEALTH
            health += potency;
            std::cout << name << " restored " << potency << " HP!" << std::endl;
            break;
        case 1: // DEFENSE
            defense += potency;
            std::cout << name << " defense increased by " << potency << std::endl;
            break;
        case 2: // AGILITY
            agility += potency;
            std::cout << name << " agility increased by " << potency << std::endl;
            break;
        case 3: // INTELLIGENCE
            intelligence += potency;
            std::cout << name << " intelligence increased by " << potency << std::endl;
            break;
        case 4: // GOLD
            gold += potency;
            std::cout << name << " got " << potency << " gold!" << std::endl;
              break;
             case 5: // STRENGTH
        strength += potency;
        std::cout << name << " strength increased by " << potency << std::endl;
        break;
        default:
            std::cout << "Unknown potion effect!" << std::endl;
    }
}

void Character::ApplyArtifactEffect(int effectType, int power)
{
 switch (effectType) {
        case 0: // HEALTH
            health += power;
            std::cout << name << " restored " << power << " HP!" << std::endl;
            break;
        case 1: // DEFENSE
            defense += power;
            std::cout << name << " defense increased by " << power << std::endl;
            break;
        case 2: // AGILITY
            agility += power;
            std::cout << name << " agility increased by " << power << std::endl;
            break;
        case 3: // INTELLIGENCE
            intelligence += power;
            std::cout << name << " intelligence increased by " << power << std::endl;
            break;
        case 4: // GOLD
            gold += power;
            std::cout << name << " got " << power << " gold!" << std::endl;
              break;
             case 5: // STRENGTH
        strength += power;
        std::cout << name << " strength increased by " << power << std::endl;
        break;
        default:
            std::cout << "Unknown artifact effect!" << std::endl;
    }
}

Weapon* Character::GetEquippedWeapon() const { return equipped_weapon; } 
Armory* Character::GetEquippedArmor() const { return equipped_armor; } 
int Character::GetTotalAttack() const { return strength + (equipped_weapon ? equipped_weapon->GetAttack() : 0); } 
int Character::GetTotalDefense() const { return defense + (equipped_armor ? equipped_armor->GetDefense() : 0); }

void Character::AddEffect(int type, int potency, bool debuff) {
    ActiveEffect eff;
    eff.type = type;
    eff.potency = potency;
    eff.isDebuff = debuff;
    activeEffects.push_back(eff);
    std::cout << name << " gained effect: " << GetEffectName(type);
}

void Character::ProcessEffects()
{
    for (auto it = activeEffects.begin(); it != activeEffects.end(); )
    {
        switch (it->type)
        {
        case 0: // HEALTH
            if (it->isDebuff)
            {
                if (health != Shealth)
                {
                    health += it->potency;
                    std::cout << name << " takes " << (-it->potency) << " poison damage! (HP: " << health << ")\n";
                }
                else
                    std::cout << name << " is at full health.\n";
            }
            // No action needed for HEALTH buffs because potions apply instantly
            break;
        case 1: defense += it->potency; break;
        case 2: agility += it->potency; break;
        case 3: intelligence += it->potency; break;
        case 4: gold += it->potency; break;
        case 5: strength += it->potency; break;
        }
        it = activeEffects.erase(it);
    }
}


char Character::GetType(AuraType type)
{
this->auraType = type;
std::cout << "Aura: " << auraType << std::endl;
return auraType;
}

int Character::GetDamage(Character& hero, int damage, MyInventory& inv1, GameHard& difficultyLevel) const
{
damage = hero.GetTotalDefense() - damage;  
if (damage < GetTotalDefense())
{
    std::cout << "You take " << damage << " damage! (HP: " << health << ")\n";
}
else if (damage >= GetTotalDefense())
{
    std::cout << "Too much damage! You take " << damage << ")\n";
    std::cout << "You are dead! Game over!" << std::endl;

    int ch=0;
    std::cout << "Do you want to restart the game? (1 - Yes, 2 - No): ";
    std::cin >> ch;
    if(ch == 1) {
        std::cout << "Restarting the game..." << std::endl;
        Reseter(hero, inv1, difficultyLevel); // Exit the program to allow for a restart
    } else {
        std::cout << "Exiting the game. Goodbye!" << std::endl;
        std::exit(0);
    }
}
  return damage;
}

int Character::GetTotalHealth() const
{
    return health;
}
//============================================================Actions_with_others================================================================================

void Character::Attack(Character& hero, Enemy& enemy)
{
    enemy.SetAttitude(-1);

    std::cout << "You attack the " << enemy.GetName() << "!" << std::endl;
    {
        int damage = hero.GetTotalAttack() - enemy.GetTotalDefense();
        if (damage < 0) damage = 0;
        enemy.ApplyPotionEffect(0, -damage);
        std::cout << enemy.GetName() << " takes " << damage << " damage! (HP: " << enemy.GetHealth() << ")\n";

        if (enemy.GetHealth() <= 0) {
            std::cout << "You have defeated " << enemy.GetName() << "!" << std::endl;
            hero.SetLevel(hero.GetLevel() + 0.1);
            hero.SetGold(hero.GetGold() + enemy.GetGold());
            return;
        }

        int counterDamage = enemy.GetTotalAttack() - hero.GetTotalDefense();
        if (counterDamage < 0) counterDamage = 0;
        hero.SetHealth(hero.GetHealth() - counterDamage);
        std::cout << enemy.GetName() << " strikes back for " << counterDamage << " damage! (Your HP: " << hero.GetHealth() << ")\n";
        hero.SetLevel(hero.GetLevel() + 0.01);

        if (hero.GetHealth() <= 0) {
            std::cout << "You have been defeated by " << enemy.GetName() << "! Game over!" << std::endl;
            std::exit(0);
        }
    }
}

void Character::DamageSystem(Enemy& enemy)
{

std::cout << "---------------------------------------------------------" << std::endl;
std::cout << "|| " << name << "           ||            " << enemy.GetName() << " ||" << std::endl;
std::cout << "|| " << "Your total attack = " << GetTotalAttack() << "  ||  " << "Enemy total defense = " << enemy.GetTotalDefense() << " ||" << std::endl;
std::cout << "|| " << "Your total defense = " << GetTotalDefense() << "  ||  " << "Enemy total attack = " << enemy.GetTotalAttack() << " ||" << std::endl;
std::cout << "||\t\t\t\t\t\t\t\t||" << std::endl;
std::cout << "||"  << "Attack - 1" << std::endl;
std::cout << "||"  << "Look in your inventory - 3" << std::endl;
std::cout << "||"  << "Leave battle - 2" << std::endl;
int choice = ChoiceInput_Number();
switch (choice)
{
    case 1:
        std::cout << "You are going to attack enemy" << std::endl;
        Attack(*this, enemy);
        break;
    case 2:
        std::cout << "You left the battle!" << std::endl;
        break;
    case 3:
        if (inventory) {
            inventory->DisplayInventory();
        } else {
            std::cout << "Inventory is empty or not linked." << std::endl;
        }
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
        break;
}


}



void Menu(Enemy& enemy, Character& hero, MyInventory& inv1, GameHard& difficultyLevel)
{
    int choice = 0;

    std::cout << "\n┌──────────────────────────────────────┐\n"
              << "│            INTERACTION               │\n"
              << "├──────────────────────────────────────┤\n"
              << "│  [1] Talk                            │\n"
              << "│  [2] Attack                          │\n"
              << "│  [3] Trade                           │\n"
              << "│  [4] Leave                           │\n"
              << "└──────────────────────────────────────┘\n"
              << "Select an action: ";

    // Handle non-integer inputs gracefully to prevent infinite loops
    if (!(std::cin >> choice)) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n[!] Invalid input. Please enter a valid number.\n";
        return;
    }

    std::cout << "\n";

    switch (choice)
    {
        case 1:
            std::cout << "💬 You talk to the " << enemy.GetName() << ".\n";
            hero.Talk(enemy);
            break;
        case 2:
            std::cout << "⚔️ You attack the " << enemy.GetName() << "!\n";
            hero.DamageSystem(enemy);
            break;
        case 3:
            std::cout << "🪙 You start trading with the " << enemy.GetName() << ".\n";
            hero.Trade(enemy);
            break;
        case 4:
            std::cout << "🚪 You leave the area.\n";
            break;
        default:
            std::cout << "❌ Invalid choice. Please select an option between 1 and 4.\n";
            break;
    }
}




int Character::Trade(Enemy& enemy)
{
    if(enemy.GetAttitude() < 0)
    {
        std::cout << "You have bad attitude to your opponent !!! \n You can't talk and trade " << std::endl;
        return 0;
    }

    Weapon* weapon_2 = new Weapon();
    weapon_2->RandomizeWeaponStart(enemy.GetProfession());

    Armory* armor_2 = new Armory();
    armor_2->RandomizeArmorStart();

    Weapon* weapon_3 = new Weapon();
    weapon_3->RandomizeWeaponSpeacial();

    MyInventory inv2;
    inv2.SetOwner(&enemy);
    enemy.SetInventory(&inv2);

    inv2.AddItem(weapon_2);
    inv2.AddItem(armor_2);
    inv2.AddItem(weapon_3);

    std::cout << "\n" << enemy.GetName() << " offers you the following goods:\n";
    inv2.DisplayInventory();

    std::cout << "Enter item ID to buy (0 to leave): ";
    int itemId = ChoiceInput_Number();
    if (itemId == 0) {
        std::cout << "You leave the trade.\n";
        return 0;
    }

    for (int i = 0; i < inv2.GetCount(); i++) {
        Item* item = inv2.GetItem(i);
        if (item && item->GetItemId() == itemId) {
            int price = item->GetValue();
            if (GetGold() < price) {
                std::cout << "You don't have enough gold! (Need " << price << ", have " << GetGold() << ")\n";
                return 0;
            }
            SetGold(GetGold() - price);
            if (inventory) {
                inventory->AddItem(item);
                inv2.RemoveFromArray(i);
                std::cout << "Bought " << item->GetName() << " for " << price << " gold!\n";
            } else {
                std::cout << "Inventory not linked to character!\n";
            }
            return 0;
        }
    }

    std::cout << "Item not found!\n";
    return 0;
}


int Character::Talk(Enemy& enemy)
{
    if(enemy.GetAttitude() < 0)
    {
        std::cout << "You have bad attitude to your opponent !!! \n You can't talk and trade " << std::endl;
        return 0;
    }

    std::cout << "\n" << enemy.GetName() << " says: 'Hello there! I'm ready for adventure.'\n";
    std::cout << "`Do what you want` ---->" << std::endl;
    std::cout << "1 - Take task \n2 - Talk about life \n3 - Leave" << std::endl;
    int choice=ChoiceInput_Number();
    switch(choice)
    {
        case 1:
        Task_Generator();
        break;
        case 2:
        Talk_About_Life();
        break;
        case 3:

        break;
        default: std::cout << "Wrong choice !" << std::endl;
    }
    return 0;
}


void Character::Fight(Enemy& enemy)
{
    std::cout << "You engage in combat with " << enemy.GetName() << "!" << std::endl;
    while (health > 0 && enemy.GetHealth() > 0) {
        DamageSystem(enemy);
        if (enemy.GetHealth() <= 0) {
            std::cout << "You have defeated " << enemy.GetName() << "!" << std::endl;
            break;
        }
        if (health <= 0) {
            std::cout << "You have been defeated by " << enemy.GetName() << "! Game over!" << std::endl;
            std::exit(0);
        }
    }
}

// OtherCharacter interaction functions
int Character::Talk(OtherCharacter& other)
{
    if (other.GetAttitude() < -50) {
        std::cout << other.GetName() << " ignores you completely.\n";
        return 0;
    }

    other.DisplayInfo();
    
    std::cout << "\n" << other.GetName() << ": \"Hey! What's up?\"\n";
    std::cout << "1. Ask for a task/quest\n";
    std::cout << "2. Chat about campus life\n";
    std::cout << "3. Ask about the area\n";
    std::cout << "4. Trade (if merchant)\n";
    std::cout << "5. Leave\n";
    std::cout << "Choice: ";
    
    int choice = ChoiceInput_Number();
    
    switch(choice) {
        case 1:
            Task_Generator();
            other.SetAttitude(other.GetAttitude() + 5);
            break;
        case 2:
            std::cout << "\nYou chat about classes, exams, and dorm life.\n";
            other.SetAttitude(other.GetAttitude() + 10);
            SetHealth(GetHealth() + 5);
            break;
        case 3:
            std::cout << "\n" << other.GetName() << ": \"This area has the dorms, library, student union, and academic buildings.\"";
            std::cout << " The dining hall is on the first floor.\"\n";
            other.SetAttitude(other.GetAttitude() + 5);
            break;
        case 4:
            if (other.GetType() == MERCHANTS || other.GetType() == VENDOR) {
                Trade(other);
            } else {
                std::cout << "\n" << other.GetName() << ": \"I don't have anything to trade.\"\n";
            }
            break;
        case 5:
            std::cout << "\nYou say goodbye.\n";
            break;
        default:
            std::cout << "\nInvalid choice.\n";
    }
    return 0;
}

int Character::Trade(OtherCharacter& other)
{
    if (!other.GetInventory()) {
        std::cout << other.GetName() << " has nothing to trade.\n";
        return 0;
    }

    std::cout << "\n" << other.GetName() << " shows you their wares:\n";
    other.GetInventory()->DisplayInventory();
    
    std::cout << "Enter item ID to buy (0 to leave): ";
    int itemId = ChoiceInput_Number();
    if (itemId == 0) {
        std::cout << "You leave the trade.\n";
        return 0;
    }

    MyInventory* inv = other.GetInventory();
    for (int i = 0; i < inv->GetCount(); i++) {
        Item* item = inv->GetItem(i);
        if (item && item->GetItemId() == itemId) {
            int price = item->GetValue();
            if (GetGold() < price) {
                std::cout << "Not enough gold! Need " << price << ", have " << GetGold() << "\n";
                return 0;
            }
            SetGold(GetGold() - price);
            if (inventory) {
                inventory->AddItem(item);
                inv->RemoveFromArray(i);
                std::cout << "Bought " << item->GetName() << " for " << price << " gold!\n";
                other.SetAttitude(other.GetAttitude() + 5);
            } else {
                std::cout << "Your inventory is not linked!\n";
            }
            return 0;
        }
    }
    std::cout << "Item not found!\n";
    return 0;
}

void Character::Attack(OtherCharacter& other)
{
    std::cout << "\n⚔️ You attack " << other.GetName() << "!\n";
    std::cout << "This is a peaceful campus. Violence is not the answer.\n";
    other.SetAttitude(other.GetAttitude() - 50);
    std::cout << other.GetName() << " is shocked and reports you to campus security!\n";
    SetHealth(GetHealth() - 10); // Security response
    std::cout << "You take 10 damage from security response.\n";
}

void Character::DamageSystem(OtherCharacter& other)
{
    // Non-combat interaction - just a placeholder for future combat with hostile NPCs
    std::cout << "DamageSystem not implemented for peaceful NPCs.\n";
}

int Character::Interact(OtherCharacter& other)
{
    std::cout << "\n┌─────────────────────────────────────────────────────┐\n";
    std::cout << "│           INTERACT WITH " << other.GetName();
    int padding = 42 - other.GetName().length();
    for (int i = 0; i < padding; i++) std::cout << " ";
    std::cout << "│\n";
    std::cout << "├─────────────────────────────────────────────────────┤\n";
    std::cout << "│  1. Talk                                            │\n";
    std::cout << "│  2. Trade                                           │\n";
    std::cout << "│  3. Attack (not recommended)                        │\n";
    std::cout << "│  4. Leave                                           │\n";
    std::cout << "└─────────────────────────────────────────────────────┘\n";
    std::cout << "Choice: ";
    
    int choice = ChoiceInput_Number();
    
    switch(choice) {
        case 1: return Talk(other);
        case 2: return Trade(other);
        case 3: Attack(other); return 0;
        case 4: std::cout << "You walk away.\n"; return 0;
        default: std::cout << "Invalid choice.\n"; return 0;
    }
}



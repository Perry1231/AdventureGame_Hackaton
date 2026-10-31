#ifndef Header_h
#define Header_h
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>

class Weapon;
class Armory;
class Character;
class Inventory;
class Item;
class OtInventory;
class Potion;
class MyInventory;  
class Chest; 
class Enemy;
class GameHard;

enum ChestType { COMMON = 52, RARE = 28, EPIC=15, LEGENDARY=5 };
enum EffectType { HEALTH, DEFENSE, AGILITY, INTELLIGENCE, GOLD, STRENGTH }; 
enum AuraType {WORST,BAD,MEDIUM,GOOD,EXCELLENT};
enum ArtifactRarity { COMMON_ARTIFACT, RARE_ARTIFACT, EPIC_ARTIFACT, LEGENDARY_ARTIFACT, UKNOWN_RARITY};
//=====================================================Item_structure==========================================
class Item {
private:
int itemId;
public:
    virtual ~Item() {}
    virtual void ShowInfo() const = 0;
    virtual std::string GetName() const = 0;
    virtual std::string GetType() const = 0;
    int GetItemId() const { return itemId; }
    void SetItemId(int id) { itemId = id; }

    virtual void Use() = 0;
    virtual void Reset() = 0;

};

//=======================================================================Character_structure===================================================================================
struct ActiveEffect {
    int type;     
    int potency;    
    bool isDebuff;  
};
class Character
{
    protected :
int health;
int Shealth;
std::string name;
int age;
std::string race;
std::string profession;
int level;
std::string description;
int strength;
int agility;
int intelligence;
int defense;
int gold;
AuraType auraType;
std::vector<ActiveEffect> activeEffects; 


Weapon* equipped_weapon;                //For equipment
Armory* equipped_armor;
MyInventory* inventory;      //Character inventory
Chest* currentChest;


    public :
//Default constructo 
Character() : health(100), Shealth(100), name ("Hero"), age(20), race("Human"),
profession("Adventurer"), level(1), description("A brave adventurer ready to explore the world."),
strength(10), agility(10), intelligence(10), defense(10), gold(100),auraType(MEDIUM) ,
equipped_weapon(nullptr), equipped_armor(nullptr),
inventory(nullptr), currentChest(nullptr) {} 

//Parameterized constructor
Character(int health_, std::string name_, int age_, std::string race_, std::string profession_, int level_, 
        std::string description_, int strength_, int agility_, int intelligence_, int defense_, int gold_) : health(health_), name(name_),
        age(age_), race(race_), profession(profession_), level(level_), description(description_), strength(strength_), agility(agility_),  
        intelligence(intelligence_), defense(defense_), gold(gold_) , auraType(MEDIUM) {}
    
    void DisplayStats();
    void RandomizeStats();
        

    char GetType(AuraType type);
    void EquipWeapon(Weapon* w); 
    void EquipArmor(Armory* a); 

    Weapon* GetEquippedWeapon() const;
    Armory* GetEquippedArmor() const; 

    //Battling
    int GetDamage(Character& hero, int damage, MyInventory& inv, GameHard& difficultyLevel) const;                  
    int GetTotalAttack() const; 
    int GetTotalDefense() const; 
    int GetTotalHealth() const;
    void UnequipWeapon(); 
    void UnequipArmor();

    int GetGold() const { return gold; }
    int GetHealth() const { return health; }
    int GetLevel() const { return level; }
    int GetDefense() const { return defense; }
    int GetStrength() const { return strength;}
    int GetAgility() const { return agility; }
    int GetIntelligence() const { return intelligence;}
    int GetAge() const {return age;}
    std::string GetRace() const {return race;}
    std::string GetDescription() const {return description;}
    std::string GetName() const { return name; }


    void Take();
    void TakeAll();

    void SetName(const std::string& n) { name = n; }
    void SetAge(int a) { age = a; }
    void SetRace(const std::string& r) { race = r; }
    void SetProfession(const std::string& p) { profession = p; }
    void SetLevel(int l) { level = l; }
    void SetDescription(const std::string& d) { description = d; }
    void SetStrength(int s) { strength = s; }
    void SetAgility(int a) { agility = a; }
    void SetIntelligence(int i) { intelligence = i; }
    void SetDefense(int d) { defense = d; }
    void SetGold(int value) { gold = value; if (gold < 0) gold = 0; }
    void SetInventory(MyInventory* inv) { inventory = inv; }
    void SetCurrentChest(Chest* chest) { currentChest = chest; }
    Chest* GetCurrentChest() const { return currentChest; }
    MyInventory* GetInventory() const { return inventory; } 

    void ApplyPotionEffect(int effectType, int potency);
    void ApplyArtifactEffect(int effectType, int power);

    void ProcessEffects(); 
    void AddEffect(int type, int potency, bool debuff = false);

    void SetHealth(int value) { health = value; if (health < 0) health = 0; if (health > Shealth) health = Shealth; }
    std::string GetProfession() const { return profession; };
    void Usage();
    
    //Interaction
    void Talk_About_Life();
    void Task_Generator();
    void Fight(Enemy& enemy);
    int Trade(Enemy& enemy);
    int Talk(Enemy& enemy);
    void Attack(Character& hero, Enemy& enemy);
    void DamageSystem(Enemy& enemy);

    ~Character(){};
};


//============================================================================Weapon_structure=============================================================================
class Weapon : public Item  
{
protected:
    bool isEquipped_w;
    bool isBroken_w;
    bool isEnchanted_w;
    int attack_w;
    int defend_w;
    float durability_w;
    int value_w;
    std::string name_w;

    public :
Weapon() : isEquipped_w(false), isBroken_w(false), 
 isEnchanted_w(false), attack_w(0), defend_w(0), durability_w(100), value_w(0), name_w("")  {}Weapon(std::string name_)
{
    this->name_w = name_;
    this->attack_w = 0;
    this->defend_w = 0;   
    this->durability_w = 100; // Default durability
    this->value_w = 0; 
    this->isEquipped_w = false;
    this->isBroken_w = false;
    this->isEnchanted_w = false;
}
Weapon(std::string name_, int attack_) : Weapon(name_)
{
    this->attack_w = attack_;
}
Weapon(std::string name_, int attack_, int defend_) : Weapon(name_, attack_)
{
    this->defend_w = defend_;
}
Weapon(std::string name_, int attack_, int defend_, float durability_) : Weapon(name_, attack_, defend_)
{
    this->durability_w = durability_; 
}
Weapon(std::string name_, int attack_, int defend_, float durability_, int value_) : Weapon(name_, attack_, defend_, durability_)
{
    this->value_w = value_;
}
Weapon(std::string name_, int attack_, int defend_, float durability_, int value_, bool isEquipped_) : Weapon(name_, attack_, defend_, durability_, value_)
{
    this->isEquipped_w = isEquipped_;
}
Weapon(std::string name_, int attack_, int defend_, float durability_, int value_, bool isEquipped_, bool isBroken_) : Weapon(name_, attack_, defend_, durability_, value_, isEquipped_)
{
    this->isBroken_w = isBroken_;
}
Weapon(std::string name_, int attack_, int defend_, float durability_, int value_, bool isEquipped_, bool isBroken_, bool isEnchanted_) : Weapon(name_, attack_, defend_, durability_, value_, isEquipped_, isBroken_)
{
    this->isEnchanted_w = isEnchanted_;
}
    


    void Use() override;
    void Reset() override;

    
    int GetAttack() const { return attack_w; };                                                      
    int GetDurability() const{ return durability_w; };  
    int GetValue() const { return value_w;};
    bool IsBroken() const { return isBroken_w;};
    bool IsEnchanted() const { return isEnchanted_w;};
    std::string RandomizeWeaponStart(const std::string& profession);
    void BrokenWeapon();
    std::string  RandomizeWeaponSpeacial();
    bool IsUsable() const { return !isBroken_w && durability_w > 0; }

    std::string RandomizeWeapon(); 
    void ShowInfo() const override ;
    std::string GetName() const override { return name_w; }
    std::string GetType() const override { return "Weapon"; }

    virtual ~Weapon() {}
};


//=======================================================================Armory_strucuture==========================================================================
class Armory : public Item
{
    protected :
bool isEquipped_a;
bool isBroken_a;
bool isEnchanted_a;
int defend_a;
float durability_a;
int value_a;
std::string name_a;


    public:
Armory() :isEquipped_a(false), isBroken_a(false),
 isEnchanted_a(false), defend_a(0), durability_a(100), value_a(0), name_a("") {}Armory(std::string name_a)
{
    this->name_a = name_a;
    this->defend_a = 0;   
    this->durability_a = 100; // Default durability
    this->value_a = 0; 
    this->isEquipped_a = false;
    this->isBroken_a = false;
    this->isEnchanted_a = false;
}
Armory(std::string name_a, int defend_) : Armory(name_a)
{
    this->defend_a = defend_;
}
Armory(std::string name_a, int defend_, float durability_) : Armory(name_a,  defend_)
{
    this->durability_a = durability_; 
}
Armory(std::string name_a,  int defend_, float durability_, int value_) : Armory(name_a,  defend_, durability_)
{
    this->value_a = value_;
}
Armory(std::string name_a,  int defend_, float durability_, int value_, bool isEquipped_) : Armory(name_a,  defend_, durability_, value_)
{
    this->isEquipped_a = isEquipped_;
}
Armory(std::string name_a,  int defend_, float durability_, int value_, bool isEquipped_, bool isBroken_) : Armory(name_a, defend_, durability_, value_, isEquipped_)
{
    this->isBroken_a = isBroken_;
}
Armory(std::string name_a,  int defend_, float durability_, int value_, bool isEquipped_, bool isBroken_, bool isEnchanted_) : Armory(name_a,  defend_, durability_, value_, isEquipped_, isBroken_)
{
    this->isEnchanted_a = isEnchanted_;
}

void Use();
void Reset();
int GetDefense() const { return defend_a; }
int GetDurability() const { return durability_a;}
int GetValue() const { return value_a; }
bool IsBroken() const { return isBroken_a; }
bool IsEnchanted() const { return isEnchanted_a; }
 

bool IsUsable() const { return !isBroken_a && durability_a > 0; }
void BrokenArmory();
void ShowInfo() const override;
std::string RandomizeArmor();
std::string RandomizeArmorSpecial();
std::string RandomizeArmorStart();
std::string GetName() const override { return name_a; }
std::string GetType() const override { return "Armor"; }
 

virtual ~Armory() {}
};


//=======================================================================Inventory_structure===========================================================================
 class MyInventory              //!!!
 {
 private:
 Item** items;
 int capacity;                  //Capacity of inventory given
 int count;                     //How many items now
 int id;
 Character* owner;

 public:
 MyInventory() : items(nullptr) , capacity(0), count(0), id(1), owner(nullptr) {}




void SetOwner(Character* c) { owner = c; }
void DisplayInventory() const;
int GetCount() const { return count;}
int GetCapacity() const {return capacity;}
int AddItem(Item* item);
Item* GetItem(int index) const;

void Clear(); //Additional
int DelItem(int id);
int ResizeInventoryBig();
void InventoryFunctions();


~MyInventory(){for (int i = 0; i < count; i++)
        delete items[i];
    delete[] items;}
};
void HelpFunction() ;





class OtInventory
{
private:
    int size=1;
     int *ot_inv_mass = new int [size];                         //Other character inventory (trader , ...)

public:            
OtInventory() : size(0), ot_inv_mass(nullptr) {}



int GetSize() const { return size; }
int* GetInventory() const { return ot_inv_mass; }


~OtInventory(){delete[] ot_inv_mass;}
};
//==================================================================Potion_structure=========================================================================================

class Potion : public Item
{
protected:
    std::string name_p;
    int effectType; 
    int potency;                                    // How strong the potion is              
    std::string description_p;
    bool isEquipped_p;
    int value_p;                                    // Value of the potion in gold
    Character* owner_p;

public:
    Potion() : name_p(""), effectType(0), potency(0), description_p(""), isEquipped_p(false), value_p(0) {}

    Potion (std::string name_, int effectType_, int potency_, std::string description_, int value_)
: name_p(name_), effectType(effectType_), potency(potency_),
description_p(description_), isEquipped_p(false), value_p(value_) {}
// Example effect types (6)

    int GetValue() const { return value_p; }
    std::string GetName() const override { return name_p; }
    std::string GetType() const override { return "Potion"; }
    int GetEffectType() const { return effectType; }
    int GetPotency() const { return potency; }
    std::string GetDescription() const { return description_p; }

    bool IsEquipped() const { return isEquipped_p; }
    void SetEquipped(bool equipped) { isEquipped_p = equipped; }
    void SetValue(int val) { value_p = val; }

    void ApplyEffect(Character* target);

    void RandomizePotion();
    void ShowInfo() const override ;
    void Use() override;
    void Reset() override;

    Character* GetOwner() const { return owner_p; } 
    void SetOwner(Character* c) { owner_p = c; }   

    virtual ~Potion() {}
};
//==================================================================Artifact_structure======================================================================================
class Artifact : public Item
{
    protected:
        std::string name;
        std::string description;
        int effectType; 
        int value;
        int power;
        bool isEquipped;
        Character* owner_p;
        
        ArtifactRarity rarityType;
    public:

Artifact() : name(""), description(""),effectType(0) ,value(0) ,power(0), isEquipped(false), rarityType(COMMON_ARTIFACT){}

    Artifact (std::string name_, std::string description_,int EffectType_ ,int value_, int power_, bool isEquipped, ArtifactRarity rarityType_)
: name(name_), description(description_), effectType(EffectType_),value(value_), power(power_), isEquipped(isEquipped), rarityType(rarityType_) {}

    int GetArtifactValue() const { return value; }
    int GetArtifactPower() const { return power; }
    std::string GetName() const override { return name; }
    std::string GetArtifactDescription() const { return description; }
    int GetEffectType() const { return effectType; }
    void GetArtifactRarity() const { std::cout << "Artifact Rarity: " << rarityType << std::endl; }

    std::string GetType() const override { return "Artifact"; }
    void ShowInfo() const override ;
    void Use() override;
    void Reset() override;
    std::string RandomizeArtifact();
    void ApplyEffect(Character* character);

    Character* GetOwner() const { return owner_p; } 
    void SetOwner(Character* c) { owner_p = c; } 
    int SetArtifactName(std::string name_) { name = name_; return 0; }
    int SetArtifactDescription(std::string description_) { description = description_; return 0; }
    int SetArtifactPower(int power_) { power = power_; return 0; }
    int SetArtifactValue(int value_) { value = value_; return 0; }
    int SetArtifactRarity(ArtifactRarity rarity_) { rarityType = rarity_; return 0; }

    virtual ~Artifact() {}
};
//==================================================================Chest_structure=========================================================================================
class Chest
{
protected :
    bool isOpen;
    std::vector<Item*> items;

    ChestType chestType;
    int capacity;
    Chest() : isOpen(false),  chestType(COMMON) , capacity(0){}

public:
    void ChestCreate(ChestType type, Character& hero);
    void RandomizeChest(Character& hero);
    void Open(Character* target);
    bool IsOpen() const{ return isOpen && capacity > 0; };
    void Close();
    void ShowInfo() const;
    void ShowItems() const;


    int GetItemCount() const { return items.size(); }
    Item* GetItem(int index) const { 
    return nullptr; 
}

~Chest(){}
    void RemoveItem(int index);
};
//==================================================================Other_Character============================================================================
enum CharacterType{QUESTGIVERS, MERCHANS, ALLIES, ANTAGONISTS};
class OtherCharacter
{
    protected:
        CharacterType ctype;

    public:
        
        OtherCharacter() : ctype(QUESTGIVERS) {}
        
        CharacterType GetType() const { return ctype; }
        void SetType(CharacterType type) { ctype = type; }
        
        static OtherCharacter CreateQuestGiver();
        static OtherCharacter CreateMerchant();

};

//=================================================================Enemy_class================================================================================
class Enemy : public Character
{
protected:
	int attitude;
public:
	Enemy() : Character(100, "Stranger", 25, "Human", "Warrior", 1, "a mysterious stranger", 20, 10, 10, 15, 50), attitude(1) {}

	Enemy(std::string name_, std::string description_, std::string race_, std::string profession_, int strength_, int health_, int age_, int defense_, int gold_, int level_, bool attitude_)
	: Character(health_, name_, age_, race_, profession_, level_, description_, strength_, 10, 10, defense_, gold_), attitude(attitude_) {}

	void DisplayStatsEnemy();
	void RandomizeStats();
	void EquipWeapon(Weapon* w);
	void EquipArmor(Armory* a);
	void ApplyPotionEffect(int effectType, int potency);
	void ProcessEffects();
	void AddEffect(int type, int potency, bool debuff = false);

	void SetAttitude(int attitude_g);
	int GetAttitude() const { return attitude; }
    void SetHealth(int value) { health = value; if (health < 0) health = 0; if (health > Shealth) health = Shealth; }
    void SetStrength(int value) { strength = value; if (strength < 0) strength = 0; }


    std::string GetName() const {return name;}
	// Battling
	int GetTotalAttack() const;
	int GetTotalDefense() const;
	int GetDamage(Character& enemy, int damage_g) const;
    std::string GetProfession() const { return profession; }
    std::string GetRace() const { return race;}
    std::string GetDescription() const { return description; }
    int GetStrength() const { return strength; }
    int GetHealth() const { return health; }
    int GetLevel() const { return level; }
    int GetDefense() const { return defense; }
    int GetGold() const { return gold; }

};

class GameHard
{
    protected:
        int difficultyLevel;
    public:
        GameHard() : difficultyLevel(1) {}
        GameHard(int level) : difficultyLevel(level) {}

        void DisplayDifficulty() const;
        void ChoiceHard(Enemy& enemy);
        void SetDifficultyLevel(int level) { difficultyLevel = level; }
        int GetDifficultyLevel() const { return difficultyLevel; }
};

struct GameEvent                            //For tracking events not ot be repeated
{
    std::vector <int> eventHistory; // Store the history of events
    int tottalEvents = eventHistory.size(); // Total number of events that have occurred
    GameEvent() : tottalEvents(0) {}
};



class Quest
{
    Quest** quests;
    protected:
        int number_quest;                       //id
        int capacity_quest;                     //capacity
        int count_quest;                        //count of quests now
        std::string questName;
        std::string questDescription;
        int questDifficulty;
        int reward;
        bool isCompleted;

    public:
        Quest() : number_quest(0), capacity_quest(0), count_quest(0), questName(""), questDescription(""), questDifficulty(1), reward(0),isCompleted(false) {}
        Quest(int number_quest1, int capacity_quest1,int count_quest1, std::string name, std::string description, int difficulty, int rewardes) : 
        number_quest(number_quest1), capacity_quest(capacity_quest1),count_quest(count_quest1),
        questName(name), questDescription(description), questDifficulty(difficulty), reward(rewardes), isCompleted(false) {}



        int GetCountQuest() const { return count_quest;}
        int GetCapacityQuest() const {return capacity_quest;}
        int AddQuest(Quest* quest1);
        Quest* GetItemQuest(int index) const;
        int ResizeQuestBig();

        
        void SetQuestNumber(int number_quest1) {number_quest = number_quest1; }
        void DisplayQuestInfo() const;
        void SetQuestName(const std::string& name) { questName = name; }
        void SetQuestDescription(const std::string& description) { questDescription = description; }
        void SetQuestDifficulty(int difficulty) { questDifficulty = difficulty; }
        void SetCompleted(bool completed) { isCompleted = completed; }
        void SetUncompleted() { isCompleted = false; }
        void SetReward(int rewardes) { reward = rewardes; }
        void DisplayAllQuestInfo() const;

        int GetQuestDifficulty() const { return questDifficulty; }
        std::string GetQuestDescription() const { return questDescription; } 
        std::string GetQuestName() const { return questName; }
        int GetQuestNumber() const {return number_quest; }

        
        int Delete_Quest(int number_quest);
        std::string RandomizeQuest(GameHard& difficulty);
        bool IsCompleted() const { return isCompleted; }


        ~Quest(){for (int i = 0; i < count_quest; i++)
        delete quests[i];
    delete[] quests;}

};

//================================================================================================================================
class Object : public Item
{
    Object** objects;
protected:

int price_object;
std::string name_object;
std::string describtion_object;
bool isQuest;
int count_object;
std::string rarityType_object; 
Character* owner_p;                          //how many

public:

Object() : price_object(0), name_object("Default name object"), describtion_object("Default describtion object"),
 isQuest("false"), count_object(0) , rarityType_object("Common") {};
Object(int price_object1, std::string name_object1, std::string describtion_object1, bool isQuest1, int count1, std::string RarityType_object1): price_object(price_object1),
 name_object(name_object1), describtion_object(describtion_object1), isQuest(isQuest1), count_object(count1), rarityType_object(RarityType_object1) {}


//Main functions
void CreateObjectConstructor();
void RecountObject();
void DisplayObjectStats();


Character* GetOwner() const { return owner_p; } 
void SetOwner(Character* c) { owner_p = c; }  
//Getters
int GetObjectCount() const {return count_object;}
std::string GetName() const {return name_object;}
std::string GetType() const override { return "Object"; }


//Base functions
void ShowInfo() const override;      // Implement in Objects.cpp
std::string GetName() const override { return name_object; }
std::string GetType() const override { return "Object"; }
void Use() override;                
void Reset() override; 


//Setters
void SetObjectCount(int count1) {count_object = count1;}
void SetObjectName(std::string name_object1) { name_object= name_object1; }
void SetObjectDescribtion(std::string describtion_object1) { describtion_object= describtion_object1; }



//Deleter
 ~Object(){for (int i = 0; i < count_object; i++)
        delete objects[i];
    delete[] objects;}
};

//==================================================================Additional_Functions================================================
char ChoiceInput_YN();
int ChoiceInput_Number();

//===============================================================================Additional_Events_Games======================================================
std::string GetEffectName(int type);
void MainFunction();

void StartGame(Enemy& enemy, Character& hero, GameHard& levelDificulty, GameEvent& gameEvent, MyInventory& inv1);
void Help();
void GetInfo();
void Menu(Enemy& enemy, Character& hero, MyInventory& inv1, GameHard& levelDificulty);
//==================================================================Main_Menu_Functions=========================================================================
void Settings(Character& hero, MyInventory& inv, Enemy& enemy, GameHard& levelDificulty);
void Reseter(Character& hero, MyInventory& inv, GameHard& levelDificulty);
void Saver(Character& hero, MyInventory& inv, GameHard& levelDificulty);
void Loader(Character& hero, MyInventory& inv);
//==================================================================Events_functions============================================================================
void ToxicRain(Character& hero, GameHard& levelDificulty);
void Rain(Character& hero, GameHard& levelDificulty);
void VolcanicEruption(Character& hero, GameHard& levelDificulty);
void FlashFlood(Character& hero, GameHard& levelDificulty);
void Mudslide(Character& hero, GameHard& levelDificulty);
void HumidHot(Character& hero, GameHard& levelDificulty);

void ConstrictorVines(Character& hero, GameHard& levelDificulty);     //Events.cpp and all down
void QuickFreezingGlad(Character& hero, GameHard& levelDificulty);
void WillWispAttraction(Character& hero, GameHard& levelDificulty);
void PollenHallucinations (Character& hero, GameHard& levelDificulty);
void EnemyPatrol(Character& hero, GameHard& levelDificulty);
void MonsterAmbush(Character& hero, GameHard& levelDificulty);
void CunningScavengers(Character& hero, GameHard& levelDificulty);
void StagedAccident(Character& hero, GameHard& levelDificulty);
void FalseHospitableHost(Character& hero, GameHard& levelDificulty);
void ThePropheticBeggar(Character& hero, GameHard& levelDificulty);
void TheShadowingKid(Character& hero, GameHard& levelDificulty);
void Extortion(Character& hero, GameHard& levelDificulty);
void TheTurncoatGuide(Character& hero, GameHard& levelDificulty);
void PoacherTrapTrigger(Character& hero, GameHard& levelDificulty);
void FakeDistressCal(Character& hero, GameHard& levelDificulty);
void Earthquake(Character& hero, GameHard& levelDificulty);
void MoneyFind(Character& hero, GameHard& levelDificulty);
void GoodStranger(Character& hero, GameHard& levelDificulty);
void GoodWeather(Character& hero, GameHard& levelDificulty);
void RandomizerEvent(Character& hero, GameHard& levelDificulty, GameEvent& gameEvent, MyInventory& inv1);
void GoodRest(Character& hero, GameHard& levelDificulty);
void Tavern(Character& hero);
void Hostel(Character& hero);
void Castle(Character& hero);
void Dungeon(Character& hero);
void Cave(Character& hero);
void Forest(Character& hero);
void Desert(Character& hero);
void Village(Character& hero);
void Bastion(Character& hero);
void TowerPlace(Character& hero);
void SimpleHouse(Character& hero);
void GoodPlace(Character& hero);
void FishingChallenge(Character& hero);
void ArcheryContest(Character& hero, GameHard& levelDificulty);
void StrangeStone(Character& hero, MyInventory& inv1);
void Tired_Granny_Event(Character& hero, GameHard& levelDificulty);
void Wendigo_Encounter_Event(Character& hero, GameHard& levelDificulty);
void TalkToLocals(Character& hero, GameHard& levelDificulty);
void TalkStrangers();
//==================================================================GameIn_Functions============================================================================
void DiceRoll(Character& hero); //OtherRandomizer.cpp
void MusicChallenge(Character& hero);
void FistFight(Character& hero);
void DrinkingContest(Character& hero, GameHard& levelDificulty);
void CardDraw(Character& hero);
//==================================================================StoryFunction_and_Turn_Functions=============================================================================
void Turn(Character& hero, GameHard& levelDificulty, GameEvent& gameEvent, MyInventory& inv1); //Plot.cpp
void BugReportFunction();           //Addition.cpp
//==================================================================Additional_functions================================================================================
void HowToPlayRollDiceFunction();
//==================================================================Error_catcher==================================================
void ManageGameSaves(Character& hero, MyInventory& inv, GameHard& levelDificulty); //ManageGamesaves.cpp
void ListSaveFiles(); 
void ListSaveFilesLoader();
void Deleter();
void Fail_To_Open_File(std::ifstream& fs);
void Fail_To_Close_File(std::ifstream& fs);
void Fail_To_Open_File(std::ofstream& fs);
void Fail_To_Close_File(std::ofstream& fs);
std::string Check_Save_Status(std::ofstream& fs, std::string path); //ifstream -> loader || ofstream -> saver

#endif

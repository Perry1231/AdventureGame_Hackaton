#include "Header.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
//Additional events for game
enum EventType {
    TOXIC_RAIN =0, RAIN=1, VOLCANIC_ERUPTION=2, FLASH_FLOOD=3, MUDSLIDE=4, HUMID_HOT=5,
    CONSTRICTOR_VINES=6, QUICK_FREEZING_GLAD=7,
    WILL_WISP_ATTRACTION=8,POLLEN_HALLUCINATIONS=9,
    ENEMY_PATROL=11, MONSTER_AMBUSH=12, CUNNING_SCAVENGERS=13, STAGED_ACCIDENT=14,
    FALSE_HOSPITABLE_HOST=15, THE_PROPHETIC_BEGGAR=16, THE_SHADOWING_KID=17,
    EXTORTION=18, THE_TURNCOAT_GUIDE=19, POACHER_TRAP_TRIGGER=20, FAKE_DISTRESS_CALL=21,
    MONEY_FIND=22, GOOD_STRANGER=23, GOOD_WEATHER=24, GOOD_REST=25 , TAVERN=26, HOSTEL=27, CASTLE=28, DUNGEON=29, CAVE=30, FOREST=31, DESERT=32,
    VILLAGE=33, BASTION=34, TOWERPLACE=35, SIMPLE_HOUSE=36, GOOD_PLACE=37 , FISHING_CHALLENGE=38, ARCHERY_CONTEST=39, STRANGE_STONE=40
    
};
void BardStory() ;
void RandomizerEvent(Character& hero, GameHard& levelDificulty, GameEvent& gameEvent, MyInventory& inv1)
{
    int eventType = rand() % 41; //From 0 to 40
    // Перевірка на повтор подій з історії — без безлімітного циклу
    for (bool duplicate = true; duplicate; ) {
        duplicate = false;
        for (int h : gameEvent.eventHistory) {
            if (h == eventType) {
                eventType = rand() % 41;
                duplicate = true;
                break;
            }
        }
    }
    gameEvent.eventHistory.push_back(eventType);
    if(gameEvent.eventHistory.size() > 3) { // Keep only the last 3 events
        gameEvent.eventHistory.erase(gameEvent.eventHistory.begin());
    }

    switch (eventType) {
        case TOXIC_RAIN: ToxicRain(hero, levelDificulty); break;
        case RAIN: Rain(hero, levelDificulty); break;
        case VOLCANIC_ERUPTION: VolcanicEruption(hero, levelDificulty); break;
        case FLASH_FLOOD: FlashFlood(hero, levelDificulty); break;
        case MUDSLIDE: Mudslide(hero, levelDificulty); break;
        case HUMID_HOT: HumidHot(hero, levelDificulty); break;
        case CONSTRICTOR_VINES: ConstrictorVines(hero, levelDificulty); break;
        case QUICK_FREEZING_GLAD: QuickFreezingGlad(hero, levelDificulty); break;
        case WILL_WISP_ATTRACTION: WillWispAttraction(hero, levelDificulty); break;
        case POLLEN_HALLUCINATIONS: PollenHallucinations(hero, levelDificulty); break;
        case ENEMY_PATROL: EnemyPatrol(hero, levelDificulty); break;
        case MONSTER_AMBUSH: MonsterAmbush(hero, levelDificulty); break;
        case CUNNING_SCAVENGERS: CunningScavengers(hero, levelDificulty); break;
        case STAGED_ACCIDENT: StagedAccident(hero, levelDificulty); break;
        case FALSE_HOSPITABLE_HOST: FalseHospitableHost(hero, levelDificulty); break;
        case THE_PROPHETIC_BEGGAR: ThePropheticBeggar(hero, levelDificulty); break;
        case THE_SHADOWING_KID: TheShadowingKid(hero, levelDificulty); break;
        case EXTORTION: Extortion(hero, levelDificulty); break;
        case THE_TURNCOAT_GUIDE: TheTurncoatGuide(hero, levelDificulty); break;
        case POACHER_TRAP_TRIGGER: PoacherTrapTrigger(hero, levelDificulty); break;
        case FAKE_DISTRESS_CALL: FakeDistressCal(hero, levelDificulty); break;
        case MONEY_FIND: MoneyFind(hero, levelDificulty); break;
        case GOOD_STRANGER: GoodStranger(hero,  levelDificulty); break;
        case GOOD_WEATHER: GoodWeather(hero,  levelDificulty); break;
        case GOOD_REST: GoodRest(hero,  levelDificulty); break;
        case TAVERN: Tavern(hero); break;
        case HOSTEL: Hostel(hero); break;
        case CASTLE: Castle(hero); break;
        case DUNGEON: Dungeon(hero); break;
        case CAVE: Cave(hero); break;
        case FOREST: Forest(hero); break;
        case DESERT: Desert(hero); break;
        case VILLAGE: Village(hero); break;
        case BASTION: Bastion(hero); break;
        case TOWERPLACE: TowerPlace(hero); break;
        case SIMPLE_HOUSE: SimpleHouse(hero); break;
        case GOOD_PLACE: GoodPlace(hero); break;
        case FISHING_CHALLENGE: FishingChallenge(hero); break;
        case ARCHERY_CONTEST: ArcheryContest(hero, levelDificulty); break;
        case STRANGE_STONE: StrangeStone(hero, inv1); break;
        default: std::cout << "Unknown event type!" << std::endl; break;
    }
}
void Tired_Granny_Event(Character& hero, GameHard& levelDificulty);

// ANSI Colors for Console
namespace Color {
    const std::string RESET   = "\033[0m";
    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string BOLD    = "\033[1m";
    const std::string DARK_GRAY = "\033[90m";
}

// Helper function to render formatted Event Cards
void PrintEventCard(const std::string& icon, const std::string& title, const std::string& description, const std::string& effectColor = Color::RED) {
    std::cout << "\n" << Color::BOLD << Color::CYAN << "┌──────────────────────────────────────────────┐\n" << Color::RESET;
    std::cout << Color::BOLD << Color::CYAN << "│ " << Color::YELLOW << icon << "  " << title;
    
    // Padding spaces for border alignment
    int padding = 43 - (title.length() + 4); 
    for (int i = 0; i < padding; ++i) std::cout << " ";
    std::cout << Color::CYAN << "│\n" << Color::RESET;
    
    std::cout << Color::BOLD << Color::CYAN << "├──────────────────────────────────────────────┤\n" << Color::RESET;
    std::cout << Color::CYAN << "│ " << effectColor << description;
    
    std::cout << Color::RESET << "\n";
    std::cout << Color::BOLD << Color::CYAN << "└──────────────────────────────────────────────┘\n" << Color::RESET;

    // Short delay for better visual pacing
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
}

// Helper function for damage logging
void DamageHero(Character& hero, int amount) {
    hero.SetHealth(hero.GetHealth() - amount);
    
    std::cout << Color::RED << Color::BOLD << " ⚔  [DAMAGE] " 
              << Color::RESET << "-" << amount << " HP  " 
              << Color::DARK_GRAY << "(Health: " << Color::GREEN << hero.GetHealth() 
              << Color::DARK_GRAY << "/" << hero.GetTotalHealth() << ")" << Color::RESET << "\n";
}

// Helper function for gold loss logging
void LoseGold(Character& hero, int amount) {
    hero.SetGold(hero.GetGold() - amount);
    
    std::cout << Color::YELLOW << Color::BOLD << " 🪙  [LOSS]   " 
              << Color::RESET << "-" << amount << " Gold " 
              << Color::DARK_GRAY << "(Remaining: " << Color::YELLOW << hero.GetGold() 
              << Color::DARK_GRAY << ")" << Color::RESET << "\n";
}

// ---------------- EVENTS ----------------

void ToxicRain(Character& hero, GameHard& levelDificulty) {
    if (levelDificulty.GetDifficultyLevel() >= 2) {
        PrintEventCard("☣️", "TOXIC RAIN", "Acidic rain burns your skin! You take extra damage due to the high difficulty level.");
        DamageHero(hero, 10); // Increased damage for higher difficulty
    } else {
        PrintEventCard("☣️", "TOXIC RAIN", "Acidic rain burns your skin!");
        DamageHero(hero, 5);
    }
    PrintEventCard("☣️", "TOXIC RAIN", "Acidic rain burns your skin!");
    DamageHero(hero, 5);
    hero.SetLevel(hero.GetLevel() + 0.01); // Increase level by 1
}


void Rain(Character& hero, GameHard& levelDificulty) {
     if (levelDificulty.GetDifficultyLevel() >= 2) {
        PrintEventCard("🌧️", "RAIN", "Heavy rain soaks you! You take extra damage due to the high difficulty level.");
        DamageHero(hero, 5); // Increased damage for higher difficulty
    }
    int rainType = rand() % 2;
    if (rainType == 0) {
        PrintEventCard("🌧️", "LIGHT RAIN", "Light rain falls. It is chilly and uncomfortable.", Color::YELLOW);
        DamageHero(hero, 2);
    } else {
        PrintEventCard("⛈️", "HEAVY RAIN", "Heavy rain pours down! You take damage from exposure.");
        DamageHero(hero, 5);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void VolcanicEruption(Character& hero, GameHard& levelDificulty) {
     if (levelDificulty.GetDifficultyLevel() >= 2) {
    if (rand() % 2 == 0) {
        PrintEventCard("🌋", "VOLCANIC ERUPTION", "The ground shakes! You manage to escape safely.", Color::GREEN);
    } else {
        PrintEventCard("🌋", "VOLCANIC ERUPTION", "Hot ash and lava burn you as you run!");
        DamageHero(hero, 10);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}
else {
    if (rand() % 2 == 0) {
        PrintEventCard("🌋", "VOLCANIC ERUPTION", "The ground shakes! You manage to escape safely.", Color::GREEN);
    } else {
        PrintEventCard("🌋", "VOLCANIC ERUPTION", "Hot ash and lava burn you as you run!");
        DamageHero(hero, 5);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}
}

void FlashFlood(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("🌊", "FLASH FLOOD", "A sudden wave sweeps you away into sharp rocks! You take extra damage due to the high difficulty level.");
        DamageHero(hero, 15); // Increased damage for higher difficulty
    } else
    if (rand() % 2 == 0) {
        PrintEventCard("🌊", "FLASH FLOOD", "Water rises fast, but you climb to high ground safely.", Color::GREEN);
    } else {
        PrintEventCard("🌊", "FLASH FLOOD", "A sudden wave sweeps you away into sharp rocks!");
        DamageHero(hero, 10);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);

}

void Mudslide(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("⛰️", "MUDSLIDE", "A torrent of mud sweeps past you closely! You take extra damage due to the high difficulty level.");
        DamageHero(hero, 10); // Increased damage for higher difficulty
    } else
    if (rand() % 2 == 0) {
        PrintEventCard("⛰️", "MUDSLIDE", "A torrent of mud sweeps past you closely.", Color::GREEN);
    } else {
        PrintEventCard("⛰️", "MUDSLIDE", "You get caught in a dangerous mudslide!");
        DamageHero(hero, 5);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void HumidHot(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("🏜️", "HUMID & HOT", "All water dried up! You suffer from severe heat exhaustion! Extra damage due to high difficulty level.");
        DamageHero(hero, 10); // Increased damage for higher difficulty
    } else
    if (rand() % 2 == 0) {
        PrintEventCard("☀️", "HUMID & HOT", "It's humid and hot, but you manage fine.", Color::YELLOW);
    } else {
        PrintEventCard("🏜️", "HUMID & HOT", "All water dried up! You suffer from severe heat exhaustion.");
        DamageHero(hero, 5);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void ConstrictorVines(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("🌿", "CONSTRICTOR VINES", "Predatory vines squeeze tight around you! Extra damage due to high difficulty level.");
        DamageHero(hero, 6); // Increased damage for higher difficulty
    } else
    {
        PrintEventCard("🌿", "CONSTRICTOR VINES", "Predatory vines squeeze tight around you!");
        DamageHero(hero, 3);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}


void QuickFreezingGlad(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("❄️", "QUICK FREEZING GLADE", "The temperature plummets. Frostbite sets in! Extra damage due to high difficulty level.");
        DamageHero(hero, 8); // Increased damage for higher difficulty
    } else
    {
    PrintEventCard("❄️", "QUICK FREEZING GLADE", "The temperature plummets. Frostbite sets in!");
    DamageHero(hero, 4);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}




void Extortion(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("💰", "EXTORTION", "Local bandits force you to hand over some coin!");
    LoseGold(hero, 15);
    } else
    {
    PrintEventCard("💰", "EXTORTION", "Local bandits force you to hand over some coin!");
    LoseGold(hero, 10);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
    
}

void PoacherTrapTrigger(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("🪤", "POACHER TRAP", "Snap! You stepped into a sharp steel trap!");
    DamageHero(hero, 10);
    } else
    {
    PrintEventCard("🪤", "POACHER TRAP", "Snap! You stepped into a sharp steel trap!");
    DamageHero(hero, 6);
    }
    hero.SetLevel(hero.GetLevel() + 0.04);
    
}
// Narrative Events (No stat loss)  =====================Need finish
void WillWispAttraction(Character& hero, GameHard& levelDificulty)   { PrintEventCard("👻", "WILL-O'-WISP", "Mysterious glowing lights attempt to lead you astray.", Color::MAGENTA); }
void PollenHallucinations(Character& hero, GameHard& levelDificulty) { PrintEventCard("🍄", "POLLEN HALLUCINATIONS", "Strange floral pollen fills the air, distorting your sight.", Color::MAGENTA); }
void EnemyPatrol(Character& hero, GameHard& levelDificulty)          { PrintEventCard("⚔️", "ENEMY PATROL", "You spot an armed patrol marching nearby!", Color::YELLOW); }
void MonsterAmbush(Character& hero, GameHard& levelDificulty)        { PrintEventCard("🐺", "MONSTER AMBUSH", "A wild beast leaps out from the shadows!", Color::RED); }
void CunningScavengers(Character& hero, GameHard& levelDificulty)    { PrintEventCard("🦅", "CUNNING SCAVENGERS", "Opportunists are watching your every step...", Color::YELLOW); }
void StagedAccident(Character& hero, GameHard& levelDificulty)       { PrintEventCard("🎭", "STAGED ACCIDENT", "A traveler cries for help, but it feels like a trap.", Color::YELLOW); }
void FalseHospitableHost(Character& hero, GameHard& levelDificulty)  { PrintEventCard("🏡", "FALSE HOSPITABLE HOST", "Your host offers food, but their smile feels unnatural.", Color::YELLOW); }
void ThePropheticBeggar(Character& hero, GameHard& levelDificulty)   { PrintEventCard("🔮", "PROPHETIC BEGGAR", "An old beggar whispers an ominous prophecy.", Color::CYAN); }
void TheShadowingKid(Character& hero, GameHard& levelDificulty)      { PrintEventCard("👀", "SHADOWING KID", "A young child stalks you quietly from behind.", Color::CYAN); }
void TheTurncoatGuide(Character& hero, GameHard& levelDificulty)     { PrintEventCard("🗺️", "TURNCOAT GUIDE", "Your guide seems to be leading you off course...", Color::YELLOW); }



void FakeDistressCal(Character& hero, GameHard& levelDificulty) {                                       //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    std::cout << "If want to check -- 1 \nIf you want pass --- 2" << std::endl;
    int choice =ChoiceInput_Number();

    if(choice == 1)
    {

    
    std::cout << "Event: Fake Distress Call!\n";
    int event_fake_diss_call = rand() % 4 +1;

    switch(event_fake_diss_call)
    {
case 1:
std::cout << "It's only your tired imagination" << std::endl;
hero.SetLevel(hero.GetLevel() + 0.01);
break;
case 2:
std::cout << "It's only old granny" << std::endl;
Tired_Granny_Event(hero, levelDificulty);
break;
case 3:
std::cout << "IT'S WENDIGO RUN !!!" << std::endl;
Wendigo_Encounter_Event(hero, levelDificulty);
break;
case 4:
std::cout << "You had entered big forest" << std::endl;
std::cout << "You see a small house" << std::endl;

break;
    }
}


    else if (choice == 2)
    {
        std::cout << "You go away" << std::endl;
        exit(0);
    }
    else {std::cout << "You entere wrong answer !";}
}

// Helper function for health gains
void GainHealth(Character& hero, int amount) {
    hero.SetHealth(hero.GetHealth() + amount);
    std::cout << Color::GREEN << Color::BOLD << "   [ + " << amount << " HP ] " 
              << Color::RESET << "Current Health: " << Color::GREEN << hero.GetHealth() << Color::RESET << "\n";
}

// Helper function for gold gains
void GainGold(Character& hero, int amount) {
    hero.SetGold(hero.GetGold() + amount);
    std::cout << Color::YELLOW << Color::BOLD << "   [ + " << amount << " Gold ] " 
              << Color::RESET << "Current Gold: " << Color::YELLOW << hero.GetGold() << Color::RESET << "\n";
}

// Events

void Earthquake(Character& hero, GameHard& levelDificulty) {
    std::cout << Color::DARK_GRAY << " 🌋 [EVENT] " << Color::RESET << "An Earthquake shakes the ground! (Exp +0.01)\n";
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void MoneyFind(Character& hero, GameHard& levelDificulty) {
    int gold = rand() % 100 + 1;
    std::cout << Color::YELLOW << " 💰 [EVENT] " << Color::RESET << "You stumbled upon a hidden stash!\n";
    GainGold(hero, gold);
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void GoodStranger(Character& hero, GameHard& levelDificulty) {
    std::cout << Color::CYAN << " 🤝 [EVENT] " << Color::RESET << "A Good Stranger shares a warm meal with you. You feel refreshed!\n";
    GainHealth(hero, 5);
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void GoodWeather(Character& hero, GameHard& levelDificulty) {
    std::cout << Color::CYAN << " ☀️  [EVENT] " << Color::RESET << "Good Weather! The clear skies rejuvenate your spirit.\n";
    GainHealth(hero, 5);
    hero.SetLevel(hero.GetLevel() + 0.03);
}

void GoodRest(Character& hero, GameHard& levelDificulty) {
    int health = rand() % 20 + 10;
    std::cout << Color::GREEN << " ⛺ [EVENT] " << Color::RESET << "You found a safe, cozy place to rest.\n";
    GainHealth(hero, health);
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void Tavern(Character& hero)
{
std::cout << "You enter a cozy tavern. The smell of food and ale fills the air." << std::endl;
std::cout << "You can rest here and regain some health." << std::endl;
std::cout << "Or you can talk to the locals and gather information about your next adventure." << std::endl;
std::cout << "You can also play a game of chance with the tavern patrons." << std::endl;

std::cout << "What would you like to do?" << std::endl;
std::cout << "1. Rest and regain health" << std::endl;
std::cout << "2. Talk to the locals" << std::endl;
std::cout << "3. Play a game of chance" << std::endl;
std::cout << "4. Leave the tavern" << std::endl;

int choice =ChoiceInput_Number();
int gameChoice;
int gameChoice2;

switch (choice) {
    case 1:
        std::cout << "You rest and regain some health." << std::endl;
        hero.SetHealth(hero.GetHealth() + 20);
        hero.SetLevel(hero.GetLevel() + 0.04);
        break;
    case 2:
        std::cout << "You talk to the locals and gather information about your next adventure." << std::endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        break;
    case 3:
        std::cout << "You play a game of chance with the tavern patrons." << std::endl;
        
        std::cout << "Choose a game to play:\n1. Dice Roll\n2. Card Draw\n3. Coin Flip\n";
        std::cin >> gameChoice;
        switch (gameChoice) {
            case 1:
                std::cout << "You choose to play Dice Roll." << std::endl;
                std::cout << "1. Roll the dice" << std::endl;
                std::cout << "2. Leave the game" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> gameChoice2;
                switch (gameChoice2) {
                    case 1:
                        std::cout << "Rolling the dice..." << std::endl;
                        DiceRoll(hero);
                        
                    case 2:
                        std::cout << "You leave the game." << std::endl;
                        break;
                    default:
                        std::cout << "Invalid choice. You leave the game." << std::endl;
                }
                break;

            case 2:
                std::cout << "You choose to play Card Draw." << std::endl;
                CardDraw(hero);
                break;
            case 3:
                std::cout << "You choose to play Coin Flip." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
                std::cin.clear();
                return;
        }

        DiceRoll(hero);
        break;
    case 4:
        std::cout << "You leave the tavern and continue your adventure." << std::endl;
        break;
    default:
        std::cout << "Invalid choice. You leave the tavern." << std::endl;
}
}

void Hostel(Character& hero) {
    // Atmospheric introduction box / header
    std::cout << Color::CYAN << Color::BOLD << "\n 🏨 [LOCATION] " 
              << Color::RESET << "The Dusty Lantern Hostel\n";
    std::cout << Color::DARK_GRAY << "----------------------------------------\n" << Color::RESET;
    std::cout << " You step into a warm, dimly lit room. The air smells of woodsmoke and stale ale.\n";
    std::cout << " A weary innkeeper nods from behind the counter, and travelers murmur in corners.\n\n";

    std::cout << Color::BOLD << " What would you like to do?\n" << Color::RESET;
    std::cout << "  " << Color::YELLOW << "1." << Color::RESET << " Rent a room to rest and recover health\n";
    std::cout << "  " << Color::YELLOW << "2." << Color::RESET << " Approach the travelers to chat and gather rumors\n";
    std::cout << "  " << Color::YELLOW << "3." << Color::RESET << " Leave the hostel and head back out\n";
    std::cout << Color::DARK_GRAY << "----------------------------------------\n" << Color::RESET;
    
    std::cout << Color::BOLD << " Choice > " << Color::RESET;
    int choice = ChoiceInput_Number();
    
    std::cout << "\n";

    switch (choice) {
        case 1: {
            std::cout << Color::GREEN << " ⛺ [REST] " << Color::RESET << "You secure a quiet cot for the night.\n";
            GainHealth(hero, 15);
            hero.SetLevel(hero.GetLevel() + 0.01);
            break;
        }
        case 2: {
            std::cout << Color::MAGENTA << " 🗣️  [RUMORS] " << Color::RESET << "You sit by the hearth and strike up a conversation...\n";
            std::cout << Color::DARK_GRAY << "----------------------------------------\n" << Color::RESET;
            std::cout << "  " << Color::YELLOW << "1." << Color::RESET << " Ask about hidden treasures\n";
            std::cout << "  " << Color::YELLOW << "2." << Color::RESET << " Ask what is going on in these lands\n";
            std::cout << "  " << Color::YELLOW << "3." << Color::RESET << " Ask where you can find work\n";
            std::cout << "  " << Color::YELLOW << "4." << Color::RESET << " Order a round of drinks for everyone ($10 Gold)\n";
            std::cout << Color::DARK_GRAY << "----------------------------------------\n" << Color::RESET;

            std::cout << Color::BOLD << " Dialogue Choice > " << Color::RESET;
            int subChoice;
            std::cin >> subChoice;
            std::cout << "\n";

            switch (subChoice) {
                case 1:
                    std::cout << Color::CYAN << " 🗺️  " << Color::RESET << "\"Old legends say a stash is buried deep within the eastern caves...\"\n";
                    break;
                case 2:
                    std::cout << Color::CYAN << " 📜 " << Color::RESET << "\"Monsters have been growing bolder by the day. Nobody feels safe anymore.\"\n";
                    break;
                case 3:
                    std::cout << Color::CYAN << " 💰 " << Color::RESET << "\"The local militia is always paying heads for goblin teeth. Check the board outside.\"\n";
                    break;
                case 4:
                    if (hero.GetGold() >= 10) {
                        LoseGold(hero, 10);
                        std::cout << Color::GREEN << " ✨ " << Color::RESET << "The tavern cheers! Everyone raises a glass to your generosity.\n";
                        hero.SetLevel(hero.GetLevel() + 0.02); // Small bonus for being generous
                    } else {
                        std::cout << Color::RED << " ❌ " << Color::RESET << "You check your pockets... you don't have enough gold to buy drinks!\n";
                    }
                    break;
                default:
                    std::cout << Color::DARK_GRAY << " The travelers grow silent, ignoring your rambling.\n" << Color::RESET;
                    break;
            }
            break;
        }
        case 3:
            std::cout << Color::DARK_GRAY << " 🚪 [LEAVE] " << Color::RESET << " You step back out into the open world.\n";
            break;
        default:
            std::cout << Color::RED << " ⚠️  [NOTICE] " << Color::RESET << "Indecisive, you are gently nudged out the front door.\n";
            break;
    }
}

void Castle(Character& hero)
{
std::cout << "You enter a grand castle. The halls are adorned with tapestries and the air smells of incense." << std::endl;
std::cout << "Select what you want to do: " << std::endl;
std::cout << "1. Rest in the royal chambers" << std::endl;
std::cout << "2. Search for hidden treasures" << std::endl;
std::cout << "3. Look around for quests or tasks" << std::endl;
std::cout << "4. Leave the castle" << std::endl;
int choice = ChoiceInput_Number();

switch (choice) {
    case 1:
    {
        std::cout << "You rest in the royal chambers and regain some health." << std::endl;
        hero.SetHealth(hero.GetHealth() + 30);
        hero.SetLevel(hero.GetLevel() + 0.02);
        break;
    }
    case 2:
    {
        int randomRsult = rand() % 2;
        int randGold = rand() % 100 + 1; // Random gold between 1 and 100
        if (randomRsult == 0) {
            std::cout << "You find a hidden treasure chest filled with gold!" << std::endl;
            hero.SetGold(hero.GetGold() + randGold);
            hero.SetLevel(hero.GetLevel() + 0.02);
        } else {
            std::cout << "You search the castle but find no treasures." << std::endl;
        }

        hero.SetLevel(hero.GetLevel() + 0.02);
        break;
    }
    case 3:
    {
        std::cout << "You look around for quests." << std::endl;
        int questResult = rand() % 2;
        if (questResult == 0) {
            std::cout << "You find a quest to help the castle guard with a problem." << std::endl;
            Quest quest;
        } else {
            std::cout << "You look around but find no quests." << std::endl;
        }
        hero.SetLevel(hero.GetLevel() + 0.02);
        break;
    }
    case 4:
    {
        std::cout << "You leave the castle and continue your adventure." << std::endl;
        break;
    }
default:
    {
        std::cout << "Invalid choice. You leave the castle." << std::endl;
        break;
    }
}
}

void Dungeon(Character& hero)
{

}

void Cave(Character& hero)//goblin cave, dragon or simple cave
{

}

void Forest(Character& hero)
{

}

void Desert(Character& hero)
{

}

void Village(Character& hero)
{

}

void Bastion(Character& hero)
{

}

void TowerPlace(Character& hero)//evil TowerPlace , mage TowerPlace
{

}

void SimpleHouse(Character& hero)//evil mage , witch , friendly house
{

}


void GoodPlace(Character& hero)//good place for rest and food
{
std::cout << "You enter a peaceful place. The atmosphere is calm and serene." << std::endl;
std::cout << "You can rest here and regain some health." << std::endl;
hero.SetLevel(hero.GetLevel() + 0.01);
hero.SetHealth(hero.GetHealth() + 7);

}
 //===============================================================================Additional_Events_Games======================================================
void FishingChallenge(Character& hero)
{
    std::cout << "You participate in a fishing challenge with the locals." << std::endl;
    std::cout << "You can try to catch the biggest fish or the rarest fish." << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Try to catch the biggest fish" << std::endl;
    std::cout << "2. Try to catch the rarest fish" << std::endl;
    std::cout << "3. Leave the fishing challenge" << std::endl;


    
    std::cout << "Enter your choice: ";
    int choice = ChoiceInput_Number();
    switch (choice) {
        case 1:
        {
            std::cout << "You try to catch the biggest fish." << std::endl;
            int fishSize = rand() % 100 + 1; // Random fish size between 1 and 100
            std::cout << "You go to the lake and cast your line. After a while, you feel a tug on the line!" << std::endl;
            std::cout << "You get into a struggle with the fish!" << std::endl;
            if(hero.GetStrength() >= fishSize) 
            {
                std::cout << "You successfully catch the biggest fish! You gain 20 gold." << std::endl;
                hero.SetGold(hero.GetGold() + 20);
                hero.SetLevel(hero.GetLevel() + 0.4);
            } 
            else 
            {
                std::cout << "The fish was too strong for you. You lose 3 health." << std::endl;
                hero.SetHealth(hero.GetHealth() - 2);
                hero.SetLevel(hero.GetLevel() + 0.01);
            }
            break;
        }
        case 2:
        {
            std::cout << "You try to catch the rarest fish." << std::endl;
            std::cout << "You go to the lake and cast your line. After a while, you feel a tug on the line!" << std::endl;
            int rareFishChance = rand() % 100 + 1; // Random chance between 1 and 100
            if(rareFishChance <= 10) {
                std::cout << "You successfully catch the rarest fish! You gain 50 gold." << std::endl;
                hero.SetGold(hero.GetGold() + 50);
                hero.SetLevel(hero.GetLevel() + 0.4);
            } else {
                std::cout << "The fish was too elusive for you. You lose 5 health." << std::endl;
                hero.SetHealth(hero.GetHealth() - 5);
                hero.SetLevel(hero.GetLevel() + 0.01);
            }
            break;
        } 
        case 3:
        {
            std::cout << "You leave the fishing challenge." << std::endl;
            break;
        }
        default:
            std::cout << "Invalid choice. You leave the fishing challenge." << std::endl;
            break;
    }

}

void ArcheryContest(Character& hero, GameHard& levelDificulty)
{
    std::cout << "You participate in an archery contest with the locals." << std::endl;
    std::cout << "You can try to hit the bullseye or aim for the highest score." << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Try to hit the bullseye" << std::endl;
    std::cout << "2. Try to aim for the highest score" << std::endl;
    std::cout << "3. Leave the archery contest" << std::endl;
    std::cout << "Enter your choice: ";
    int choice = ChoiceInput_Number();

    switch(choice)
    {
        case 1:
        {
            std::cout << "You try to hit the bullseye." << std::endl;
            int bullseyeChance = rand() % 100 + 1; // Random chance between 1 and 100
            if(bullseyeChance <= 20) {
                std::cout << "You successfully hit the bullseye! You gain 30 gold." << std::endl;
                hero.SetGold(hero.GetGold() + levelDificulty.GetDifficultyLevel() * 10); 
                hero.SetLevel(hero.GetLevel() + 0.4);
            } else {
                std::cout << "You miss the bullseye. You lose 2 health." << std::endl;
                hero.SetHealth(hero.GetHealth() - 2);
                hero.SetLevel(hero.GetLevel() + 0.01);
            }
            break;
        }
        case 2:
        {
            std::cout << "You try to aim for the highest score." << std::endl;
            int highScoreChance = rand() % 100 + 1; // Random chance between 1 and 100
            if(highScoreChance <= 30) {
                std::cout << "You achieve the highest score! You gain 40 gold." << std::endl;
                hero.SetGold(hero.GetGold() + levelDificulty.GetDifficultyLevel() * 10);
                hero.SetLevel(hero.GetLevel() + 0.4);
            } else {
                std::cout << "You fail to achieve a high score. You lose 3 health." << std::endl;
                hero.SetHealth(hero.GetHealth() - 3);
                hero.SetLevel(hero.GetLevel() + 0.01);
            }
            break;
        }
        case 3:
        {
            std::cout << "You leave the archery contest." << std::endl;
            break;
        }
        default:
            std::cout << "Invalid choice. You leave the archery contest." << std::endl;
            break;
    }

}

void StrangeStone(Character& hero, MyInventory& inv1)
{
    std::cout << "You find a strange stone with mysterious markings." << std::endl;
    std::cout << "You can try to decipher the markings or leave it alone." << std::endl;
    std::cout << "Enter your choice:\n1. Decipher the markings\n2. Leave it alone\n";
    int choice= ChoiceInput_Number();

    switch(choice)
    {
        case 1:
        {
            std::cout << "You attempt to decipher the markings." << std::endl;
            int decipherChance = rand() % 100 + 1; // Random chance between 1 and 100
            if(decipherChance <= 25) {
                std::cout << "You successfully decipher the markings! You gain a magical artifact." << std::endl;
                Artifact* artifact2 = new Artifact();       //Adding artifact for test in inventory
                artifact2->RandomizeArtifact();
                artifact2->SetArtifactName("Ancient Stone of Wisdom");
                artifact2->SetArtifactDescription("A stone inscribed with ancient runes. It radiates a faint magical energy.");
                artifact2->SetArtifactPower(10);
                artifact2->SetArtifactValue(100);

                inv1.AddItem(artifact2);

                hero.SetLevel(hero.GetLevel() + 0.5);
            } else {
                std::cout << "You fail to decipher the markings. You feel a strange energy drain from you." << std::endl;
                hero.SetHealth(hero.GetHealth() - 5);
                hero.SetLevel(hero.GetLevel() + 0.01);
            }
            break;
        }
        case 2:
        {
            std::cout << "You leave the stone alone and continue your journey." << std::endl;
            break;
        }
        default:
            std::cout << "Invalid choice. You leave the stone alone." << std::endl;
            break;
    }
}


//==================================================================================Additional_Events========================================================

// Helper function for a short delay between text reveals
void SleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void Tired_Granny_Event(Character& hero, GameHard& levelDifficulty)
{
    std::cout << "\n==================================================" << std::endl;
    std::cout << "               EVENT: RANDOM ENCOUNTER           " << std::endl;
    std::cout << "==================================================\n" << std::endl;

    std::cout << "You see a tired old woman on the roadside struggling with heavy bags.\n" << std::endl;
    SleepMs(600);

    std::cout << "What will you do?" << std::endl;
    std::cout << "  [1] Help the old woman carry her bags home" << std::endl;
    std::cout << "  [2] Walk past and ignore her" << std::endl;
    std::cout << "\nYour choice -> ";

    int choice;
    while (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter 1 or 2: ";
    }

    std::cout << "\n--------------------------------------------------" << std::endl;

    switch(choice)
    {
        case 1:
            std::cout << "You help the old woman carry her belongings to her cottage." << std::endl;
            SleepMs(800);
            std::cout << "She thanks you warmly and hands you a small pouch of coins!" << std::endl;
            hero.SetLevel(hero.GetLevel() + 0.03);
            hero.SetGold(hero.GetGold() + 10);
            
            std::cout << "\n[REWARD]: +10 Gold (Total: " << hero.GetGold() << ")" << std::endl;
            break;

        case 2:
            std::cout << "You pretend not to notice her and continue on your journey." << std::endl;
            hero.SetLevel(hero.GetLevel() + 0.01);
            break;

        default:
            std::cout << "Hesitation costs you. You end up walking past her anyway." << std::endl;
            break;
    }

    std::cout << "==================================================\n" << std::endl;
}


void Wendigo_Encounter_Event(Character& hero, GameHard& levelDificulty)
{

}

//===============================Talking to Locals Event (Placeholder)=============================
void TalkToLocals(Character& hero, GameHard& levelDificulty)
{
    std::cout << "You engage in conversation with the locals.\n";
    std::cout << "They share rumors of hidden treasures and dangerous creatures in the area.\n";
    std::cout << "You gain valuable information for your next adventure!\n";
    hero.SetLevel(hero.GetLevel() + 0.02);

    int choice = 0;
    while (choice != 4)
    {
        std::cout << "\nWhat would you like to get to know?\n";
        std::cout << "1. Gain some info about treasures\n";
        std::cout << "2. What is going on here?\n";
        std::cout << "3. Where can I find a job?\n";
        std::cout << "4. Exit talk\n";
        std::cout << "Choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
            case 1:
                if (hero.GetLevel() > 1.0) {
                    std::cout << "The locals tell you about a hidden treasure in the nearby forest.\n";
                    hero.SetLevel(hero.GetLevel() + 0.05);
                    hero.SetGold(hero.GetGold() + 20);
                    std::cout << "[REWARD]: +20 Gold (Total: " << hero.GetGold() << ")\n";
                } else {
                    std::cout << "The locals are hesitant to share information with you.\n";
                }
                break;

            case 2:
                TalkStrangers();
                hero.SetLevel(hero.GetLevel() + 0.02);
                break;

            case 3:
                if (hero.GetLevel() > 1.0) {
                    std::cout << "The locals suggest checking the village board for high-paying contracts.\n";
                    hero.SetLevel(hero.GetLevel() + 0.02);
                } else {
                    std::cout << "The locals suggest checking the village for basic odd jobs.\n";
                }
                break;

            case 4:
                std::cout << "You end the conversation with the locals.\n";
                break;

            default:
                std::cout << "Invalid choice. Please choose options 1 through 4.\n";
                break;
        }
    }
}


void TalkStrangers()
{
    int talk_random = rand() % 6 + 1;       //6 diffarnte talks with strangers
    switch(talk_random)
    {
        case 1:
            std::cout << "You meet a wandering bard who shares tales of ancient heroes." << std::endl;
            BardStory();
            break;

        case 2:
            std::cout << "A mysterious traveler offers you a cryptic riddle to solve." << std::endl;
            break;

        case 3:
            std::cout << "You encounter a merchant who offers rare items for trade." << std::endl;


            break;

        case 4:
            std::cout << "A local farmer tells you about the best fishing spots nearby." << std::endl;
            break;

        case 5:
            std::cout << "You meet a retired adventurer who shares tips for surviving in the wild." << std::endl;
                break;
        case 6:
            std::cout << "A wandering scholar discusses the history of the region and its legends." << std::endl;
            break;

    }
}


void BardStory()
{
int story_random = rand() % 4 + 1;      
switch(story_random)
    {
        case 1:
            std::cout << "The bard sings of a legendary sword that can vanquish any foe." << std::endl;
            std::cout << "The legend of heroic knight Valador, who sought the hand of a fair noble maiden, " << std::endl;
            std::cout << "and rode off to battle against a dragon to prove his worth." << std::endl;
            std::cout << "While typical of such tales the knight was indeed victorious and returned with the somewhat smallish head of the terrifying beast," << std::endl;
            std::cout << "and was proclaimed worthy to marry the princess and inherit the kingdom." << std::endl;
            std::cout << "The ending however is more tragic, as it recounts the kingdom being plagued by two greater," << std::endl;
            std::cout << "more fearsome dragons that destroyed the castle and its occupants in vengeance for the slaying of their young hatchling." << std::endl;
            break;

        case 2:
            std::cout << "This historical favorite is told more cautiously in the emperors' lands, " << std::endl;
            std::cout << "for fear of the retribution that comes with openly mocking the nobility's ancestors. " << std::endl;
            std::cout << "The tale itself concerns an arrogant emperor who received a pair of cursed dancing shoes as a wedding gift that gave him two left feet. " << std::endl;
            std::cout << "Aside from the embarrassment upon the ballroom floor that evening," << std::endl;
            std::cout << "he was forever remembered for his clumsy gait and inability to climb stairs without stumbling." << std::endl;
            break;

        case 3:
            std::cout << "A touching lesbian romance, recounting the chance meeting of a ranger and a priestess at a small towns harvest festival. " << std::endl;
            std::cout << "It tells of their blossoming love during the following winter as they struggled to protect the hamlet from vicious goblins," << std::endl;
            std::cout << "hungry predators and a small epidemic." << std::endl;
            std::cout << "While of mixed popularity among the more conservative crowds, it has become a favorite of independent women and perverse men across the land; both appreciating the tale for very different reasons. " << std::endl;
            std::cout << "\"Ones caress like silk, the others touch like fire, between them sparked a burning desire. Days turned to weeks and their friendship did grow, evolving into a love more pure then hinterlands snow.\"" << std::endl;
            break;

        case 4:
            std::cout << "The valiant legend of the famed Scorpion Sword," << std::endl;
            std::cout << "the blade forged from the bodies of desert scorpions and given a life of its own. " << std::endl;
            std::cout << "While carried by bandits and desert tyrants for centuries and the subject of many a campfire tale, " << std::endl;
            std::cout << "no other retelling quite captures the horror and overwhelming sense of doom those on the wrong end of this blade felt as this one. " << std::endl;
            std::cout << "Often sung in a deep baritone with rattles and thumb cymbals signifying the scorpions clawed grasps, it is not soon forgotten by any present." << std::endl;
            break;
    }

}


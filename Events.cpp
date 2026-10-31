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
    ENEMY_PATROL=10, MONSTER_AMBUSH=11, CUNNING_SCAVENGERS=12, STAGED_ACCIDENT=13,
    FALSE_HOSPITABLE_HOST=14, THE_PROPHETIC_BEGGAR=15, THE_SHADOWING_KID=16,
    EXTORTION=17, THE_TURNCOAT_GUIDE=18, POACHER_TRAP_TRIGGER=19, FAKE_DISTRESS_CALL=20,
    MONEY_FIND=21, GOOD_STRANGER=22, GOOD_WEATHER=23, GOOD_REST=24 , TAVERN=25, HOSTEL=26, CASTLE=27, DUNGEON=28, CAVE=29, FOREST=30, DESERT=31,
    VILLAGE=32, BASTION=33, TOWERPLACE=34, SIMPLE_HOUSE=35, GOOD_PLACE=36 , FISHING_CHALLENGE=37, ARCHERY_CONTEST=38, STRANGE_STONE=39,
    QUEST_ENCOUNTER=40
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
        case QUEST_ENCOUNTER: QuestEncounter(hero); break;
        default: std::cout << "Unknown event type!" << std::endl; break;
    }
}


void QuestEncounter(Character& hero)
{
    Quest* activeQuests = hero.GetActiveQuests();
    if (!activeQuests || activeQuests->GetCountQuest() == 0) {
        std::cout << "\nYou come across a lead related to a task, but you have no active quests right now.\n";
        return;
    }

    std::cout << "\nYou find clues related to one of your active quests!\n";
    for (int i = 0; i < activeQuests->GetCountQuest(); i++) {
        Quest* q = activeQuests->GetItemQuest(i);
        if (q && !q->IsCompleted()) {
            std::cout << "You make progress on: " << q->GetQuestName() << "\n";
            q->CompleteQuest(hero);
            return;
        }
    }
    std::cout << "All your active quests are already completed.\n";
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
        PrintEventCard("☣️", "MOLD OUTBREAK", "Black mold spores spread through the ventilation! You cough violently.", Color::RED);
        DamageHero(hero, 10);
    } else {
        PrintEventCard("☣️", "MOLD OUTBREAK", "Musty smell in the hallway. Mild respiratory irritation.", Color::YELLOW);
        DamageHero(hero, 5);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}


void Rain(Character& hero, GameHard& levelDificulty) {
    if (levelDificulty.GetDifficultyLevel() >= 2) {
        PrintEventCard("🌧️", "CEILING LEAK", "A pipe bursts above your room! Water damages your belongings.", Color::RED);
        DamageHero(hero, 8);
        LoseGold(hero, 15);
    } else {
        PrintEventCard("🌧️", "DRIPPING FAUCET", "Annoying drip keeps you awake. You lose some rest.", Color::YELLOW);
        DamageHero(hero, 3);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void VolcanicEruption(Character& hero, GameHard& levelDificulty) {
    if (levelDificulty.GetDifficultyLevel() >= 2) {
        PrintEventCard("🌋", "HEATING SYSTEM FAILURE", "The boiler explodes! Scalding steam fills the corridors.", Color::RED);
        DamageHero(hero, 15);
    } else {
        PrintEventCard("🌋", "RADIATOR BURST", "Your radiator cracks. Hot water sprays everywhere.", Color::YELLOW);
        DamageHero(hero, 8);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void FlashFlood(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("🌊", "BASEMENT FLOODING", "Sewage backup floods the lower floors! You wade through waste.", Color::RED);
        DamageHero(hero, 15);
        LoseGold(hero, 20);
    } else
    if (rand() % 2 == 0) {
        PrintEventCard("🌊", "BATHROOM FLOOD", "Someone clogged the toilet. Water seeps into the hallway.", Color::YELLOW);
        DamageHero(hero, 5);
    } else {
        PrintEventCard("🌊", "WASHING MACHINE LEAK", "Laundry room floods. Your socks are ruined.", Color::YELLOW);
        DamageHero(hero, 5);
        LoseGold(hero, 10);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);

}

void Mudslide(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("⛰️", "TRASH CHUTE AVALANCHE", "Garbage compactor jams! Trash cascades down all floors.", Color::RED);
        DamageHero(hero, 12);
    } else
    if (rand() % 2 == 0) {
        PrintEventCard("⛰️", "LAUNDRY PILE COLLAPSE", "Mountain of dirty clothes topples on you.", Color::YELLOW);
        DamageHero(hero, 6);
    } else {
        PrintEventCard("⛰️", "BOOKSHELF TOPPLES", "Your roommate's textbook tower falls. Bruised but alive.", Color::YELLOW);
        DamageHero(hero, 8);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void HumidHot(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("🏜️", "AC BROKEN HEATWAVE", "Air conditioning dies during finals week! Unbearable heat.", Color::RED);
        DamageHero(hero, 12);
    } else
    if (rand() % 2 == 0) {
        PrintEventCard("☀️", "STUFFY ROOM", "Windows painted shut. Stale air makes you sluggish.", Color::YELLOW);
        DamageHero(hero, 4);
    } else {
        PrintEventCard("🏜️", "SAUNA DORM", "Someone left the dryer on all night. Humidity at 90%.", Color::RED);
        DamageHero(hero, 7);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void ConstrictorVines(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("🌿", "CABLE MAZE", "Tangled charger cables ensnare you! Panic attack.", Color::RED);
        DamageHero(hero, 8);
    } else
    {
        PrintEventCard("🌿", "BLIND CORDS", "Window blind cords wrap around your neck briefly.", Color::YELLOW);
        DamageHero(hero, 4);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}


void QuickFreezingGlad(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("❄️", "WINDOW BROKEN IN WINTER", "Dorm window shattered! Arctic wind blasts through.", Color::RED);
        DamageHero(hero, 12);
    } else
    {
        PrintEventCard("❄️", "HEATING OFF", "Radiators cold. You wake up shivering.", Color::YELLOW);
        DamageHero(hero, 6);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}




void Extortion(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("💰", "EXTORTION", "The RA demands you hand over some snacks for the floor meeting!");
    LoseGold(hero, 15);
    } else
    {
    PrintEventCard("💰", "EXTORTION", "A senior student demands you hand over some snacks!");
    LoseGold(hero, 10);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
    
}

void PoacherTrapTrigger(Character& hero, GameHard& levelDificulty) {
    if(levelDificulty.GetDifficultyLevel()  ==3 ) 
    {
        PrintEventCard("🪤", "ELEVATOR TRAP", "Elevator drops between floors! You're stuck for hours.", Color::RED);
        DamageHero(hero, 10);
        LoseGold(hero, 20);
    } else
    {
        PrintEventCard("🪤", "DOOR JAM", "Your dorm room door jams. You climb out the window.", Color::YELLOW);
        DamageHero(hero, 6);
    }
    hero.SetLevel(hero.GetLevel() + 0.04);
    
}
// Narrative Events (No stat loss)  =====================Need finish
void WillWispAttraction(Character& hero, GameHard& levelDificulty)   { PrintEventCard("👻", "GHOST IN THE HALLWAY", "Flickering lights guide you to a hidden study nook.", Color::MAGENTA); hero.SetLevel(hero.GetLevel() + 0.02); }
void PollenHallucinations(Character& hero, GameHard& levelDificulty) { PrintEventCard("🍄", "EXHAUSTION HALLUCINATIONS", "Sleep deprivation makes shadows move. You see things.", Color::MAGENTA); hero.SetLevel(hero.GetLevel() + 0.01); }
void EnemyPatrol(Character& hero, GameHard& levelDificulty)          { PrintEventCard("⚔️", "SECURITY PATROL", "Campus security does rounds. Hide your contraband!", Color::YELLOW); hero.SetLevel(hero.GetLevel() + 0.01); }
void MonsterAmbush(Character& hero, GameHard& levelDificulty)        { PrintEventCard("🐺", "LOUD NEIGHBOR AMBUSH", "A loud neighbor bursts out from their room!", Color::RED); DamageHero(hero, 5); hero.SetLevel(hero.GetLevel() + 0.03); }
void CunningScavengers(Character& hero, GameHard& levelDificulty)    { PrintEventCard("🦅", "TEXTBOOK SCALPERS", "Students resell notes at 10x price. Watch your wallet.", Color::YELLOW); LoseGold(hero, 15); hero.SetLevel(hero.GetLevel() + 0.02); }
void StagedAccident(Character& hero, GameHard& levelDificulty)       { PrintEventCard("🎭", "STAGED SPILL", "Someone 'accidentally' spills coffee on your laptop.", Color::YELLOW); DamageHero(hero, 3); LoseGold(hero, 50); hero.SetLevel(hero.GetLevel() + 0.02); }
void FalseHospitableHost(Character& hero, GameHard& levelDificulty)  { PrintEventCard("🏡", "ROOMMATE'S MYSTERY MEAL", "Your roommate offers 'special brownies'. Suspicious.", Color::YELLOW); hero.SetHealth(hero.GetHealth() - 5); hero.SetLevel(hero.GetLevel() + 0.02); }
void ThePropheticBeggar(Character& hero, GameHard& levelDificulty)   { PrintEventCard("🔮", "PROPHETIC SENIOR", "An old senior whispers an ominous prophecy about finals.", Color::CYAN); hero.SetLevel(hero.GetLevel() + 0.03); hero.SetIntelligence(hero.GetIntelligence() + 1); }
void TheShadowingKid(Character& hero, GameHard& levelDificulty)      { PrintEventCard("👀", "SHADOWING FRESHMAN", "A lost freshman follows you thinking you're their RA.", Color::CYAN); hero.SetLevel(hero.GetLevel() + 0.01); GainGold(hero, 5); }
void TheTurncoatGuide(Character& hero, GameHard& levelDificulty)     { PrintEventCard("🗺️", "BAD DIRECTIONS", "Upperclassman sends you to the wrong building for your exam.", Color::YELLOW); DamageHero(hero, 2); hero.SetLevel(hero.GetLevel() + 0.02); }



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
            std::cout << "You had entered an overgrown storage room" << std::endl;
            std::cout << "You see a small supply closet" << std::endl;

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
std::cout << "You walk into the dorm common room. The smell of instant noodles and energy drinks fills the air." << std::endl;
std::cout << "You can rest here on the old couch and regain some health." << std::endl;
std::cout << "Or you can talk to your roommates and gather information about your next adventure." << std::endl;
std::cout << "You can also play a game of chance with the other students." << std::endl;

std::cout << "What would you like to do?" << std::endl;
std::cout << "1. Rest and regain health" << std::endl;
std::cout << "2. Talk to your roommates" << std::endl;
std::cout << "3. Play a game of chance" << std::endl;
std::cout << "4. Leave the common room" << std::endl;

int choice = ChoiceInput_Number();

switch (choice) {
    case 1:
        std::cout << "You rest and regain some health." << std::endl;
        hero.SetHealth(hero.GetHealth() + 20);
        hero.SetLevel(hero.GetLevel() + 0.04);
        break;
    case 2: {
        GameHard localDifficulty;
        TalkToLocals(hero, localDifficulty);
        break;
    }
    case 3: {
        std::cout << "You play a game of chance with the other students." << std::endl;

        std::cout << "Choose a game to play:\n1. Dice Roll\n2. Card Draw\n3. Coin Flip\n";
        int gameChoice = ChoiceInput_Number();
        switch (gameChoice) {
            case 1:
                std::cout << "You choose to play Dice Roll." << std::endl;
                DiceRoll(hero);
                break;

            case 2:
                std::cout << "You choose to play Card Draw." << std::endl;
                CardDraw(hero);
                break;
            case 3: {
                std::cout << "You choose to play Coin Flip." << std::endl;
                std::cout << "Call it: 1. Heads  2. Tails\n";
                int call = ChoiceInput_Number();
                int result = rand() % 2 + 1;
                std::cout << "The coin lands on " << (result == 1 ? "Heads" : "Tails") << "!\n";
                if (call == result) {
                    std::cout << "You won! +10 gold.\n";
                    hero.SetGold(hero.GetGold() + 10);
                } else {
                    std::cout << "You lost. -5 gold.\n";
                    hero.SetGold(hero.GetGold() - 5);
                }
                break;
            }
            default:
                std::cout << "Invalid choice. You leave the game." << std::endl;
                break;
        }
        break;
    }
    case 4:
        std::cout << "You leave the common room and continue your adventure." << std::endl;
        break;
    default:
        std::cout << "Invalid choice. You leave the common room." << std::endl;
}
}

void Hostel(Character& hero) {
    // Atmospheric introduction box / header
    std::cout << Color::CYAN << Color::BOLD << "\n 🏨 [LOCATION] " 
              << Color::RESET << "The Dorm Kitchen Lounge\n";
    std::cout << Color::DARK_GRAY << "----------------------------------------\n" << Color::RESET;
    std::cout << " You step into a warm, dimly lit kitchen. The air smells of instant noodles and burnt toast.\n";
    std::cout << " A weary resident advisor nods from behind the counter, and other students murmur in corners.\n\n";

    std::cout << Color::BOLD << " What would you like to do?\n" << Color::RESET;
    std::cout << "  " << Color::YELLOW << "1." << Color::RESET << " Grab a nap on the couch to rest and recover health\n";
    std::cout << "  " << Color::YELLOW << "2." << Color::RESET << " Approach the other students to chat and gather rumors\n";
    std::cout << "  " << Color::YELLOW << "3." << Color::RESET << " Leave the lounge and head back out\n";
    std::cout << Color::DARK_GRAY << "----------------------------------------\n" << Color::RESET;
    
    std::cout << Color::BOLD << " Choice > " << Color::RESET;
    int choice = ChoiceInput_Number();
    
    std::cout << "\n";

    switch (choice) {
        case 1: {
            std::cout << Color::GREEN << " ⛺ [REST] " << Color::RESET << "You secure a quiet spot on the couch for a nap.\n";
            GainHealth(hero, 15);
            hero.SetLevel(hero.GetLevel() + 0.01);
            break;
        }
        case 2: {
            std::cout << Color::MAGENTA << " 🗣️  [RUMORS] " << Color::RESET << "You sit by the microwave and strike up a conversation...\n";
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
                    std::cout << Color::CYAN << " 🗺️  " << Color::RESET << "\"Old legends say someone's stash of snacks is buried deep in the far dorm closet...\"\n";
                    break;
                case 2:
                    std::cout << Color::CYAN << " 📜 " << Color::RESET << "\"The exams have been growing harder by the day. Nobody feels safe anymore.\"\n";
                    break;
                case 3:
                    std::cout << Color::CYAN << " 💰 " << Color::RESET << "\"The student council is always paying for help moving furniture. Check the board outside.\"\n";
                    break;
                case 4:
                    if (hero.GetGold() >= 10) {
                        LoseGold(hero, 10);
                        std::cout << Color::GREEN << " ✨ " << Color::RESET << "The lounge cheers! Everyone raises a cup of instant coffee to your generosity.\n";
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
            std::cout << Color::DARK_GRAY << " 🚪 [LEAVE] " << Color::RESET << " You step back out into the dorm hallway.\n";
            break;
        default:
            std::cout << Color::RED << " ⚠️  [NOTICE] " << Color::RESET << "Indecisive, you are gently nudged out the front door.\n";
            break;
    }
}

void Castle(Character& hero)
{
std::cout << "You enter the dean's office floor. The halls are lined with framed diplomas and the air smells of fresh coffee." << std::endl;
std::cout << "Select what you want to do: " << std::endl;
std::cout << "1. Rest in the staff lounge" << std::endl;
std::cout << "2. Search for hidden treasures" << std::endl;
std::cout << "3. Look around for quests or tasks" << std::endl;
std::cout << "4. Leave the dean's office" << std::endl;
int choice = ChoiceInput_Number();

switch (choice) {
    case 1:
    {
        std::cout << "You rest in the staff lounge and regain some health." << std::endl;
        hero.SetHealth(hero.GetHealth() + 30);
        hero.SetLevel(hero.GetLevel() + 0.02);
        break;
    }
    case 2:
    {
        int randomRsult = rand() % 2;
        int randGold = rand() % 100 + 1; // Random gold between 1 and 100
        if (randomRsult == 0) {
            std::cout << "You find a hidden stash of cash in a desk drawer!" << std::endl;
            hero.SetGold(hero.GetGold() + randGold);
            hero.SetLevel(hero.GetLevel() + 0.02);
        } else {
            std::cout << "You search the office but find no treasures." << std::endl;
        }

        hero.SetLevel(hero.GetLevel() + 0.02);
        break;
    }
    case 3:
    {
        std::cout << "You look around for quests." << std::endl;
        int questResult = rand() % 2;
        if (questResult == 0) {
            std::cout << "You find a quest to help the dorm supervisor with a problem." << std::endl;
            Quest quest;
        } else {
            std::cout << "You look around but find no quests." << std::endl;
        }
        hero.SetLevel(hero.GetLevel() + 0.02);
        break;
    }
    case 4:
    {
        std::cout << "You leave the dean's office and continue your adventure." << std::endl;
        break;
    }
default:
    {
        std::cout << "Invalid choice. You leave the dean's office." << std::endl;
        break;
    }
}
}

void Dungeon(Character& hero)
{
    std::cout << Color::DARK_GRAY << "\n [LOCATION] " << Color::RESET << "You descend into the dark, damp basement storage room.\n";
    std::cout << "Choose your action:\n1. Search for treasure\n2. Look for monsters\n3. Leave\n";
    int choice = ChoiceInput_Number();
    switch (choice) {
        case 1: {
            int found = rand() % 100 + 1;
            if (found <= 40) {
                int gold = rand() % 50 + 10;
                std::cout << "You found " << gold << " gold hidden behind an old locker!\n";
                hero.SetGold(hero.GetGold() + gold);
            } else {
                std::cout << "You search but find nothing of value.\n";
            }
            hero.SetLevel(hero.GetLevel() + 0.02);
            break;
        }
        case 2:
            std::cout << "You hear scratching from behind the pipes but decide not to provoke it.\n";
            hero.SetLevel(hero.GetLevel() + 0.01);
            break;
        case 3:
            std::cout << "You leave the basement.\n";
            break;
        default:
            std::cout << "Invalid choice. You leave the basement.\n";
    }
}

void Cave(Character& hero)//laundry room: lost socks, machine rumble, or empty
{
    std::cout << Color::DARK_GRAY << "\n [LOCATION] " << Color::RESET << "You enter the dim, cluttered laundry room.\n";
    int caveType = rand() % 3;
    if (caveType == 0) {
        std::cout << "This appears to be a den of lost socks. Something stirs behind the dryers!\n";
        hero.SetHealth(hero.GetHealth() - 3);
    } else if (caveType == 1) {
        std::cout << "You hear a distant rumble from an overloaded washing machine. You retreat carefully.\n";
    } else {
        std::cout << "It's just a simple, empty laundry room. You rest for a moment.\n";
        hero.SetHealth(hero.GetHealth() + 5);
    }
    hero.SetLevel(hero.GetLevel() + 0.02);
}

void Forest(Character& hero)
{
    std::cout << Color::GREEN << "\n [LOCATION] " << Color::RESET << "You walk through a room that has grown wild with potted trees and overgrown plants.\n";
    int event = rand() % 3;
    if (event == 0) {
        std::cout << "You gather some herbs from the windowsill planters.\n";
        hero.SetHealth(hero.GetHealth() + 3);
    } else if (event == 1) {
        std::cout << "You get scratched by a thorny cactus someone left in the corner.\n";
        hero.SetHealth(hero.GetHealth() - 2);
    } else {
        std::cout << "The overgrown room is quiet and peaceful.\n";
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void Desert(Character& hero)
{
    std::cout << Color::YELLOW << "\n [LOCATION] " << Color::RESET << "You cross the attic room, scorching hot from the sun beating on the roof.\n";
    int heatDamage = rand() % 5 + 1;
    std::cout << "The relentless heat drains you. You lose " << heatDamage << " health.\n";
    hero.SetHealth(hero.GetHealth() - heatDamage);
    hero.SetLevel(hero.GetLevel() + 0.02);
}

void Village(Character& hero)
{
    std::cout << Color::CYAN << "\n [LOCATION] " << Color::RESET << "You arrive at a small, quiet shared room down the hall.\n";
    std::cout << "The roommates greet you warmly and offer you a place to rest.\n";
    hero.SetHealth(hero.GetHealth() + 5);
    hero.SetLevel(hero.GetLevel() + 0.01);
}

void Bastion(Character& hero)
{
    std::cout << Color::CYAN << "\n [LOCATION] " << Color::RESET << "You reach the reinforced security office manned by the dorm guards.\n";
    std::cout << "The guards let you rest within its safe walls.\n";
    hero.SetHealth(hero.GetHealth() + 10);
    hero.SetDefense(hero.GetDefense() + 1);
    hero.SetLevel(hero.GetLevel() + 0.02);
}

void TowerPlace(Character& hero)//evil TowerPlace , mage TowerPlace
{
    std::cout << Color::MAGENTA << "\n [LOCATION] " << Color::RESET << "You approach the tall, mysterious stairwell tower at the end of the building.\n";
    int towerType = rand() % 2;
    if (towerType == 0) {
        std::cout << "Dark energy radiates from this stairwell's flickering lights. You feel uneasy.\n";
        hero.SetHealth(hero.GetHealth() - 4);
    } else {
        std::cout << "A reclusive senior student lives on the top floor and shares some wisdom with you.\n";
        hero.SetIntelligence(hero.GetIntelligence() + 1);
    }
    hero.SetLevel(hero.GetLevel() + 0.02);
}

void SimpleHouse(Character& hero)//evil mage , witch , friendly house
{
    std::cout << Color::YELLOW << "\n [LOCATION] " << Color::RESET << "You come across a small room at the end of the corridor.\n";
    int houseType = rand() % 3;
    if (houseType == 0) {
        std::cout << "A grumpy roommate lives here and curses at you as you pass!\n";
        hero.SetHealth(hero.GetHealth() - 5);
    } else if (houseType == 1) {
        std::cout << "A friendly old resident advisor offers you a warm meal.\n";
        hero.SetHealth(hero.GetHealth() + 8);
    } else {
        std::cout << "The room is friendly and welcoming. You rest a while.\n";
        hero.SetHealth(hero.GetHealth() + 5);
    }
    hero.SetLevel(hero.GetLevel() + 0.01);
}


void GoodPlace(Character& hero)//good place for rest and food
{
std::cout << "You enter a peaceful study room. The atmosphere is calm and serene." << std::endl;
std::cout << "You can rest here and regain some health." << std::endl;
hero.SetLevel(hero.GetLevel() + 0.01);
hero.SetHealth(hero.GetHealth() + 7);

}
 //===============================================================================Additional_Events_Games======================================================
void FishingChallenge(Character& hero)
{
    std::cout << "You participate in a laundry fishing challenge with other students." << std::endl;
    std::cout << "You can try to catch the biggest lost sock or the rarest item." << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Try to catch the biggest item" << std::endl;
    std::cout << "2. Try to catch the rarest item" << std::endl;
    std::cout << "3. Leave the laundry challenge" << std::endl;


    
    std::cout << "Enter your choice: ";
    int choice = ChoiceInput_Number();
    switch (choice) {
case 1:
        {
            std::cout << "You try to catch the biggest item." << std::endl;
            int itemSize = rand() % 100 + 1; // Random size between 1 and 100
            std::cout << "You reach into the washing machine and feel around. After a while, you feel a tug!" << std::endl;
            std::cout << "You get into a struggle with whatever is inside!" << std::endl;
            if(hero.GetStrength() >= itemSize)
            {
                std::cout << "You successfully pull out a huge bundle of laundry! You gain 20 gold." << std::endl;
                hero.SetGold(hero.GetGold() + 20);
                hero.SetLevel(hero.GetLevel() + 0.4);
            }
            else
            {
                std::cout << "The item was too heavy for you. You lose 3 health." << std::endl;
                hero.SetHealth(hero.GetHealth() - 2);
                hero.SetLevel(hero.GetLevel() + 0.01);
            }
            break;
        }
        case 2:
        {
            std::cout << "You try to catch the rarest item." << std::endl;
            std::cout << "You reach into the washing machine and feel around. After a while, you feel a tug!" << std::endl;
            int rareFishChance = rand() % 100 + 1; // Random chance between 1 and 100
            if(rareFishChance <= 10) {
                std::cout << "You successfully find a rare vintage item! You gain 50 gold." << std::endl;
                hero.SetGold(hero.GetGold() + 50);
                hero.SetLevel(hero.GetLevel() + 0.4);
            } else {
                std::cout << "The item slipped away. You lose 5 health." << std::endl;
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
    std::cout << "You participate in a dart contest with other students in the common room." << std::endl;
    std::cout << "You can try to hit the bullseye or aim for the highest score." << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Try to hit the bullseye" << std::endl;
    std::cout << "2. Try to aim for the highest score" << std::endl;
    std::cout << "3. Leave the dart contest" << std::endl;
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
            std::cout << "You leave the dart contest." << std::endl;
            break;
        }
        default:
            std::cout << "Invalid choice. You leave the dart contest." << std::endl;
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
    std::cout << Color::RED << "\n┌──────────────────────────────────────────────┐\n" << Color::RESET;
    std::cout << Color::RED << "│ 👻  MIDNIGHT FIRE ALARM                      │\n" << Color::RESET;
    std::cout << Color::RED << "├──────────────────────────────────────────────┤\n" << Color::RESET;
    std::cout << "│ The fire alarm screams at 3 AM! Everyone     │\n";
    std::cout << "│ evacuates into the cold night. Someone       │\n";
    std::cout << "│ pulled it as a prank... or was it?           │\n";
    std::cout << Color::RED << "└──────────────────────────────────────────────┘\n" << Color::RESET;

    std::cout << "\nWhat do you do?\n";
    std::cout << "1. Grab your go-bag and evacuate properly\n";
    std::cout << "2. Hide in your room and hope it's false\n";
    std::cout << "3. Help the RA check floors\n";
    std::cout << "Choice: ";
    
    int choice = ChoiceInput_Number();
    
    switch(choice) {
        case 1:
            std::cout << "You evacuate calmly with your essentials. Smart move.\n";
            GainHealth(hero, 5);
            hero.SetLevel(hero.GetLevel() + 0.05);
            break;
        case 2:
            std::cout << "The RA kicks your door open. You get written up and lose sleep.\n";
            DamageHero(hero, 8);
            hero.SetLevel(hero.GetLevel() + 0.01);
            break;
        case 3:
            std::cout << "You help the RA. They're grateful and share insider info.\n";
            GainGold(hero, 20);
            hero.SetLevel(hero.GetLevel() + 0.08);
            break;
        default:
            std::cout << "You freeze in panic. The crowd pushes you outside.\n";
            DamageHero(hero, 5);
            hero.SetLevel(hero.GetLevel() + 0.01);
    }
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
                    std::cout << "The locals tell you about a hidden stash in the overgrown storage room.\n";
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
                    std::cout << "The students suggest checking the bulletin board for high-paying gigs.\n";
                    hero.SetLevel(hero.GetLevel() + 0.02);
                } else {
                    std::cout << "The students suggest checking the common room for basic odd jobs.\n";
                }
                break;

            case 4:
                std::cout << "You end the conversation with the other students.\n";
                break;

            default:
                std::cout << "Invalid choice. Please choose options 1 through 4.\n";
                break;
        }
    }
}


void TalkStrangers()
{
    int talk_random = rand() % 6 + 1;       //6 different talks with strangers
    switch(talk_random)
    {
        case 1:
            std::cout << "You meet a senior student who shares tales of exam survival." << std::endl;
            BardStory();
            break;

        case 2:
            std::cout << "A mysterious exchange student offers you a cryptic riddle to solve." << std::endl;
            break;

        case 3:
            std::cout << "You encounter a student selling lecture notes and cheat sheets." << std::endl;
            break;

        case 4:
            std::cout << "A laundry room regular tells you about the best lost-and-find spots." << std::endl;
            break;

        case 5:
            std::cout << "You meet a graduate student who shares tips for surviving final exams." << std::endl;
                break;
        case 6:
            std::cout << "A professor discusses the history of the university and its legends." << std::endl;
            break;

    }
}


void BardStory()
{
int story_random = rand() % 4 + 1;      
switch(story_random)
    {
        case 1:
            std::cout << "The senior tells of a legendary cheat sheet that can pass any exam." << std::endl;
            std::cout << "The legend of heroic student Alex, who sought the perfect GPA, " << std::endl;
            std::cout << "and stayed up all night to battle against the final boss exam to prove their worth." << std::endl;
            std::cout << "While typical of such tales the student was indeed victorious and returned with the somewhat smallish grade of B+," << std::endl;
            std::cout << "and was proclaimed worthy to graduate and inherit the alumni network." << std::endl;
            std::cout << "The ending however is more tragic, as it recounts the student loans being plagued by two greater," << std::endl;
            std::cout << "more fearsome interest rates that destroyed the budget and its occupants in vengeance for the slaying of their young savings." << std::endl;
            break;

        case 2:
            std::cout << "This historical favorite is told more cautiously in the dean's office, " << std::endl;
            std::cout << "for fear of the retribution that comes with openly mocking the faculty's ancestors. " << std::endl;
            std::cout << "The tale itself concerns an arrogant freshman who received a pair of cursed dancing shoes as a orientation gift that gave them two left feet. " << std::endl;
            std::cout << std::endl;
            std::cout << "Aside from the embarrassment upon the welcome party dance floor that evening," << std::endl;
            std::cout << "they were forever remembered for their clumsy gait and inability to climb stairs without stumbling." << std::endl;
            break;

        case 3:
            std::cout << "A touching roommate romance, recounting the chance meeting of a CS major and an Art major at a campus harvest festival. " << std::endl;
            std::cout << "It tells of their blossoming friendship during the following winter as they struggled to protect their shared apartment from vicious bugs," << std::endl;
            std::cout << "hungry deadlines and a small epidemic of flu." << std::endl;
            std::cout << "While of mixed popularity among the more conservative crowds, it has become a favorite of independent students across campus; both appreciating the tale for very different reasons. " << std::endl;
            std::cout << "\"Ones code like silk, the others art like fire, between them sparked a burning desire. Days turned to weeks and their friendship did grow, evolving into a bond more pure then library silence.\"" << std::endl;
            break;

        case 4:
            std::cout << "The valiant legend of the famed Scorpion Energy Drink," << std::endl;
            std::cout << "the beverage brewed from the essence of deadlines and given a life of its own. " << std::endl;
            std::cout << "While carried by procrastinators and all-nighters for centuries and the subject of many a campus tale, " << std::endl;
            std::cout << "no other retelling quite captures the horror and overwhelming sense of doom those on the wrong end of this drink felt as this one. " << std::endl;
            std::cout << "Often sung in a deep baritone with rattles and thumb cymbals signifying the scorpion's clawed grasps, it is not soon forgotten by any present." << std::endl;
            break;
    }

}


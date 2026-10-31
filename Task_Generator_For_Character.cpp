#include <iostream>
#include <string>
#include <map>
#include "Header.h"



constexpr const char* CYAN = "\033[36m";
constexpr const char* YELLOW = "\033[33m";
constexpr const char* GRAY = "\033[90m";
constexpr const char* RED = "\033[31m";
constexpr const char* RESET = "\033[0m";

// void Task_1_CollectThings();
// void Task_2_Rescue();
// void Task_3_Explore();
// void Task_4_Eliminate();
// void Task_5_Deliver();
// void Task_6_Escort();
// void Task_7_Puzzle();

struct QuestStructBasic
{
    int gold_task;
    int difficulty_task;
    float experience_task;
};

int Quest::ResizeQuestBig()
{
   int new_capacity = capacity_quest + 1;
    Quest** temp = new Quest*[new_capacity];
    for (int i = 0; i < count_quest; i++)
        temp[i] = quests[i];
    delete[] quests;
    quests = temp;
    capacity_quest = new_capacity;
    return 0;
}


int Quest::AddQuest(Quest* quest1) {
    if (count_quest >= capacity_quest) ResizeQuestBig();
    quest1->SetQuestNumber(number_quest);   
    quests[count_quest++] = quest1;
    number_quest++;
    return 0;
}


// name + gold
// name -> {gold, difficulty}
static std::map<std::string, QuestStructBasic>& GetQuestTaskDB() {                       //Basic tasks
    static std::map<std::string, QuestStructBasic> yar;
    if (yar.empty()) {
        yar = { //Collect tasks
            {"Collect Magic Sticks", {25, 2, 0.01}}, // 25 gold, 2 difficulty , 0.01 exp
            {"Collect Magic Stones", {25, 2, 0.01}},
            {"ColLect Magic Items", {18,1, 0.01}},
            {"ColLect Magic Grass",{15, 2, 0.01}},
            {"Collect Magic Flowers", {18, 2, 0.01}},
            {"Collect Rare Ores",{23, 2, 0.01}},
            {"Collect Broken Portal Fragments",{39, 2, 0.01}},
            {"Collect Festival Ingredients",{20, 1, 0.01}},
            {"Collect Magic White moss",{15,1, 0.01}},
            {"Collect Mandragora",{22, 2, 0.01}},
            {"Collect Magic Mirror",{20, 1, 0.01}},
            {"Collect Magic Pages from Book",{25, 5, 0.01}},
            {"Collect Magic Pages from Evil Book",{32, 2, 0.01}},
            {"Collect Magical Herb for village",{25, 2, 0.01}},
            {"Collect pinocones for magic squirrel",{12, 1, 0.01}},
            {"Collect leaves for small dwarf's house",{20, 1, 0.01}},


            {"Rescue girl form goblin", {40, 3, 0.3}},
            {"Rescue village form orks", {50, 3, 0.3}},
            {"Rescue boy form orks camp", {35, 3, 0.25}},
            {"Rescue dog form misfortune", {15, 3, 0.09}},
            {"Rescue a herd pf pigs for farmer", {20, 3, 0.05}},

            {"Explore new lands for farmers", {15, 1, 0.03}},
            {"Explore new lands for king", {27, 1, 0.05}},
            {"Explore new lands for farmers", {15, 1, 0.03}},
            {"Explore new lands for farmers", {15, 1, 0.03}},


            {"Eliminate danger ork", {25, 2, 0.08}},
            {"Kill big hog", {15, 1, 0.04}},
            {"Eliminate danger bear", {17, 2, 0.05}}
            
        };
    }
    return yar;
}





std::string Quest::RandomizeQuest(GameHard& difficulty) {
    auto& yar = GetQuestTaskDB();

    std::string task_ar[] = {   //List of tasks
       "Collect Magic Sticks" , "Collect Magic Stones", "ColLect Magic Items", "ColLect Magic Grass", "Collect Magic Flowers",
        "Collect Rare Ores", "Collect Broken Portal Fragments", "Collect Festival Ingredients"
    };

    std::string chosen_name_t;
    chosen_name_t = task_ar[rand() % std::size(task_ar)];    //Change number of tasks
    questDifficulty = rand() + 3;
    auto it = yar.find(chosen_name_t);
    if (it != yar.end()) {
        reward = it->second.gold_task;                      //get reward
        questDifficulty = it->second.difficulty_task;       //get diffilculty
        int exp = it->second.experience_task;               //get experience
        
        reward = reward / difficulty.GetDifficultyLevel();
    }

    questName = chosen_name_t;
    return questName;
}



void Quest::DisplayQuestInfo() const {
    std::cout << "\n┌───────────────────────────────────────────────────┐\n";
    std::cout << "│                 QUEST DETAILS                     │\n";
    std::cout << "├───────────────────────────────────────────────────┤\n";
    std::cout << "│  Title       : " << questName << "\n";
    std::cout << "│  Difficulty  : " << questDifficulty << "\n";
    std::cout << "│  Reward      : " << reward << " gold\n";
    std::cout << "│  Status      : " << (isCompleted ? "Completed" : "In Progress") << "\n";
    std::cout << "└───────────────────────────────────────────────────┘\n\n";
}


void Quest::DisplayAllQuestInfo() const 
{

    if (count_quest == 0)
    {
        std::cout << RED << "\n[!] Quest's list is completely empty.\n" << RESET;
        return;
    }

    std::cout << CYAN << "\n================ Quest's list (" << count_quest << " items) ================\n" << RESET;

    for (int i = 0; i < count_quest; ++i)
    {
        std::cout << YELLOW << "#" << (i + 1) << " " << RESET
                  << quests[i]->GetQuestName() 
                  << GRAY << " [ID: " << quests[i]->GetQuestNumber() 
                  << " | Type: " << quests[i]->GetQuestDifficulty() << "]" << RESET << "\n";

  
        quests[i]->DisplayQuestInfo();//Details here are

        if (i < count_quest - 1) {
            std::cout << GRAY << "--------------------------------------------------\n" << RESET;
        }
    }

    std::cout << CYAN << "====================================================\n\n" << RESET;
}



void Character::Talk_About_Life()
{
std::cout << "Talk about life Not implemented yet" << std::endl;
}




int Quest::Delete_Quest(int ) {
    for (int i = 0; i < count_quest; i++) {
        if (quests[i]->GetQuestNumber() == number_quest) {
            delete quests[i];
            for (int j = i; j < count_quest - 1; j++) {
                quests[j] = quests[j + 1];
            }
            count_quest--;
            std::cout << "Item with ID " << number_quest << " deleted." << std::endl;
            return 0;
        }
    }
    std::cout << "Item with ID " << number_quest << " not found!" << std::endl;
    return -1;
}
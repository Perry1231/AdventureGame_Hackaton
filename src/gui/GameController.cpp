#include "GameController.h"
#include "Header.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStandardPaths>
#include <QDebug>

static QString savesDir()
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                  + "/DormAdventureSaves/";
    QDir().mkpath(dir);
    return dir;
}

GameController::GameController(QObject *parent) : QObject(parent)
{
}

GameController::~GameController()
{
    cleanupGameObjects();
}

void GameController::cleanupGameObjects()
{
    delete m_hero; m_hero = nullptr;
    delete m_inventory; m_inventory = nullptr;
    delete m_quest; m_quest = nullptr;
    delete m_enemy; m_enemy = nullptr;
    delete m_difficulty; m_difficulty = nullptr;
    delete m_gameEvent; m_gameEvent = nullptr;
}

bool GameController::initializeNewGame(int difficultyLevel)
{
    cleanupGameObjects();
    
    try {
        setupNewGame(difficultyLevel);
        emit gameInitialized(true);
        emit heroStatusUpdated(formatHeroStatus());
        emit inventoryUpdated(formatInventory());
        emit questUpdated(formatQuests());
        return true;
    } catch (...) {
        emit gameInitialized(false);
        return false;
    }
}

void GameController::setupNewGame(int difficultyLevel)
{
    m_difficulty = new GameHard();
    m_difficulty->SetDifficultyLevel(difficultyLevel);
    
    m_hero = new Character();
    m_hero->SetName("Dorm Hero");
    m_hero->SetHealth(100);
    m_hero->SetStrength(10 + difficultyLevel * 2);
    m_hero->SetDefense(5 + difficultyLevel);
    m_hero->SetIntelligence(5);
    m_hero->SetGold(50);
    m_hero->SetLevel(1.0f);
    
    m_inventory = new MyInventory();
    m_hero->SetInventory(m_inventory);
    
    m_quest = new Quest();
    m_hero->SetActiveQuests(m_quest);
    
    m_enemy = new Enemy();
    m_enemy->RandomizeStats();
    
    m_gameEvent = new GameEvent();
}

bool GameController::loadGame(const QString &saveName)
{
    QString savesPath = savesDir();
    QString filePath = savesPath + saveName;
    
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit gameLoaded(false);
        return false;
    }
    
    try {
        QTextStream in(&file);
        QString allText = in.readAll();
        file.close();
        
        // First pass: read difficulty so the game is created with correct settings
        int difficulty = 1;
        int health = 100, strength = 10, defense = 5, intelligence = 5, gold = 50;
        float level = 1.0f;
        QString heroName = "Dorm Hero";
        QStringList inventoryItems;
        QStringList questLines;
        enum Section { None, Inventory, Quests } section = None;
        
        for (const QString &line : allText.split('\n')) {
            QString trimmed = line.trimmed();
            if (trimmed.isEmpty()) continue;
            if (trimmed == "--- INVENTORY ---") { section = Inventory; continue; }
            if (trimmed == "--- QUESTS ---") { section = Quests; continue; }
            if (trimmed.startsWith("===")) continue;
            
            if (section == Inventory) { inventoryItems << trimmed; continue; }
            if (section == Quests) { questLines << trimmed; continue; }
            
            int sep = trimmed.indexOf(':');
            if (sep < 0) continue;
            QString key = trimmed.left(sep).trimmed();
            QString val = trimmed.mid(sep + 1).trimmed();
            
            if (key == "Hero") heroName = val;
            else if (key == "Health") health = val.section('/', 0, 0).trimmed().toInt();
            else if (key == "Strength") strength = val.toInt();
            else if (key == "Defense") defense = val.toInt();
            else if (key == "Intelligence") intelligence = val.toInt();
            else if (key == "Gold") gold = val.toInt();
            else if (key == "Level") level = val.toFloat();
            else if (key == "Difficulty") difficulty = val.toInt();
        }
        
        if (difficulty < 1) difficulty = 1;
        cleanupGameObjects();
        setupNewGame(difficulty);
        
        m_hero->SetName(heroName.toStdString());
        m_hero->SetStrength(strength);
        m_hero->SetDefense(defense);
        m_hero->SetIntelligence(intelligence);
        m_hero->SetGold(gold);
        m_hero->SetLevel(level);
        m_hero->SetHealth(health);
        
        // Restore quest names as active quests
        for (const QString &q : questLines) {
            QString name = q.section('|', 0, 0).trimmed();
            if (name.isEmpty()) continue;
            Quest *nq = new Quest();
            nq->SetQuestName(name.toStdString());
            bool completed = q.contains("Completed: Yes");
            nq->SetCompleted(completed);
            m_quest->AddQuest(nq);
        }
        
        emit gameLoaded(true);
        emit heroStatusUpdated(formatHeroStatus());
        emit inventoryUpdated(formatInventory());
        emit questUpdated(formatQuests());
        return true;
    } catch (...) {
        emit gameLoaded(false);
        return false;
    }
}

void GameController::saveGame(const QString &saveName)
{
    QString savesPath = savesDir();
    QDir().mkpath(savesPath);
    QString filePath = savesPath + saveName;
    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit gameSaved(false);
        return;
    }
    
    QTextStream out(&file);
    out << "=== ADVENTURE GAME SAVE ===\n";
    out << "Hero: " << m_hero->GetName().c_str() << "\n";
    out << "Health: " << m_hero->GetHealth() << "/" << m_hero->GetTotalHealth() << "\n";
    out << "Attack: " << m_hero->GetStrength() << "\n";
    out << "Defense: " << m_hero->GetDefense() << "\n";
    out << "Intelligence: " << m_hero->GetIntelligence() << "\n";
    out << "Strength: " << m_hero->GetStrength() << "\n";
    out << "Gold: " << m_hero->GetGold() << "\n";
    out << "Level: " << m_hero->GetLevel() << "\n";
    out << "Difficulty: " << m_difficulty->GetDifficultyLevel() << "\n";
    
    // Save inventory
    out << "\n--- INVENTORY ---\n";
    for (int i = 0; i < m_inventory->GetCount(); ++i) {
        Item* obj = m_inventory->GetItem(i);
        if (obj) {
            out << obj->GetName().c_str() << " (value " << obj->GetValue() << ")\n";
        }
    }
    
    // Save quests
    out << "\n--- QUESTS ---\n";
    if (m_quest && m_quest->GetCountQuest() > 0) {
        for (int i = 0; i < m_quest->GetCountQuest(); ++i) {
            Quest* q = m_quest->GetItemQuest(i);
            if (q) {
                out << q->GetQuestName().c_str() << " | Difficulty: " << q->GetQuestDifficulty() 
                    << " | Completed: " << (q->IsCompleted() ? "Yes" : "No") << "\n";
            }
        }
    }
    
    file.close();
    emit gameSaved(true);
}

Character* GameController::getHero() const { return m_hero; }
MyInventory* GameController::getInventory() const { return m_inventory; }
Quest* GameController::getActiveQuests() const { return m_quest; }
Enemy* GameController::getCurrentEnemy() const { return m_enemy; }
GameHard* GameController::getDifficulty() const { return m_difficulty; }
GameEvent* GameController::getGameEvent() const { return m_gameEvent; }

void GameController::processTurn(int action)
{
    if (!m_hero || !m_inventory || !m_quest || !m_enemy || !m_difficulty || !m_gameEvent) return;
    
    QString result;
    QTextStream out(&result);
    
    switch (action) {
        case 0: { // Make turn
            struct EventDef {
                const char *icon;
                const char *title;
                const char *text;
                const char *color;
                int health;
                int gold;
                float exp;
            };
            static const EventDef events[] = {
                {"🌧️", "LEAKY CEILING",       "Water drips from the ceiling onto your notes. You move your desk and lose some sleep.", "#2980b9",  -4,  0, 0.01f},
                {"🔥", "FIRE DRILL AT 3 AM",   "The alarm shrieks. You stumble outside in slippers and lose precious rest.",          "#c0392b",  -6,  0, 0.02f},
                {"🍜", "FREE INSTANT NOODLES", "A kind neighbor shares their stash. Warm food restores your spirit.",                    "#27ae60",  +6,  0, 0.01f},
                {"💰", "FOUND COIN IN COUCH",  "You dig between the cushions and find forgotten coins!",                                  "#f1c40f",   0, 25, 0.02f},
                {"📚", "LIBRARY ALL-NIGHTER",  "You study until sunrise. Exhausting, but you learn a lot.",                               "#8e44ad",  -5,  0, 0.05f},
                {"🐭", "MOUSE IN THE ROOM",    "Something rustles under the bed. You spend an hour hunting it.",                          "#7f8c8d",  -3,  0, 0.01f},
                {"🚿", "NO HOT WATER",         "A cold shower jolts you awake. Brutal but effective.",                                     "#16a085",  -2,  0, 0.02f},
                {"🎉", "FLOOR PARTY",          "The whole floor is celebrating. You join in and make new friends.",                        "#e67e22",  +4, 10, 0.03f},
                {"📦", "PACKAGE DELIVERY",     "A package arrives for you. Inside: snacks and a note from home.",                         "#27ae60",  +8,  0, 0.02f},
                {"😴", "OVERSLEPT",            "You miss your alarm and rush out. In the panic you drop some coins.",                      "#c0392b",  -3, -10, 0.01f},
                {"🧹", "CLEANING DAY",         "The RA forces a room inspection. You clean everything and feel accomplished.",              "#3498db",  +2,  0, 0.03f},
                {"🕹️", "ARCADE NIGHT",         "Someone brought a console to the lounge. You win a few rounds.",                           "#9b59b6",  +3, 15, 0.03f},
                {"🦠", "DORM FLU",             "Half the floor is sick. You catch it too and feel terrible.",                              "#c0392b",  -8,  0, 0.01f},
                {"☕", "COFFEE MACHINE JACKPOT","The machine gives two cups for the price of one. Small victories.",                        "#e67e22",  +2,  5, 0.01f},
                {"📢", "LOUD NEIGHBORS",       "Bass shakes the wall until midnight. You get no rest.",                                   "#e74c3c",  -5,  0, 0.01f},
                {"🎓", "GUEST LECTURE",        "A brilliant speaker visits the dorm. You leave inspired.",                                 "#2980b9",   0,  0, 0.06f},
                {"🍕", "PIZZA SHARE",          "Someone orders too much pizza and shares the leftovers.",                                 "#e67e22",  +7,  0, 0.02f},
                {"🧾", "SURPRISE BILL",        "The dorm charges an unexpected fee. Your wallet weeps.",                                    "#c0392b",   0, -30, 0.01f},
                {"🧑‍🤝‍🧑", "NEW ROOMMATE",      "A new roommate moves in. You help carry boxes and bond.",                                   "#27ae60",  +3,  0, 0.04f},
                {"🌙", "CALM NIGHT",           "A rare, peaceful evening. You finally relax.",                                             "#16a085",  +9,  0, 0.02f},
            };
            const int eventCount = static_cast<int>(sizeof(events) / sizeof(events[0]));

            int idx = rand() % eventCount;
            for (int attempt = 0; attempt < eventCount; ++attempt) {
                bool seen = false;
                for (int h : m_gameEvent->eventHistory) {
                    if (h == idx) { seen = true; break; }
                }
                if (!seen) break;
                idx = rand() % eventCount;
            }
            m_gameEvent->eventHistory.push_back(idx);
            if (m_gameEvent->eventHistory.size() > 3) {
                m_gameEvent->eventHistory.erase(m_gameEvent->eventHistory.begin());
            }

            const EventDef &e = events[idx];

            int usedHealth = e.health;
            int usedGold = e.gold;

            if (m_difficulty && m_difficulty->GetDifficultyLevel() >= 3) {
                if (usedHealth < 0) usedHealth *= 2;
                if (usedGold < 0) usedGold *= 2;
            }

            if (usedHealth != 0) {
                int newHealth = m_hero->GetHealth() + usedHealth;
                m_hero->SetHealth(newHealth);
            }
            if (usedGold != 0) {
                int newGold = m_hero->GetGold() + usedGold;
                m_hero->SetGold(newGold);
            }
            m_hero->SetLevel(m_hero->GetLevel() + e.exp);

            out << "<div style='margin:6px 0;'>"
                << "<span style='font-size:16px;'>" << e.icon << "</span> "
                << "<b style='color:" << e.color << ";'>" << e.title << "</b><br/>"
                << "<span style='color:#2c3e50;'>" << e.text << "</span><br/>";

            if (usedHealth > 0)
                out << "<span style='color:#27ae60;'><b>+ " << usedHealth << " HP</b></span> ";
            else if (usedHealth < 0)
                out << "<span style='color:#c0392b;'><b>- " << (-usedHealth) << " HP</b></span> ";

            if (usedGold > 0)
                out << "<span style='color:#f39c12;'><b>+ " << usedGold << " gold</b></span> ";
            else if (usedGold < 0)
                out << "<span style='color:#c0392b;'><b>- " << (-usedGold) << " gold</b></span> ";

            out << "<span style='color:#7f8c8d;'><b>+ " << e.exp << " XP</b></span></div>";

            if (m_hero->GetHealth() <= 0) {
                emit gameOver("You collapsed in the dorm. Game over.");
                return;
            }
            break;
        }
        case 1: { // Inventory
            emit inventoryUpdated(formatInventory());
            return; // Don't emit turnProcessed for inventory
        }
        case 2: { // Active Quest
            emit questUpdated(formatQuests());
            return;
        }
        case 3: { // Main Menu
            emit returnedToMainMenu();
            return;
        }
        case 4: { // Fight an enemy
            m_enemy->RandomizeStats();
            m_enemyMaxHealth = m_enemy->GetHealth();
            if (m_enemyMaxHealth < 1) m_enemyMaxHealth = 1;
            m_heroMaxHealth = m_hero->GetHealth();
            if (m_heroMaxHealth < 1) m_heroMaxHealth = 1;
            m_inCombat = true;
            emit combatStarted(QString::fromStdString(m_enemy->GetName()),
                               m_enemy->GetHealth(), m_enemyMaxHealth,
                               m_enemy->GetTotalAttack(), m_enemy->GetTotalDefense());
            emit combatUpdated(m_enemy->GetHealth(), m_enemyMaxHealth,
                               m_hero->GetHealth(), m_heroMaxHealth);
            emit heroStatusUpdated(formatHeroStatus());
            return;
        }
    }
    
    emit turnProcessed(result);
    emit heroStatusUpdated(formatHeroStatus());
}

void GameController::processCombatAction(int action)
{
    if (!m_hero || !m_enemy) return;

    QString result;
    QTextStream out(&result);
    bool combatOver = false;

    switch (action) {
        case 0: { // Attack
            int damage = m_hero->GetTotalAttack() - m_enemy->GetTotalDefense();
            if (damage < 1) damage = 1;
            m_enemy->SetHealth(m_enemy->GetHealth() - damage);
            out << "<span style='color:#2980b9;'><b>You strike the "
                << m_enemy->GetName().c_str() << " for " << damage << " damage!</b></span>";

            if (m_enemy->GetHealth() <= 0) {
                int reward = m_enemy->GetGold();
                m_hero->SetGold(m_hero->GetGold() + reward);
                m_hero->SetLevel(m_hero->GetLevel() + 0.1f);
                out << "<br/><span style='color:#27ae60;'><b>🏆 VICTORY! "
                    << m_enemy->GetName().c_str() << " is defeated. +" << reward
                    << " gold, +0.10 XP.</b></span>";
                combatOver = true;
            } else {
                int enemyDmg = m_enemy->GetTotalAttack() - m_hero->GetTotalDefense();
                if (enemyDmg < 1) enemyDmg = 1;
                m_hero->SetHealth(m_hero->GetHealth() - enemyDmg);
                out << "<br/><span style='color:#c0392b;'><b>⚔ "
                    << m_enemy->GetName().c_str() << " hits back for " << enemyDmg
                    << " damage!</b></span>";

                if (m_hero->GetHealth() <= 0) {
                    emit combatProcessed(result);
                    emit combatUpdated(m_enemy->GetHealth(), m_enemyMaxHealth, 0, m_heroMaxHealth);
                    emit gameOver("You have been defeated in battle!");
                    return;
                }
            }
            break;
        }
        case 1: { // Talk
            out << "<span style='color:#8e44ad;'><b>You try to talk to the "
                << m_enemy->GetName().c_str() << "...</b></span>";
            if (m_enemy->GetAttitude() < 0) {
                int enemyDmg = m_enemy->GetTotalAttack() - m_hero->GetTotalDefense();
                if (enemyDmg < 1) enemyDmg = 1;
                m_hero->SetHealth(m_hero->GetHealth() - enemyDmg);
                out << "<br/><span style='color:#c0392b;'><b>The enemy is hostile and attacks for "
                    << enemyDmg << " damage!</b></span>";
                if (m_hero->GetHealth() <= 0) {
                    emit combatProcessed(result);
                    emit combatUpdated(m_enemy->GetHealth(), m_enemyMaxHealth, 0, m_heroMaxHealth);
                    emit gameOver("You have been defeated in battle!");
                    return;
                }
            } else {
                m_hero->SetLevel(m_hero->GetLevel() + 0.02f);
                out << "<br/><span style='color:#27ae60;'><b>The enemy calms down. +0.02 XP</b></span>";
                combatOver = true;
            }
            break;
        }
        case 2: { // Trade
            out << "<span style='color:#f39c12;'><b>You offer to trade...</b></span>";
            if (m_enemy->GetAttitude() < 0) {
                out << "<br/><span style='color:#c0392b;'><b>The enemy refuses to trade!</b></span>";
            } else {
                m_hero->SetGold(m_hero->GetGold() + 10);
                out << "<br/><span style='color:#27ae60;'><b>Trade successful! +10 gold.</b></span>";
                combatOver = true;
            }
            break;
        }
        case 3: { // Flee
            m_hero->SetLevel(m_hero->GetLevel() + 0.01f);
            out << "<span style='color:#95a5a6;'><b>You flee from combat. +0.01 XP</b></span>";
            combatOver = true;
            break;
        }
    }

    if (combatOver) m_inCombat = false;

    emit combatProcessed(result);
    emit combatUpdated(m_enemy->GetHealth(), m_enemyMaxHealth,
                       m_hero->GetHealth(), m_heroMaxHealth);
    emit heroStatusUpdated(formatHeroStatus());

    if (combatOver) {
        emit combatEnded(m_enemy->GetHealth() <= 0 ? "Victory!" : "Combat ended.");
    }
}

void GameController::processEventChoice(int choice)
{
    QString result = "Event choice processed: " + QString::number(choice);
    emit turnProcessed(result);
    emit heroStatusUpdated(formatHeroStatus());
}

void GameController::processTavernAction(int action)
{
    QStringList actions;
    switch (action) {
        case 0: // Rest
            if (m_hero) {
                m_hero->SetHealth(qMin(m_hero->GetHealth() + 20, m_hero->GetTotalHealth()));
                m_hero->SetLevel(m_hero->GetLevel() + 0.04);
            }
            actions << "Rest" << "Talk to locals" << "Play games" << "Leave";
            emit tavernOpened(actions);
            emit heroStatusUpdated(formatHeroStatus());
            break;
        case 1: // Talk to locals
            if (m_hero) m_hero->SetLevel(m_hero->GetLevel() + 0.02);
            actions << "Rest" << "Talk to locals" << "Play games" << "Leave";
            emit tavernOpened(actions);
            emit heroStatusUpdated(formatHeroStatus());
            break;
        case 2: // Play games
            actions << "Rest" << "Talk to locals" << "Play games" << "Leave";
            emit tavernOpened(actions);
            break;
        case 3: // Leave
            m_inTavern = false;
            emit turnProcessed("You leave the tavern.");
            break;
    }
}

void GameController::processLocationAction(const QString &location, int action)
{
    QString result = "Location: " + location + " Action: " + QString::number(action);
    
    if (m_hero) {
        m_hero->SetLevel(m_hero->GetLevel() + 0.01);
        m_hero->SetHealth(qMin(m_hero->GetHealth() + 5, m_hero->GetTotalHealth()));
    }
    
    emit turnProcessed(result);
    emit heroStatusUpdated(formatHeroStatus());
}

QString GameController::getHeroStatus() const
{
    return formatHeroStatus();
}

QString GameController::getInventoryText() const
{
    return formatInventory();
}

QString GameController::getQuestText() const
{
    return formatQuests();
}

QString GameController::getCurrentEventText() const
{
    return m_lastEventText;
}

QStringList GameController::getAvailableActions() const
{
    return {"Make Turn", "Inventory", "Active Quest", "Main Menu", "⚔️ Fight Enemy"};
}

QStringList GameController::getCombatActions() const
{
    return {"Attack", "Talk", "Trade", "Flee"};
}

QStringList GameController::getTavernActions() const
{
    return {"Rest", "Talk to Locals", "Play Games", "Leave"};
}

QStringList GameController::getLocationActions(const QString &location) const
{
    Q_UNUSED(location);
    return {"Search", "Rest", "Leave"};
}

QStringList GameController::getSaveFiles() const
{
    QString savesPath = savesDir();
    QDir dir(savesPath);
    if (!dir.exists()) return QStringList();
    
    QStringList filters;
    filters << "*.sav" << "*.txt";
    return dir.entryList(filters, QDir::Files);
}

bool GameController::hasSaveFiles() const
{
    return !getSaveFiles().isEmpty();
}

QString GameController::formatHeroStatus() const
{
    if (!m_hero) return "No hero data";
    
    QString status;
    QTextStream out(&status);
    out << "=== HERO STATUS ===\n";
    out << "Name: " << m_hero->GetName().c_str() << "\n";
    out << "Health: " << m_hero->GetHealth() << " / " << m_hero->GetTotalHealth() << "\n";
    out << "Attack: " << m_hero->GetTotalAttack() << " (Base: " << m_hero->GetStrength() << ")\n";
    out << "Defense: " << m_hero->GetTotalDefense() << " (Base: " << m_hero->GetDefense() << ")\n";
    out << "Intelligence: " << m_hero->GetIntelligence() << "\n";
    out << "Strength: " << m_hero->GetStrength() << "\n";
    out << "Gold: " << m_hero->GetGold() << "\n";
    out << "Level: " << m_hero->GetLevel() << "\n";
    if (m_difficulty) out << "Difficulty: " << m_difficulty->GetDifficultyLevel() << "\n";
    return status;
}

QString GameController::formatInventory() const
{
    if (!m_inventory) return "No inventory";
    
    QString inv;
    QTextStream out(&inv);
    out << "=== INVENTORY ===\n";
    out << "Capacity: " << m_inventory->GetCount() << " / " << m_inventory->GetCapacity() << "\n\n";
    
    for (int i = 0; i < m_inventory->GetCount(); ++i) {
        Item* obj = m_inventory->GetItem(i);
        if (obj) {
            out << "[" << i << "] " << obj->GetName().c_str() 
                << " (Value: " << obj->GetValue() << ")\n";
        }
    }
    return inv;
}

QString GameController::formatQuests() const
{
    if (!m_quest) return "No quests";
    
    QString qtext;
    QTextStream out(&qtext);
    out << "=== ACTIVE QUESTS ===\n";
    
    int count = m_quest->GetCountQuest();
    if (count == 0) {
        out << "No active quests.\n";
        out << "Use 'Task Generator' to create a new quest.\n";
    } else {
        for (int i = 0; i < count; ++i) {
            Quest* q = m_quest->GetItemQuest(i);
            if (q) {
                out << "[" << i << "] " << q->GetQuestName().c_str() << "\n";
                out << "    Description: " << q->GetQuestDescription().c_str() << "\n";
                out << "    Difficulty: " << q->GetQuestDifficulty() << "\n";
                out << "    Reward: " << q->GetReward() << " gold\n";
                out << "    Status: " << (q->IsCompleted() ? "COMPLETED" : "IN PROGRESS") << "\n\n";
            }
        }
    }
    return qtext;
}
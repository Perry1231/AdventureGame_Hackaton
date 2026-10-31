#include "GameController.h"
#include "Header.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStandardPaths>
#include <QDebug>

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
    m_hero->SetHealth(100);
    m_hero->SetTotalHealth(100);
    m_hero->SetAttack(10);
    m_hero->SetDefense(5);
    m_hero->SetIntelligence(5);
    m_hero->SetStrength(10);
    m_hero->SetGold(50);
    m_hero->SetLevel(1.0f);
    
    m_inventory = new MyInventory();
    
    m_quest = new Quest();
    m_hero->SetActiveQuests(m_quest);
    
    m_enemy = new Enemy();
    m_enemy->RandomizeEnemy(*m_difficulty);
    
    m_gameEvent = new GameEvent();
}

bool GameController::loadGame(const QString &saveName)
{
    cleanupGameObjects();
    
    QString savesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/saves/";
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
        
        // Parse save file - simplified for now
        setupNewGame(1); // Default difficulty, will be overridden by parsed data
        
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
    QString savesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/saves/";
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
    out << "Attack: " << m_hero->GetAttack() << "\n";
    out << "Defense: " << m_hero->GetDefense() << "\n";
    out << "Intelligence: " << m_hero->GetIntelligence() << "\n";
    out << "Strength: " << m_hero->GetStrength() << "\n";
    out << "Gold: " << m_hero->GetGold() << "\n";
    out << "Level: " << m_hero->GetLevel() << "\n";
    out << "Difficulty: " << m_difficulty->GetDifficultyLevel() << "\n";
    
    // Save inventory
    out << "\n--- INVENTORY ---\n";
    for (int i = 0; i < m_inventory->GetCount(); ++i) {
        Object* obj = m_inventory->GetItem(i);
        if (obj) {
            out << obj->GetName().c_str() << " (x" << obj->GetCount() << ")\n";
        }
    }
    
    // Save quests
    out << "\n--- QUESTS ---\n";
    if (m_quest && m_quest->GetCountQuest() > 0) {
        for (int i = 0; i < m_quest->GetCountQuest(); ++i) {
            Quest* q = m_quest->GetItemQuest(i);
            if (q) {
                out << q->GetQuestName().c_str() << " | Difficulty: " << q->GetDifficulty() 
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
            // Random event
            int eventType = rand() % 41;
            m_gameEvent->eventHistory.push_back(eventType);
            if (m_gameEvent->eventHistory.size() > 3) {
                m_gameEvent->eventHistory.erase(m_gameEvent->eventHistory.begin());
            }
            
            // Process event - simplified, just show text
            out << "You take a turn... Event type: " << eventType << "\n";
            m_hero->SetLevel(m_hero->GetLevel() + 0.01);
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
    }
    
    emit turnProcessed(result);
    emit heroStatusUpdated(formatHeroStatus());
}

void GameController::processCombatAction(int action)
{
    if (!m_hero || !m_enemy) return;
    
    QString result;
    QTextStream out(&result);
    
    switch (action) {
        case 0: { // Attack
            int damage = m_hero->GetTotalAttack() - m_enemy->GetTotalDefense();
            if (damage < 1) damage = 1;
            m_enemy->SetHealth(m_enemy->GetHealth() - damage);
            out << "You attack for " << damage << " damage!\n";
            
            if (m_enemy->GetHealth() <= 0) {
                out << "Enemy defeated!\n";
                m_hero->SetGold(m_hero->GetGold() + m_enemy->GetGoldReward());
                m_hero->SetLevel(m_hero->GetLevel() + 0.1);
                m_enemy->RandomizeEnemy(*m_difficulty);
                m_inCombat = false;
            } else {
                // Enemy counterattack
                int enemyDmg = m_enemy->GetTotalAttack() - m_hero->GetTotalDefense();
                if (enemyDmg < 1) enemyDmg = 1;
                m_hero->SetHealth(m_hero->GetHealth() - enemyDmg);
                out << "Enemy counterattacks for " << enemyDmg << " damage!\n";
                
                if (m_hero->GetHealth() <= 0) {
                    emit gameOver("You have been defeated!");
                    return;
                }
            }
            break;
        }
        case 1: { // Talk
            out << "You try to talk to the enemy...\n";
            if (m_enemy->GetAttitude() < 0) {
                out << "The enemy is hostile!\n";
                int enemyDmg = m_enemy->GetTotalAttack() - m_hero->GetTotalDefense();
                if (enemyDmg < 1) enemyDmg = 1;
                m_hero->SetHealth(m_hero->GetHealth() - enemyDmg);
            } else {
                out << "The enemy calms down.\n";
                m_hero->SetLevel(m_hero->GetLevel() + 0.02);
                m_inCombat = false;
            }
            break;
        }
        case 2: { // Trade
            out << "You offer to trade...\n";
            if (m_enemy->GetAttitude() < 0) {
                out << "The enemy refuses to trade!\n";
            } else {
                out << "Trade successful! You gain some gold.\n";
                m_hero->SetGold(m_hero->GetGold() + 10);
                m_inCombat = false;
            }
            break;
        }
        case 3: { // Flee
            out << "You flee from combat!\n";
            m_hero->SetLevel(m_hero->GetLevel() + 0.01);
            m_inCombat = false;
            break;
        }
    }
    
    emit combatProcessed(result);
    emit heroStatusUpdated(formatHeroStatus());
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
    return {"Make Turn", "Inventory", "Active Quest", "Main Menu"};
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
    QString savesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/saves/";
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
    out << "Attack: " << m_hero->GetTotalAttack() << " (Base: " << m_hero->GetAttack() << ")\n";
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
        Object* obj = m_inventory->GetItem(i);
        if (obj) {
            out << "[" << i << "] " << obj->GetName().c_str() 
                << " x" << obj->GetCount()
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
                out << "    Difficulty: " << q->GetDifficulty() << "\n";
                out << "    Reward: " << q->GetReward() << " gold\n";
                out << "    Status: " << (q->IsCompleted() ? "COMPLETED" : "IN PROGRESS") << "\n\n";
            }
        }
    }
    return qtext;
}
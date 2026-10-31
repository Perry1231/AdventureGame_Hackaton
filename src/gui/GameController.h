#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>

// Forward declarations for existing game classes
class Character;
class MyInventory;
class Quest;
class Enemy;
class GameHard;
class GameEvent;

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = nullptr);
    ~GameController();

    // Game initialization
    bool initializeNewGame(int difficultyLevel);
    bool loadGame(const QString &saveName);
    void saveGame(const QString &saveName);

    // Game state access
    Character* getHero() const;
    MyInventory* getInventory() const;
    Quest* getActiveQuests() const;
    Enemy* getCurrentEnemy() const;
    GameHard* getDifficulty() const;
    GameEvent* getGameEvent() const;

    // Game actions
    void processTurn(int action); // 0=make turn, 1=inventory, 2=active quest, 3=main menu
    void processCombatAction(int action); // 0=attack, 1=talk, 2=trade, 3=flee
    void processEventChoice(int choice);
    void processTavernAction(int action);
    void processLocationAction(const QString &location, int action);

    // Getters for UI
    QString getHeroStatus() const;
    QString getInventoryText() const;
    QString getQuestText() const;
    QString getCurrentEventText() const;
    QStringList getAvailableActions() const;
    QStringList getCombatActions() const;
    QStringList getTavernActions() const;
    QStringList getLocationActions(const QString &location) const;

    // Save/Load
    QStringList getSaveFiles() const;
    bool hasSaveFiles() const;

signals:
    void gameInitialized(bool success);
    void gameLoaded(bool success);
    void gameSaved(bool success);
    void turnProcessed(const QString &resultText);
    void combatProcessed(const QString &resultText);
    void eventTriggered(const QString &eventText, const QStringList &choices);
    void tavernOpened(const QStringList &actions);
    void locationEntered(const QString &locationName, const QStringList &actions);
    void inventoryUpdated(const QString &inventoryText);
    void questUpdated(const QString &questText);
    void heroStatusUpdated(const QString &statusText);
    void gameOver(const QString &reason);
    void returnedToMainMenu();
    void combatStarted(const QString &enemyName, int enemyHp, int enemyMaxHp, int enemyAttack, int enemyDefense);
    void combatUpdated(int enemyHp, int enemyMaxHp, int heroHp, int heroMaxHp);
    void combatEnded(const QString &message);

private:
    // Existing game objects
    Character *m_hero = nullptr;
    MyInventory *m_inventory = nullptr;
    Quest *m_quest = nullptr;
    Enemy *m_enemy = nullptr;
    GameHard *m_difficulty = nullptr;
    GameEvent *m_gameEvent = nullptr;

    // Game state
    bool m_inCombat = false;
    bool m_inTavern = false;
    int m_enemyMaxHealth = 0;
    int m_heroMaxHealth = 100;
    QString m_currentLocation;
    QString m_lastEventText;
    QStringList m_lastChoices;

    // Helper methods
    void cleanupGameObjects();
    void setupNewGame(int difficultyLevel);
    QString formatHeroStatus() const;
    QString formatInventory() const;
    QString formatQuests() const;
};

#endif // GAMECONTROLLER_H
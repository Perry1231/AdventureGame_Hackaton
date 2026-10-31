#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QSplitter>
#include <QScrollArea>
#include <functional>
#include <QColor>
#include <QProgressBar>

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    
    void setGameController(class GameController *controller);
    void updateHeroStatus(const QString &status);
    void updateInventory(const QString &inventory);
    void updateQuests(const QString &quests);
    void appendGameLog(const QString &text);
    void setAvailableActions(const QStringList &actions);
    void setCombatActions(const QStringList &actions);
    void setTavernActions(const QStringList &actions);
    void setLocationActions(const QStringList &actions);
    void showCombatMode(bool show);
    void showTavernMode(bool show);
    void showLocationMode(bool show, const QString &locationName);
    void enableMainActions(bool enable);
    void setNpcPortrait(const QString &title, const QColor &color);
    void showCombatInterface(const QString &enemyName, int enemyHp, int enemyMaxHp,
                             int enemyAttack, int enemyDefense);
    void updateCombatStatus(int enemyHp, int enemyMaxHp, int heroHp, int heroMaxHp);
    void hideCombatInterface();

signals:
    void actionSelected(int actionIndex);
    void combatActionSelected(int actionIndex);
    void tavernActionSelected(int actionIndex);
    void locationActionSelected(int actionIndex);
    void returnToMainMenuRequested();
    void saveGameRequested();
    void loadGameRequested();

private slots:
    void onMainActionClicked(int index);
    void onCombatActionClicked(int index);
    void onTavernActionClicked(int index);
    void onLocationActionClicked(int index);
    void onMenuButtonClicked();
    void onSaveButtonClicked();
    void onLoadButtonClicked();

private:
    void setupUI();
    void applyWhiteTheme();
    void updateActionButtons(const QStringList &actions, QWidget *container, std::function<void(int)> callback);
    
    GameController *m_controller = nullptr;
    
    // Main layout
    QWidget *m_centralWidget = nullptr;
    QHBoxLayout *m_mainLayout = nullptr;
    
    // Left panel - Game Log
    QWidget *m_leftPanel = nullptr;
    QVBoxLayout *m_leftLayout = nullptr;
    QLabel *m_logLabel = nullptr;
    QTextEdit *m_gameLog = nullptr;
    
    // Right panel - Status & Actions
    QWidget *m_rightPanel = nullptr;
    QVBoxLayout *m_rightLayout = nullptr;
    
    // NPC Portrait
    QWidget *m_portraitWidget = nullptr;
    QLabel *m_portraitImage = nullptr;
    QLabel *m_portraitName = nullptr;

    // Battle interface
    QWidget *m_battlePanel = nullptr;
    QLabel *m_battleEnemyName = nullptr;
    QLabel *m_battleEnemyStats = nullptr;
    QProgressBar *m_enemyHpBar = nullptr;
    QProgressBar *m_heroHpBar = nullptr;
    QLabel *m_enemyHpText = nullptr;
    QLabel *m_heroHpText = nullptr;
    QLabel *m_battleHint = nullptr;

    // Hero Status
    QWidget *m_statusWidget = nullptr;
    QVBoxLayout *m_statusLayout = nullptr;
    QLabel *m_statusLabel = nullptr;
    QTextEdit *m_statusText = nullptr;
    
    // Inventory
    QWidget *m_inventoryWidget = nullptr;
    QVBoxLayout *m_inventoryLayout = nullptr;
    QLabel *m_inventoryLabel = nullptr;
    QTextEdit *m_inventoryText = nullptr;
    
    // Quests
    QWidget *m_questWidget = nullptr;
    QVBoxLayout *m_questLayout = nullptr;
    QLabel *m_questLabel = nullptr;
    QTextEdit *m_questText = nullptr;
    
    // Action Buttons
    QWidget *m_actionWidget = nullptr;
    QVBoxLayout *m_actionLayout = nullptr;
    QLabel *m_actionLabel = nullptr;
    QWidget *m_mainActionContainer = nullptr;
    QVBoxLayout *m_mainActionLayout = nullptr;
    QWidget *m_combatActionContainer = nullptr;
    QVBoxLayout *m_combatActionLayout = nullptr;
    QWidget *m_tavernActionContainer = nullptr;
    QVBoxLayout *m_tavernActionLayout = nullptr;
    QWidget *m_locationActionContainer = nullptr;
    QVBoxLayout *m_locationActionLayout = nullptr;
    
    // Menu buttons
    QWidget *m_menuWidget = nullptr;
    QHBoxLayout *m_menuLayout = nullptr;
    QPushButton *m_menuButton = nullptr;
    QPushButton *m_saveButton = nullptr;
    QPushButton *m_loadButton = nullptr;
    
    bool m_inCombatMode = false;
    bool m_inTavernMode = false;
    QString m_lastInventory;
    QString m_lastQuests;
    bool m_inLocationMode = false;
};

#endif // GAMEWINDOW_H
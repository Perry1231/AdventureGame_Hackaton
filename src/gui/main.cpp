#include <QApplication>
#include <QMessageBox>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStandardPaths>
#include <QKeyEvent>
#include <QWidget>
#include "MainWindow.h"
#include "DifficultyWindow.h"
#include "GameWindow.h"
#include "SaveLoadWindow.h"
#include "InfoDialog.h"
#include "GameController.h"
#include "Header.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("AdventureGameDormEdition");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("DormAdventure");

    // Headless self-test: verifies core game flow without showing windows
    for (int i = 1; i < argc; ++i) {
        if (QString(argv[i]) == "--selftest") {
            GameController testController;
            QString report;
            QTextStream rep(&report);
            bool ok = testController.initializeNewGame(2);
            rep << "init: " << (ok ? "OK" : "FAIL") << "\n";
            for (int t = 0; t < 5; ++t) {
                testController.processTurn(0);
            }
            testController.processTurn(4); // start combat
            for (int c = 0; c < 6; ++c) {
                testController.processCombatAction(0); // attack
            }
            rep << "combat: OK\n";
            rep << testController.getHeroStatus() << "\n";
            rep << testController.getInventoryText() << "\n";
            rep << testController.getQuestText() << "\n";
            testController.saveGame("selftest.sav");
            rep << "hasSaves after save: " << (testController.hasSaveFiles() ? "YES" : "NO") << "\n";
            testController.loadGame("selftest.sav");
            rep << "after load:\n" << testController.getHeroStatus() << "\n";

            QFile reportFile(QDir::tempPath() + "/dorm_selftest.txt");
            if (reportFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream fileOut(&reportFile);
                fileOut << report;
                reportFile.close();
            }

            // Remove the test save so it doesn't appear in the real menu
            QFile::remove(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                          + "/DormAdventureSaves/selftest.sav");

            return ok ? 0 : 1;
        }
    }
    
    // Set global font
    QFont globalFont("Arial", 10);
    app.setFont(globalFont);
    
    // Create main objects
    MainWindow mainWindow;
    GameController gameController;
    GameWindow gameWindow;
    gameWindow.setGameController(&gameController);
    
    // State management
    enum AppState { MainMenu, DifficultySelect, InGame, SaveLoad };
    AppState currentState = MainMenu;

    // Easter egg state (Konami code on the main menu)
    bool dormSpiritBlessing = false;
    QObject::connect(&mainWindow, &MainWindow::easterEggUnlocked, [&]() {
        dormSpiritBlessing = true;
    });
    
    // Show main window initially
    mainWindow.setContinueMode(gameController.hasSaveFiles());
    mainWindow.showFullScreen();
    
    // ===== CONNECTIONS =====
    
    // Main Menu -> Difficulty Select
    QObject::connect(&mainWindow, &MainWindow::startNewGameRequested, [&]() {
        mainWindow.hide();
        DifficultyWindow diffWindow;
        if (diffWindow.exec() == QDialog::Accepted) {
            int difficulty = diffWindow.getSelectedDifficulty();
            if (gameController.initializeNewGame(difficulty)) {
                gameWindow.updateHeroStatus(gameController.getHeroStatus());
                gameWindow.updateInventory(gameController.getInventoryText());
                gameWindow.updateQuests(gameController.getQuestText());
                gameWindow.setAvailableActions(gameController.getAvailableActions());
                gameWindow.appendGameLog("=== NEW GAME STARTED ===");
                gameWindow.appendGameLog(QString("Difficulty: %1").arg(difficulty));
                if (dormSpiritBlessing && gameController.getHero()) {
                    gameController.getHero()->SetGold(gameController.getHero()->GetGold() + 100);
                    gameController.getHero()->SetStrength(gameController.getHero()->GetStrength() + 2);
                    gameWindow.appendGameLog("🍀 <b>The Legendary Dorm Spirit grants you +100 gold and +2 luck!</b>");
                    dormSpiritBlessing = false;
                    gameWindow.updateHeroStatus(gameController.getHeroStatus());
                }
                gameWindow.appendGameLog("Welcome to the Dorm Adventure!");
                gameWindow.appendGameLog("Use the action buttons on the right to play.");
                gameWindow.showFullScreen();
                currentState = InGame;
            } else {
                QMessageBox::critical(nullptr, "Error", "Failed to initialize game!");
                mainWindow.showFullScreen();
            }
        } else {
            mainWindow.showFullScreen();
        }
    });
    
    // Main Menu -> Load Game
    QObject::connect(&mainWindow, &MainWindow::loadGameRequested, [&]() {
        QStringList saves = gameController.getSaveFiles();
        if (saves.isEmpty()) {
            QMessageBox::information(&mainWindow, "No Saves",
                "There are no saved games yet.\nStart a new game and save your progress first.");
            return;
        }
        mainWindow.hide();
        SaveLoadWindow loadWindow(SaveLoadWindow::LoadMode, saves);
        if (loadWindow.exec() == QDialog::Accepted) {
            QString saveName = loadWindow.getSelectedSave();
            if (gameController.loadGame(saveName)) {
                gameWindow.updateHeroStatus(gameController.getHeroStatus());
                gameWindow.updateInventory(gameController.getInventoryText());
                gameWindow.updateQuests(gameController.getQuestText());
                gameWindow.setAvailableActions(gameController.getAvailableActions());
                gameWindow.appendGameLog("=== GAME LOADED ===");
                gameWindow.appendGameLog(QString("Loaded: %1").arg(saveName));
                gameWindow.showFullScreen();
                currentState = InGame;
            } else {
                QMessageBox::critical(nullptr, "Error", "Failed to load game!");
                mainWindow.showFullScreen();
            }
        } else {
            mainWindow.showFullScreen();
        }
    });
    
    // Main Menu -> Settings (placeholder)
    QObject::connect(&mainWindow, &MainWindow::settingsRequested, [&]() {
        QMessageBox::information(&mainWindow, "Settings", "Settings panel coming soon!\n\nCurrent features:\n- White theme (default)\n- Full Qt6 native UI\n- Save/Load system\n- Dorm-themed adventure");
    });
    
    // Main Menu -> Exit
    QObject::connect(&mainWindow, &MainWindow::exitRequested, [&]() {
        QApplication::quit();
    });
    
    // Game Window -> Main Menu
    QObject::connect(&gameWindow, &GameWindow::returnToMainMenuRequested, [&]() {
        gameController.saveGame("autosave.sav");
        gameWindow.hide();
        mainWindow.setContinueMode(gameController.hasSaveFiles());
        mainWindow.showFullScreen();
        currentState = MainMenu;
    });
    
    // Game Window -> Save Game
    QObject::connect(&gameWindow, &GameWindow::saveGameRequested, [&]() {
        QStringList saves = gameController.getSaveFiles();
        SaveLoadWindow saveWindow(SaveLoadWindow::SaveMode, saves);
        if (saveWindow.exec() == QDialog::Accepted) {
            QString saveName = saveWindow.getSelectedSave();
            gameController.saveGame(saveName);
            gameWindow.appendGameLog(QString("Game saved as: %1").arg(saveName));
            mainWindow.setContinueMode(gameController.hasSaveFiles());
        }
    });
    
    // Game Window -> Load Game
    QObject::connect(&gameWindow, &GameWindow::loadGameRequested, [&]() {
        QStringList saves = gameController.getSaveFiles();
        if (saves.isEmpty()) {
            QMessageBox::information(&gameWindow, "Load Game", "No save files found!");
            return;
        }
        
        SaveLoadWindow loadWindow(SaveLoadWindow::LoadMode, saves);
        if (loadWindow.exec() == QDialog::Accepted) {
            QString saveName = loadWindow.getSelectedSave();
            if (gameController.loadGame(saveName)) {
                gameWindow.updateHeroStatus(gameController.getHeroStatus());
                gameWindow.updateInventory(gameController.getInventoryText());
                gameWindow.updateQuests(gameController.getQuestText());
                gameWindow.appendGameLog(QString("Game loaded: %1").arg(saveName));
            } else {
                QMessageBox::critical(&gameWindow, "Error", "Failed to load game!");
            }
        }
    });
    
    // Game Controller -> Game Window updates
    QObject::connect(&gameController, &GameController::heroStatusUpdated, &gameWindow, &GameWindow::updateHeroStatus);
    QObject::connect(&gameController, &GameController::inventoryUpdated, &gameWindow, &GameWindow::updateInventory);
    QObject::connect(&gameController, &GameController::questUpdated, &gameWindow, &GameWindow::updateQuests);
    QObject::connect(&gameController, &GameController::turnProcessed, &gameWindow, &GameWindow::appendGameLog);
    QObject::connect(&gameController, &GameController::combatProcessed, &gameWindow, &GameWindow::appendGameLog);
    QObject::connect(&gameController, &GameController::combatStarted,
                     [&](const QString &name, int hp, int maxHp, int atk, int def) {
        gameWindow.appendGameLog(QString("<b style='color:#c0392b;'>⚔️ A %1 blocks your way! (HP %2, ATK %3, DEF %4)</b>")
                                 .arg(name).arg(maxHp).arg(atk).arg(def));
        gameWindow.setCombatActions(gameController.getCombatActions());
        gameWindow.showCombatMode(true);
        gameWindow.showCombatInterface(name, hp, maxHp, atk, def);
        gameWindow.updateCombatStatus(hp, maxHp, gameController.getHero()->GetHealth(), gameController.getHero()->GetHealth());
    });
    QObject::connect(&gameController, &GameController::combatUpdated,
                     &gameWindow, &GameWindow::updateCombatStatus);
    QObject::connect(&gameController, &GameController::combatEnded,
                     [&](const QString &message) {
        gameWindow.appendGameLog(QString("<b style='color:#27ae60;'>✔ %1</b>").arg(message));
        gameWindow.showCombatMode(false);
        gameWindow.hideCombatInterface();
        gameWindow.setAvailableActions(gameController.getAvailableActions());
        gameWindow.updateHeroStatus(gameController.getHeroStatus());
    });

    // Hidden self-test for the Konami easter egg (no user focus required)
    for (int i = 1; i < argc; ++i) {
        if (QString(argv[i]) == "--eastertest") {
            static bool unlocked = false;
            QObject::connect(&mainWindow, &MainWindow::easterEggUnlocked, [&]() { unlocked = true; });
            QTimer::singleShot(300, [&]() {
                const int keys[] = { Qt::Key_Up, Qt::Key_Up, Qt::Key_Down, Qt::Key_Down,
                                     Qt::Key_Left, Qt::Key_Right, Qt::Key_Left, Qt::Key_Right,
                                     Qt::Key_B, Qt::Key_A };
                for (int k : keys) {
                    QKeyEvent press(QEvent::KeyPress, k, Qt::NoModifier);
                    QApplication::sendEvent(&mainWindow, &press);
                }
            });
            QTimer::singleShot(600, [&]() {
                if (QWidget *modal = QApplication::activeModalWidget()) modal->close();
            });
            QTimer::singleShot(1000, [&]() {
                QFile report(QDir::tempPath() + "/dorm_eastertest.txt");
                if (report.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream stream(&report);
                    stream << (unlocked ? "UNLOCKED" : "FAILED") << "\n";
                }
                QApplication::quit();
            });
        }
    }
    QObject::connect(&gameController, &GameController::eventTriggered, [&](const QString &text, const QStringList &choices) {
        gameWindow.appendGameLog(text);
        for (const QString &choice : choices) {
            gameWindow.appendGameLog("  > " + choice);
        }
    });
    QObject::connect(&gameController, &GameController::gameOver, [&](const QString &reason) {
        gameWindow.appendGameLog("=== GAME OVER ===");
        gameWindow.appendGameLog(reason);
        gameWindow.enableMainActions(false);
        QTimer::singleShot(3000, [&]() {
            gameWindow.hide();
            mainWindow.showFullScreen();
            currentState = MainMenu;
        });
    });
    QObject::connect(&gameController, &GameController::returnedToMainMenu, [&]() {
        gameWindow.hide();
        mainWindow.showFullScreen();
        currentState = MainMenu;
    });
    
    // Game Window Actions -> Game Controller
    QObject::connect(&gameWindow, &GameWindow::actionSelected, [&](int action) {
        if (action == 1) {
            InfoDialog dialog("🎒 INVENTORY", gameController.getInventoryText(), &gameWindow);
            dialog.exec();
            return;
        }
        if (action == 2) {
            InfoDialog dialog("📋 ACTIVE QUESTS", gameController.getQuestText(), &gameWindow);
            dialog.exec();
            return;
        }
        gameController.processTurn(action);
    });
    
    QObject::connect(&gameWindow, &GameWindow::combatActionSelected, [&](int action) {
        gameController.processCombatAction(action);
    });
    
    QObject::connect(&gameWindow, &GameWindow::tavernActionSelected, [&](int action) {
        gameController.processTavernAction(action);
    });
    
    QObject::connect(&gameWindow, &GameWindow::locationActionSelected, [&](int action) {
        // For now, use a default location
        gameController.processLocationAction("Dorm Room", action);
    });
    
    // Initial welcome message
    gameWindow.appendGameLog("Welcome to Adventure Game: Dorm Edition!");
    
    return app.exec();
}
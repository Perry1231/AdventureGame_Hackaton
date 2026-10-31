#include <QApplication>
#include <QMessageBox>
#include <QTimer>
#include "MainWindow.h"
#include "DifficultyWindow.h"
#include "GameWindow.h"
#include "SaveLoadWindow.h"
#include "GameController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Adventure Game: Dorm Edition");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("DormAdventure");
    
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
    
    // Show main window initially
    mainWindow.show();
    
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
                gameWindow.appendGameLog("Welcome to the Dorm Adventure!");
                gameWindow.appendGameLog("Use the action buttons on the right to play.");
                gameWindow.show();
                currentState = InGame;
            } else {
                QMessageBox::critical(nullptr, "Error", "Failed to initialize game!");
                mainWindow.show();
            }
        } else {
            mainWindow.show();
        }
    });
    
    // Main Menu -> Load Game
    QObject::connect(&mainWindow, &MainWindow::loadGameRequested, [&]() {
        mainWindow.hide();
        QStringList saves = gameController.getSaveFiles();
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
                gameWindow.show();
                currentState = InGame;
            } else {
                QMessageBox::critical(nullptr, "Error", "Failed to load game!");
                mainWindow.show();
            }
        } else {
            mainWindow.show();
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
        mainWindow.show();
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
            mainWindow.show();
            currentState = MainMenu;
        });
    });
    QObject::connect(&gameController, &GameController::returnedToMainMenu, [&]() {
        gameWindow.hide();
        mainWindow.show();
        currentState = MainMenu;
    });
    
    // Game Window Actions -> Game Controller
    QObject::connect(&gameWindow, &GameWindow::actionSelected, [&](int action) {
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
    QTimer::singleShot(500, [&]() {
        mainWindow.appendGameLog("Welcome to Adventure Game: Dorm Edition!");
    });
    
    return app.exec();
}
#include "GameWindow.h"
#include "GameController.h"
#include <QFont>
#include <QScrollBar>
#include <QApplication>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include <functional>
#include <QPainter>
#include <QPixmap>
#include <QLinearGradient>
#include <QShortcut>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Adventure Game: Dorm Edition - In Progress");
    resize(1200, 800);
    setupUI();
    applyWhiteTheme();
    
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        move(screen->availableGeometry().center() - rect().center());
    }

    // F11 toggles fullscreen, Esc leaves fullscreen
    new QShortcut(QKeySequence(Qt::Key_F11), this, [this]() {
        isFullScreen() ? showNormal() : showFullScreen();
    });
    new QShortcut(QKeySequence(Qt::Key_Escape), this, [this]() {
        if (isFullScreen()) showNormal();
    });
}

GameWindow::~GameWindow()
{
}

void GameWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    m_mainLayout = new QHBoxLayout(m_centralWidget);
    m_mainLayout->setSpacing(10);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    
    // ===== LEFT PANEL - GAME LOG =====
    m_leftPanel = new QWidget(this);
    m_leftLayout = new QVBoxLayout(m_leftPanel);
    m_leftLayout->setContentsMargins(5, 5, 5, 5);
    
    m_logLabel = new QLabel("📜 GAME LOG", m_leftPanel);
    m_logLabel->setFont(QFont("Arial", 14, QFont::Bold));
    m_logLabel->setStyleSheet("color: #2c3e50; padding: 5px; border-bottom: 2px solid #3498db;");
    m_leftLayout->addWidget(m_logLabel);
    
    m_gameLog = new QTextEdit(m_leftPanel);
    m_gameLog->setReadOnly(true);
    m_gameLog->setFont(QFont("Consolas", 11));
    m_gameLog->setStyleSheet(
        "QTextEdit {"
        "   background-color: #f8f9fa;"
        "   border: 1px solid #dee2e6;"
        "   border-radius: 5px;"
        "   padding: 10px;"
        "   color: #2c3e50;"
        "}"
    );
    m_leftLayout->addWidget(m_gameLog);
    
    m_mainLayout->addWidget(m_leftPanel, 3);
    
    // ===== RIGHT PANEL - STATUS & ACTIONS =====
    m_rightPanel = new QWidget(this);
    m_rightPanel->setFixedWidth(400);
    m_rightLayout = new QVBoxLayout(m_rightPanel);
    m_rightLayout->setSpacing(10);
    m_rightLayout->setContentsMargins(5, 5, 5, 5);
    
    // --- NPC / Location Portrait ---
    m_portraitWidget = new QWidget(m_rightPanel);
    m_portraitWidget->setStyleSheet(
        "QWidget {"
        "   background-color: #f8f9fa;"
        "   border: 1px solid #dee2e6;"
        "   border-radius: 8px;"
        "}"
    );
    QVBoxLayout *portraitLayout = new QVBoxLayout(m_portraitWidget);
    portraitLayout->setContentsMargins(5, 5, 5, 5);
    portraitLayout->setSpacing(4);

    m_portraitImage = new QLabel(m_portraitWidget);
    m_portraitImage->setAlignment(Qt::AlignCenter);
    m_portraitImage->setFixedHeight(110);

    m_portraitName = new QLabel("HERO", m_portraitWidget);
    m_portraitName->setAlignment(Qt::AlignCenter);
    m_portraitName->setFont(QFont("Arial", 10, QFont::Bold));
    m_portraitName->setStyleSheet("color: #2c3e50; background: transparent; border: none;");

    portraitLayout->addWidget(m_portraitImage);
    portraitLayout->addWidget(m_portraitName);
    m_rightLayout->addWidget(m_portraitWidget);

    setNpcPortrait("HERO", QColor("#27ae60"));

    // --- Battle Interface ---
    m_battlePanel = new QWidget(m_rightPanel);
    m_battlePanel->setStyleSheet(
        "QWidget {"
        "   background-color: #fff5f5;"
        "   border: 2px solid #c0392b;"
        "   border-radius: 8px;"
        "}"
    );
    QVBoxLayout *battleLayout = new QVBoxLayout(m_battlePanel);
    battleLayout->setContentsMargins(8, 8, 8, 8);
    battleLayout->setSpacing(5);

    QLabel *battleTitle = new QLabel("⚔️ BATTLE", m_battlePanel);
    battleTitle->setFont(QFont("Arial", 12, QFont::Bold));
    battleTitle->setStyleSheet("color: #c0392b; background: transparent; border: none;");
    battleLayout->addWidget(battleTitle);

    m_battleEnemyName = new QLabel("Enemy", m_battlePanel);
    m_battleEnemyName->setFont(QFont("Arial", 11, QFont::Bold));
    m_battleEnemyName->setStyleSheet("color: #2c3e50; background: transparent; border: none;");
    battleLayout->addWidget(m_battleEnemyName);

    m_battleEnemyStats = new QLabel("ATK 0 / DEF 0", m_battlePanel);
    m_battleEnemyStats->setStyleSheet("color: #7f8c8d; background: transparent; border: none;");
    battleLayout->addWidget(m_battleEnemyStats);

    auto makeBar = [this](const QString &color) {
        QProgressBar *bar = new QProgressBar(m_battlePanel);
        bar->setRange(0, 100);
        bar->setValue(100);
        bar->setTextVisible(false);
        bar->setFixedHeight(16);
        bar->setStyleSheet(QString(
            "QProgressBar { background-color: #ecf0f1; border: 1px solid #bdc3c7; border-radius: 6px; }"
            "QProgressBar::chunk { background-color: %1; border-radius: 5px; }"
        ).arg(color));
        return bar;
    };

    QLabel *enemyHpLabel = new QLabel("Enemy HP", m_battlePanel);
    enemyHpLabel->setStyleSheet("color: #2c3e50; background: transparent; border: none;");
    battleLayout->addWidget(enemyHpLabel);
    m_enemyHpBar = makeBar("#e74c3c");
    battleLayout->addWidget(m_enemyHpBar);

    m_enemyHpText = new QLabel("0 / 0", m_battlePanel);
    m_enemyHpText->setAlignment(Qt::AlignRight);
    m_enemyHpText->setStyleSheet("color: #c0392b; background: transparent; border: none;");
    battleLayout->addWidget(m_enemyHpText);

    QLabel *heroHpLabel = new QLabel("Your HP", m_battlePanel);
    heroHpLabel->setStyleSheet("color: #2c3e50; background: transparent; border: none;");
    battleLayout->addWidget(heroHpLabel);
    m_heroHpBar = makeBar("#27ae60");
    battleLayout->addWidget(m_heroHpBar);

    m_heroHpText = new QLabel("0 / 0", m_battlePanel);
    m_heroHpText->setAlignment(Qt::AlignRight);
    m_heroHpText->setStyleSheet("color: #27ae60; background: transparent; border: none;");
    battleLayout->addWidget(m_heroHpText);

    m_battleHint = new QLabel("Choose an action below.", m_battlePanel);
    m_battleHint->setWordWrap(true);
    m_battleHint->setStyleSheet("color: #7f8c8d; background: transparent; border: none;");
    battleLayout->addWidget(m_battleHint);

    m_battlePanel->setVisible(false);
    m_rightLayout->addWidget(m_battlePanel);

    // --- Hero Status ---
    m_statusWidget = new QWidget(m_rightPanel);
    m_statusWidget->setStyleSheet(
        "QWidget {"
        "   background-color: #f8f9fa;"
        "   border: 1px solid #dee2e6;"
        "   border-radius: 8px;"
        "}"
    );
    m_statusLayout = new QVBoxLayout(m_statusWidget);
    
    m_statusLabel = new QLabel("❤️ HERO STATUS", m_statusWidget);
    m_statusLabel->setFont(QFont("Arial", 12, QFont::Bold));
    m_statusLabel->setStyleSheet("color: #2c3e50; padding: 5px;");
    m_statusLayout->addWidget(m_statusLabel);
    
    m_statusText = new QTextEdit(m_statusWidget);
    m_statusText->setReadOnly(true);
    m_statusText->setMaximumHeight(180);
    m_statusText->setFont(QFont("Consolas", 10));
    m_statusText->setStyleSheet("background: transparent; border: none; color: #2c3e50;");
    m_statusLayout->addWidget(m_statusText);
    
    m_rightLayout->addWidget(m_statusWidget);
    
    // --- Action Buttons ---
    m_actionWidget = new QWidget(m_rightPanel);
    m_actionLayout = new QVBoxLayout(m_actionWidget);
    
    m_actionLabel = new QLabel("⚡ ACTIONS", m_actionWidget);
    m_actionLabel->setFont(QFont("Arial", 12, QFont::Bold));
    m_actionLabel->setStyleSheet("color: #2c3e50; padding: 5px;");
    m_actionLayout->addWidget(m_actionLabel);
    
    // Main Actions Container
    m_mainActionContainer = new QWidget(m_actionWidget);
    m_mainActionLayout = new QVBoxLayout(m_mainActionContainer);
    m_mainActionLayout->setSpacing(5);
    m_mainActionLayout->setContentsMargins(0, 0, 0, 0);
    m_actionLayout->addWidget(m_mainActionContainer);
    
    // Combat Actions Container (hidden by default)
    m_combatActionContainer = new QWidget(m_actionWidget);
    m_combatActionContainer->setVisible(false);
    m_combatActionLayout = new QVBoxLayout(m_combatActionContainer);
    m_combatActionLayout->setSpacing(5);
    m_combatActionLayout->setContentsMargins(0, 0, 0, 0);
    m_actionLayout->addWidget(m_combatActionContainer);
    
    // Tavern Actions Container (hidden by default)
    m_tavernActionContainer = new QWidget(m_actionWidget);
    m_tavernActionContainer->setVisible(false);
    m_tavernActionLayout = new QVBoxLayout(m_tavernActionContainer);
    m_tavernActionLayout->setSpacing(5);
    m_tavernActionLayout->setContentsMargins(0, 0, 0, 0);
    m_actionLayout->addWidget(m_tavernActionContainer);
    
    // Location Actions Container (hidden by default)
    m_locationActionContainer = new QWidget(m_actionWidget);
    m_locationActionContainer->setVisible(false);
    m_locationActionLayout = new QVBoxLayout(m_locationActionContainer);
    m_locationActionLayout->setSpacing(5);
    m_locationActionLayout->setContentsMargins(0, 0, 0, 0);
    m_actionLayout->addWidget(m_locationActionContainer);
    
    m_actionLayout->addStretch();
    m_rightLayout->addWidget(m_actionWidget);
    
    // --- Menu Buttons ---
    m_menuWidget = new QWidget(m_rightPanel);
    m_menuLayout = new QHBoxLayout(m_menuWidget);
    m_menuLayout->setSpacing(5);
    
    m_menuButton = new QPushButton("🏠 MENU", m_menuWidget);
    m_saveButton = new QPushButton("💾 SAVE", m_menuWidget);
    m_loadButton = new QPushButton("📂 LOAD", m_menuWidget);
    
    QString menuBtnStyle = 
        "QPushButton {"
        "   background-color: #ecf0f1;"
        "   color: #2c3e50;"
        "   border: 1px solid #bdc3c7;"
        "   border-radius: 5px;"
        "   padding: 8px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #bdc3c7; }"
        "QPushButton:pressed { background-color: #95a5a6; }";
    
    m_menuButton->setStyleSheet(menuBtnStyle);
    m_saveButton->setStyleSheet(menuBtnStyle);
    m_loadButton->setStyleSheet(menuBtnStyle);
    
    m_menuLayout->addWidget(m_menuButton);
    m_menuLayout->addWidget(m_saveButton);
    m_menuLayout->addWidget(m_loadButton);
    
    m_rightLayout->addWidget(m_menuWidget);
    
    connect(m_menuButton, &QPushButton::clicked, this, &GameWindow::onMenuButtonClicked);
    connect(m_saveButton, &QPushButton::clicked, this, &GameWindow::onSaveButtonClicked);
    connect(m_loadButton, &QPushButton::clicked, this, &GameWindow::onLoadButtonClicked);
    
    // Wrap the right panel in a scroll area so all widgets remain reachable
    QScrollArea *rightScroll = new QScrollArea(this);
    rightScroll->setWidget(m_rightPanel);
    rightScroll->setWidgetResizable(true);
    rightScroll->setFixedWidth(420);
    rightScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    rightScroll->setStyleSheet("QScrollArea { border: none; background-color: #ffffff; }");
    m_mainLayout->addWidget(rightScroll);

    setCentralWidget(m_centralWidget);
}

void GameWindow::applyWhiteTheme()
{
    setStyleSheet(
        "QMainWindow { background-color: #ffffff; }"
        "QWidget { background-color: #ffffff; color: #2c3e50; }"
        "QLabel { color: #2c3e50; }"
        "QTextEdit { color: #2c3e50; }"
        "QScrollBar:vertical { background: #f1f1f1; width: 10px; }"
        "QScrollBar::handle:vertical { background: #bdc3c7; border-radius: 5px; }"
        "QScrollBar::handle:vertical:hover { background: #95a5a6; }"
    );
}

void GameWindow::setGameController(GameController *controller)
{
    m_controller = controller;
}

void GameWindow::setNpcPortrait(const QString &title, const QColor &color)
{
    if (!m_portraitImage) return;

    const int size = 96;
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QColor light = color.lighter(160);
    QLinearGradient gradient(0, 0, size, size);
    gradient.setColorAt(0.0, light);
    gradient.setColorAt(1.0, color);
    painter.setBrush(gradient);
    painter.setPen(QPen(color.darker(120), 2));
    painter.drawEllipse(3, 3, size - 6, size - 6);

    // Simple face
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255, 220));
    painter.drawEllipse(size * 0.32, size * 0.26, 10, 10);
    painter.drawEllipse(size * 0.58, size * 0.26, 10, 10);
    painter.setBrush(QColor(255, 255, 255, 180));
    painter.drawRoundedRect(QRectF(size * 0.36, size * 0.52, size * 0.28, 8), 4, 4);

    painter.setPen(QColor(255, 255, 255));
    QFont f = painter.font();
    f.setPointSize(16);
    f.setBold(true);
    painter.setFont(f);
    painter.drawText(QRect(0, size - 30, size, 24), Qt::AlignCenter, title.left(1).toUpper());
    painter.end();

    m_portraitImage->setPixmap(pixmap);
    if (m_portraitName) m_portraitName->setText(title.toUpper());
}

void GameWindow::showCombatInterface(const QString &enemyName, int enemyHp, int enemyMaxHp,
                                     int enemyAttack, int enemyDefense)
{
    if (!m_battlePanel) return;

    m_battleEnemyName->setText("Enemy: " + enemyName);
    m_battleEnemyStats->setText(QString("ATK %1   •   DEF %2").arg(enemyAttack).arg(enemyDefense));

    int maxHp = qMax(1, enemyMaxHp);
    m_enemyHpBar->setRange(0, maxHp);
    m_enemyHpBar->setValue(qBound(0, enemyHp, maxHp));
    m_enemyHpText->setText(QString("%1 / %2").arg(enemyHp).arg(maxHp));

    m_battleHint->setText("Choose a combat action below!");
    m_battlePanel->setVisible(true);

    setNpcPortrait(enemyName, QColor("#c0392b"));
}

void GameWindow::updateCombatStatus(int enemyHp, int enemyMaxHp, int heroHp, int heroMaxHp)
{
    if (!m_battlePanel) return;

    int eMax = qMax(1, enemyMaxHp);
    int hMax = qMax(1, heroMaxHp);

    m_enemyHpBar->setRange(0, eMax);
    m_enemyHpBar->setValue(qBound(0, enemyHp, eMax));
    m_enemyHpText->setText(QString("%1 / %2").arg(qMax(0, enemyHp)).arg(eMax));

    m_heroHpBar->setRange(0, hMax);
    m_heroHpBar->setValue(qBound(0, heroHp, hMax));
    m_heroHpText->setText(QString("%1 / %2").arg(qMax(0, heroHp)).arg(hMax));
}

void GameWindow::hideCombatInterface()
{
    if (m_battlePanel) m_battlePanel->setVisible(false);
    setNpcPortrait("HERO", QColor("#27ae60"));
}

void GameWindow::updateHeroStatus(const QString &status)
{
    m_statusText->setPlainText(status);
}

void GameWindow::updateInventory(const QString &inventory)
{
    m_lastInventory = inventory;
}

void GameWindow::updateQuests(const QString &quests)
{
    m_lastQuests = quests;
}

void GameWindow::appendGameLog(const QString &text)
{
    m_gameLog->append(text);
    // Auto-scroll to bottom
    QScrollBar *scrollbar = m_gameLog->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void GameWindow::setAvailableActions(const QStringList &actions)
{
    updateActionButtons(actions, m_mainActionContainer, [this](int index) { onMainActionClicked(index); });
}

void GameWindow::setCombatActions(const QStringList &actions)
{
    updateActionButtons(actions, m_combatActionContainer, [this](int index) { onCombatActionClicked(index); });
}

void GameWindow::setTavernActions(const QStringList &actions)
{
    updateActionButtons(actions, m_tavernActionContainer, [this](int index) { onTavernActionClicked(index); });
}

void GameWindow::setLocationActions(const QStringList &actions)
{
    updateActionButtons(actions, m_locationActionContainer, [this](int index) { onLocationActionClicked(index); });
}

void GameWindow::updateActionButtons(const QStringList &actions, QWidget *container, std::function<void(int)> callback)
{
    QLayout *layout = container->layout();
    if (!layout) return;
    
    // Clear existing buttons
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }
    
    // Create new buttons
    for (int i = 0; i < actions.size(); ++i) {
        QPushButton *btn = new QPushButton(actions[i], container);
        btn->setFixedHeight(40);
        btn->setFont(QFont("Arial", 11, QFont::Bold));
        btn->setStyleSheet(
            "QPushButton {"
            "   background-color: #3498db;"
            "   color: white;"
            "   border: none;"
            "   border-radius: 5px;"
            "   padding: 8px;"
            "   text-align: left;"
            "}"
            "QPushButton:hover { background-color: #2980b9; }"
            "QPushButton:pressed { background-color: #1c6ea4; }"
        );
        int index = i; // Capture for lambda
        connect(btn, &QPushButton::clicked, [callback, index]() { callback(index); });
        layout->addWidget(btn);
    }
}

void GameWindow::showCombatMode(bool show)
{
    m_inCombatMode = show;
    m_mainActionContainer->setVisible(!show);
    m_combatActionContainer->setVisible(show);
    m_tavernActionContainer->setVisible(false);
    m_locationActionContainer->setVisible(false);
    m_actionLabel->setText(show ? "⚔️ COMBAT ACTIONS" : "⚡ ACTIONS");
    if (show) setNpcPortrait("ENEMY", QColor("#c0392b"));
}

void GameWindow::showTavernMode(bool show)
{
    m_inTavernMode = show;
    m_mainActionContainer->setVisible(!show);
    m_combatActionContainer->setVisible(false);
    m_tavernActionContainer->setVisible(show);
    m_locationActionContainer->setVisible(false);
    m_actionLabel->setText(show ? "🍻 TAVERN ACTIONS" : "⚡ ACTIONS");
    if (show) setNpcPortrait("COMMON ROOM", QColor("#8e44ad"));
}

void GameWindow::showLocationMode(bool show, const QString &locationName)
{
    m_inLocationMode = show;
    m_mainActionContainer->setVisible(!show);
    m_combatActionContainer->setVisible(false);
    m_tavernActionContainer->setVisible(false);
    m_locationActionContainer->setVisible(show);
    m_actionLabel->setText(show ? ("📍 " + locationName.toUpper() + " ACTIONS") : "⚡ ACTIONS");
    if (show) setNpcPortrait(locationName, QColor("#2980b9"));
}

void GameWindow::enableMainActions(bool enable)
{
    m_mainActionContainer->setEnabled(enable);
    m_combatActionContainer->setEnabled(enable);
    m_tavernActionContainer->setEnabled(enable);
    m_locationActionContainer->setEnabled(enable);
}

void GameWindow::onMainActionClicked(int index)
{
    emit actionSelected(index);
}

void GameWindow::onCombatActionClicked(int index)
{
    emit combatActionSelected(index);
}

void GameWindow::onTavernActionClicked(int index)
{
    emit tavernActionSelected(index);
}

void GameWindow::onLocationActionClicked(int index)
{
    emit locationActionSelected(index);
}

void GameWindow::onMenuButtonClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Return to Menu", 
        "Are you sure you want to return to the main menu?\nYour progress will be saved automatically.",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit returnToMainMenuRequested();
    }
}

void GameWindow::onSaveButtonClicked()
{
    emit saveGameRequested();
}

void GameWindow::onLoadButtonClicked()
{
    emit loadGameRequested();
}
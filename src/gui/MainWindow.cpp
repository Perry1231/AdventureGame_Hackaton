#include "MainWindow.h"
#include <QPixmap>
#include <QFont>
#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Adventure Game - Dorm Edition");
    setFixedSize(800, 600);
    setupUI();
    applyWhiteTheme();
    
    // Center on screen
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    m_layout = new QVBoxLayout(m_centralWidget);
    m_layout->setSpacing(20);
    m_layout->setContentsMargins(50, 50, 50, 50);
    
    // Title
    m_titleLabel = new QLabel("🏠 ADVENTURE GAME: DORM EDITION 🏠", this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = m_titleLabel->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);
    m_titleLabel->setStyleSheet("color: #2c3e50; margin-bottom: 10px;");
    m_layout->addWidget(m_titleLabel);
    
    // Image
    m_imageLabel = new QLabel(this);
    m_imageLabel->setAlignment(Qt::AlignCenter);
    QPixmap pixmap(":/images/Photo.png");
    if (!pixmap.isNull()) {
        m_imageLabel->setPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        m_imageLabel->setText("🏠\n[Image not found]");
        m_imageLabel->setStyleSheet("font-size: 48px; color: #95a5a6;");
    }
    m_layout->addWidget(m_imageLabel);
    
    // Buttons
    auto createButton = [this](const QString &text, const QString &color) {
        QPushButton *btn = new QPushButton(text, this);
        btn->setFixedHeight(50);
        btn->setFont(QFont("Arial", 14, QFont::Bold));
        btn->setStyleSheet(QString(
            "QPushButton {"
            "   background-color: %1;"
            "   color: white;"
            "   border: none;"
            "   border-radius: 8px;"
            "   padding: 10px;"
            "}"
            "QPushButton:hover {"
            "   background-color: %2;"
            "}"
            "QPushButton:pressed {"
            "   background-color: %3;"
            "}"
        ).arg(color).arg(color).arg(color));
        m_layout->addWidget(btn);
        return btn;
    };
    
    m_startButton = createButton("🎮 START NEW GAME", "#27ae60");
    m_loadButton = createButton("📂 LOAD GAME", "#3498db");
    m_settingsButton = createButton("⚙️ SETTINGS", "#f39c12");
    m_exitButton = createButton("🚪 EXIT", "#e74c3c");
    
    connect(m_startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(m_loadButton, &QPushButton::clicked, this, &MainWindow::onLoadClicked);
    connect(m_settingsButton, &QPushButton::clicked, this, &MainWindow::onSettingsClicked);
    connect(m_exitButton, &QPushButton::clicked, this, &MainWindow::onExitClicked);
    
    m_layout->addStretch();
    
    // Version label
    QLabel *versionLabel = new QLabel("v1.0.0 | Dorm Adventure", this);
    versionLabel->setAlignment(Qt::AlignCenter);
    versionLabel->setStyleSheet("color: #95a5a6; font-size: 10px;");
    m_layout->addWidget(versionLabel);
    
    setCentralWidget(m_centralWidget);
}

void MainWindow::applyWhiteTheme()
{
    setStyleSheet(
        "QMainWindow {"
        "   background-color: #ffffff;"
        "}"
        "QWidget {"
        "   background-color: #ffffff;"
        "   color: #2c3e50;"
        "}"
        "QLabel {"
        "   color: #2c3e50;"
        "}"
    );
}

void MainWindow::onStartClicked()
{
    emit startNewGameRequested();
}

void MainWindow::onLoadClicked()
{
    emit loadGameRequested();
}

void MainWindow::onSettingsClicked()
{
    emit settingsRequested();
}

void MainWindow::onExitClicked()
{
    emit exitRequested();
}
#include "MainWindow.h"
#include <QPixmap>
#include <QFont>
#include <QApplication>
#include <QScreen>
#include <QGuiApplication>
#include <QShortcut>
#include <QKeyEvent>
#include <QMessageBox>
#include <QList>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Adventure Game - Dorm Edition");
    resize(900, 700);
    setupUI();
    applyWhiteTheme();

    // Center on screen (used in windowed mode)
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

    // Catch the Konami code even when child widgets have focus
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    m_layout = new QVBoxLayout(m_centralWidget);
    m_layout->setSpacing(20);
    m_layout->setContentsMargins(50, 30, 50, 30);
    m_layout->addStretch(1);
    
    // Title
    m_titleLabel = new QLabel("🏠 ADVENTURE GAME: DORM EDITION 🏠", this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = m_titleLabel->font();
    titleFont.setPointSize(28);
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);
    m_titleLabel->setStyleSheet("color: #2c3e50; margin-bottom: 10px;");
    m_layout->addWidget(m_titleLabel);
    
    // Image
    m_imageLabel = new QLabel(this);
    m_imageLabel->setAlignment(Qt::AlignCenter);
    QPixmap pixmap(":/images/Photo.png");
    if (!pixmap.isNull()) {
        int side = 380;
        if (QScreen *screen = QGuiApplication::primaryScreen()) {
            side = qMin(380, static_cast<int>(screen->availableGeometry().height() * 0.35));
        }
        m_imageLabel->setPixmap(pixmap.scaled(side, side, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        m_imageLabel->setText("🏠\n[Image not found]");
        m_imageLabel->setStyleSheet("font-size: 48px; color: #95a5a6;");
    }
    m_layout->addWidget(m_imageLabel);
    
    // Buttons
    auto createButton = [this](const QString &text, const QString &color) {
        QPushButton *btn = new QPushButton(text, this);
        btn->setFixedHeight(52);
        btn->setMaximumWidth(460);
        btn->setMinimumWidth(320);
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
        m_layout->addWidget(btn, 0, Qt::AlignHCenter);
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
    
    m_layout->addStretch(2);
    
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    // Easter egg: Konami code (Up Up Down Down Left Right Left Right B A)
    if (event->type() == QEvent::KeyPress && isVisible()) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        static const QList<int> konami = {
            Qt::Key_Up, Qt::Key_Up, Qt::Key_Down, Qt::Key_Down,
            Qt::Key_Left, Qt::Key_Right, Qt::Key_Left, Qt::Key_Right,
            Qt::Key_B, Qt::Key_A
        };

        int key = keyEvent->key();
        if (key == konami[m_konamiProgress]) {
            ++m_konamiProgress;
            if (m_konamiProgress >= konami.size()) {
                m_konamiProgress = 0;
                if (!m_easterEggTriggered) {
                    m_easterEggTriggered = true;
                    m_titleLabel->setText("🍀 THE DORM SPIRIT BLESSES YOU 🍀");
                    m_titleLabel->setStyleSheet("color: #d4a017; margin-bottom: 10px;");
                    QMessageBox::information(this, "🥚 Easter Egg Found!",
                        "You discovered the Legendary Dorm Spirit!\n\n"
                        "\"May your noodles never overcook and your alarm always ring.\"\n\n"
                        "Reward: your next new game starts with +100 gold and +2 luck (strength).");
                    emit easterEggUnlocked();
                }
            }
        } else {
            m_konamiProgress = (key == konami[0]) ? 1 : 0;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::setContinueMode(bool hasSaves)
{
    if (hasSaves) {
        m_loadButton->setText("▶ CONTINUE GAME");
        m_loadButton->setEnabled(true);
    } else {
        m_loadButton->setText("📂 LOAD GAME (no saves)");
        m_loadButton->setEnabled(true);
    }
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
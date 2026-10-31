#include "DifficultyWindow.h"
#include <QFont>
#include <QApplication>

DifficultyWindow::DifficultyWindow(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Select Difficulty");
    setFixedSize(500, 450);
    setModal(true);
    setupUI();
    applyWhiteTheme();
    
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

DifficultyWindow::~DifficultyWindow()
{
}

void DifficultyWindow::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(15);
    layout->setContentsMargins(30, 30, 30, 30);
    
    QLabel *titleLabel = new QLabel("⚔️ CHOOSE YOUR DIFFICULTY ⚔️", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #2c3e50; margin-bottom: 10px;");
    layout->addWidget(titleLabel);
    
    m_difficultyGroup = new QButtonGroup(this);
    
    auto createDifficultyOption = [this, &layout](int id, const QString &name, const QString &desc, const QString &color) {
        QRadioButton *radio = new QRadioButton(name, this);
        radio->setFont(QFont("Arial", 12, QFont::Bold));
        radio->setStyleSheet(QString(
            "QRadioButton {"
            "   color: %1;"
            "   spacing: 10px;"
            "}"
            "QRadioButton::indicator {"
            "   width: 20px;"
            "   height: 20px;"
            "   border-radius: 10px;"
            "   border: 2px solid %1;"
            "}"
            "QRadioButton::indicator:checked {"
            "   background-color: %1;"
            "   border: 2px solid %1;"
            "}"
        ).arg(color));
        
        QLabel *descLabel = new QLabel(desc, this);
        descLabel->setWordWrap(true);
        descLabel->setStyleSheet("color: #7f8c8d; margin-left: 30px; margin-bottom: 15px;");
        descLabel->setFont(QFont("Arial", 10));
        
        m_difficultyGroup->addButton(radio, id);
        layout->addWidget(radio);
        layout->addWidget(descLabel);
        
        return radio;
    };
    
    m_easyRadio = createDifficultyOption(1, "😊 EASY", 
        "Enemies are weaker, more gold, faster leveling. Perfect for learning the ropes of dorm life!", "#27ae60");
    m_normalRadio = createDifficultyOption(2, "😐 NORMAL", 
        "Balanced experience. Enemies hit back, resources are fair. The standard dorm survival.", "#f39c12");
    m_hardRadio = createDifficultyOption(3, "😤 HARD", 
        "Tough enemies, scarce resources, permadeath risk. Only for seasoned dorm residents.", "#e67e22");
    m_nightmareRadio = createDifficultyOption(4, "💀 NIGHTMARE", 
        "Brutal difficulty. One mistake ends your run. The final exams week experience.", "#c0392b");
    
    m_normalRadio->setChecked(true);
    
    layout->addStretch();
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    
    m_confirmButton = new QPushButton("✅ CONFIRM & START", this);
    m_confirmButton->setFixedHeight(45);
    m_confirmButton->setFont(QFont("Arial", 12, QFont::Bold));
    m_confirmButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #27ae60;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 10px;"
        "}"
        "QPushButton:hover { background-color: #219a52; }"
        "QPushButton:pressed { background-color: #1e8a49; }"
    );
    
    m_cancelButton = new QPushButton("❌ BACK TO MENU", this);
    m_cancelButton->setFixedHeight(45);
    m_cancelButton->setFont(QFont("Arial", 12));
    m_cancelButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #95a5a6;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 10px;"
        "}"
        "QPushButton:hover { background-color: #7f8c8d; }"
    );
    
    buttonLayout->addWidget(m_confirmButton);
    buttonLayout->addWidget(m_cancelButton);
    layout->addLayout(buttonLayout);
    
    connect(m_confirmButton, &QPushButton::clicked, this, &DifficultyWindow::onConfirmClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &DifficultyWindow::onCancelClicked);
}

void DifficultyWindow::applyWhiteTheme()
{
    setStyleSheet(
        "QDialog { background-color: #ffffff; }"
        "QLabel { color: #2c3e50; }"
        "QRadioButton { color: #2c3e50; }"
    );
}

void DifficultyWindow::onConfirmClicked()
{
    m_selectedDifficulty = m_difficultyGroup->checkedId();
    if (m_selectedDifficulty <= 0) m_selectedDifficulty = 1;
    emit difficultySelected(m_selectedDifficulty);
    accept();
}

void DifficultyWindow::onCancelClicked()
{
    reject();
}

int DifficultyWindow::getSelectedDifficulty() const
{
    return m_selectedDifficulty;
}
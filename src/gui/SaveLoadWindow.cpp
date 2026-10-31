#include "SaveLoadWindow.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFont>
#include <QApplication>
#include <QScreen>
#include <QGuiApplication>

SaveLoadWindow::SaveLoadWindow(Mode mode, const QStringList &saveFiles, QWidget *parent) 
    : QDialog(parent), m_mode(mode), m_saveFiles(saveFiles)
{
    setWindowTitle(mode == SaveMode ? "Save Game" : "Load Game");
    setFixedSize(500, 450);
    setModal(true);
    setupUI();
    applyWhiteTheme();
    
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        move(screen->availableGeometry().center() - rect().center());
    }
}

SaveLoadWindow::~SaveLoadWindow()
{
}

void SaveLoadWindow::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(15);
    layout->setContentsMargins(20, 20, 20, 20);
    
    QString titleText = m_mode == SaveMode ? "💾 SAVE GAME" : "📂 LOAD GAME";
    QLabel *titleLabel = new QLabel(titleText, this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #2c3e50; margin-bottom: 10px;");
    layout->addWidget(titleLabel);
    
    if (m_mode == SaveMode) {
        QLabel *hintLabel = new QLabel("Enter a name for your save or select existing to overwrite:", this);
        hintLabel->setWordWrap(true);
        hintLabel->setStyleSheet("color: #7f8c8d; margin-bottom: 10px;");
        layout->addWidget(hintLabel);
        
        m_newSaveEdit = new QLineEdit(this);
        m_newSaveEdit->setPlaceholderText("Enter save name (e.g., my_adventure_1)");
        m_newSaveEdit->setFont(QFont("Arial", 11));
        m_newSaveEdit->setStyleSheet(
            "QLineEdit {"
            "   padding: 10px;"
            "   border: 2px solid #bdc3c7;"
            "   border-radius: 5px;"
            "   background-color: #ffffff;"
            "   color: #2c3e50;"
            "}"
            "QLineEdit:focus { border-color: #3498db; }"
        );
        layout->addWidget(m_newSaveEdit);
        
        connect(m_newSaveEdit, &QLineEdit::textChanged, this, &SaveLoadWindow::onNewSaveNameChanged);
    }
    
    QLabel *listLabel = new QLabel(m_mode == SaveMode ? "Existing saves (click to overwrite):" : "Select a save to load:", this);
    listLabel->setStyleSheet("color: #2c3e50; font-weight: bold;");
    layout->addWidget(listLabel);
    
    m_listWidget = new QListWidget(this);
    m_listWidget->setFont(QFont("Consolas", 11));
    m_listWidget->setStyleSheet(
        "QListWidget {"
        "   background-color: #f8f9fa;"
        "   border: 1px solid #dee2e6;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "   color: #2c3e50;"
        "}"
        "QListWidget::item {"
        "   padding: 10px;"
        "   border-bottom: 1px solid #eee;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #3498db;"
        "   color: white;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #e8f4fd;"
        "}"
    );
    
    if (m_saveFiles.isEmpty()) {
        m_listWidget->addItem("(No saves found)");
        m_listWidget->setEnabled(false);
    } else {
        for (const QString &file : m_saveFiles) {
            m_listWidget->addItem(file);
        }
    }
    
    layout->addWidget(m_listWidget);
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    
    if (m_mode == LoadMode) {
        m_deleteButton = new QPushButton("🗑️ DELETE", this);
        m_deleteButton->setFixedHeight(40);
        m_deleteButton->setFont(QFont("Arial", 11, QFont::Bold));
        m_deleteButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #e74c3c;"
            "   color: white;"
            "   border: none;"
            "   border-radius: 5px;"
            "   padding: 8px;"
            "}"
            "QPushButton:hover { background-color: #c0392b; }"
        );
        connect(m_deleteButton, &QPushButton::clicked, this, &SaveLoadWindow::onDeleteClicked);
        buttonLayout->addWidget(m_deleteButton);
    }
    
    buttonLayout->addStretch();
    
    m_cancelButton = new QPushButton("❌ CANCEL", this);
    m_cancelButton->setFixedHeight(40);
    m_cancelButton->setFont(QFont("Arial", 11));
    m_cancelButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #95a5a6;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "   padding: 8px 20px;"
        "}"
        "QPushButton:hover { background-color: #7f8c8d; }"
    );
    
    m_confirmButton = new QPushButton(m_mode == SaveMode ? "💾 SAVE" : "📂 LOAD", this);
    m_confirmButton->setFixedHeight(40);
    m_confirmButton->setFont(QFont("Arial", 11, QFont::Bold));
    m_confirmButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #27ae60;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "   padding: 8px 20px;"
        "}"
        "QPushButton:hover { background-color: #219a52; }"
        "QPushButton:disabled { background-color: #bdc3c7; }"
    );
    m_confirmButton->setEnabled(false);
    
    buttonLayout->addWidget(m_cancelButton);
    buttonLayout->addWidget(m_confirmButton);
    
    layout->addLayout(buttonLayout);
    
    connect(m_confirmButton, &QPushButton::clicked, this, &SaveLoadWindow::onConfirmClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_listWidget, &QListWidget::itemDoubleClicked, this, &SaveLoadWindow::onItemDoubleClicked);
    connect(m_listWidget, &QListWidget::itemSelectionChanged, [this]() {
        bool hasSelection = !m_listWidget->selectedItems().isEmpty() && m_listWidget->isEnabled();
        bool hasText = m_mode != SaveMode || !m_newSaveEdit->text().trimmed().isEmpty();
        m_confirmButton->setEnabled(hasSelection || hasText);
    });
}

void SaveLoadWindow::applyWhiteTheme()
{
    setStyleSheet(
        "QDialog { background-color: #ffffff; }"
        "QLabel { color: #2c3e50; }"
        "QLineEdit { color: #2c3e50; }"
    );
}

void SaveLoadWindow::onConfirmClicked()
{
    QString saveName;
    
    if (m_mode == SaveMode && !m_newSaveEdit->text().trimmed().isEmpty()) {
        saveName = m_newSaveEdit->text().trimmed() + ".sav";
    } else if (!m_listWidget->selectedItems().isEmpty()) {
        saveName = m_listWidget->currentItem()->text();
    } else {
        return;
    }
    
    m_selectedSave = saveName;
    
    if (m_mode == SaveMode) {
        emit saveRequested(saveName);
    } else {
        emit loadRequested(saveName);
    }
    
    accept();
}

void SaveLoadWindow::onItemDoubleClicked(QListWidgetItem *item)
{
    if (!m_listWidget->isEnabled()) return;
    m_selectedSave = item->text();
    if (m_mode == SaveMode) {
        m_newSaveEdit->setText(item->text().replace(".sav", ""));
    }
    onConfirmClicked();
}

void SaveLoadWindow::onDeleteClicked()
{
    if (m_listWidget->selectedItems().isEmpty()) return;
    
    QString fileName = m_listWidget->currentItem()->text();
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Save",
        "Are you sure you want to delete \"" + fileName + "\"?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Note: Actual file deletion would be handled by the controller
        m_listWidget->takeItem(m_listWidget->row(m_listWidget->currentItem()));
    }
}

void SaveLoadWindow::onNewSaveNameChanged(const QString &text)
{
    bool hasText = !text.trimmed().isEmpty();
    bool hasSelection = !m_listWidget->selectedItems().isEmpty() && m_listWidget->isEnabled();
    m_confirmButton->setEnabled(hasText || hasSelection);
}

QString SaveLoadWindow::getSelectedSave() const
{
    return m_selectedSave;
}
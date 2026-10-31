#include "InfoDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QFont>
#include <QApplication>
#include <QScreen>
#include <QGuiApplication>

InfoDialog::InfoDialog(const QString &title, const QString &content, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(title);
    resize(640, 520);
    setModal(true);
    setupUI(title, content);

    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        move(screen->availableGeometry().center() - rect().center());
    }
}

InfoDialog::~InfoDialog()
{
}

void InfoDialog::setupUI(const QString &title, const QString &content)
{
    setStyleSheet(
        "QDialog { background-color: #ffffff; }"
        "QLabel { color: #2c3e50; }"
        "QTextEdit { color: #2c3e50; }"
    );

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(12);
    layout->setContentsMargins(20, 20, 20, 20);

    QLabel *titleLabel = new QLabel(title, this);
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    titleLabel->setStyleSheet("color: #2c3e50; border-bottom: 2px solid #3498db; padding-bottom: 6px;");
    layout->addWidget(titleLabel);

    QTextEdit *text = new QTextEdit(this);
    text->setReadOnly(true);
    text->setFont(QFont("Consolas", 11));
    text->setPlainText(content.isEmpty() ? "Nothing to show." : content);
    text->setStyleSheet(
        "QTextEdit {"
        "   background-color: #f8f9fa;"
        "   border: 1px solid #dee2e6;"
        "   border-radius: 6px;"
        "   padding: 10px;"
        "   color: #2c3e50;"
        "}"
    );
    layout->addWidget(text);

    QPushButton *closeButton = new QPushButton("Close", this);
    closeButton->setFixedHeight(40);
    closeButton->setFont(QFont("Arial", 11, QFont::Bold));
    closeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 6px;"
        "   padding: 8px 24px;"
        "}"
        "QPushButton:hover { background-color: #2980b9; }"
        "QPushButton:pressed { background-color: #1c6ea4; }"
    );

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    layout->addLayout(buttonLayout);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
}

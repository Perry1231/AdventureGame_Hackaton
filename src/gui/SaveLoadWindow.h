#ifndef SAVELOADWINDOW_H
#define SAVELOADWINDOW_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStringList>

class SaveLoadWindow : public QDialog
{
    Q_OBJECT
public:
    enum Mode { SaveMode, LoadMode };
    
    explicit SaveLoadWindow(Mode mode, const QStringList &saveFiles, QWidget *parent = nullptr);
    ~SaveLoadWindow();
    
    QString getSelectedSave() const;

signals:
    void saveRequested(const QString &name);
    void loadRequested(const QString &name);

private slots:
    void onConfirmClicked();
    void onItemDoubleClicked(QListWidgetItem *item);
    void onDeleteClicked();
    void onNewSaveNameChanged(const QString &text);

private:
    void setupUI();
    void applyWhiteTheme();
    
    Mode m_mode;
    QStringList m_saveFiles;
    QListWidget *m_listWidget = nullptr;
    QPushButton *m_confirmButton = nullptr;
    QPushButton *m_cancelButton = nullptr;
    QPushButton *m_deleteButton = nullptr;
    QLineEdit *m_newSaveEdit = nullptr;
    QString m_selectedSave;
};

#endif // SAVELOADWINDOW_H
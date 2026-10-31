#ifndef DIFFICULTYWINDOW_H
#define DIFFICULTYWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>

class DifficultyWindow : public QDialog
{
    Q_OBJECT
public:
    explicit DifficultyWindow(QWidget *parent = nullptr);
    ~DifficultyWindow();
    
    int getSelectedDifficulty() const;

signals:
    void difficultySelected(int level);

private slots:
    void onConfirmClicked();
    void onCancelClicked();

private:
    void setupUI();
    void applyWhiteTheme();
    
    QButtonGroup *m_difficultyGroup = nullptr;
    QRadioButton *m_easyRadio = nullptr;
    QRadioButton *m_normalRadio = nullptr;
    QRadioButton *m_hardRadio = nullptr;
    QRadioButton *m_nightmareRadio = nullptr;
    QPushButton *m_confirmButton = nullptr;
    QPushButton *m_cancelButton = nullptr;
    int m_selectedDifficulty = 1;
};

#endif // DIFFICULTYWINDOW_H
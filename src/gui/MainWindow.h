#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void startNewGameRequested();
    void loadGameRequested();
    void settingsRequested();
    void exitRequested();

private slots:
    void onStartClicked();
    void onLoadClicked();
    void onSettingsClicked();
    void onExitClicked();

private:
    void setupUI();
    void applyWhiteTheme();
    
    QWidget *m_centralWidget = nullptr;
    QVBoxLayout *m_layout = nullptr;
    QLabel *m_titleLabel = nullptr;
    QLabel *m_imageLabel = nullptr;
    QPushButton *m_startButton = nullptr;
    QPushButton *m_loadButton = nullptr;
    QPushButton *m_settingsButton = nullptr;
    QPushButton *m_exitButton = nullptr;
};

#endif // MAINWINDOW_H
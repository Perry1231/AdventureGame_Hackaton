#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QString>

class InfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InfoDialog(const QString &title, const QString &content, QWidget *parent = nullptr);
    ~InfoDialog();

private:
    void setupUI(const QString &title, const QString &content);
};

#endif // INFODIALOG_H
#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QString>
#include <QMessageBox>

namespace Ui {
class loginwindow;
}

class loginwindow : public QWidget
{
    Q_OBJECT

public:
    explicit loginwindow(bool (*functionPtr)(QString, QString), QWidget *parent = 0);
    ~loginwindow();

private slots:
    void on_loginButton_clicked();

private:
    Ui::loginwindow *ui;
    bool (*loginfunction)(QString, QString);
};

#endif // LOGINWINDOW_H

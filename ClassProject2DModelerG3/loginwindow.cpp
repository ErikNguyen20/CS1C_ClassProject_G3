#include "loginwindow.h"
#include "ui_loginwindow.h"

loginwindow::loginwindow(bool (*functionPtr)(QString, QString), QWidget *parent) :
    QWidget(parent),
    loginfunction(functionPtr),
    ui(new Ui::loginwindow)
{
    ui->setupUi(this);
}

loginwindow::~loginwindow()
{
    delete ui;
}

void loginwindow::on_loginButton_clicked()
{
    if(loginfunction(ui->usernameTextEdit->toPlainText(), ui->passwordTextEdit->toPlainText()))
    {
        QMessageBox::information(this, "Login", "Login Successful!");
        close();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Username or Password was incorrect.");
        ui->usernameTextEdit->setPlainText("");
        ui->passwordTextEdit->setPlainText("");
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTextStream>
#include <QFile>
using std::endl;

const QString ADMIN_USERNAME = "Admin";
const QString ADMIN_PASSWORD = "Password";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLogin_triggered()
{
    //Login Button In the Menu Bar
}

void MainWindow::on_loginButton_clicked()
{
    QString username = ui->usernameTextEdit->toPlainText();
    QString password = ui->passwordTextEdit->toPlainText();
    bool successfulLogin;

    successfulLogin = false;

    QFile accounts("Accounts.txt");
    if(accounts.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream iFile(&accounts);

        while(!iFile.atEnd() && !successfulLogin)
        {
            QString userLine = iFile.readLine();
            QString passLine = iFile.readLine();
            if(username == userLine && password == passLine)
            {
                successfulLogin = true;
                statusBar()->showMessage("Successful");
            }
        }
    }
    if(!successfulLogin)
    {
        statusBar()->showMessage("Unsuccessful");
    }
}

void MainWindow::on_registerButton_clicked()
{
    QFile accounts("Accounts.txt");

    if(accounts.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream oFile(&accounts);
        oFile << ui->usernameTextEdit->toPlainText() << endl;
        oFile << ui->passwordTextEdit->toPlainText() << endl << endl;

        accounts.close();
        statusBar()->showMessage("Successful created new account!");
    }
    else
    {
        statusBar()->showMessage("Unable to write to file Accounts.txt");
    }
}

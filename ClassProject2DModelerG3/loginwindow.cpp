#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

loginwindow::loginwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginwindow)
{
    ui->setupUi(this);
    setWindowTitle("Administrator Login");
}

loginwindow::~loginwindow()
{
    delete ui;
}

void loginwindow::on_loginButton_clicked()
{
    if(ADMINISTRATOR_USERNAME == ui->usernameTextEdit->toPlainText() && ADMINISTRATOR_PASSWORD == ui->passwordTextEdit->toPlainText())
    {
        QMessageBox::information(this, "Login", "Login Successful!");
        emit loginSuccessful();
        close();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Username or Password was incorrect.");
        ui->usernameTextEdit->setPlainText("");
        ui->passwordTextEdit->setPlainText("");
    }
}

/*void MainWindow::on_loginButton_clicked()
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

        accounts.close();
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
        oFile << ui->passwordTextEdit->toPlainText() << endl;

        accounts.close();
        statusBar()->showMessage("Successful created new account!");
    }
    else
    {
        statusBar()->showMessage("Unable to write to file Accounts.txt");
    }
}
*/

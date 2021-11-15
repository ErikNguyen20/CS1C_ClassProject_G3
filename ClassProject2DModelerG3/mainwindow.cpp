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

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,"2D Modeler - Open File",QDir::homePath(),"Text Files (*.txt)");
    if(!filePath.isEmpty())
    {
        QFile file(filePath);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream iFile(&file);

            //Vector<Shape> newObjects;

            while(!iFile.atEnd())
            {
                QString title;
                QString shapeId;
                QString shapeType;
                QString penColor;
                QString penWidth;
                QString penStyle;
                QString penCapStyle;
                QString penJoinStyle;
                QString brushColor;
                QString brushStyle;
                QString textString;
                QString textColor;
                QString textAlignment;
                QString textPointSize;
                QString textFontFamily;
                QString textFontStyle;
                QString textFontWeight;

                //Shape* shapePtr;

                iFile >> title >> shapeId;
                iFile >> title >> shapeType;
                iFile >> title;
                iFile.skipWhiteSpace();
                QString shapeDimensions = iFile.readLine();

                QRegularExpression pattern;
                pattern.setPattern("\\W+");
                QStringList dimensionsList = shapeDimensions.split(pattern);

                int dimensionAr[dimensionsList.size()];
                for(int index = 0; index < dimensionsList.size(); index++)
                {
                    bool ok;
                    dimensionAr[index] = dimensionsList.at(index).toInt(&ok,10);
                }

                if(shapeType == "Line" || shapeType == "Polyline")
                {
                    iFile >> title >> penColor;
                    iFile >> title >> penWidth;
                    iFile >> title >> penStyle;
                    iFile >> title >> penCapStyle;
                    iFile >> title >> penJoinStyle;
                }
                else if(shapeType == "Text")
                {
                    iFile >> title >> textString;
                    iFile >> title >> textColor;
                    iFile >> title >> textAlignment;
                    iFile >> title >> textPointSize;
                    iFile >> title >> textFontFamily;
                    iFile >> title >> textFontStyle;
                    iFile >> title >> textFontWeight;
                }
                else
                {
                    iFile >> title >> penColor;
                    iFile >> title >> penWidth;
                    iFile >> title >> penStyle;
                    iFile >> title >> penCapStyle;
                    iFile >> title >> penJoinStyle;
                    iFile >> title >> brushColor;
                    iFile >> title >> brushStyle;
                }
                switch(SHAPE_TABLE.indexOf(shapeType)) //Could be shapeId or shapeType
                { //const QStringList SHAPE_TABLE = {"Line","Polyline","Polygon","Rectangle","Square","Ellipse","Circle","Text"};
                case 0: //Line
                    //Create Line Object
                    //shapePtr = new Line(shapeId,);
                    break;
                case 1: //Polyline
                    // Create Polyline Object
                    break;
                case 2: //Polygon
                    //Create Polygon object
                    break;
                case 3: //Rectangle
                    //Create Rectangle Object
                    break;
                case 4: //Square
                    //Create Square Object
                    break;
                case 5: //Ellipse
                    //Create Ellipse Object
                    break;
                case 6: //Circle
                    break;
                case 7: //Text
                    break;
                };

                //objects.append(shapePtr);
            }

            //objects = newObjects;

            currentFilePath = filePath;

            statusBar()->showMessage("Successfully opened file.");
            file.close();
        }
        else
        {
            statusBar()->showMessage("Failed to open file.");
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(currentFilePath.isEmpty())
    {
        on_actionSave_As_triggered();
    }
    else
    {
        QFile saveFile(currentFilePath);

        if(saveFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream oFile(&saveFile);
            //Save Shape Data Here.



            statusBar()->showMessage("Successful Save!");
            saveFile.close();
        }
        else
        {
            statusBar()->showMessage("Failed to save.");
        }
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this,"2D Modeler - Save-As",QDir::homePath(),"Text File (*.txt)") + ".txt"; //Concat .txt extension.
    if(!filePath.isEmpty())
    {
        currentFilePath = filePath;
        on_actionSave_triggered();
    }
}

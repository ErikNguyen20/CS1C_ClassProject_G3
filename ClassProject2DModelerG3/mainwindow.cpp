#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTextStream>
#include <QFile>
using std::endl;

const QString ADMIN_USERNAME = "Admin";
const QString ADMIN_PASSWORD = "Password";
const QString DEFAULT_WINDOW_NAME = "Untitled";
const QStringList SHAPE_TABLE = {"Line","Polyline","Polygon","Rectangle","Square","Ellipse","Circle","Text"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->LoginBox->hide();
    renderArea = new RenderArea(ui->renderCanvas);
    renderArea->show();
    renderArea->update();
    //setWindowTitle(DEFAULT_WINDOW_NAME);
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
                int shapeId;
                QString shapeType;
                QString penColor;
                int penWidth;
                QString penStyle;
                QString penCapStyle;
                QString penJoinStyle;
                QString brushColor;
                QString brushStyle;
                QString textString;
                QString textColor;
                QString textAlignment;
                int textPointSize;
                QString textFontFamily;
                QString textFontStyle;
                QString textFontWeight;

                //Shape* shapePtr;

                iFile >> title >> shapeId;
                iFile >> title >> shapeType;
                iFile >> title;
                iFile.skipWhiteSpace();

                //Splits the Shape Dimensions Qstring into seperate Qstrings by digits.
                QRegularExpression pattern;
                pattern.setPattern("\\W+");
                QStringList dimensionsList = iFile.readLine().split(pattern);

                //Converts QStrings from the list into integers, storing them into dimensionAr
                int dimensionAr[dimensionsList.size()];
                for(int index = 0; index < dimensionsList.size(); index++)
                {
                    bool ok;
                    dimensionAr[index] = dimensionsList.at(index).toInt(&ok,10);
                }

                //Read in specific properties to each shape type.
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
                    iFile >> title;
                    iFile.skipWhiteSpace();
                    textString = iFile.readLine();
                    iFile >> title >> textColor;
                    iFile >> title >> textAlignment;
                    iFile >> title >> textPointSize;
                    iFile >> title;
                    iFile.skipWhiteSpace();
                    textFontFamily = iFile.readLine();
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
                iFile.skipWhiteSpace();

                //Create new derived shapes, then place them into a vector
                switch(SHAPE_TABLE.indexOf(shapeType))
                { //const QStringList SHAPE_TABLE = {"Line","Polyline","Polygon","Rectangle","Square","Ellipse","Circle","Text"};
                case 0: //Line
                    //Create Line Object
                    //shapePtr = new Line(shapeId,...);
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
                    //Create Circle Object
                    break;
                case 7: //Text
                    //Create Text Object
                    break;
                };

                //newObjects.append(shapePtr);
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
    QString filePath = QFileDialog::getSaveFileName(this,"2D Modeler - Save-As",QDir::homePath(),"Text File (*.txt)");
    if(!filePath.isEmpty())
    {
        if(!filePath.contains(".txt"))
        {
            filePath = filePath + ".txt";
        }
        currentFilePath = filePath;
        on_actionSave_triggered();
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shapemaster.h"
#include "vector.h"
#include "parserexception.h"
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include "functions.h"
#include <QDebug>


/******************** CONSTANTS ********************/

const QString DEFAULT_WINDOW_NAME = "Untitled";


/******************** Main Window Constructor ********************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    addLineWindow(nullptr),
    addPolylineWindow(nullptr),
    addPolygonWindow(nullptr),
    addRectangleWindow(nullptr),
    addEllipseWindow(nullptr),
    addTextWindow(nullptr),
    needsSave(false)
{
    ui->setupUi(this);
    loginWindow = new loginwindow();
    ContactUs = new contactus();

    connect(&*loginWindow,SIGNAL(loginSuccessful()),this,SLOT(Login()));

    renderArea = new RenderArea(ui->renderCanvas);
    renderArea->show();
    renderArea->update();

    setWindowTitle(DEFAULT_WINDOW_NAME);
}

/******************** Main Window Destructor ********************/

MainWindow::~MainWindow()
{
    delete loginWindow;
    delete renderArea;
    delete Testimonials;
    delete ContactUs;
    delete ui;
    delete addLineWindow;
    delete addPolylineWindow;
    delete addPolygonWindow;
    delete addRectangleWindow;
    delete addEllipseWindow;
    delete addTextWindow;
}


//Login Button in the toolbar <- can change location later
void MainWindow::on_actionLogin_triggered()
{
    loginWindow->show();
}


/******************** Open File (Parser) ********************/

void MainWindow::on_actionOpen_triggered()
{
    if(needsSave) //If the shapes are modified, it will prompt a save before opening a new file.
    {
        QMessageBox savePrompt;
        savePrompt.setWindowTitle("Save Changes");
        savePrompt.setText("Do you want to save your changes?");
        savePrompt.setStandardButtons(QMessageBox::Discard | QMessageBox::Save);

        if(savePrompt.exec() == QMessageBox::Save)
        {
            on_actionSave_triggered();
        }
        needsSave = false;
    }

    try //Exception handler for Parser (ParserException Class)
    {
        QString filePath = QFileDialog::getOpenFileName(this,"2D Modeler - Open File",QDir::homePath(),"Text Files (*.txt)");
        if(!filePath.isEmpty() && filePath != currentFilePath)
        {
            QFile file(filePath);
            if(file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream iFile(&file);

                //Parse from file
                vector<Shape*> newObjects;
                readShapesFromFile(iFile, newObjects);

                //Renders the objects on the canvas and sets the path.
                renderArea->SetShapes(newObjects);
                currentFilePath = filePath;
                setWindowTitle(file.fileName());

                statusBar()->showMessage("Successfully opened file.");
                file.close();

                ui->comboBox->clear();
                QStringList idAndNameList;
                QString idAndName;
                for(int i = 0; i < newObjects.size(); i++)
                {
                    idAndName = QString::number(newObjects[i]->getID());
                    idAndName = idAndName + ' ';
                    idAndName = idAndName + newObjects[i]->getShapeStypeString();

                    idAndNameList.append(idAndName);
                }
                ui->comboBox->addItems(idAndNameList);

            }
            else
            {
                throw ParserException("Failed to open file.");
            }
        }
    }
    catch(const ParserException& exceptionObj)
    {
        QMessageBox::warning(this, "Open File", exceptionObj.what());
    }
}

/******************** Save Function (Write into file) ********************/

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
            vector<Shape*> currentShapes = renderArea->GetShapes();

            writeShapesToFile(oFile, currentShapes);

            setWindowTitle(saveFile.fileName());
            statusBar()->showMessage("Successful Save!");
            saveFile.close();
        }
        else
        {
            QMessageBox::warning(this, "Save", "Failed to save to file.");
        }
    }
    needsSave = false;
}

/******************** Save-as Function ********************/

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

/******************** New Function ********************/

void MainWindow::on_actionNew_triggered()
{
    if(needsSave) //If the shapes are modified, it will prompt a save before opening a new file.
    {
        QMessageBox savePrompt;
        savePrompt.setWindowTitle("Save Changes");
        savePrompt.setText("Do you want to save your changes?");
        savePrompt.setStandardButtons(QMessageBox::Discard | QMessageBox::Save);

        if(savePrompt.exec() == QMessageBox::Save)
        {
            on_actionSave_triggered();
        }
        needsSave = false;
    }
    vector<Shape*> emptyVector;
    renderArea->SetShapes(emptyVector);
    currentFilePath.clear();
    ui->comboBox->clear();
    setWindowTitle(DEFAULT_WINDOW_NAME);
}


/******************** Login Function ********************/

void MainWindow::Login()
{
    //Add code to enable ui features.
}

void MainWindow::on_actionTestimonials_triggered()
{
    Testimonials = new testimonials();
    Testimonials -> show();
}


void MainWindow::on_actionContact_Us_triggered()
{
    ContactUs -> show();
}

void MainWindow::on_actionAddLine_triggered()
{
    addLineWindow = new addLineDetails();

    if (addLineWindow->exec() == QDialog::Accepted)
    {
        if(addLineWindow->GetSuccessBool())
        {
            Shape *newShape = addLineWindow->GetShape();
            vector<Shape*> currentShapes = renderArea->GetShapes();
            newShape->setID(currentShapes.size() + 1);
            currentShapes.push_back(newShape);
            renderArea->SetShapes(currentShapes);

            QString idAndName = QString::number(currentShapes[currentShapes.size() - 1]->getID());
            idAndName = idAndName + ' ';
            idAndName = idAndName + currentShapes[currentShapes.size() - 1]->getShapeStypeString();
            ui->comboBox->addItem(idAndName);

            if(!needsSave)
            {
                setWindowTitle('*'+windowTitle());
                needsSave = true;
            }
        }

    }
}


void MainWindow::on_actionAddPolyline_triggered()
{
    addPolylineWindow = new addPolylineDetails();

    if (addPolylineWindow->exec() == QDialog::Accepted)
    {
        if(addPolylineWindow->GetSuccessBool())
        {
            Shape *newShape = addPolylineWindow->GetShape();
            vector<Shape*> currentShapes = renderArea->GetShapes();
            newShape->setID(currentShapes.size() + 1);
            currentShapes.push_back(newShape);
            renderArea->SetShapes(currentShapes);

            QString idAndName = QString::number(currentShapes[currentShapes.size() - 1]->getID());
            idAndName = idAndName + ' ';
            idAndName = idAndName + currentShapes[currentShapes.size() - 1]->getShapeStypeString();
            ui->comboBox->addItem(idAndName);

            if(!needsSave)
            {
                setWindowTitle('*'+windowTitle());
                needsSave = true;
            }
        }

    }
}


void MainWindow::on_actionAddPolygon_triggered()
{
    addPolygonWindow = new addPolygonDetails();

    if (addPolygonWindow->exec() == QDialog::Accepted)
    {
        if(addPolygonWindow->GetSuccessBool())
        {
            Shape *newShape = addPolygonWindow->GetShape();
            vector<Shape*> currentShapes = renderArea->GetShapes();
            newShape->setID(currentShapes.size() + 1);
            currentShapes.push_back(newShape);
            renderArea->SetShapes(currentShapes);

            QString idAndName = QString::number(currentShapes[currentShapes.size() - 1]->getID());
            idAndName = idAndName + ' ';
            idAndName = idAndName + currentShapes[currentShapes.size() - 1]->getShapeStypeString();
            ui->comboBox->addItem(idAndName);

            if(!needsSave)
            {
                setWindowTitle('*'+windowTitle());
                needsSave = true;
            }
        }

    }
}


void MainWindow::on_actionAddRectangle_triggered()
{
    addRectangleWindow = new addRectangleDetails();

    if (addRectangleWindow->exec() == QDialog::Accepted)
    {
        if(addRectangleWindow->GetSuccessBool())
        {
            Shape *newShape = addRectangleWindow->GetShape();
            vector<Shape*> currentShapes = renderArea->GetShapes();
            newShape->setID(currentShapes.size() + 1);
            currentShapes.push_back(newShape);
            renderArea->SetShapes(currentShapes);

            QString idAndName = QString::number(currentShapes[currentShapes.size() - 1]->getID());
            idAndName = idAndName + ' ';
            idAndName = idAndName + currentShapes[currentShapes.size() - 1]->getShapeStypeString();
            ui->comboBox->addItem(idAndName);

            if(!needsSave)
            {
                setWindowTitle('*'+windowTitle());
                needsSave = true;
            }
        }

    }
}


void MainWindow::on_actionAddEllipse_triggered()
{
    addEllipseWindow = new addEllipseDetails();

    if (addEllipseWindow->exec() == QDialog::Accepted)
    {
        if(addEllipseWindow->GetSuccessBool())
        {
            Shape *newShape = addEllipseWindow->GetShape();
            vector<Shape*> currentShapes = renderArea->GetShapes();
            newShape->setID(currentShapes.size() + 1);
            currentShapes.push_back(newShape);
            renderArea->SetShapes(currentShapes);

            QString idAndName = QString::number(currentShapes[currentShapes.size() - 1]->getID());
            idAndName = idAndName + ' ';
            idAndName = idAndName + currentShapes[currentShapes.size() - 1]->getShapeStypeString();
            ui->comboBox->addItem(idAndName);

            if(!needsSave)
            {
                setWindowTitle('*'+windowTitle());
                needsSave = true;
            }
        }

    }
}


void MainWindow::on_actionAddText_triggered()
{
    addTextWindow = new addTextDetails();

    if (addTextWindow->exec() == QDialog::Accepted)
    {
        if(addTextWindow->GetSuccessBool())
        {
            Shape *newShape = addTextWindow->GetShape();
            vector<Shape*> currentShapes = renderArea->GetShapes();
            newShape->setID(currentShapes.size() + 1);
            currentShapes.push_back(newShape);
            renderArea->SetShapes(currentShapes);

            QString idAndName = QString::number(currentShapes[currentShapes.size() - 1]->getID());
            idAndName = idAndName + ' ';
            idAndName = idAndName + currentShapes[currentShapes.size() - 1]->getShapeStypeString();
            ui->comboBox->addItem(idAndName);

            if(!needsSave)
            {
                setWindowTitle('*'+windowTitle());
                needsSave = true;
            }
        }

    }
}


void MainWindow::closeEvent(QCloseEvent*)
{
    if(needsSave) //If the shapes are modified, it will prompt a save before closing.
    {
        QMessageBox savePrompt;
        savePrompt.setWindowTitle("Save Changes");
        savePrompt.setText("Do you want to save your changes?");
        savePrompt.setStandardButtons(QMessageBox::Discard | QMessageBox::Save);

        if(savePrompt.exec() == QMessageBox::Save)
        {
            on_actionSave_triggered();
        }
        needsSave = false;
    }
}

void MainWindow::on_pushButton_clicked()
{
    vector<Shape*> currentShapes = renderArea->GetShapes();
    if(currentShapes.size() > 0)
    {
        currentShapes.erase(currentShapes.begin() + ui->comboBox->currentIndex());
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
        renderArea->SetShapes(currentShapes);

        if(!needsSave)
        {
            setWindowTitle('*'+windowTitle());
            needsSave = true;
        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    vector<Shape*> currentShapes = renderArea->GetShapes();
    if(currentShapes.size() > 0)
    {
        currentShapes[ui->comboBox->currentIndex()]->move(ui->textEdit->toPlainText().toInt(), ui->textEdit_2->toPlainText().toInt());
        renderArea->SetShapes(currentShapes);

        if(!needsSave)
        {
            setWindowTitle('*'+windowTitle());
            needsSave = true;
        }
    }

}


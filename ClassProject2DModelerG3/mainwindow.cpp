#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shapes.h"
#include "vector.h"
#include <iostream>
#include <QTextStream>
#include <QFile>

using std::endl;

/******************** CONSTANTS ********************/

const QString ADMIN_USERNAME = "Admin";
const QString ADMIN_PASSWORD = "Password";
const QString DEFAULT_WINDOW_NAME = "Untitled";
const QStringList SHAPE_LIST = {"Line","Polyline","Polygon","Rectangle","Square","Ellipse","Circle","Text"};
const QStringList GLOBALCOLOR_LIST = {"white","black","red","green","blue","cyan","magenta","yellow","gray"};
const QStringList PENSTYLE_LIST = {"NoPen","SolidLine","DashLine","DotLine","DashDotLine","DashDotDotLine"};
const QStringList PENCAPSTYLE_LIST = {"FlatCap","SquareCap","RoundCap"};
const QStringList PENJOINSTYLE_LIST = {"MiterJoin","BevelJoin","RoundJoin"};
const QStringList BRUSHSTYLE_LIST = {"SolidPattern","HorPattern","VerPattern","NoBrush"};
const QStringList ALIGNMENTFLAG_LIST = {"AlignLeft","AlignRight","AlignTop","AlignBottom","AlignCenter"};
const QStringList QFONTSTYLE_LIST = {"StyleNormal","StyleItalic","StyleOblique"};
const QStringList QFONTWEIGHT_LIST = {"Thin","Light","Normal","Bold"};


/******************** Function Prototypes ********************/

bool Login(QString username, QString password);

Qt::GlobalColor QStringToGlobalColor(const QString& color);
Qt::PenStyle QStringToPenStyle(const QString& penstyle);
Qt::PenCapStyle QStringToPenCapStyle(const QString& pencapstyle);
Qt::PenJoinStyle QStringToPenJoinStyle(const QString& penjoinstyle);
Qt::BrushStyle QStringToBrushStyle(const QString& brushstyle);
Qt::AlignmentFlag QStringToAlignmentFlag(const QString& alignmentflag);
QFont::Style QStringToQFontStyle(const QString& qfontstyle);
QFont::Weight QStringToQFontWeight(const QString& qfontweight);



/******************** Main Window Constructor ********************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    loginWindow(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderArea = new RenderArea(ui->renderCanvas);
    renderArea->show();
    renderArea->update();
    setWindowTitle(DEFAULT_WINDOW_NAME);
}

/******************** Main Window Destructor ********************/

MainWindow::~MainWindow()
{
    delete ui;
}


//Login Button in the toolbar <- can change location later
void MainWindow::on_actionLogin_triggered()
{
    loginWindow = new loginwindow(Login);
    loginWindow->setWindowTitle("Administrator Login");
    loginWindow->show();
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

/******************** Open File (Parser) ********************/

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,"2D Modeler - Open File",QDir::homePath(),"Text Files (*.txt)");
    if(!filePath.isEmpty())
    {
        QFile file(filePath);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream iFile(&file);

            vector<Shape*> newObjects;
            bool successfulParse = true;


            while(!iFile.atEnd() && successfulParse)
            {
                QString title,shapeType;
                int shapeId,shapeTypeIndex;
                QString penColor,penStyle,penCapStyle,penJoinStyle;
                int penWidth;
                QString brushColor,brushStyle;
                QString textString,textColor,textAlignment,textFontFamily,textFontStyle,textFontWeight;
                int textPointSize;
                vector<QPoint> pointsVector;

                Shape* shapePtr = nullptr;



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

                Qt::GlobalColor penColorEnum,textColorEnum,brushColorEnum;
                Qt::PenStyle penStyleEnum;
                Qt::PenCapStyle penCapStyleEnum;
                Qt::PenJoinStyle penJoinStyleEnum;
                Qt::AlignmentFlag textAlignmentEnum;
                QFont::Style textFontStyleEnum;
                QFont::Weight textFontWeightEnum;
                Qt::BrushStyle brushStyleEnum;

                if(shapeType == "Line" || shapeType == "Polyline")
                {
                    iFile >> title >> penColor;
                    iFile >> title >> penWidth;
                    iFile >> title >> penStyle;
                    iFile >> title >> penCapStyle;
                    iFile >> title >> penJoinStyle;

                    penColorEnum = QStringToGlobalColor(penColor);
                    penStyleEnum = QStringToPenStyle(penStyle);
                    penCapStyleEnum = QStringToPenCapStyle(penCapStyle);
                    penJoinStyleEnum = QStringToPenJoinStyle(penJoinStyle);
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

                    textColorEnum = QStringToGlobalColor(textColor);
                    textAlignmentEnum = QStringToAlignmentFlag(textAlignment);
                    textFontStyleEnum = QStringToQFontStyle(textFontStyle);
                    textFontWeightEnum = QStringToQFontWeight(textFontWeight);
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

                    penColorEnum = QStringToGlobalColor(penColor);
                    penStyleEnum = QStringToPenStyle(penStyle);
                    penCapStyleEnum = QStringToPenCapStyle(penCapStyle);
                    penJoinStyleEnum = QStringToPenJoinStyle(penJoinStyle);
                    brushColorEnum = QStringToGlobalColor(brushColor);
                    brushStyleEnum = QStringToBrushStyle(brushStyle);
                }
                iFile.skipWhiteSpace();



                //Create new derived shapes, then place them into a vector

                shapeTypeIndex = SHAPE_LIST.indexOf(shapeType);

                if(((shapeTypeIndex == 4 || shapeTypeIndex == 6) && (dimensionsList.size()%2 == 0)) ||
                   ((shapeTypeIndex != 4 && shapeTypeIndex != 6) && (dimensionsList.size()%2 == 1)))
                {
                    successfulParse = false; //Invalid number of dimensions
                }
                else
                {
                    switch(shapeTypeIndex)
                    {
                    case 0: //Line
                        //Create Line Object
                        shapePtr = new Line(shapeId,
                                            QPoint(dimensionAr[0],dimensionAr[1]),
                                            QPoint(dimensionAr[2],dimensionAr[3]),
                                            penColorEnum,
                                            penWidth,
                                            penStyleEnum,
                                            penCapStyleEnum,
                                            penJoinStyleEnum
                                        );
                        break;
                    case 1: //Polyline
                        // Create Polyline Object
                        for(int index = 0; index < dimensionsList.size(); index += 2)
                        {
                            pointsVector.push_back(QPoint(dimensionAr[index],dimensionAr[index+1]));
                        }
                        shapePtr = new Polyline(shapeId,
                                            pointsVector,
                                            penColorEnum,
                                            penWidth,
                                            penStyleEnum,
                                            penCapStyleEnum,
                                            penJoinStyleEnum
                                        );
                        break;
                    case 2: //Polygon
                        //Create Polygon object
                        for(int index = 0; index < dimensionsList.size(); index += 2)
                        {
                            pointsVector.push_back(QPoint(dimensionAr[index],dimensionAr[index+1]));
                        }

                        shapePtr = new Polygon(shapeId,
                                            pointsVector,
                                            penColorEnum,
                                            penWidth,
                                            penStyleEnum,
                                            penCapStyleEnum,
                                            penJoinStyleEnum,
                                            brushColorEnum,
                                            brushStyleEnum
                                        );
                        break;
                    case 3: //Rectangle
                        //Create Rectangle Object
                        shapePtr = new Rectangle(shapeId,
                                            QPoint(dimensionAr[0],dimensionAr[1]),
                                            dimensionAr[2],
                                            dimensionAr[3],
                                            penColorEnum,
                                            penWidth,
                                            penStyleEnum,
                                            penCapStyleEnum,
                                            penJoinStyleEnum,
                                            brushColorEnum,
                                            brushStyleEnum
                                        );
                        break;
                    case 4: //Square
                        //Create Square Object
                        shapePtr = new Square(shapeId,
                                            QPoint(dimensionAr[0],dimensionAr[1]),
                                            dimensionAr[2],
                                            penColorEnum,
                                            penWidth,
                                            penStyleEnum,
                                            penCapStyleEnum,
                                            penJoinStyleEnum,
                                            brushColorEnum,
                                            brushStyleEnum
                                        );
                        break;
                    case 5: //Ellipse
                        //Create Ellipse Object
                        shapePtr = new Ellipse(shapeId,
                                            QPoint(dimensionAr[0],dimensionAr[1]),
                                            dimensionAr[2],
                                            dimensionAr[3],
                                            penColorEnum,
                                            penWidth,
                                            penStyleEnum,
                                            penCapStyleEnum,
                                            penJoinStyleEnum,
                                            brushColorEnum,
                                            brushStyleEnum
                                        );
                        break;
                    case 6: //Circle
                        //Create Circle Object
                        shapePtr = new Circle(shapeId,
                                            QPoint(dimensionAr[0],dimensionAr[1]),
                                            dimensionAr[2],
                                            penColorEnum,
                                            penWidth,
                                            penStyleEnum,
                                            penCapStyleEnum,
                                            penJoinStyleEnum,
                                            brushColorEnum,
                                            brushStyleEnum
                                        );
                        break;
                    case 7: //Text
                        //Create Text Object
                        shapePtr = new Text(shapeId,
                                            QPoint(dimensionAr[0],dimensionAr[1]),
                                            dimensionAr[2],
                                            dimensionAr[3],
                                            textString,
                                            textColorEnum,
                                            textAlignmentEnum,
                                            textPointSize,
                                            textFontFamily,
                                            textFontStyleEnum,
                                            textFontWeightEnum
                                        );
                        break;
                    default:
                        successfulParse = false; //invalid shape type
                    };

                    newObjects.push_back(shapePtr);
                }
            }

            if(successfulParse)
            {
                //Renders the objects on the canvas and sets the path.
                renderArea->SetShapes(newObjects);
                currentFilePath = filePath;
                setWindowTitle(file.fileName());

                statusBar()->showMessage("Successfully parsed file.");
            }
            else
            {
                statusBar()->showMessage("Failed to parse file.");
            }
            file.close();
        }
        else
        {
            statusBar()->showMessage("Failed to open file.");
        }
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



            statusBar()->showMessage("Successful Save!");
            saveFile.close();
        }
        else
        {
            statusBar()->showMessage("Failed to save.");
        }
    }
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
    vector<Shape*> emptyVector;
    renderArea->SetShapes(emptyVector);
    currentFilePath.clear();
    setWindowTitle(DEFAULT_WINDOW_NAME);
}


/******************** Login Function ********************/

bool Login(QString username, QString password)
{
    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
    {
        //Add code to enable the admin features in ui.
        return true;
    }
    else
    {
        return false;
    }
}



/******************** QString to Enum Conversion Function Definitions ********************/

Qt::GlobalColor QStringToGlobalColor(const QString& color)
{
    switch(GLOBALCOLOR_LIST.indexOf(color))
        //const QStringList GLOBALCOLOR_LIST = {"white","black","red","green","blue","cyan","magenta","yellow","gray"};
    {
    case 0:
        return Qt::white;
    case 1:
        return Qt::black;
    case 2:
        return Qt::red;
    case 3:
        return Qt::green;
    case 4:
        return Qt::blue;
    case 5:
        return Qt::cyan;
    case 6:
        return Qt::magenta;
    case 7:
        return Qt::yellow;
    case 8:
        return Qt::gray;
    default:
        return Qt::white; //Default
    };
}

Qt::PenStyle QStringToPenStyle(const QString& penstyle)
{
    switch(PENSTYLE_LIST.indexOf(penstyle))
        //const QStringList PENSTYLE_LIST = {"NoPen","SolidLine","DashLine","DotLine","DashDotLine","DashDotDotLine"};
    {
    case 0:
        return Qt::NoPen;
    case 1:
        return Qt::SolidLine;
    case 2:
        return Qt::DashLine;
    case 3:
        return Qt::DotLine;
    case 4:
        return Qt::DashDotLine;
    case 5:
        return Qt::DashDotDotLine;
    default:
        return Qt::NoPen; //Default
    };
}

Qt::PenCapStyle QStringToPenCapStyle(const QString& pencapstyle)
{
    switch(PENCAPSTYLE_LIST.indexOf(pencapstyle))
        //const QStringList PENCAPSTYLE_LIST = {"FlatCap","SquareCap","RoundCap"};
    {
    case 0:
        return Qt::FlatCap;
    case 1:
        return Qt::SquareCap;
    case 2:
        return Qt::RoundCap;
    default:
        return Qt::FlatCap; //Default
    };
}

Qt::PenJoinStyle QStringToPenJoinStyle(const QString& penjoinstyle)
{
    switch(PENJOINSTYLE_LIST.indexOf(penjoinstyle))
        //const QStringList PENJOINSTYLE_LIST = {"MiterJoin","BevelJoin","RoundJoin"};
    {
    case 0:
        return Qt::MiterJoin;
    case 1:
        return Qt::BevelJoin;
    case 2:
        return Qt::RoundJoin;
    default:
        return Qt::MiterJoin; //Default
    };
}

Qt::BrushStyle QStringToBrushStyle(const QString& brushstyle)
{
    switch(BRUSHSTYLE_LIST.indexOf(brushstyle))
        //const QStringList BRUSHSTYLE_LIST = {"SolidPattern","HorPattern","VerPattern","NoBrush"};
    {
    case 0:
        return Qt::SolidPattern;
    case 1:
        return Qt::HorPattern;
    case 2:
        return Qt::VerPattern;
    case 3:
        return Qt::NoBrush;
    default:
        return Qt::NoBrush; //Default
    };
}

Qt::AlignmentFlag QStringToAlignmentFlag(const QString& alignmentflag)
{
    switch(ALIGNMENTFLAG_LIST.indexOf(alignmentflag))
        //const QStringList ALIGNMENTFLAG_LIST = {"AlignLeft","AlignRight","AlignTop","AlignBottom","AlignCenter"};
    {
    case 0:
        return Qt::AlignLeft;
    case 1:
        return Qt::AlignRight;
    case 2:
        return Qt::AlignBottom;
    case 3:
        return Qt::AlignCenter;
    default:
        return Qt::AlignCenter; //Default
    };
}

QFont::Style QStringToQFontStyle(const QString& qfontstyle)
{
    switch(QFONTSTYLE_LIST.indexOf(qfontstyle))
        //const QStringList QFONTSTYLE_LIST = {"StyleNormal","StyleItalic","StyleOblique"};
    {
    case 0:
        return QFont::StyleNormal;
    case 1:
        return QFont::StyleItalic;
    case 2:
        return QFont::StyleOblique;
    default:
        return QFont::StyleNormal; //Default
    };
}

QFont::Weight QStringToQFontWeight(const QString& qfontweight)
{
    switch(QFONTWEIGHT_LIST.indexOf(qfontweight))
        //const QStringList QFONTWEIGHT_LIST = {"Thin","Light","Normal","Bold"};
    {
    case 0:
        return QFont::Thin;
    case 1:
        return QFont::Light;
    case 2:
        return QFont::Normal;
    case 3:
        return QFont::Bold;
    default:
        return QFont::Normal; //Default
    };
}


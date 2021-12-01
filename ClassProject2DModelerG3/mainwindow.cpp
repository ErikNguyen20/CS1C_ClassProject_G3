#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shapes.h"
#include "vector.h"
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>

using std::endl;

/******************** CONSTANTS ********************/

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

Qt::GlobalColor QStringToGlobalColor(const QString& color,bool& success);
Qt::PenStyle QStringToPenStyle(const QString& penstyle,bool& success);
Qt::PenCapStyle QStringToPenCapStyle(const QString& pencapstyle,bool& success);
Qt::PenJoinStyle QStringToPenJoinStyle(const QString& penjoinstyle,bool& success);
Qt::BrushStyle QStringToBrushStyle(const QString& brushstyle,bool& success);
Qt::AlignmentFlag QStringToAlignmentFlag(const QString& alignmentflag,bool& success);
QFont::Style QStringToQFontStyle(const QString& qfontstyle,bool& success);
QFont::Weight QStringToQFontWeight(const QString& qfontweight,bool& success);



/******************** Main Window Constructor ********************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginWindow = new loginwindow();
    Testimonials = new testimonials();
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
    delete ui;
}


//Login Button in the toolbar <- can change location later
void MainWindow::on_actionLogin_triggered()
{
    loginWindow->show();
    connect(&(*loginWindow),SIGNAL(loginSuccessful()),this,SLOT(Login()));
}


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

                    penColorEnum = QStringToGlobalColor(penColor,successfulParse);
                    penStyleEnum = QStringToPenStyle(penStyle,successfulParse);
                    penCapStyleEnum = QStringToPenCapStyle(penCapStyle,successfulParse);
                    penJoinStyleEnum = QStringToPenJoinStyle(penJoinStyle,successfulParse);
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

                    textColorEnum = QStringToGlobalColor(textColor,successfulParse);
                    textAlignmentEnum = QStringToAlignmentFlag(textAlignment,successfulParse);
                    textFontStyleEnum = QStringToQFontStyle(textFontStyle,successfulParse);
                    textFontWeightEnum = QStringToQFontWeight(textFontWeight,successfulParse);
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

                    penColorEnum = QStringToGlobalColor(penColor,successfulParse);
                    penStyleEnum = QStringToPenStyle(penStyle,successfulParse);
                    penCapStyleEnum = QStringToPenCapStyle(penCapStyle,successfulParse);
                    penJoinStyleEnum = QStringToPenJoinStyle(penJoinStyle,successfulParse);
                    brushColorEnum = QStringToGlobalColor(brushColor,successfulParse);
                    brushStyleEnum = QStringToBrushStyle(brushStyle,successfulParse);
                }
                iFile.skipWhiteSpace();



                if(!successfulParse)
                {
                    //Invalid Qstring to Enum conversion
                }

                //Create new derived shapes, then place them into a vector

                shapeTypeIndex = SHAPE_LIST.indexOf(shapeType);

                if(((shapeTypeIndex == 4 || shapeTypeIndex == 6) && (dimensionsList.size()%2 == 0)) ||
                   ((shapeTypeIndex != 4 && shapeTypeIndex != 6) && (dimensionsList.size()%2 == 1)) ||
                     !successfulParse)
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
                currentShapes = newObjects;
                renderArea->SetShapes(newObjects);
                currentFilePath = filePath;
                setWindowTitle(file.fileName());

                statusBar()->showMessage("Successfully opened file.");
            }
            else
            {
                QMessageBox::warning(this, "Open File", "File format is incorrect.");
            }
            file.close();
        }
        else
        {
            QMessageBox::warning(this, "Open File", "Failed to open file.");
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
            //(Iterate through the instance datamember of 'currentShapes' (vector of Shape*))



            statusBar()->showMessage("Successful Save!");
            saveFile.close();
        }
        else
        {
            QMessageBox::warning(this, "Save", "Failed to save to file.");
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
    currentShapes = emptyVector;
    renderArea->SetShapes(emptyVector);
    currentFilePath.clear();
    setWindowTitle(DEFAULT_WINDOW_NAME);
}


/******************** Login Function ********************/

void MainWindow::Login()
{
    //Add code to enable ui features.
}



/******************** QString to Enum Conversion Function Definitions ********************/

Qt::GlobalColor QStringToGlobalColor(const QString& color,bool& success)
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
        success = false;
        return Qt::white; //Default
    };
}

Qt::PenStyle QStringToPenStyle(const QString& penstyle,bool& success)
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
        success = false;
        return Qt::NoPen; //Default
    };
}

Qt::PenCapStyle QStringToPenCapStyle(const QString& pencapstyle,bool& success)
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
        success = false;
        return Qt::FlatCap; //Default
    };
}

Qt::PenJoinStyle QStringToPenJoinStyle(const QString& penjoinstyle,bool& success)
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
        success = false;
        return Qt::MiterJoin; //Default
    };
}

Qt::BrushStyle QStringToBrushStyle(const QString& brushstyle,bool& success)
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
        success = false;
        return Qt::NoBrush; //Default
    };
}

Qt::AlignmentFlag QStringToAlignmentFlag(const QString& alignmentflag,bool& success)
{
    switch(ALIGNMENTFLAG_LIST.indexOf(alignmentflag))
        //const QStringList ALIGNMENTFLAG_LIST = {"AlignLeft","AlignRight","AlignTop","AlignBottom","AlignCenter"};
    {
    case 0:
        return Qt::AlignLeft;
    case 1:
        return Qt::AlignRight;
    case 2:
        return Qt::AlignTop;
    case 3:
        return Qt::AlignBottom;
    case 4:
        return Qt::AlignCenter;
    default:
        success = false;
        return Qt::AlignCenter; //Default
    };
}

QFont::Style QStringToQFontStyle(const QString& qfontstyle,bool& success)
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
        success = false;
        return QFont::StyleNormal; //Default
    };
}

QFont::Weight QStringToQFontWeight(const QString& qfontweight,bool& success)
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
        success = false;
        return QFont::Normal; //Default
    };
}


void MainWindow::on_actionTestimonials_triggered()
{
    Testimonials -> show();
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shapemaster.h"
#include "vector.h"
#include "parserexception.h"
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <string>
#include <QRegularExpression>

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
void writeShapesToFile(QTextStream& file, const vector<Shape*> &shapes);
void printPolyshapeDataToFile(QTextStream& file, PolyShape* polyshape);
void printTextShapeDataToFile(QTextStream& file, Text* text);
string colorToString(const Qt::GlobalColor& color);
string penJoinStyleToString(const Qt::PenJoinStyle& penJoinStyleEnum);
string penCapStyleToString(const Qt::PenCapStyle& capStyle);
string penStyleToString(const Qt::PenStyle& penStyleEnum);
string brushStyleToString(const Qt::BrushStyle& brushStyle);
string textAlignToString(const Qt::AlignmentFlag& alignment);
string textStyleToString(const QFont::Style& style);
string textWeightToString(const QFont::Weight& weight);


/******************** Main Window Constructor ********************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    needsSave(false),
    ui(new Ui::MainWindow),
    addLineWindow(nullptr),
    addPolylineWindow(nullptr),
    addPolygonWindow(nullptr),
    addRectangleWindow(nullptr),
    addEllipseWindow(nullptr),
    addTextWindow(nullptr)
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
        int result = savePrompt.exec();

        if(result == QMessageBox::Save)
        {
            on_actionSave_triggered();
        }
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
                    shapeTypeIndex = SHAPE_LIST.indexOf(shapeType);


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

                    if(((shapeTypeIndex == 4 || shapeTypeIndex == 6) && (dimensionsList.size()%2 == 0)) ||
                       ((shapeTypeIndex != 4 && shapeTypeIndex != 6) && (dimensionsList.size()%2 == 1)))
                    {
                        throw ParserException("One of the shapes has an invalid number of dimensions.");
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

                    if(shapeTypeIndex == 0 || shapeTypeIndex == 1)
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
                    else if(shapeTypeIndex == 7)
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
                        throw ParserException("One of the shape properties are invalid.");
                    }


                    //Create new derived shapes, then place them into a vector
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
                        throw ParserException("One of the shapes is of an invalid type.");
                    };

                    newObjects.push_back(shapePtr);
                }

                //Renders the objects on the canvas and sets the path.
                renderArea->SetShapes(newObjects);
                currentFilePath = filePath;
                setWindowTitle(file.fileName());

                statusBar()->showMessage("Successfully opened file.");
                file.close();
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
            //(Iterate through the instance datamember of 'currentShapes' (vector of Shape*))
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
        }

    }
}


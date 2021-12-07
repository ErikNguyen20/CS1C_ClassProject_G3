#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shapemaster.h"
#include "vector.h"
#include "parserexception.h"
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <unordered_map>

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
    needsSave(false),
    ui(new Ui::MainWindow)
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
    Testimonials = new testimonials();
    Testimonials -> show();
}


void MainWindow::on_actionContact_Us_triggered()
{
    ContactUs -> show();
}

/******************** Write Shape Vector to Save File Function Definitions ********************/

// helper functions
//-----------writing functions--------------------
void printPolyshapeDataToFile(QTextStream& file, Polyshape* polyshape)
{
	file << "PenColor: " << QString::fromStdString(colorToStringMap[polyshape->getPenColor()]) << endl;
	file << "PenWidth: " << polyshape->getPenWidth() << endl;
	file << "PenStyle: " << QString::fromStdString(penStyleToString(polyshape->getPenStyle())) << endl;
	file << "PenCapStyle: " << QString::fromStdString(penCapStyleToString(polyshape->getPenCapStyle())) << endl;
	file << "PenJoinStyle: " << QString::fromStdString(penJoinStyleToString(polyshape->getPenJoinStyle())) << endl;
}

void printTextShapeDataToFile(QTextStream& file, Text* text)
{
	file << "TextString: " << text->getTextString() << endl;
	file << "TextColor: " << QString::fromStdString(colorToStringMap[text->getTextColor()]) << endl;
	file << "TextAlignment: " << QString::fromStdString(textAlignToString(text->getTextAlign())) << endl;
	file << "TextPointSize: " << text->getTextPointSize() << endl;
	file << "TextFontFamily: " << text->getTextFontFam() << endl;
	file << "TextFontStyle: " << QString::fromStdString(textStyleToString(text->getTextFontStyle())) << endl;
	file << "TextFontWeight: " << QString::fromStdString(textFontWeightToString(text->getTextFontWeight())) << endl;
}

//-------------conversion functions------------------
void buildColorToStringMap(unorderd_map<Qt::GlobalColor, string> &umap)
{
	umap[Qt::white]="white";
	umap[Qt::black]="black";
	umap[Qt::red]="red";
	umap[Qt::green]="green";
	umap[Qt::blue]="blue";
	umap[Qt::cyan]="cyan";
	umap[Qt::magenta]="magenta";
	umap[Qt::yellow]="yellow";
	umap[Qt::gray]="gray";
}


string penJoinStyleToString(const Qt::PenJoinStyle& penJoinStyleEnum)
{
	switch (penJoinStyleEnum)
	{
		case Qt::MiterJoin:
			return "MiterJoin";
		case Qt::BevelJoin:
			return "BevelJoin";
		case Qt::RoundJoin:
			return "RoundJoin";
	}
}

string penCapStyleToString(const Qt::PenCapStyle& capStyle)
{
	switch (capStyle)
	{
		case Qt::FlatCap:
			return "FlatCap";
		case Qt::RoundCap:
			return "RoundCap";
		case Qt::SquareCap:
			return "SquareCap";
	}
}

string penStyleToString(const Qt::PenStyle& penStyleEnum)
{
	switch(penStyleEnum)
	{
		case Qt::NoPen:
			return "NoPen";
		case Qt::SolidLine:
			return "SolidLine";
		case Qt::DashLine:
			return "DashLine";
		case Qt::DotLine:
			return "DotLine";
		case Qt::DashDotLine:
			return "DashDotLine";
		case Qt::DashDotDotLine:
			return "DashDotDotLine";
	}
}

string brushStyleToString(const Qt::BrushStyle& brushStyle)
{
	switch (brushStyle)
	{
		case Qt::SolidPattern:
		return "SolidPattern";
		case Qt::HorPattern:
		return "HorPattern";
		case Qt::VerPattern:
		return "VerPattern";
		case Qt::NoBrush:
		return "NoBrush";
	}
}

string textAlignToString(const Qt::AlignmentFlag& alignment)
{
	switch (alignment)
	{
		case Qt::AlignLeft:
		return "AlignLeft";
		case Qt::AlignTop:
		return "AlignTop";
		case Qt::AlignRight:
		return "AlignRight";
		case Qt::AlignBottom:
		return "AlignBottom";
		case Qt::AlignCenter:
		return "AlignCenter";
	}
}

string textStyleToString(const Qt::Style& style)
{
	switch (style)
	{
		case Qt::StyleNormal:
		return "StyleNormal";
		case Qt::StyleItalic:
		return "StyleItalic";
		case Qt::StyleOblique:
		return "StyleOblique";
	}
}

string textWeightToString(const Qt::Weight& weight)
{
	switch (weight)
	{
		case Qt::Normal: return "Normal";
		case Qt::Bold: return "Bold";
		case Qt::Italic: return "Italic";
		case Qt::Thin: return "Thin";
		case Qt::Light: return "Light";
	}
}

// primary file writing function
void writeShapesToFile(QTextStream& file, const vector<Shape*> &shapes)
{
	Shape* currShape;
	
	unorderd_map<Qt::GlobalColor, string> colorToStringMap;
	buildColorToStringMap(colorToStringMap);

	// print all shapes to file
	for(int i = 0; i < shapes.size(); ++i)
	{
		currShape = shapes[i];
		
		// determine shape type
		string shapeTypeString = currShape->getShapeTypeString();
		
		// begin writing to file
		file << "ShapeId: " << currShape->getID() << endl;
		file << "ShapeType: ";
	
		if(shapeTypeString == "Line")
		{
			Line* line = (Line*)currShape;

			file << QString::fromStdString(shapeTypeString) << endl;

			file << "ShapeDimensions: " << line->getStartPoint().x() << ", " << line->getStartPoint().y() << ", "
					<<  line->endPoint.x() << ", " << line->endPoint.y() << endl;

			printPolyshapeDataToFile(file, (Polyshape*)currShape);

			file << endl;		
		}
		else if(shapeTypeString == "Polyline")
		{
			Polyline* polyline = (Polyline*)currShape;

			file << QString::fromStdString(shapeTypeString) << endl;

			file << "ShapeDimensions: ";

			// print polyline points
			vector<QPoint> points = polyline->getPoints();
			int count = polyline->getPointCount();
			for(int i = 0; i < count; i++)
			{
				file << points[i].x() << ", " << points[i].y;

				if(i < count - 1)
					file << ", ";
				else
					file << endl;
			}
			
			printPolyshapeDataToFile(file, (Polyshape*)currShape);

			file << endl;
		}
		else if(shapeTypeString == "Polygon")
		{
			Polygon* shape = (Polygon*)currShape;

			file << QString::fromStdString(shapeTypeString) << endl;

			file << "ShapeDimensions: ";

			// print polygon points
			vector<QPoint> points = shape->getPoints();
			int count = shape->getPointCount();
			for(int i = 0; i < count; i++)
			{
				file << points[i].x() << ", " << points[i].y;

				if(i < count - 1)
					file << ", ";
				else
					file << endl;
			}
			
			printPolyshapeDataToFile(file, (Polyshape*)currShape);

			file << "BrushColor: " << QString::fromStdString(colorToStringMap[polyshape->getBrushColor()]) << endl;
			file << "BrushStyle: " << QString::fromStdString(brushStyleToString(shape->getBrushStyle())) << endl;

			file << endl;
		}
		else if(shapeTypeString == "Rectangle")
		{
			Recangle* shape = (Rectangle*)currShape;

			file << QString::fromStdString(shapeTypeString) << endl;

			file << "ShapeDimensions: " << shape->getOrigin().x() << "," << shape->getOrigin().y() << ", " << shape->getLength() << ", " << shape->getWidth() << endl;
			
			printPolyshapeDataToFile(file, (Polyshape*)currShape);

			file << "BrushColor: " << QString::fromStdString(colorToStringMap[polyshape->getBrushColor()]) << endl;
			file << "BrushStyle: " << QString::fromStdString(brushStyleToString(shape->getBrushStyle())) << endl;

			file << endl;
		}
		else if (shapeTypeString == "Square")
		{
			Recangle* shape = (Rectangle*)currShape;

			file << QString::fromStdString(shapeTypeString) << endl;

			file << "ShapeDimensions: " << shape->getOrigin().x() << "," << shape->getOrigin().y() << ", " << shape->getLength() << endl;
			
			printPolyshapeDataToFile(file, (Polyshape*)currShape);

			file << "BrushColor: " << QString::fromStdString(colorToStringMap[polyshape->getBrushColor()]) << endl;
			file << "BrushStyle: " << QString::fromStdString(brushStyleToString(shape->getBrushStyle())) << endl;

			file << endl;
		}
		else if(shapeTypeString == "Ellipse")
		{
			Ellipse* shape = (Ellipse*)currShape;

			file << QString::fromStdString(shapeTypeString) << endl;

			file << "ShapeDimensions: " << shape->getOrigin().x() << "," << shape->getOrigin().y() << ", " << shape->getSemiMajor() << ", " << shape->getSemiMinor() << endl;
			
			printPolyshapeDataToFile(file, (Polyshape*)currShape);

			file << "BrushColor: " << QString::fromStdString(colorToStringMap[polyshape->getBrushColor()]) << endl;
			file << "BrushStyle: " << QString::fromStdString(brushStyleToString(shape->getBrushStyle())) << endl;

			file << endl;
		}
		else if(shapeTypeString == "Circle")
		{
			Ellipse* shape = (Ellipse*)currShape;

			file << QString::fromStdString(shapeTypeString) << endl;

			file << "ShapeDimensions: " << shape->getOrigin().x() << "," << shape->getOrigin().y() << ", " << shape->getSemiMajor() << endl;
			
			printPolyshapeDataToFile(file, (Polyshape*)currShape);

			file << "BrushColor: " << QString::fromStdString(colorToStringMap[polyshape->getBrushColor()]) << endl;
			file << "BrushStyle: " << QString::fromStdString(brushStyleToString(shape->getBrushStyle())) << endl;

			file << endl;
		}
		else if(shapeTypeString == "Text")
		{
			Text* shape = (Text*)currShape;

			file << QString::fromStdString(shapeTypeString) << endl;

			file << "ShapeDimensions: " << shape->getOrigin().x() << "," << shape->getOrigin().y() << ", " << shape->getLength() << ", " << shape->getWidth() << endl;

			printPolyshapeDataToFile(file, (Text*)currShape);

			file << endl;
		}
	}
}
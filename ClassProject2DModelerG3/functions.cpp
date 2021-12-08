#include "functions.h"


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


/******************** Write Shape Vector to Save File Function Definitions ********************/

// helper functions
//-----------writing functions--------------------
void printPolyshapeDataToFile(QTextStream& file, PolyShape* polyshape)
{
    file << "PenColor: " << colorToString(polyshape->getPenColor()) << '\n';
    file << "PenWidth: " << polyshape->getPenWidth() << '\n';
    file << "PenStyle: " << penStyleToString(polyshape->getPenStyle()) << '\n';
    file << "PenCapStyle: " << penCapStyleToString(polyshape->getPenCapStyle()) << '\n';
    file << "PenJoinStyle: " << penJoinStyleToString(polyshape->getPenJoinStyle()) << '\n';
}

void printTextShapeDataToFile(QTextStream& file, Text* text)
{
    file << "TextString: " << text->getTextString() << '\n';
    file << "TextColor: " << colorToString(text->getTextColor()) << '\n';
    file << "TextAlignment: " << textAlignToString(text->getTextAlign()) << '\n';
    file << "TextPointSize: " << text->getTextPointSize() << '\n';
    file << "TextFontFamily: " << text->getTextFontFam() << '\n';
    file << "TextFontStyle: " << textStyleToString(text->getTextFontStyle()) << '\n';
    file << "TextFontWeight: " << textWeightToString(text->getTextFontWeight()) << '\n';
}

//-------------conversion functions------------------

QString colorToString(const Qt::GlobalColor& color)
{
    switch (color)
    {
        case Qt::white: return "white";
        case Qt::black: return "black";
        case Qt::red: return "red";
        case Qt::green: return "green";
        case Qt::blue: return "blue";
        case Qt::cyan: return "cyan";
        case Qt::magenta: return "magenta";
        case Qt::yellow: return "yellow";
        case Qt::gray: return "gray";
        default: return "white";
    };
}

QString penJoinStyleToString(const Qt::PenJoinStyle& penJoinStyleEnum)
{
    switch (penJoinStyleEnum)
    {
        case Qt::MiterJoin:
            return "MiterJoin";
        case Qt::BevelJoin:
            return "BevelJoin";
        case Qt::RoundJoin:
            return "RoundJoin";
        default: return "MiterJoin";
    };
}

QString penCapStyleToString(const Qt::PenCapStyle& capStyle)
{
    switch (capStyle)
    {
        case Qt::FlatCap:
            return "FlatCap";
        case Qt::RoundCap:
            return "RoundCap";
        case Qt::SquareCap:
            return "SquareCap";
        default: return "FlatCap";
    };
}

QString penStyleToString(const Qt::PenStyle& penStyleEnum)
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
        default: return "NoPen";
    };
}

QString brushStyleToString(const Qt::BrushStyle& brushStyle)
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
        default: return "SolidPattern";
    };
}

QString textAlignToString(const Qt::AlignmentFlag& alignment)
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
        default: return "AlignLeft";
    };
}

QString textStyleToString(const QFont::Style& style)
{
    switch (style)
    {
        case QFont::StyleNormal:
        return "StyleNormal";
        case QFont::StyleItalic:
        return "StyleItalic";
        case QFont::StyleOblique:
        return "StyleOblique";
        default: return "StyleNormal";
    };
}

QString textWeightToString(const QFont::Weight& weight)
{
    switch (weight)
    {
        case QFont::Normal: return "Normal";
        case QFont::Bold: return "Bold";
        case QFont::Thin: return "Thin";
        case QFont::Light: return "Light";
        default: return "Normal";
    };
}


void readShapesFromFile(QTextStream& iFile,vector<Shape*> &newObjects) throw(ParserException)
{
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
}

// primary file writing function
void writeShapesToFile(QTextStream& file, const vector<Shape*> &shapes)
{
    Shape* currShape;

    // print all shapes to file
    for(int i = 0; i < shapes.size(); ++i)
    {
        currShape = shapes[i];

        // determine shape type
        QString shapeTypeString = currShape->getShapeStypeString();

        // begin writing to file
        file << "ShapeId: " << currShape->getID() << '\n';
        file << "ShapeType: ";

        if(shapeTypeString == "Line")
        {
            Line* line = (Line*)currShape;

            file << shapeTypeString << '\n';

            file << "ShapeDimensions: " << line->getStartPoint().x() << ", " << line->getStartPoint().y() << ", "
                    <<  line->getEndPoint().x() << ", " << line->getEndPoint().y() << '\n';

            printPolyshapeDataToFile(file, (PolyShape*)currShape);

            file << '\n';
        }
        else if(shapeTypeString == "Polyline")
        {
            Polyline* polyline = (Polyline*)currShape;

            file << shapeTypeString << '\n';

            file << "ShapeDimensions: ";

            // print polyline points
            vector<QPoint> points = polyline->getPoints();
            int count = polyline->getPointCount();
            for(int i = 0; i < count; i++)
            {
                file << points[i].x() << ", " << points[i].y();

                if(i < count - 1)
                    file << ", ";
                else
                    file << '\n';
            }

            printPolyshapeDataToFile(file, (PolyShape*)currShape);

            file << '\n';
        }
        else if(shapeTypeString == "Polygon")
        {
            Polygon* shape = (Polygon*)currShape;

            file << shapeTypeString << '\n';

            file << "ShapeDimensions: ";

            // print polygon points
            vector<QPoint> points = shape->getPoints();
            int count = shape->getPointCount();
            for(int i = 0; i < count; i++)
            {
                file << points[i].x() << ", " << points[i].y();

                if(i < count - 1)
                    file << ", ";
                else
                    file << '\n';
            }

            printPolyshapeDataToFile(file, (PolyShape*)currShape);

            file << "BrushColor: " << colorToString(shape->getBrushColor()) << '\n';
            file << "BrushStyle: " << brushStyleToString(shape->getBrushStyle()) << '\n';

            file << '\n';
        }
        else if(shapeTypeString == "Rectangle")
        {
            Rectangle* shape = (Rectangle*)currShape;

            file << shapeTypeString << '\n';

            file << "ShapeDimensions: " << shape->getOrigin().x() << "," << shape->getOrigin().y() << ", " << shape->getLength() << ", " << shape->getWidth() << '\n';

            printPolyshapeDataToFile(file, (PolyShape*)currShape);

            file << "BrushColor: " << colorToString(shape->getBrushColor()) << '\n';
            file << "BrushStyle: " << brushStyleToString(shape->getBrushStyle()) << '\n';

            file << '\n';
        }
        else if (shapeTypeString == "Square")
        {
            Rectangle* shape = (Rectangle*)currShape;

            file << shapeTypeString << '\n';

            file << "ShapeDimensions: " << shape->getOrigin().x() << "," << shape->getOrigin().y() << ", " << shape->getLength() << '\n';

            printPolyshapeDataToFile(file, (PolyShape*)currShape);

            file << "BrushColor: " << colorToString(shape->getBrushColor()) << '\n';
            file << "BrushStyle: " << brushStyleToString(shape->getBrushStyle()) << '\n';

            file << '\n';
        }
        else if(shapeTypeString == "Ellipse")
        {
            Ellipse* shape = (Ellipse*)currShape;

            file << shapeTypeString << '\n';

            file << "ShapeDimensions: " << shape->getOrigin().x() << "," << shape->getOrigin().y() << ", " << shape->getSemiMajor() << ", " << shape->getSemiMinor() << '\n';

            printPolyshapeDataToFile(file, (PolyShape*)currShape);

            file << "BrushColor: " << colorToString(shape->getBrushColor()) << '\n';
            file << "BrushStyle: " << brushStyleToString(shape->getBrushStyle()) << '\n';

            file << '\n';
        }
        else if(shapeTypeString == "Circle")
        {
            Ellipse* shape = (Ellipse*)currShape;

            file << shapeTypeString << '\n';

            file << "ShapeDimensions: " << shape->getOrigin().x() << "," << shape->getOrigin().y() << ", " << shape->getSemiMajor() << '\n';

            printPolyshapeDataToFile(file, (PolyShape*)currShape);

            file << "BrushColor: " << colorToString(shape->getBrushColor()) << '\n';
            file << "BrushStyle: " << brushStyleToString(shape->getBrushStyle()) << '\n';

            file << '\n';
        }
        else if(shapeTypeString == "Text")
        {
            Text* shape = (Text*)currShape;

            file << shapeTypeString << '\n';

            file << "ShapeDimensions: " << shape->getOrigin().x() << "," << shape->getOrigin().y() << ", " << shape->getLength() << ", " << shape->getWidth() << '\n';

            printTextShapeDataToFile(file, (Text*)currShape);

            file << '\n';
        }
    }
}

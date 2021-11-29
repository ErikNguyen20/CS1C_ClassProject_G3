/********************************************************************/
/*                          SHAPES.CPP                              */
/********************************************************************/
/* This source files contains class definitions for all Shape-based */
/* classes.  The only functions not defined here are move() and     */
/* draw(), which are included in shapemanip.cpp, since they are     */
/* directly manipulaing the object from within the 2D rendering     */
/* program.                                                         */
/********************************************************************/
/* A diagram showing inheritance has been included below:           */
/*                                                                  */
/*                           Shape                                  */
/*                             |-------------------------|          */
/*                         PolyShape                   Text         */
/*           |-----------------|-----------|                        */
/*      OriginBasedShape    Polyline      Line                      */
/*       |---|---------|       |                                    */
/*  Rectangle      Ellipse  Polygon                                 */
/*      |             |                                             */
/*   Square        Circle                                           */
/*                                                                  */
/********************************************************************/

#include "shapes.h"

/********************************************************************/
/*                    BASIC FUNCTION DEFINITIONS                    */
/********************************************************************/


double DistanceBetween(const QPoint a, const QPoint b)
{
    return sqrt( pow((b.x() - a.x()), 2) + pow((b.y() - a.y()), 2) );
}

/********************************************************************/
/*                     BACKEND CLASS DEFINITIONS                    */
/********************************************************************/

/******************** SHAPE CLASS CODE ********************/

Shape::Shape() : shapeID(0) {}

Shape::Shape(int id) : shapeID(id) {}

Shape::~Shape() {}

int Shape::getID() const
{ return shapeID; }

void Shape::setID(int num)
{ shapeID = num; }

bool Shape::operator== (const Shape& compare) const
{
    if(shapeID == compare.getID())
    { return true; }
    else
    { return false; }
}

bool Shape::operator< (const Shape& compare) const
{
    if(shapeID < compare.getID())
    { return true; }
    else
    { return false; }
}


/******************** POLYSHAPE CLASS CODE ********************/

PolyShape::PolyShape() : Shape(), penColor(Qt::white), penWidth(0), penStyle(Qt::NoPen),
                         penCapStyle(Qt::FlatCap), penJoinStyle(Qt::MiterJoin),
                         brushColor(Qt::white), brushStyle(Qt::SolidPattern) {}

PolyShape::PolyShape(Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle)
    : penColor(penColor), penWidth(penWidth), penStyle(penStyle),
      penCapStyle(penCapStyle), penJoinStyle(penJoinStyle) {}

PolyShape::PolyShape(Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : penColor(penColor), penWidth(penWidth), penStyle(penStyle),
      penCapStyle(penCapStyle), penJoinStyle(penJoinStyle),
      brushColor(brushColor), brushStyle(brushStyle) {}

PolyShape::~PolyShape() {}

void PolyShape::setPenColor(Qt::GlobalColor color)
{ penColor = color; }

void PolyShape::setPenWidth(int width)
{ penWidth = width; }

void PolyShape::setPenStyle(Qt::PenStyle style)
{ penStyle = style; }

void PolyShape::setPenCapStyle(Qt::PenCapStyle style)
{ penCapStyle = style; }

void PolyShape::setPenJoinStyle(Qt::PenJoinStyle style)
{ penJoinStyle = style; }

void PolyShape::setBrushColor(Qt::GlobalColor color)
{ brushColor = color; }

void PolyShape::setBrushStyle(Qt::BrushStyle style)
{ brushStyle = style; }

Qt::GlobalColor PolyShape::getPenColor() const
{ return penColor; }

int PolyShape::getPenWidth() const
{ return penWidth; }

Qt::PenStyle PolyShape::getPenStyle() const
{ return penStyle; }

Qt::PenCapStyle PolyShape::getPenCapStyle() const
{ return penCapStyle; }

Qt::PenJoinStyle PolyShape::getPenJoinStyle() const
{ return penJoinStyle; }

Qt::GlobalColor PolyShape::getBrushColor() const
{ return brushColor; }

Qt::BrushStyle PolyShape::getBrushStyle() const
{ return brushStyle; }


/******************** ORIGINBASEDSHAPE CLASS CODE ********************/

OriginBasedShape::OriginBasedShape() : PolyShape(), origin{0, 0} {}

OriginBasedShape::OriginBasedShape(QPoint origin, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : PolyShape(penColor,penWidth,penStyle,penCapStyle,penJoinStyle,brushColor,brushStyle), origin(origin) {}

OriginBasedShape::~OriginBasedShape() {}

void OriginBasedShape::setOrigin(QPoint newOrigin)
{ origin = newOrigin; }

QPoint OriginBasedShape::getOrigin() const
{ return origin; }


/********************************************************************/
/*                    FRONTEND CLASS DEFINITIONS                    */
/********************************************************************/

/******************** LINE CLASS CODE ********************/

Line::Line() : PolyShape(), startPoint{0, 0}, endPoint{0, 0} {}

Line::Line(int id, QPoint start, QPoint end) : PolyShape(), startPoint(start), endPoint(end)
{ setID(id); }

Line::Line(int id, QPoint start, QPoint end, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle)
    : PolyShape(penColor,penWidth,penStyle,penCapStyle,penJoinStyle), startPoint(start), endPoint(end)
{ setID(id); }

Line::~Line() {}

void Line::setPonts(QPoint start, QPoint end)
{ startPoint = start; endPoint = end; }

void Line::setStartPoint(QPoint start)
{ startPoint = start; }

void Line::setEndPoint(QPoint end)
{ endPoint = end; }

QPoint Line::getStartPoint() const
{ return startPoint; }

QPoint Line::getEndPoint() const
{ return endPoint; }

double Line::perimeter() const
{
   return DistanceBetween(startPoint, endPoint);
}

double Line::area() const { return 0; }


/******************** POLYLINE CLASS CODE ********************/

Polyline::Polyline() : PolyShape(), pointCount(0)
{ pointVector.reserve(2); }

Polyline::Polyline(int id, vector<QPoint>& points, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle)
    : PolyShape(penColor,penWidth,penStyle,penCapStyle,penJoinStyle), pointVector(std::move(points))
{
    setID(id);
    pointCount = pointVector.size();
}

Polyline::Polyline(int id, vector<QPoint>& points, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : PolyShape(penColor,penWidth,penStyle,penCapStyle,penJoinStyle,brushColor,brushStyle), pointVector(std::move(points))
{
    setID(id);
    pointCount = pointVector.size();
}

Polyline::~Polyline() {}

void Polyline::addPoint(QPoint add)
{
    pointVector.push_back(add);
    pointCount++;
}

void Polyline::removePoint()
{
    if(pointVector.size() > 0)
    {
        pointVector.erase(pointVector.end());
        pointCount--;
    }
}

double Polyline::perimeter() const
{
    double perimeter = 0;
    for(int count = 0; count < pointCount - 1; count++)
    { perimeter += DistanceBetween(pointVector[count], pointVector[count + 1]); }
    return perimeter;
}

double Polyline::area() const { return 0; }

vector<QPoint> Polyline::getPoints() const
{ return pointVector; }

int Polyline::getPointCount() const
{ return pointCount; }


/******************** POLYGON CLASS CODE ********************/

Polygon::Polygon() : Polyline() {}

Polygon::Polygon(int id, vector<QPoint>& points, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : Polyline(id,points,penColor,penWidth,penStyle,penCapStyle,penJoinStyle,brushColor,brushStyle) {}

Polygon::~Polygon() {}

double Polygon::perimeter() const
{
    double perimeter = 0;
    for(int count = 0; count < pointCount - 1; count++)
    { perimeter += DistanceBetween(pointVector[count], pointVector[count + 1]); }
    perimeter += DistanceBetween(pointVector[pointCount - 1], pointVector[0]);
    return perimeter;
}

double Polygon::area() const
{
    double area = 0;
    for(int count = 0; count < pointCount - 1; count++)
    {
      area += ( pointVector[count].x() * pointVector[count + 1].y() )
              - ( pointVector[count + 1].x() * pointVector[count].y() );
    }
    area += ( pointVector[pointCount - 1].x() * pointVector[0].y() )
            - ( pointVector[0].x() * pointVector[pointCount - 1].y() );
    area = abs(area) / 2;
    return area;
}


/******************** RECTANGLE CLASS CODE ********************/

Rectangle::Rectangle() : OriginBasedShape(), length(0), width(0) {}

Rectangle::Rectangle(int id, QPoint origin, int length, int width, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : OriginBasedShape(origin, penColor,penWidth,penStyle,penCapStyle,penJoinStyle,brushColor,brushStyle), length(length), width(width)
{
    setID(id);
}

Rectangle::~Rectangle() {}

void Rectangle::setLength(int l)
{ length = l; }

void Rectangle::setWidth(int w)
{ width = w; }

int Rectangle::getLength() const
{ return length; }

int Rectangle::getWidth() const
{ return width; }

double Rectangle::perimeter() const
{ return length + length + width + width; }

double Rectangle::area() const
{ return length * width; }


/******************** SQUARE CLASS CODE ********************/

Square::Square() : Rectangle() {}

Square::Square(int id, QPoint origin, int length, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : Rectangle(id, origin, length, length, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, brushColor, brushStyle) {}

Square::~Square() {}

void Square::setLength(int l)
{ length = l; width = length; }

void Square::setWidth(int w)
{ width = w; length = width; }


/******************** ELLIPSE CLASS CODE ********************/

Ellipse::Ellipse() : OriginBasedShape(), a(0), b(0) {}

Ellipse::Ellipse(int id, QPoint origin, int a, int b, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : OriginBasedShape(origin, penColor,penWidth,penStyle,penCapStyle,penJoinStyle,brushColor,brushStyle), a(a), b(b)
{
    setID(id);
}
Ellipse::~Ellipse() {}

void Ellipse::setSemiMajor(int semi)
{ a = semi; }

void Ellipse::setSemiMinor(int semi)
{ b = semi; }

int Ellipse::getSemiMajor() const
{ return a; }

int Ellipse::getSemiMinor() const
{ return b; }

double Ellipse::perimeter() const
{ return M_PI * a * b; }

double Ellipse::area() const
{ return 2 * M_PI * sqrt((a * a) + (b * b) / 2 ); }


/******************** CIRCLE CLASS CODE ********************/

Circle::Circle() : Ellipse() {}

Circle::Circle(int id, QPoint origin, int a, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : Ellipse(id, origin, a, a, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, brushColor, brushStyle) {}

Circle::~Circle() {}

void Circle::setSemiMajor(int semi)
{ a = semi; b = a; }

void Circle::setSemiMinor(int semi)
{ b = semi; a = b;}


/******************** TEXT CLASS CODE ********************/

Text::Text() : Shape(), origin{0, 0}, length(0), width(0), textString(""),
               textColor(Qt::white), textAlign(Qt::AlignLeft), textPointSize(0), textFontFam(""),
               textFontStyle(QFont::StyleNormal), textFontWeight(QFont::Thin) {}

Text::Text(QString text) : Shape(), origin{0, 0}, length(0), width(0), textString(text),
                           textColor(Qt::white), textAlign(Qt::AlignLeft), textPointSize(0), textFontFam(""),
                           textFontStyle(QFont::StyleNormal), textFontWeight(QFont::Thin) {}

Text::Text(int id, QPoint origin, int length, int width, QString textstring, Qt::GlobalColor textColor, Qt::AlignmentFlag textAlign, int textPointSize, QString textFontFam, QFont::Style textFontStyle, QFont::Weight textFontWeight)
    : origin(origin), length(length), width(width), textString(textstring),
      textColor(textColor), textAlign(textAlign), textPointSize(textPointSize), textFontFam(textFontFam),
      textFontStyle(textFontStyle), textFontWeight(textFontWeight)
{
    setID(id);
}

Text::~Text() {}

void Text::setOrigin(QPoint newOrigin)
{ origin = newOrigin; }

void Text::setLength(int l)
{ length = l; }

void Text::setWidth(int w)
{ width = w; }

void Text::setTextString(QString text)
{ textString = text; }

void Text::setTextColor(Qt::GlobalColor color)
{ textColor = color; }

void Text::setTextAlign(Qt::AlignmentFlag align)
{ textAlign = align; }

void Text::setTextPointSize(int size)
{ textPointSize = size; }

void Text::setTextFontFam(QString text)
{ textFontFam = text; }

void Text::setTextFontStyle(QFont::Style style)
{ textFontStyle = style; }

void Text::setTextFontWeight(QFont::Weight weight)
{ textFontWeight = weight; }

QPoint Text::getOrigin() const
{ return origin; }

int Text::getLength() const
{ return length; }

int Text::getWidth() const
{ return width; }

QString Text::getTextString() const
{ return textString; }

Qt::GlobalColor Text::getTextColor() const
{ return textColor; }

Qt::AlignmentFlag Text::getTextAlign() const
{ return textAlign; }

int Text::getTextPointSize() const
{ return textPointSize; }

QString Text::getTextFontFam() const
{ return textFontFam; }

QFont::Style Text::getTextFontStyle() const
{ return textFontStyle; }

QFont::Weight Text::getTextFontWeight() const
{ return textFontWeight; }

double Text::perimeter() const
{ return length + length + width + width; }

double Text::area() const
{ return length * width; }

#include "shapes.h"

/********** BASIC FUNCTION DEFINITIONS **********/

double DistanceBetween(const QPoint a, const QPoint b)
{
    return sqrt( pow((b.x() - a.x()), 2) + pow((b.y() - a.y()), 2) );
}


/********** BACKEND CLASS DEFINITIONS **********/

// SHAPE CLASS CODE

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

void Shape::draw() const {}
void Shape::move() const {}


// POLYSHAPE CLASS CODE
// Included in polyshape.cpp


// ORIGINBASEDSHAPE CLASS CODE

OriginBasedShape::OriginBasedShape() : PolyShape(), origin{0, 0} {}

OriginBasedShape::~OriginBasedShape() {}

void OriginBasedShape::setOrigin(QPoint newOrigin)
{ origin = newOrigin; }

QPoint OriginBasedShape::getOrigin() const
{ return origin; }


/********** FRONTEND CLASS DEFINITIONS **********/

// LINE CLASS CODE

Line::Line() : PolyShape(), startPoint{0, 0}, endPoint{0, 0} {}

Line::Line(int id, QPoint start, QPoint end) : PolyShape(), startPoint(start), endPoint(end)
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

void Line::draw() const {}
void Line::move() const {}
double Line::perimeter() const { return 0; }
double Line::area() const { return 0; }


// POLYLINE CLASS CODE

Polyline::Polyline() : PolyShape(), pointCount(0)
{ pointVector.reserve(2); }

Polyline::~Polyline() {}

void Polyline::addPoint(QPoint add)
{
    pointVector.push_back(add);
    pointCount++;
}

void Polyline::removePoint()
{
    if(!pointVector.isEmpty())
    {
        pointVector.pop_back();
        pointCount--;
    }
}

void Polyline::draw() const {}
void Polyline::move() const {}
double Polyline::perimeter() const { return 0; }
double Polyline::area() const { return 0; }

QVector<QPoint> Polyline::getPoints() const
{ return pointVector; }

int Polyline::getPointCount() const
{ return pointCount; }

// POLYGON CLASS CODE

Polygon::Polygon() : Polyline() {}
Polygon::~Polygon() {}

void Polygon::draw() const {}
void Polygon::move() const {}
double Polygon::perimeter() const { return 0; }
double Polygon::area() const { return 0; }


// RECTANGLE CLASS CODE

Rectangle::Rectangle() : OriginBasedShape(), length(0), width(0) {}

Rectangle::~Rectangle() {}

void Rectangle::setLength(int l)
{ length = l; }

void Rectangle::setWidth(int w)
{ width = w; }

double Rectangle::getLength() const
{ return length; }

double Rectangle::getWidth() const
{ return width; }

void Rectangle::draw() const {}
void Rectangle::move() const {}

double Rectangle::perimeter() const
{ return length + length + width + width; }

double Rectangle::area() const
{ return length * width; }


// SQUARE CLASS CODE

Square::Square() : Rectangle() {}

Square::~Square() {}

void Square::setLength(int l)
{ length = l; width = length; }

void Square::setWidth(int w)
{ width = w; length = width; }


// ELLIPSE CLASS CODE

Ellipse::Ellipse() : OriginBasedShape(), a(0), b(0) {}

Ellipse::~Ellipse() {}

void Ellipse::setSemiMajor(int semi)
{ a = semi; }

void Ellipse::setSemiMinor(int semi)
{ b = semi; }

double Ellipse::getSemiMajor() const
{ return a; }

double Ellipse::getSemiMinor() const
{ return b; }

void Ellipse::draw() const {}
void Ellipse::move() const {}

double Ellipse::perimeter() const
{ return M_PI * a * b; }

double Ellipse::area() const
{ return 2 * M_PI * sqrt((a * a) + (b * b) / 2 ); }


// CIRCLE CLASS CODE

Circle::Circle() : Ellipse() {}

Circle::~Circle() {}

void Circle::setSemiMajor(int semi)
{ a = semi; b = a; }

void Circle::setSemiMinor(int semi)
{ b = semi; a = b;}

// TEXT CLASS CODE
// Included in text.cpp


#include "shapes.h"

/********** BACKEND CLASS DEFINITIONS **********/

// SHAPE CLASS CODE

Shape::Shape() : shapeID(0) {}

Shape::Shape(int id) : shapeID(id) {}

Shape::Shape(const Shape &copy)
{ shapeID = copy.getID(); }

Shape::~Shape() {}

int Shape::getID() const
{ return shapeID; }

void Shape::setID(int num)
{ shapeID = num; }


// POLYSHAPE CLASS CODE
// Included in polyshape.cpp


// ORIGINBASEDSHAPE CLASS CODE

OriginBasedShape::OriginBasedShape() : PolyShape(), origin{0, 0} {}

OriginBasedShape::OriginBasedShape(const OriginBasedShape &copy) : PolyShape(copy), origin(copy.getOrigin()) {}

OriginBasedShape::~OriginBasedShape() {}

void OriginBasedShape::setOrigin(QPoint newOrigin)
{ origin = newOrigin; }

QPoint OriginBasedShape::getOrigin() const
{ return origin; }


/********** FRONTEND CLASS DEFINITIONS **********/

// LINE CLASS CODE

Line::Line() : PolyShape(), startPoint{0, 0}, endPoint{0, 0} {}

Line::Line(const Line &copy) : PolyShape(copy), startPoint(copy.getStartPoint()), endPoint(copy.getEndPoint()) {}

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


// POLYLINE CLASS CODE

Polyline::Polyline() : PolyShape(), pointCount(0)
{ pointVector.reserve(2); }

Polyline::Polyline(const Polyline &copy) : PolyShape(copy), pointVector(copy.getPoints()), pointCount(copy.getPointCount()) {}

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

QVector<QPoint> Polyline::getPoints() const
{ return pointVector; }

int Polyline::getPointCount() const
{ return pointCount; }

// POLYGON CLASS CODE

Polygon::Polygon() : Polyline() {}
Polygon::Polygon(const Polygon &copy) : Polyline(copy) {}
Polygon::~Polygon() {}


// RECTANGLE CLASS CODE

Rectangle::Rectangle() : OriginBasedShape(), length(0), width(0) {}

Rectangle::Rectangle(const Rectangle &copy) : OriginBasedShape(copy), length(copy.getLength()), width(copy.getWidth()) {}

Rectangle::~Rectangle() {}

void Rectangle::setLength(double l)
{ length = l; }

void Rectangle::setWidth(double w)
{ width = w; }

double Rectangle::getLength() const
{ return length; }

double Rectangle::getWidth() const
{ return width; }


// SQUARE CLASS CODE

Square::Square() : Rectangle() {}

Square::Square(const Square &copy) : Rectangle(copy) {}

Square::~Square() {}

void Square::setLength(double l)
{ length = l; width = length; }

void Square::setWidth(double w)
{ width = w; length = width; }


// ELLIPSE CLASS CODE

Ellipse::Ellipse() : OriginBasedShape(), a(0), b(0) {}

Ellipse::Ellipse(const Ellipse &copy) : OriginBasedShape(copy), a(copy.getSemiMajor()), b(copy.getSemiMinor()) {}

Ellipse::~Ellipse() {}

void Ellipse::setSemiMajor(double semi)
{ a = semi; }

void Ellipse::setSemiMinor(double semi)
{ b = semi; }

double Ellipse::getSemiMajor() const
{ return a; }

double Ellipse::getSemiMinor() const
{ return b; }


// CIRCLE CLASS CODE

Circle::Circle() : Ellipse() {}

Circle::Circle(const Circle &copy) : Ellipse(copy) {}

Circle::~Circle() {}

void Circle::setSemiMajor(double semi)
{ a = semi; b = a; }

void Circle::setSemiMinor(double semi)
{ b = semi; a = b;}

// TEXT CLASS CODE
// Included in text.cpp

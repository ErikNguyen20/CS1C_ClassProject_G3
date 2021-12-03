#include "_shape.h"

double DistanceBetween(const QPoint a, const QPoint b)
{
    return sqrt( pow((b.x() - a.x()), 2) + pow((b.y() - a.y()), 2) );
}

Shape::Shape() : shapeID(0) {}

Shape::Shape(int id) : shapeID(id) {}

Shape::~Shape() {}

int Shape::getID() const
{ return shapeID; }

void Shape::setID(int num)
{ shapeID = num; }

void Shape::setPainter(QPainter *p_painter)
{ qpainter = p_painter; }

QPainter* Shape::getPainter() const
{ return qpainter;}

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

// No draw() or move() function definitions for this class.

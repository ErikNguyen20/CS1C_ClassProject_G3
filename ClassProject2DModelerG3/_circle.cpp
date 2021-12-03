#include "_circle.h"

Circle::Circle() : Ellipse() {}

Circle::Circle(int id, QPoint origin, int a, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : Ellipse(id, origin, a, a, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, brushColor, brushStyle) {}

Circle::~Circle() {}

void Circle::setSemiMajor(int semi)
{ a = semi; b = a; }

void Circle::setSemiMinor(int semi)
{ b = semi; a = b;}

// Circle inherits Ellipse's move() and draw() functions.

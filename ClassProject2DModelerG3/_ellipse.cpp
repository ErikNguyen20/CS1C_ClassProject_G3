#include "_ellipse.h"

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

void Ellipse::draw() const
{
    QPen newPen;
    QBrush newBrush;
    newPen.setCapStyle(getPenCapStyle());
    newPen.setColor(getPenColor());
    newPen.setStyle(getPenStyle());
    newPen.setJoinStyle(getPenJoinStyle());
    newPen.setWidth(getPenWidth());

    newBrush.setColor(getBrushColor());
    newBrush.setStyle(getBrushStyle());

    getPainter()->setPen(newPen);
    getPainter()->setBrush(newBrush);
    getPainter()->drawEllipse(getOrigin(),getSemiMajor(),getSemiMinor());
}
// Move() function is defined by OriginBasedShape

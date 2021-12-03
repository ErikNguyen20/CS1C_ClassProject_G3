#include "_rectangle.h"

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

void Rectangle::draw() const
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
    getPainter()->drawRect(getOrigin().x(),getOrigin().y(),getLength(),getWidth());
}
// Move() function is defined by OriginBasedShape

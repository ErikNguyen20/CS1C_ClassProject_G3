#include "_line.h"

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

void Line::draw() const
{
    QPen newPen;

    newPen.setCapStyle(getPenCapStyle());
    newPen.setColor(getPenColor());
    newPen.setStyle(getPenStyle());
    newPen.setJoinStyle(getPenJoinStyle());
    newPen.setWidth(getPenWidth());

    getPainter()->setPen(newPen);
    getPainter()->drawLine(getStartPoint(), getEndPoint());
}

void Line::move(int deltaX, int deltaY)
{
    setStartPoint(QPoint(getStartPoint().x() + deltaX, getStartPoint().y() + deltaY));
    setEndPoint(QPoint(getEndPoint().x() + deltaX, getEndPoint().y() + deltaY));
}

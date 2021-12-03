#include "_polyline.h"

Polyline::Polyline() : PolyShape(), pointCount(0)
{ pointVector.reserve(2); }

Polyline::Polyline(int id, vector<QPoint> points, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle)
    : PolyShape(penColor,penWidth,penStyle,penCapStyle,penJoinStyle), pointVector(points)
{
    setID(id);
    pointCount = pointVector.size();
}

Polyline::Polyline(int id, vector<QPoint> points, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : PolyShape(penColor,penWidth,penStyle,penCapStyle,penJoinStyle,brushColor,brushStyle), pointVector(points)
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
        pointVector.erase(pointVector.end()-1);
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

void Polyline::draw() const
{
    QPen newPen;
    newPen.setCapStyle(getPenCapStyle());
    newPen.setColor(getPenColor());
    newPen.setStyle(getPenStyle());
    newPen.setJoinStyle(getPenJoinStyle());
    newPen.setWidth(getPenWidth());

    getPainter()->setPen(newPen);
    getPainter()->drawPolyline(pointVector.begin(),getPointCount());
}
void Polyline::move(int deltaX, int deltaY)
{
    for(int count = 0; count < pointCount; count++)
    {
        pointVector[count].setX(pointVector[count].x() + deltaX);
        pointVector[count].setY(pointVector[count].y() + deltaY);
    }
}

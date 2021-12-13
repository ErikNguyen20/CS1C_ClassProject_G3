#include "_polygon.h"

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

void Polygon::draw() const
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
    getPainter()->drawPolygon(pointVector.begin(), getPointCount());

    QString idName = "ID: " + QString::number(getID());
    getPainter()->setPen(Qt::black);
    getPainter()->drawText(pointVector[0].x(),(pointVector[1].y() - 15), 100, 50, Qt::AlignLeft, idName);
}
// Move() function is defined by Polyline

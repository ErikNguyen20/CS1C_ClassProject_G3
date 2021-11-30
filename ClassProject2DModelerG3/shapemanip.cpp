/********************************************************************/
/*                        SHAPEMANIP.CPP                            */
/********************************************************************/
/* This source files contains class definitions for move() and      */
/* draw() since they are directly manipulaing the object from       */
/* within the 2D rendering program.  Class definitions are included */
/* in shapes.cpp                                                    */
/********************************************************************/

#include "shapes.h"

/******************** SHAPE CLASS CODE ********************/

// No draw() or move() function definitions for this class.


/******************** POLYSHAPE CLASS CODE ********************/

// No draw() or move() function definitions for this class.


/******************** ORIGINBASEDSHAPE CLASS CODE ********************/

// Draw() functions are defined by the individual shape classes
void OriginBasedShape::move(int deltaX, int deltaY)
{
    setOrigin(QPoint(getOrigin().x() + deltaX, getOrigin().y() + deltaY));
}

/******************** LINE CLASS CODE ********************/

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


/******************** POLYLINE CLASS CODE ********************/

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


/******************** POLYGON CLASS CODE ********************/

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
}
// Move() function is defined by Polyline


/******************** RECTANGLE CLASS CODE ********************/

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


/******************** SQUARE CLASS CODE ********************/

// Square inherits Rectangle's move() and draw() functions.


/******************** ELLIPSE CLASS CODE ********************/

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


/******************** CIRCLE CLASS CODE ********************/

// Circle inherits Ellipse's move() and draw() functions.


/******************** TEXT CLASS CODE ********************/

void Text::draw() const
{
    QFont newFont;
    newFont.setFamily(getTextFontFam());
    newFont.setWeight(getTextFontWeight());
    newFont.setStyle(getTextFontStyle());
    newFont.setPointSize(getTextPointSize());

    getPainter()->setPen(getTextColor());
    getPainter()->setFont(newFont);

    getPainter()->drawText(getOrigin().x(),getOrigin().y(),getLength(),getWidth(),getTextAlign(),getTextString());
}
void Text::move(int deltaX, int deltaY)
{
    origin.setX(origin.x() + deltaX);
    origin.setY(origin.y() + deltaY);
}

#include "_originbasedshape.h"

OriginBasedShape::OriginBasedShape() : PolyShape(), origin{0, 0} {}

OriginBasedShape::OriginBasedShape(QPoint origin, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : PolyShape(penColor,penWidth,penStyle,penCapStyle,penJoinStyle,brushColor,brushStyle), origin(origin) {}

OriginBasedShape::~OriginBasedShape() {}

void OriginBasedShape::setOrigin(QPoint newOrigin)
{ origin = newOrigin; }

QPoint OriginBasedShape::getOrigin() const
{ return origin; }

// Draw() functions are defined by the individual shape classes
void OriginBasedShape::move(int deltaX, int deltaY)
{
    setOrigin(QPoint(deltaX, deltaY));
}

#include "_polyshape.h"

PolyShape::PolyShape() : Shape(), penColor(Qt::white), penWidth(0), penStyle(Qt::NoPen),
                         penCapStyle(Qt::FlatCap), penJoinStyle(Qt::MiterJoin),
                         brushColor(Qt::white), brushStyle(Qt::SolidPattern) {}

PolyShape::PolyShape(Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle)
    : penColor(penColor), penWidth(penWidth), penStyle(penStyle),
      penCapStyle(penCapStyle), penJoinStyle(penJoinStyle) {}

PolyShape::PolyShape(Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : penColor(penColor), penWidth(penWidth), penStyle(penStyle),
      penCapStyle(penCapStyle), penJoinStyle(penJoinStyle),
      brushColor(brushColor), brushStyle(brushStyle) {}

PolyShape::~PolyShape() {}

void PolyShape::setPenColor(Qt::GlobalColor color)
{ penColor = color; }

void PolyShape::setPenWidth(int width)
{ penWidth = width; }

void PolyShape::setPenStyle(Qt::PenStyle style)
{ penStyle = style; }

void PolyShape::setPenCapStyle(Qt::PenCapStyle style)
{ penCapStyle = style; }

void PolyShape::setPenJoinStyle(Qt::PenJoinStyle style)
{ penJoinStyle = style; }

void PolyShape::setBrushColor(Qt::GlobalColor color)
{ brushColor = color; }

void PolyShape::setBrushStyle(Qt::BrushStyle style)
{ brushStyle = style; }

Qt::GlobalColor PolyShape::getPenColor() const
{ return penColor; }

int PolyShape::getPenWidth() const
{ return penWidth; }

Qt::PenStyle PolyShape::getPenStyle() const
{ return penStyle; }

Qt::PenCapStyle PolyShape::getPenCapStyle() const
{ return penCapStyle; }

Qt::PenJoinStyle PolyShape::getPenJoinStyle() const
{ return penJoinStyle; }

Qt::GlobalColor PolyShape::getBrushColor() const
{ return brushColor; }

Qt::BrushStyle PolyShape::getBrushStyle() const
{ return brushStyle; }

// No draw() or move() function definitions for this class.

#include "shapes.h"

// POLYSHAPE CLASS CODE

PolyShape::PolyShape() : Shape(), penColor(white), penWidth(0), penStyle(NoPen),
                         penCapStyle(FlatCap), penJoinStyle(MiterJoin),
                         brushColor(white), brushStyle(SolidPattern) {}

PolyShape::~PolyShape() {}

void PolyShape::setPenColor(GlobalColor color)
{ penColor = color; }

void PolyShape::setPenWidth(int width)
{ penWidth = width; }

void PolyShape::setPenStyle(PenStyle style)
{ penStyle = style; }

void PolyShape::setPenCapStyle(PenCapStyle style)
{ penCapStyle = style; }

void PolyShape::setPenJoinStyle(PenJoinStyle style)
{ penJoinStyle = style; }

void PolyShape::setBrushColor(GlobalColor color)
{ brushColor = color; }

void PolyShape::setBrushStyle(BrushStyle style)
{ brushStyle = style; }

GlobalColor PolyShape::getPenColor() const
{ return penColor; }

int PolyShape::getPenWidth() const
{ return penWidth; }

PenStyle PolyShape::getPenStyle() const
{ return penStyle; }

PenCapStyle PolyShape::getPenCapStyle() const
{ return penCapStyle; }

PenJoinStyle PolyShape::getPenJoinStyle() const
{ return penJoinStyle; }

GlobalColor PolyShape::getBrushColor() const
{ return brushColor; }

BrushStyle PolyShape::getBrushStyle() const
{ return brushStyle; }


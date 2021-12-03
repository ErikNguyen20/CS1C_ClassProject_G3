#include "_square.h"

Square::Square() : Rectangle() {}

Square::Square(int id, QPoint origin, int length, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle)
    : Rectangle(id, origin, length, length, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, brushColor, brushStyle) {}

Square::~Square() {}

void Square::setLength(int l)
{ length = l; width = length; }

void Square::setWidth(int w)
{ width = w; length = width; }

// Square inherits Rectangle's move() and draw() functions.

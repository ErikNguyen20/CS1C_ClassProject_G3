#ifndef SHAPES_H
#define SHAPES_H

#include <QString>

/********** ENUM DEFINITIONS **********/

enum GlobalColor
{ white, black, red, green, blue, cyan, magenta, yellow, gray };

enum PenStyle
{ NoPen, SolidLine, DashLine, DotLine, DashDotLine, DashDotDotLine };

enum PenCapStyle
{ FlatCap, SquareCap, RoundCap };

enum PenJoinStyle
{ MiterJoin, BevelJoin, RoundJoin };

enum BrushStyle
{ SolidPattern, HorPattern, VerPattern, NoBrush };

enum AlignmentFlag
{ AlignLeft, AlignRight, AlignTop, AlignBottom, AlignCenter };

enum Style
{ StyleNormal, StyleItalic, StyleOblique };

enum Weight
{ Thin, Light, Normal, Bold };

/********** CLASS DEFINITIONS **********/

class Shape
{
public:
    Shape();
    Shape(int id);
    Shape(const Shape &copy);

    int getID();

private:
    int shapeID;
};



class Polygon : public Shape // Polygon extends Shape
{
public:

private:
    // PEN PROPERTIES
    GlobalColor penColor;
    int penWidth;
    PenStyle penStyle;
    PenCapStyle penCapStyle;
    PenJoinStyle penJoinStyle;

    // BRUSH PROPERTIES
    GlobalColor brushColor;
    BrushStyle brushStyle;
};



class Text : public Shape // Text extends Shape
{
public:

private:
    QString textString;
    GlobalColor textColor;
    AlignmentFlag textAlign;
    int textPointSize;
    QString textFontFam;
    Style textFontStyle;
    Weight textFontWeight;
};


#endif // SHAPES_H

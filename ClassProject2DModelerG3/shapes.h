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

/********** STRUCT DEFINITIONS **********/

struct Point
{
    int x;
    int y;
};

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



class PolyShape : public Shape // Polygon extends Shape
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



class Line : public PolyShape // Line extends PolyShape
{
private:
    Point start;
    Point end;
};

class Polyline : public PolyShape // Polyline extends PolyShape
{
    
};

class Polygon : public PolyShape // Polygon extends PolyShape
{
    
};

class Rectangle : public PolyShape // Rectangle extends PolyShape
{
private:
    Point origin;  // top left corner
    double length;
    double width;
};

class Square : public PolyShape // Square extends PolyShape
{
private:
    Point origin;  // top left corner
    double length;
};

class Ellipse : public PolyShape // Ellipse extends PolyShape
{
private:
    Point origin;  // top left corner
    double a;      // semi-major axis
    double b;      // semi-minor axis
};

class Circle : public PolyShape // Circle extends PolyShape
{
private:
    Point origin;  // top left corner
    double r;      // radius
};



class Text : public Shape // Text extends Shape
{
public:

private:
    Point origin;  // top left corner
    double length;
    double width;
    QString textString;
    GlobalColor textColor;
    AlignmentFlag textAlign;
    int textPointSize;
    QString textFontFam;
    Style textFontStyle;
    Weight textFontWeight;
};


#endif // SHAPES_H

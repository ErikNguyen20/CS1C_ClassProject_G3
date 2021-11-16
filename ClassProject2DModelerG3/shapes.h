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
    ~Shape();

    int getID() const;
    void setID(int num);

private:
    int shapeID;
};



class PolyShape : public Shape // Polygon extends Shape
{
public:
    PolyShape();
    PolyShape(const PolyShape &copy);
    ~PolyShape();

    // ACCESSORS
    void setPenColor(GlobalColor color);
    void setPenWidth(int width);
    void setPenStyle(PenStyle style);
    void setPenCapStyle(PenCapStyle style);
    void setPenJoinStyle(PenJoinStyle style);
    void setBrushColor(GlobalColor color);
    void setBrushStyle(BrushStyle style);

    // MUTATORS
    GlobalColor getPenColor() const;
    int getPenWidth() const;
    PenStyle getPenStyle() const;
    PenCapStyle getPenCapStyle() const;
    PenJoinStyle getPenJoinStyle() const;
    GlobalColor getBrushColor() const;
    BrushStyle getBrushStyle() const;

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
public:
    Line();
    Line(const Line &copy);
    Line(int id, Point start, Point end);
    ~Line();

    void setPonts(Point start, Point end);
    void setStartPoint(Point start);
    void setEndPoint(Point end);

    Point getStartPoint() const;
    Point getEndPoint() const;

private:
    Point startPoint;
    Point endPoint;
};

class Polyline : public PolyShape // Polyline extends PolyShape
{
public:
    Polyline();
    Polyline(const Polyline &copy);
    ~Polyline();
private:

};

class Polygon : public PolyShape // Polygon extends PolyShape
{
public:
    Polygon();
    Polygon(const Polygon &copy);
    ~Polygon();
private:

};

class OriginBasedShape : public PolyShape // OriginBasedShape extends PolyShape
{
public:
    OriginBasedShape();
    OriginBasedShape(const OriginBasedShape &copy);
    ~OriginBasedShape();

    void setOrigin(Point newOrigin);
    Point getOrigin() const;
private:
    Point origin;  // top left corner
};

class Rectangle : public OriginBasedShape // Rectangle extends OriginBasedShape
{
public:
    Rectangle();
    Rectangle(const Rectangle &copy);
    virtual ~Rectangle();

    virtual void setLength(double l);
    virtual void setWidth(double w);

    double getLength() const;
    double getWidth() const;
protected:
    double length;
    double width;
};

class Square : public Rectangle // Square extends Rectangle
{
public:
    Square();
    Square(const Square &copy);
    ~Square();

    void setLength(double l) override;
    void setWidth(double w) override;
};

class Ellipse : public OriginBasedShape // Ellipse extends OriginBasedShape
{
public:
    Ellipse();
    Ellipse(const Ellipse &copy);
    ~Ellipse();

    void setSemiMajor(double a);
    void setSemiMinor(double b);

    double getSemiMajor() const;
    double getSemiMinor() const;
private:
    double a;      // semi-major axis
    double b;      // semi-minor axis
};

class Circle : public OriginBasedShape // Circle extends OriginBasedShape
{
public:
    Circle();
    Circle(const Circle &copy);
    ~Circle();

    void setRadius(double r);

    double getRadius() const;
private:
    double r;      // radius
};



class Text : public Shape // Text extends Shape
{
public:
    Text();
    Text(const Text &copy);
    Text(QString text);
    ~Text();
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

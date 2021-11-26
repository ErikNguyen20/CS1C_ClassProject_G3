#ifndef SHAPES_H
#define SHAPES_H

#include <QString>
#include <QPoint>
#include <QVector> //Use templated vector.h

/********** ENUM DEFINITIONS **********/

enum GlobalColor //QColor should be used
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
    Line(int id, QPoint start, QPoint end);
    ~Line();

    void setPonts(QPoint start, QPoint end);
    void setStartPoint(QPoint start);
    void setEndPoint(QPoint end);

    QPoint getStartPoint() const;
    QPoint getEndPoint() const;

private:
    QPoint startPoint;
    QPoint endPoint;
};



class Polyline : public PolyShape // Polyline extends PolyShape
{
public:
    Polyline();
    Polyline(const Polyline &copy);
    ~Polyline();

    void addPoint(QPoint add);
    void removePoint();

    QVector<QPoint> getPoints() const;
    int getPointCount() const;
private:
    QVector<QPoint> pointVector;
    int pointCount;
};


class Polygon : public Polyline // Polygon extends PolyShape
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

    void setOrigin(QPoint newOrigin);
    QPoint getOrigin() const;
private:
    QPoint origin;  // top left corner
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
    double length; //make int
    double width;  //make int
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

    virtual void setSemiMajor(double semi);
    virtual void setSemiMinor(double semi);

    double getSemiMajor() const;
    double getSemiMinor() const;
protected:
    double a;      // semi-major axis <- make int
    double b;      // semi-minor axis <- make int
};



class Circle : public Ellipse // Circle extends Ellipse
{
public:
    Circle();
    Circle(const Circle &copy);
    ~Circle();

   void setSemiMajor(double semi) override;
   void setSemiMinor(double semi) override;
};



class Text : public Shape // Text extends Shape
{
public:
    Text();
    Text(const Text &copy);
    Text(QString text);
    ~Text();

    void setOrigin(QPoint newOrigin);
    void setLength(double l);
    void setWdith(double w);
    void setTextString(QString text);
    void setTextColor(GlobalColor color);
    void setTextAlign(AlignmentFlag align);
    void setTextPointSize(int size);
    void setTextFontFam(QString text);
    void setTextFontStyle(Style style);
    void setTextFontWeight(Weight weight);

    QPoint getOrigin() const;
    double getLength() const;
    double getWidth() const;
    QString getTextString() const;
    GlobalColor getTextColor() const;
    AlignmentFlag getTextAlign() const;
    int getTextPointSize() const;
    QString getTextFontFam() const;
    Style getTextFontStyle() const;
    Weight getTextFontWeight() const;

private:
    QPoint origin;  // top left corner
    double length; //make int
    double width;  //make int
    QString textString;
    GlobalColor textColor;
    AlignmentFlag textAlign;
    int textPointSize;
    QString textFontFam;
    Style textFontStyle; //Use QPoint Style enum
    Weight textFontWeight;
};


#endif // SHAPES_H

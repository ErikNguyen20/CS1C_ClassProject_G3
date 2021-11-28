#ifndef SHAPES_H
#define SHAPES_H

/********************************************************************/
/*                          SHAPES.H                                */
/********************************************************************/
/* This header file contains the class definitions for all Shape-   */
/* based classes.  Member function implimentations are included in  */
/* shapes.cpp and shapemanip.cpp.                                   */
/********************************************************************/
/* A diagram showing inheritance has been included below:           */
/*                                                                  */
/*                           Shape                                  */
/*                             |-------------------------|          */
/*                         PolyShape                   Text         */
/*           |-----------------|-----------|                        */
/*      OriginBasedShape    Polyline      Line                      */
/*       |---|---------|       |                                    */
/*  Rectangle      Ellipse  Polygon                                 */
/*      |             |                                             */
/*   Square        Circle                                           */
/*                                                                  */
/********************************************************************/

#include <QString>
#include <QPoint>
#include <QVector>
#include <QtMath>
#include <QColor>
#include <QFont>

#include "vector.h"

/********************************************************************/
/*                     BACKEND CLASS DEFINITIONS                    */
/********************************************************************/

/******************** SHAPE CLASS DEFINITION ********************/

class Shape
{
public:
    Shape();
    Shape(int id);
    Shape(const Shape &copy) = delete;
    Shape& operator= (const Shape&) = delete;
    ~Shape();

    bool operator== (const Shape& compare) const;
    bool operator< (const Shape& compare) const;

    int getID() const;
    void setID(int num);

    virtual void draw() const = 0;
    virtual void move(int deltaX, int deltaY) = 0;
    virtual double perimeter() const = 0;
    virtual double area() const = 0;


private:
    int shapeID;
};


/******************** POLYSHAPE CLASS DEFINITION ********************/

class PolyShape : public Shape // Polygon extends Shape
{
public:
    PolyShape();
    PolyShape(const PolyShape &copy) = delete;
    PolyShape& operator= (const PolyShape&) = delete;
    ~PolyShape();

    // ACCESSORS
    void setPenColor(Qt::GlobalColor color);
    void setPenWidth(int width);
    void setPenStyle(Qt::PenStyle style);
    void setPenCapStyle(Qt::PenCapStyle style);
    void setPenJoinStyle(Qt::PenJoinStyle style);
    void setBrushColor(Qt::GlobalColor color);
    void setBrushStyle(Qt::BrushStyle style);

    // MUTATORS
    Qt::GlobalColor getPenColor() const;
    int getPenWidth() const;
    Qt::PenStyle getPenStyle() const;
    Qt::PenCapStyle getPenCapStyle() const;
    Qt::PenJoinStyle getPenJoinStyle() const;
    Qt::GlobalColor getBrushColor() const;
    Qt::BrushStyle getBrushStyle() const;

private:
    // PEN PROPERTIES
    Qt::GlobalColor penColor;
    int penWidth;
    Qt::PenStyle penStyle;
    Qt::PenCapStyle penCapStyle;
    Qt::PenJoinStyle penJoinStyle;

    // BRUSH PROPERTIES
    Qt::GlobalColor brushColor;
    Qt::BrushStyle brushStyle;
};


/******************** ORIGINBASEDSHAPE CLASS DEFINITION ********************/

class OriginBasedShape : public PolyShape // OriginBasedShape extends PolyShape
{
public:
    OriginBasedShape();
    OriginBasedShape(const OriginBasedShape &copy) = delete;
    OriginBasedShape& operator= (const OriginBasedShape&) = delete;
    ~OriginBasedShape();

    void move(int deltaX, int deltaY) override;

    void setOrigin(QPoint newOrigin);
    QPoint getOrigin() const;
private:
    QPoint origin;  // top left corner
};


/********************************************************************/
/*                    FRONTEND CLASS DEFINITIONS                    */
/********************************************************************/

/******************** LINE CLASS DEFINITION ********************/

class Line : public PolyShape // Line extends PolyShape
{
public:
    Line();
    Line(const Line &copy) = delete;
    Line& operator= (const Line&) = delete;
    Line(int id, QPoint start, QPoint end);
    ~Line();

    void setPonts(QPoint start, QPoint end);
    void setStartPoint(QPoint start);
    void setEndPoint(QPoint end);

    QPoint getStartPoint() const;
    QPoint getEndPoint() const;

    void draw() const override;
    void move(int deltaX, int deltaY) override;
    double perimeter() const override;
    double area() const override = 0;

private:
    QPoint startPoint;
    QPoint endPoint;
};


/******************** POLYLINE CLASS DEFINITION ********************/

class Polyline : public PolyShape // Polyline extends PolyShape
{
public:
    Polyline();
    Polyline(const Polyline &copy) = delete;
    Polyline& operator= (const Polyline&) = delete;
    ~Polyline();

    void addPoint(QPoint add);
    void removePoint();

    QVector<QPoint> getPoints() const;
    int getPointCount() const;

    void draw() const override;
    void move(int deltaX, int deltaY) override;
    double perimeter() const override;
    double area() const override;

protected:
    QVector<QPoint> pointVector;
    int pointCount;
};


/******************** POLYGON CLASS DEFINITION ********************/

class Polygon : public Polyline // Polygon extends PolyShape
{
public:
    Polygon();
    Polygon(const Polygon &copy) = delete;
    Polygon& operator= (const Polygon&) = delete;
    virtual ~Polygon();

    void draw() const override;
    double perimeter() const override;
    double area() const override;
private:
};


/******************** RECTANGLE CLASS DEFINITION ********************/

class Rectangle : public OriginBasedShape // Rectangle extends OriginBasedShape
{
public:
    Rectangle();
    Rectangle(const Rectangle &copy) = delete;
    Rectangle& operator= (const Rectangle&) = delete;
    virtual ~Rectangle();

    virtual void setLength(int l);
    virtual void setWidth(int w);

    double getLength() const;
    double getWidth() const;

    void draw() const override;
    double perimeter() const override;
    double area() const override;
protected:
    int length; //make int
    int width;  //make int
};


/******************** SQUARE CLASS DEFINITION ********************/

class Square : public Rectangle // Square extends Rectangle
{
public:
    Square();
    Square(const Square &copy) = delete;
    Square& operator= (const Square&) = delete;
    ~Square();

    void setLength(int l) override;
    void setWidth(int w) override;
};


/******************** ELLIPSE CLASS DEFINITION ********************/

class Ellipse : public OriginBasedShape // Ellipse extends OriginBasedShape
{
public:
    Ellipse();
    Ellipse(const Ellipse &copy) = delete;
    Ellipse& operator= (const Ellipse&) = delete;
    ~Ellipse();

    virtual void setSemiMajor(int semi);
    virtual void setSemiMinor(int semi);

    double getSemiMajor() const;
    double getSemiMinor() const;

    void draw() const override;
    double perimeter() const override;
    double area() const override;
protected:
    int a;      // semi-major axis <- make int
    int b;      // semi-minor axis <- make int
};


/******************** CIRCLE CLASS DEFINITION ********************/

class Circle : public Ellipse // Circle extends Ellipse
{
public:
    Circle();
    Circle(const Circle &copy) = delete;
    Circle& operator= (const Circle&) = delete;
    ~Circle();

   void setSemiMajor(int semi) override;
   void setSemiMinor(int semi) override;
};


/******************** TEXT CLASS DEFINITION ********************/

class Text : public Shape // Text extends Shape
{
public:
    Text();
    Text(const Text &copy) = delete;
    Text& operator= (const Text&) = delete;
    Text(QString text);
    ~Text();

    void setOrigin(QPoint newOrigin);
    void setLength(double l);
    void setWdith(double w);
    void setTextString(QString text);
    void setTextColor(Qt::GlobalColor color);
    void setTextAlign(Qt::AlignmentFlag align);
    void setTextPointSize(int size);
    void setTextFontFam(QString text);
    void setTextFontStyle(QFont::Style style);
    void setTextFontWeight(QFont::Weight weight);

    QPoint getOrigin() const;
    double getLength() const;
    double getWidth() const;
    QString getTextString() const;
    Qt::GlobalColor getTextColor() const;
    Qt::AlignmentFlag getTextAlign() const;
    int getTextPointSize() const;
    QString getTextFontFam() const;
    QFont::Style getTextFontStyle() const;
    QFont::Weight getTextFontWeight() const;

private:
    QPoint origin;  // top left corner
    double length; //make int
    double width;  //make int
    QString textString;
    Qt::GlobalColor textColor;
    Qt::AlignmentFlag textAlign;
    int textPointSize;
    QString textFontFam;
    QFont::Style textFontStyle; //Use QPoint Style enum
    QFont::Weight textFontWeight;

    void draw() const override;
    void move(int deltaX, int deltaY) override;
};


#endif // SHAPES_H


#ifndef _SHAPE_H
#define _SHAPE_H

#include <QPainter>
#include <QString>
#include <QPoint>
#include <QtMath>
#include <QColor>
#include <string>
using std::string;

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

double DistanceBetween(const QPoint a, const QPoint b);

class Shape
{
public:
    Shape();
    Shape(int id);
    Shape(const Shape &copy) = delete;
    Shape& operator= (const Shape&) = delete;
    virtual ~Shape();

    bool operator== (const Shape& compare) const;
    bool operator< (const Shape& compare) const;

    int getID() const;
    void setID(int num);
    void setPainter(QPainter* p_painter);
    QPainter* getPainter() const;

    virtual void draw() const = 0;
    virtual void move(int deltaX, int deltaY) = 0;
    virtual double perimeter() const = 0;
    virtual double area() const = 0;

    virtual string getShapeStypeString() const = 0;

private:
    QPainter* qpainter;
    int shapeID;
};


#endif // _SHAPE_H

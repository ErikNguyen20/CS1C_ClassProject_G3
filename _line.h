#ifndef _LINE_H
#define _LINE_H

#include "_polyshape.h"

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

class Line : public PolyShape // Line extends PolyShape
{
public:
    Line();
    Line(const Line &copy) = delete;
    Line& operator= (const Line&) = delete;
    Line(int id, QPoint start, QPoint end); //Alt Constructor
    Line(int id, QPoint start, QPoint end, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle);
    ~Line();

    void setPonts(QPoint start, QPoint end);
    void setStartPoint(QPoint start);
    void setEndPoint(QPoint end);

    QPoint getStartPoint() const;
    QPoint getEndPoint() const;

    void draw() const override;
    void move(int deltaX, int deltaY) override;
    double perimeter() const override;
    double area() const override;

    string getShapeTypeString() {return "Line";}

private:
    QPoint startPoint;
    QPoint endPoint;
};

#endif // _LINE_H

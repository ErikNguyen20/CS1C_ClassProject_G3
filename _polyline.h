#ifndef _POLYLINE_H
#define _POLYLINE_H

#include "_polyshape.h"
#include "vector.h"

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

class Polyline : public PolyShape // Polyline extends PolyShape
{
public:
    Polyline();
    Polyline(int id, vector<QPoint> points, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle); //Alt Constructor
    Polyline(int id, vector<QPoint> points, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Polyline(const Polyline &copy) = delete;
    Polyline& operator= (const Polyline&) = delete;
    ~Polyline();

    void addPoint(QPoint add);
    void removePoint();

    vector<QPoint> getPoints() const;
    int getPointCount() const;

    void draw() const override;
    void move(int deltaX, int deltaY) override;
    double perimeter() const override;
    double area() const override;
	
	string getShapeTypeString() {return "Polyline";}

protected:
    vector<QPoint> pointVector;
    int pointCount;
};

#endif // _POLYLINE_H

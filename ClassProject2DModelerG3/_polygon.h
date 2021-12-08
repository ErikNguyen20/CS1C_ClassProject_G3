#ifndef _POLYGON_H
#define _POLYGON_H

#include "_polyline.h"

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

class Polygon : public Polyline // Polygon extends PolyShape
{
public:
    Polygon();
    Polygon(int id, vector<QPoint>& points, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Polygon(const Polygon &copy) = delete;
    Polygon& operator= (const Polygon&) = delete;
    virtual ~Polygon();

    void draw() const override;
    double perimeter() const override;
    double area() const override;

    QString getShapeStypeString() const override {return "Polygon";}
    
private:
};

#endif // _POLYGON_H

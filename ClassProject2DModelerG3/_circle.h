#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "_ellipse.h"

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

class Circle : public Ellipse // Circle extends Ellipse
{
public:
    Circle();
    Circle(int id, QPoint origin, int a, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Circle(const Circle &copy) = delete;
    Circle& operator= (const Circle&) = delete;
    ~Circle();

   void setSemiMajor(int semi) override;
   void setSemiMinor(int semi) override;

   QString getShapeStypeString() const override {return "Circle";}
};

#endif // _CIRCLE_H

#ifndef _SQUARE_H
#define _SQUARE_H

#include "_rectangle.h"

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

class Square : public Rectangle // Square extends Rectangle
{
public:
    Square();
    Square(int id, QPoint origin, int length, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Square(const Square &copy) = delete;
    Square& operator= (const Square&) = delete;
    ~Square();

    void setLength(int l) override;
    void setWidth(int w) override;

    QString getShapeStypeString() const override {return "Square";}
};

#endif // _SQUARE_H

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "_originbasedshape.h"

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

class Rectangle : public OriginBasedShape // Rectangle extends OriginBasedShape
{
public:
    Rectangle();
    Rectangle(int id, QPoint origin, int length, int width, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Rectangle(const Rectangle &copy) = delete;
    Rectangle& operator= (const Rectangle&) = delete;
    virtual ~Rectangle();

    virtual void setLength(int l);
    virtual void setWidth(int w);

    int getLength() const;
    int getWidth() const;

    void draw() const override;
    double perimeter() const override;
    double area() const override;

    string getShapeStypeString() {return "Rectangle";}
    
protected:
    int length; //make int
    int width;  //make int
};

#endif // _RECTANGLE_H

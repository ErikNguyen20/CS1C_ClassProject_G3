#ifndef _ELLIPSE_H
#define _ELLIPSE_H

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

class Ellipse : public OriginBasedShape // Ellipse extends OriginBasedShape
{
public:
    Ellipse();
    Ellipse(int id, QPoint origin, int a, int b, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Ellipse(const Ellipse &copy) = delete;
    Ellipse& operator= (const Ellipse&) = delete;
    ~Ellipse();

    virtual void setSemiMajor(int semi);
    virtual void setSemiMinor(int semi);

    int getSemiMajor() const;
    int getSemiMinor() const;

    void draw() const override;
    double perimeter() const override;
    double area() const override;

    string getShapeStypeString() {return "Ellipse";}
    
protected:
    int a;      // semi-major axis <- make int
    int b;      // semi-minor axis <- make int
};

#endif // _ELLIPSE_H

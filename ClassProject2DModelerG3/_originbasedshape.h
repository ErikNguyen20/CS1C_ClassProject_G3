#ifndef _ORIGINBASEDSHAPE_H
#define _ORIGINBASEDSHAPE_H

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

class OriginBasedShape : public PolyShape // OriginBasedShape extends PolyShape
{
public:
    OriginBasedShape();
    OriginBasedShape(QPoint origin, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    OriginBasedShape(const OriginBasedShape &copy) = delete;
    OriginBasedShape& operator= (const OriginBasedShape&) = delete;
    ~OriginBasedShape();

    void move(int deltaX, int deltaY) override;

    void setOrigin(QPoint newOrigin);
    QPoint getOrigin() const;
private:
    QPoint origin;  // top left corner
};

#endif // _ORIGINBASEDSHAPE_H

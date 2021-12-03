#ifndef _POLYSHAPE_H
#define _POLYSHAPE_H

#include "_shape.h"

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

class PolyShape : public Shape // Polygon extends Shape
{
public:
    PolyShape();
    PolyShape(Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle); //Alt Constructor without brush params
    PolyShape(Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
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
#endif // _POLYSHAPE_H

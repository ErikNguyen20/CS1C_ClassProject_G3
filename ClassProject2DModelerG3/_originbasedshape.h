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
//! OriginBasedShape Class
/*! An Abstract Base Class derived from PolyShape. */
class OriginBasedShape : public PolyShape // OriginBasedShape extends PolyShape
{
public:
    //! Default Constructor
    /*! Constructs a new OriginBasedShape object. */
    OriginBasedShape();

    //! Alternate Constructor
    /*! Constructs a new OriginBasedShape object.
        \param origin a QPoint argument that specifies the origin.
        \param penColor an enum for color.
        \param penWidth an integer argument for the pen's width.
        \param penStyle an enum for the pen style.
        \param penCapStyle an enum for the pen cap style.
        \param penJoinStyle an enum for the pen join style.
        \param brushColor an enum for the brush color.
        \param brushStyle an enum for the brush style.
    */
    OriginBasedShape(QPoint origin, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    OriginBasedShape(const OriginBasedShape &copy) = delete;
    OriginBasedShape& operator= (const OriginBasedShape&) = delete;

    //! Destructor
    /*! Destructs the rectangle object. */
    ~OriginBasedShape();

    //! Member function that moves the shape.
    /*! Overriden from the abstract base class Shape
        \param deltaX a new integer position X.
        \param deltaY a new integer position Y.
    */
    void move(int deltaX, int deltaY) override;

    //! Member function that sets the origin point of the shape.
    /*!
        \param newOrigin a QPoint argument that specifies the origin.
    */
    void setOrigin(QPoint newOrigin);

    //! Member function that returns the origin point of the shape.
    /*!
        \return QPoint of the origin point.
    */
    QPoint getOrigin() const;
private:
    //! A private variable data member.
    /*! Contains the QPoint origin point of the shape. */
    QPoint origin;  // top left corner
};

#endif // _ORIGINBASEDSHAPE_H

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
//! Circle Class
/*! Derived from Ellipse. */
class Circle : public Ellipse // Circle extends Ellipse
{
public:
    //! Default Constructor
    /*! Constructs a new circle object. */
    Circle();

    //! Alternate Constructor
    /*! Constructs a new circle object.
        \param id an integer argument for id.
        \param a an integer argument for the axis size.
        \param penColor an enum for color.
        \param penWidth an integer argument for the pen's width.
        \param penStyle an enum for the pen style.
        \param penCapStyle an enum for the pen cap style.
        \param penJoinStyle an enum for the pen join style.
        \param brushColor an enum for the brush color.
        \param brushStyle an enum for the brush style.
    */
    Circle(int id, QPoint origin, int a, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Circle(const Circle &copy) = delete;
    Circle& operator= (const Circle&) = delete;

    //! Destructor
    /*! Destructs the circle object. */
    ~Circle();

    //! Member function that sets the semi major axis.
    /*!
        \param semi an integer argument for the major axis size.
    */
    void setSemiMajor(int semi) override;

    //! Member function that sets the semi minor axis.
    /*!
        \param semi an integer argument for the minor axis size.
    */
    void setSemiMinor(int semi) override;

    //! Member function that returns the shape type.
    /*!
        \return QString for the shape type.
    */
    QString getShapeStypeString() const override {return "Circle";}
};

#endif // _CIRCLE_H

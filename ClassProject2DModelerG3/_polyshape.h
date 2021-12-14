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
//! PolyShape Class
/*! An Abstract Base Class derived from Shape. */
class PolyShape : public Shape // Polygon extends Shape
{
public:
    //! Default Constructor
    /*! Constructs a new PolyShape object. */
    PolyShape();

    //! Alternate Constructor
    /*! Constructs a new PolyShape object.
        \param penColor an enum for color.
        \param penWidth an integer argument for the pen's width.
        \param penStyle an enum for the pen style.
        \param penCapStyle an enum for the pen cap style.
        \param penJoinStyle an enum for the pen join style.
    */
    PolyShape(Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle); //Alt Constructor without brush params

    //! Alternate Constructor
    /*! Constructs a new PolyShape object.
        \param penColor an enum for color.
        \param penWidth an integer argument for the pen's width.
        \param penStyle an enum for the pen style.
        \param penCapStyle an enum for the pen cap style.
        \param penJoinStyle an enum for the pen join style.
        \param brushColor an enum for the brush color.
        \param brushStyle an enum for the brush style.
    */
    PolyShape(Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    PolyShape(const PolyShape &copy) = delete;
    PolyShape& operator= (const PolyShape&) = delete;

    //! Destructor
    /*! Destructs the PolyShape object. */
    ~PolyShape();

    // MUTATORS
    //! Member function that sets the pen color of the shape.
    /*!
        \param color an enum for color.
    */
    void setPenColor(Qt::GlobalColor color);

    //! Member function that sets the pen width of the shape.
    /*!
        \param width an integer argument for the pen's width.
    */
    void setPenWidth(int width);

    //! Member function that sets the pen style of the shape.
    /*!
        \param style an enum for the pen style.
    */
    void setPenStyle(Qt::PenStyle style);

    //! Member function that sets the pen cap style of the shape.
    /*!
        \param style an enum for the pen cap style.
    */
    void setPenCapStyle(Qt::PenCapStyle style);

    //! Member function that sets the pen join style of the shape.
    /*!
        \param style an enum for the pen join style.
    */
    void setPenJoinStyle(Qt::PenJoinStyle style);

    //! Member function that sets the brush color of the shape.
    /*!
        \param color an enum for color.
    */
    void setBrushColor(Qt::GlobalColor color);

    //! Member function that sets the brush style of the shape.
    /*!
        \param style an enum for brush style.
    */
    void setBrushStyle(Qt::BrushStyle style);

    // ACCESSORS
    //! Member function that returns the pen color of the shape.
    /*!
        \return An enum for the pen color.
    */
    Qt::GlobalColor getPenColor() const;

    //! Member function that returns the pen width of the shape.
    /*!
        \return An integer value for the pen width.
    */
    int getPenWidth() const;

    //! Member function that returns the pen style of the shape.
    /*!
        \return An enum for the pen style.
    */
    Qt::PenStyle getPenStyle() const;

    //! Member function that returns the pen cap style of the shape.
    /*!
        \return An enum for the pen cap style.
    */
    Qt::PenCapStyle getPenCapStyle() const;

    //! Member function that returns the pen join style of the shape.
    /*!
        \return An enum for the pen join style.
    */
    Qt::PenJoinStyle getPenJoinStyle() const;

    //! Member function that returns the brush color of the shape.
    /*!
        \return An enum for the brush color.
    */
    Qt::GlobalColor getBrushColor() const;

    //! Member function that returns the brush style of the shape.
    /*!
        \return An enum for the brush style.
    */
    Qt::BrushStyle getBrushStyle() const;

private:
    // PEN PROPERTIES
    //! A private variable data member.
    /*! Contains the enum pen color of the shape. */
    Qt::GlobalColor penColor;

    //! A private variable data member.
    /*! Contains the integer pen width of the shape. */
    int penWidth;

    //! A private variable data member.
    /*! Contains the enum pen style of the shape. */
    Qt::PenStyle penStyle;

    //! A private variable data member.
    /*! Contains the enum pen cap style of the shape. */
    Qt::PenCapStyle penCapStyle;

    //! A private variable data member.
    /*! Contains the enum pen join style of the shape. */
    Qt::PenJoinStyle penJoinStyle;

    // BRUSH PROPERTIES
    //! A private variable data member.
    /*! Contains the enum brush color of the shape. */
    Qt::GlobalColor brushColor;

    //! A private variable data member.
    /*! Contains the enum brush style of the shape. */
    Qt::BrushStyle brushStyle;
};
#endif // _POLYSHAPE_H

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
//! Ellipse Class
/*! Derived from OriginBasedShape. */
class Ellipse : public OriginBasedShape // Ellipse extends OriginBasedShape
{
public:
    //! Default Constructor
    /*! Constructs a new ellipse object. */
    Ellipse();

    //! Alternate Constructor
    /*! Constructs a new ellipse object.
        \param id an integer argument for id.
        \param origin a QPoint argument that specifies the origin.
        \param a an integer argument for the semi major axis size.
        \param b an integer argument for the semi minor axis size.
        \param penColor an enum for color.
        \param penWidth an integer argument for the pen's width.
        \param penStyle an enum for the pen style.
        \param penCapStyle an enum for the pen cap style.
        \param penJoinStyle an enum for the pen join style.
        \param brushColor an enum for the brush color.
        \param brushStyle an enum for the brush style.
    */
    Ellipse(int id, QPoint origin, int a, int b, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Ellipse(const Ellipse &copy) = delete;
    Ellipse& operator= (const Ellipse&) = delete;

    //! Destructor
    /*! Destructs the ellipse object. */
    ~Ellipse();

    //! Member function that sets the semi major axis.
    /*!
        \param semi an integer argument for the major axis size.
    */
    virtual void setSemiMajor(int semi);

    //! Member function that sets the semi minor axis.
    /*!
        \param semi an integer argument for the minor axis size.
    */
    virtual void setSemiMinor(int semi);

    //! Member function that returns the semi major axis size.
    /*!
        \return An integer for the semi major axis size.
    */
    int getSemiMajor() const;

    //! Member function that returns the semi minor axis size.
    /*!
        \return An integer for the semi minor axis size.
    */
    int getSemiMinor() const;

    //! Member function that draws the shape.
    /*! Overriden from the abstract base class Shape */
    void draw() const override;

    //! Member function that returns the perimeter of the shape.
    /*!
        \return A double for the perimeter of the shape.
    */
    double perimeter() const override;

    //! Member function that returns the area of the shape.
    /*!
        \return A double for the area of the shape.
    */
    double area() const override;

    //! Member function that returns the shape type.
    /*!
        \return QString for the shape type.
    */
    QString getShapeStypeString() const override  {return "Ellipse";}
    
protected:
    //! A protected variable data member.
    /*! Contains the integer size of the semi major axis. */
    int a;      // semi-major axis <- make int

    //! A protected variable data member.
    /*! Contains the integer size of the semi minor axis. */
    int b;      // semi-minor axis <- make int
};

#endif // _ELLIPSE_H

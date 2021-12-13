#ifndef _POLYGON_H
#define _POLYGON_H

#include "_polyline.h"

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
//! Polyline Class
/*! Derived from Polyline. */
class Polygon : public Polyline // Polygon extends PolyShape
{
public:
    //! Default Constructor
    /*! Constructs a new polygon object. */
    Polygon();

    //! Alternate Constructor
    /*! Constructs a new polygon object.
        \param id an integer argument for id.
        \param points a vector of QPoints.
        \param penColor an enum for color.
        \param penWidth an integer argument for the pen's width.
        \param penStyle an enum for the pen style.
        \param penCapStyle an enum for the pen cap style.
        \param penJoinStyle an enum for the pen join style.
        \param brushColor an enum for the brush color.
        \param brushStyle an enum for the brush style.
    */
    Polygon(int id, vector<QPoint>& points, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Polygon(const Polygon &copy) = delete;
    Polygon& operator= (const Polygon&) = delete;

    //! Destructor
    /*! Destructs the polygon object. */
    virtual ~Polygon();

    //! Member function that draws the shape.
    /*! Overriden from the abstract base class Shape */
    void draw() const override;

    //! Member function that returns the perimeter of the shape.
    /*!
        \return a double for the perimeter of the shape.
    */
    double perimeter() const override;

    //! Member function that returns the area of the shape.
    /*!
        \return a double for the area of the shape.
    */
    double area() const override;

    //! Member function that returns the shape type.
    /*!
        \return QString for the shape type.
    */
    QString getShapeStypeString() const override {return "Polygon";}
    
private:
};

#endif // _POLYGON_H

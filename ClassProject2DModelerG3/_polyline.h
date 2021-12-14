#ifndef _POLYLINE_H
#define _POLYLINE_H

#include "_polyshape.h"
#include "vector.h"

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
/*! Derived from PolyShape. */
class Polyline : public PolyShape // Polyline extends PolyShape
{
public:
    //! Default Constructor
    /*! Constructs a new polyline object. */
    Polyline();

    //! Alternate Constructor
    /*! Constructs a new polyline object.
        \param id an integer argument for id.
        \param points a vector of QPoints.
        \param penColor an enum for color.
        \param penWidth an integer argument for the pen's width.
        \param penStyle an enum for the pen style.
        \param penCapStyle an enum for the pen cap style.
        \param penJoinStyle an enum for the pen join style.
    */
    Polyline(int id, vector<QPoint> points, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle); //Alt Constructor

    //! Alternate Constructor
    /*! Constructs a new polyline object.
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
    Polyline(int id, vector<QPoint> points, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Polyline(const Polyline &copy) = delete;
    Polyline& operator= (const Polyline&) = delete;

    //! Destructor
    /*! Destructs the line object. */
    ~Polyline();

    //! Member function that adds a point to the polyline.
    /*!
        \param add a QPoint argument for the point.
    */
    void addPoint(QPoint add);

    //! Member function that removes a point from the polyline.
    void removePoint();

    //! Member function that returns the points on the polyline.
    /*!
        \return vector of QPoints for every point on the polyline.
    */
    vector<QPoint> getPoints() const;

    //! Member function that returns the number of points on the polyline.
    /*!
        \return Integer count for the number of points on the polyline.
    */
    int getPointCount() const;

    //! Member function that draws the shape.
    /*! Overriden from the abstract base class Shape */
    void draw() const override;

    //! Member function that moves the shape.
    /*! Overriden from the abstract base class Shape
        \param deltaX a new integer position X.
        \param deltaY a new integer position Y.
    */
    void move(int deltaX, int deltaY) override;

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
    QString getShapeStypeString() const override {return "Polyline";}

protected:
    //! A private variable data member.
    /*! Contains a vector of QPoints representing the polyline. */
    vector<QPoint> pointVector;

    //! A private variable data member.
    /*! Contains the number of points on the polyline. */
    int pointCount;
};

#endif // _POLYLINE_H

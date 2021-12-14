#ifndef _SHAPE_H
#define _SHAPE_H

#include <QPainter>
#include <QString>
#include <QPoint>
#include <QtMath>
#include <QColor>
#include <string>
using std::string;

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

double DistanceBetween(const QPoint a, const QPoint b);
//! Shape Class
/*! An Abstract Base Class. */
class Shape
{
public:
    //! Default Constructor
    /*! Constructs a new Shape object. */
    Shape();
    //! Alternate Constructor
    /*! Constructs a new Shape object.
        \param id an integer argument for id.
    */
    Shape(int id);
    Shape(const Shape &copy) = delete;
    Shape& operator= (const Shape&) = delete;

    //! Destructor
    /*! Destructs the Shape object. */
    virtual ~Shape();

    //! Overloaded Relational Equality Operator
    /*! Allows for equality comparison between two shape objects.
        \param compare the r-side shape object.
        \return The boolean value (true or false).
    */
    bool operator== (const Shape& compare) const;

    //! Overloaded Relational Less-than Operator
    /*! Allows for less-than comparison between two shape objects.
        \param compare the r-side shape object.
        \return The boolean value (true or false).
    */
    bool operator< (const Shape& compare) const;

    //! Member function that returns the id of the shape.
    /*!
        \return An integer representing the id of the shape.
    */
    int getID() const;

    //! Member function that sets the id of the shape.
    /*!
        \param id an integer argument or id.
    */
    void setID(int num);

    //! Member function that sets painter object used by the draw functions of the shape.
    /*!
        \param p_painter an existing instance of a painter object.
    */
    void setPainter(QPainter* p_painter);

    //! Member function that returns the painter object used by the shape.
    /*!
        \return QPainter object used by the shape.
    */
    QPainter* getPainter() const;

    //! Member function that draws the shape.
    /*! A pure virtual function. */
    virtual void draw() const = 0;

    //! Member function that moves the shape.
    /*! A pure virtual function.
        \param deltaX a new integer position X.
        \param deltaY a new integer position Y.
    */
    virtual void move(int deltaX, int deltaY) = 0;

    //! Member function that returns the perimeter of the shape.
    /*! A pure virtual function.
        \return A double for the perimeter of the shape.
    */
    virtual double perimeter() const = 0;

    //! Member function that returns the area of the shape.
    /*! A pure virtual function.
        \return A double for the area of the shape.
    */
    virtual double area() const = 0;

    //! Member function that returns the shape type.
    /*! A pure virtual function.
        \return QString for the shape type.
    */
    virtual QString getShapeStypeString() const = 0;

private:
    //! A private pointer data member.
    /*! Contains a QPainter object which shares an aggregate relationship with the shape. */
    QPainter* qpainter;

    //! A private variable data member.
    /*! Contains the integer id of the shape. */
    int shapeID;
};


#endif // _SHAPE_H

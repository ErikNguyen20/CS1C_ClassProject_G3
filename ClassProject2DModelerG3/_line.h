#ifndef _LINE_H
#define _LINE_H

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
//! Line Class
/*! Derived from PolyShape. */
class Line : public PolyShape // Line extends PolyShape
{
public:
    //! Default Constructor
    /*! Constructs a new line object. */
    Line();
    Line(const Line &copy) = delete;
    Line& operator= (const Line&) = delete;

    //! Alternate Constructor
    /*! Constructs a new line object.
        \param id an integer argument for id.
        \param start a QPoint argument for the start point.
        \param end a QPoint argument for the end point.
    */
    Line(int id, QPoint start, QPoint end); //Alt Constructor

    //! Alternate Constructor
    /*! Constructs a new line object.
        \param id an integer argument for id.
        \param start a QPoint argument for the start point.
        \param end a QPoint argument for the end point.
        \param penColor an enum for color.
        \param penWidth an integer argument for the pen's width.
        \param penStyle an enum for the pen style.
        \param penCapStyle an enum for the pen cap style.
        \param penJoinStyle an enum for the pen join style.
    */
    Line(int id, QPoint start, QPoint end, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle);

    //! Destructor
    /*! Destructs the line object. */
    ~Line();

    //! Member function that sets the start and end points of the line.
    /*!
        \param start a QPoint argument for the start point.
        \param end a QPoint argument for the end point.
    */
    void setPonts(QPoint start, QPoint end);

    //! Member function that sets the start point of the line.
    /*!
        \param start a QPoint argument for the start point.
    */
    void setStartPoint(QPoint start);

    //! Member function that sets the end point of the line.
    /*!
        \param end a QPoint argument for the end point.
    */
    void setEndPoint(QPoint end);

    //! Member function that returns the start point of the line.
    /*!
        \return QPoint to the starting point of the line.
    */
    QPoint getStartPoint() const;

    //! Member function that returns the end point of the line.
    /*!
        \return QPoint to the ending point of the line.
    */
    QPoint getEndPoint() const;

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
    QString getShapeStypeString() const override {return "Line";}

private:
    //! A private variable data member.
    /*! Contains the QPoint position of the starting point. */
    QPoint startPoint;

    //! A private variable data member.
    /*! Contains the QPoint position of the ending point. */
    QPoint endPoint;
};

#endif // _LINE_H

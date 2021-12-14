#ifndef _RECTANGLE_H
#define _RECTANGLE_H

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
//! Rectangle Class
/*! Derived from OriginBasedShape. */
class Rectangle : public OriginBasedShape // Rectangle extends OriginBasedShape
{
public:
    //! Default Constructor
    /*! Constructs a new rectangle object. */
    Rectangle();

    //! Alternate Constructor
    /*! Constructs a new rectangle object.
        \param id an integer argument for id.
        \param origin a QPoint argument that specifies the origin.
        \param length an integer argument for the length.
        \param width an integer argument for the width.
        \param penColor an enum for color.
        \param penWidth an integer argument for the pen's width.
        \param penStyle an enum for the pen style.
        \param penCapStyle an enum for the pen cap style.
        \param penJoinStyle an enum for the pen join style.
        \param brushColor an enum for the brush color.
        \param brushStyle an enum for the brush style.
    */
    Rectangle(int id, QPoint origin, int length, int width, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Rectangle(const Rectangle &copy) = delete;
    Rectangle& operator= (const Rectangle&) = delete;

    //! Destructor
    /*! Destructs the ellipse object. */
    virtual ~Rectangle();

    //! Member function that sets the length of the rectangle.
    /*!
        \param l an integer argument for the length.
    */
    virtual void setLength(int l);

    //! Member function that sets the width of the rectangle.
    /*!
        \param w an integer argument for the width.
    */
    virtual void setWidth(int w);


    //! Member function that returns the length of the rectangle.
    /*!
        \return An integer for the length.
    */
    int getLength() const;

    //! Member function that returns the width of the rectangle.
    /*!
        \return An integer for the width.
    */
    int getWidth() const;

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
    QString getShapeStypeString() const override {return "Rectangle";}
    
protected:
    //! A private variable data member.
    /*! Contains the integer length of the rectangle. */
    int length; //make int

    //! A private variable data member.
    /*! Contains the integer width of the rectangle. */
    int width;  //make int
};

#endif // _RECTANGLE_H

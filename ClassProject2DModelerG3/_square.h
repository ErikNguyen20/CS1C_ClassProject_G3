#ifndef _SQUARE_H
#define _SQUARE_H

#include "_rectangle.h"

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
//! Square Class
/*! Derived from Rectangle. */
class Square : public Rectangle // Square extends Rectangle
{
public:
    //! Default Constructor
    /*! Constructs a new square object. */
    Square();

    //! Alternate Constructor
    /*! Constructs a new square object.
        \param id an integer argument for id.
        \param origin a QPoint argument that specifies the origin.
        \param length an integer argument for the length.
        \param penColor an enum for color.
        \param penWidth an integer argument for the pen's width.
        \param penStyle an enum for the pen style.
        \param penCapStyle an enum for the pen cap style.
        \param penJoinStyle an enum for the pen join style.
        \param brushColor an enum for the brush color.
        \param brushStyle an enum for the brush style.
    */
    Square(int id, QPoint origin, int length, Qt::GlobalColor penColor,int penWidth,Qt::PenStyle penStyle,Qt::PenCapStyle penCapStyle,Qt::PenJoinStyle penJoinStyle,Qt::GlobalColor brushColor,Qt::BrushStyle brushStyle); //Alt Constructor
    Square(const Square &copy) = delete;
    Square& operator= (const Square&) = delete;

    //! Destructor
    /*! Destructs the square object. */
    ~Square();

    //! Member function that sets the length of the rectangle.
    /*!
        \param l an integer argument for the length.
    */
    virtual void setLength(int l);

    //! Member function that sets the width of the rectangle.
    /*!
        \param w an integer argument for the width.
    */
    void setWidth(int w) override;

    //! Member function that returns the shape type.
    /*!
        \return QString for the shape type.
    */
    QString getShapeStypeString() const override {return "Square";}
};

#endif // _SQUARE_H

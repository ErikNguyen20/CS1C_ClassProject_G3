#ifndef _TEXT_H
#define _TEXT_H

#include <QFont>
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
//! Text Class
/*! Derived from Shape. */
class Text : public Shape // Text extends Shape
{
public:
    //! Default Constructor
    /*! Constructs a new text object. */
    Text();

    //! Alternate Constructor
    /*! Constructs a new text object.
        \param id an integer argument for id.
        \param origin a QPoint argument that specifies the origin.
        \param length an integer argument for the length.
        \param width an integer argument for the width.
        \param textstring a QString argument for the text.
        \param textColor an enum for color.
        \param textAlign an enum for alignment.
        \param textPointSize an integer argument for the text's size.
        \param textFontFam a QString argument for the text font family.
        \param textFontStyle an enum for the text font style.
        \param textFontWeight an enum for the text weight style.
    */
    Text(int id, QPoint origin, int length, int width, QString textstring, Qt::GlobalColor textColor, Qt::AlignmentFlag textAlign, int textPointSize, QString textFontFam, QFont::Style textFontStyle, QFont::Weight textFontWeight); //alt constructor
    Text(const Text &copy) = delete;
    Text& operator= (const Text&) = delete;

    //! Alternate Constructor
    /*! Constructs a new text object.
        \param text a QString argument for the text.
    */
    Text(QString text);

    //! Destructor
    /*! Destructs the text object. */
    ~Text();

    //! Member function that sets the origin point.
    /*!
        \param newOrigin a QPoint argument for the origin point.
    */
    void setOrigin(QPoint newOrigin);

    //! Member function that sets the length of the text.
    /*!
        \param l an integer argument for the length.
    */
    void setLength(int l);

    //! Member function that sets the width of the text.
    /*!
        \param w an integer argument for the width.
    */
    void setWidth(int w);

    //! Member function that sets the text.
    /*!
        \param text a QString argument for the text.
    */
    void setTextString(QString text);

    //! Member function that sets the color of the text.
    /*!
        \param color an enum for color.
    */
    void setTextColor(Qt::GlobalColor color);

    //! Member function that sets the alignment of the text.
    /*!
        \param align an enum for alignment.
    */
    void setTextAlign(Qt::AlignmentFlag align);

    //! Member function that sets the size of the text.
    /*!
        \param size an integer argument for the text point size.
    */
    void setTextPointSize(int size);

    //! Member function that sets the text font family.
    /*!
        \param text a QString argument for the text font family.
    */
    void setTextFontFam(QString text);

    //! Member function that sets the font style.
    /*!
        \param style an enum for the font style.
    */
    void setTextFontStyle(QFont::Style style);

    //! Member function that sets the font weight.
    /*!
        \param weight an enum for the font weight.
    */
    void setTextFontWeight(QFont::Weight weight);

    //! Member function that returns the origin point.
    /*!
        \return QPoint for the origin point of the text.
    */
    QPoint getOrigin() const;

    //! Member function that returns the length.
    /*!
        \return An integer value for the length.
    */
    int getLength() const;

    //! Member function that returns the width.
    /*!
        \return An integer value for the width.
    */
    int getWidth() const;

    //! Member function that returns the text string.
    /*!
        \return A QString of the text.
    */
    QString getTextString() const;

    //! Member function that returns the color of the text.
    /*!
        \return An enum for color.
    */
    Qt::GlobalColor getTextColor() const;

    //! Member function that returns the alignment of the text.
    /*!
        \return An enum for alignment.
    */
    Qt::AlignmentFlag getTextAlign() const;

    //! Member function that returns the text point size.
    /*!
        \return An integer value for the text point size.
    */
    int getTextPointSize() const;

    //! Member function that returns the text font family.
    /*!
        \return A QString for the text font family.
    */
    QString getTextFontFam() const;

    //! Member function that returns the text font style.
    /*!
        \return An enum for the text font style.
    */
    QFont::Style getTextFontStyle() const;

    //! Member function that returns the text font weight.
    /*!
        \return An enum for the text font weight.
    */
    QFont::Weight getTextFontWeight() const;

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
    QString getShapeStypeString() const override {return "Text";}

private:
    //! A private variable data member.
    /*! Contains the origin point of the text. */
    QPoint origin;  // top left corner

    //! A private variable data member.
    /*! Contains the integer length of the text. */
    int length; //make int

    //! A private variable data member.
    /*! Contains the integer width of the text. */
    int width;  //make int

    //! A private variable data member.
    /*! Contains the QString of the text. */
    QString textString;

    //! A private variable data member.
    /*! Contains the enum color of the text. */
    Qt::GlobalColor textColor;

    //! A private variable data member.
    /*! Contains the enum alignmet of the text. */
    Qt::AlignmentFlag textAlign;

    //! A private variable data member.
    /*! Contains the integer text point size of the text. */
    int textPointSize;

    //! A private variable data member.
    /*! Contains the QString text font family of the text. */
    QString textFontFam;

    //! A private variable data member.
    /*! Contains the enum text font style of the text. */
    QFont::Style textFontStyle; //Use QPoint Style enum

    //! A private variable data member.
    /*! Contains the enum text font weight of the text. */
    QFont::Weight textFontWeight;
};

#endif // _TEXT_H

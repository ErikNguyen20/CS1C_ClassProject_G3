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

class Text : public Shape // Text extends Shape
{
public:
    Text();
    Text(int id, QPoint origin, int length, int width, QString textstring, Qt::GlobalColor textColor, Qt::AlignmentFlag textAlign, int textPointSize, QString textFontFam, QFont::Style textFontStyle, QFont::Weight textFontWeight); //alt constructor
    Text(const Text &copy) = delete;
    Text& operator= (const Text&) = delete;
    Text(QString text);
    ~Text();

    void setOrigin(QPoint newOrigin);
    void setLength(int l);
    void setWidth(int w);
    void setTextString(QString text);
    void setTextColor(Qt::GlobalColor color);
    void setTextAlign(Qt::AlignmentFlag align);
    void setTextPointSize(int size);
    void setTextFontFam(QString text);
    void setTextFontStyle(QFont::Style style);
    void setTextFontWeight(QFont::Weight weight);

    QPoint getOrigin() const;
    int getLength() const;
    int getWidth() const;
    QString getTextString() const;
    Qt::GlobalColor getTextColor() const;
    Qt::AlignmentFlag getTextAlign() const;
    int getTextPointSize() const;
    QString getTextFontFam() const;
    QFont::Style getTextFontStyle() const;
    QFont::Weight getTextFontWeight() const;

    void draw() const override;
    void move(int deltaX, int deltaY) override;
    double perimeter() const override;
    double area() const override;

private:
    QPoint origin;  // top left corner
    int length; //make int
    int width;  //make int
    QString textString;
    Qt::GlobalColor textColor;
    Qt::AlignmentFlag textAlign;
    int textPointSize;
    QString textFontFam;
    QFont::Style textFontStyle; //Use QPoint Style enum
    QFont::Weight textFontWeight;
};

#endif // _TEXT_H

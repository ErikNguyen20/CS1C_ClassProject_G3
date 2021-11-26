#include "shapes.h"

// TEXT CLASS CODE

Text::Text() : Shape(), origin{0, 0}, length(0), width(0), textString(""),
               textColor(white), textAlign(AlignLeft), textPointSize(0), textFontFam(""),
               textFontStyle(StyleNormal), textFontWeight(Thin) {}

Text::Text(QString text) : Shape(), origin{0, 0}, length(0), width(0), textString(text),
                           textColor(white), textAlign(AlignLeft), textPointSize(0), textFontFam(""),
                           textFontStyle(StyleNormal), textFontWeight(Thin) {}

Text::~Text() {}

void Text::setOrigin(QPoint newOrigin)
{ origin = newOrigin; }

void Text::setLength(double l)
{ length = l; }

void Text::setWdith(double w)
{ width = w; }

void Text::setTextString(QString text)
{ textString = text; }

void Text::setTextColor(GlobalColor color)
{ textColor = color; }

void Text::setTextAlign(AlignmentFlag align)
{ textAlign = align; }

void Text::setTextPointSize(int size)
{ textPointSize = size; }

void Text::setTextFontFam(QString text)
{ textFontFam = text; }

void Text::setTextFontStyle(Style style)
{ textFontStyle = style; }

void Text::setTextFontWeight(Weight weight)
{ textFontWeight = weight; }

QPoint Text::getOrigin() const
{ return origin; }

double Text::getLength() const
{ return length; }

double Text::getWidth() const
{ return width; }

QString Text::getTextString() const
{ return textString; }

GlobalColor Text::getTextColor() const
{ return textColor; }

AlignmentFlag Text::getTextAlign() const
{ return textAlign; }

int Text::getTextPointSize() const
{ return textPointSize; }

QString Text::getTextFontFam() const
{ return textFontFam; }

Style Text::getTextFontStyle() const
{ return textFontStyle; }

Weight Text::getTextFontWeight() const
{ return textFontWeight; }

void Text::draw() const {}
void Text::move() const {}
double Text::perimeter() const { return 0; }
double Text::area() const { return 0; }

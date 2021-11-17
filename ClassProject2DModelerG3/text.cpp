#include "shapes.h"

// TEXT CLASS CODE

Text::Text() : Shape(), origin{0, 0}, length(0), width(0), textString(""),
               textColor(white), textAlign(AlignLeft), textPointSize(0), textFontFam(""),
               textFontStyle(StyleNormal), textFontWeight(Thin) {}

Text::Text(const Text &copy) : Shape(copy), length(copy.getLength()), width(copy.getWidth()),
                               textString(copy.getTextString()), textColor(copy.getTextColor()),
                               textAlign(copy.getTextAlign()), textPointSize(copy.getTextPointSize()),
                               textFontFam(copy.getTextFontFam()), textFontStyle(copy.getTextFontStyle()),
                               textFontWeight(copy.getTextFontWeight()) {}

Text::Text(QString text) : Shape(), origin{0, 0}, length(0), width(0), textString(text),
                           textColor(white), textAlign(AlignLeft), textPointSize(0), textFontFam(""),
                           textFontStyle(StyleNormal), textFontWeight(Thin) {}

Text::~Text() {}

void Text::setOrigin(Point newOrigin)
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

Point Text::getOrigin() const
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

#include "shapes.h"

// TEXT CLASS CODE

Text::Text() : Shape(), origin{0, 0}, length(0), width(0), textString(""),
               textColor(Qt::white), textAlign(Qt::AlignLeft), textPointSize(0), textFontFam(""),
               textFontStyle(QFont::StyleNormal), textFontWeight(QFont::Thin) {}

Text::Text(QString text) : Shape(), origin{0, 0}, length(0), width(0), textString(text),
                           textColor(Qt::white), textAlign(Qt::AlignLeft), textPointSize(0), textFontFam(""),
                           textFontStyle(QFont::StyleNormal), textFontWeight(QFont::Thin) {}

Text::~Text() {}

void Text::setOrigin(QPoint newOrigin)
{ origin = newOrigin; }

void Text::setLength(double l)
{ length = l; }

void Text::setWdith(double w)
{ width = w; }

void Text::setTextString(QString text)
{ textString = text; }

void Text::setTextColor(Qt::GlobalColor color)
{ textColor = color; }

void Text::setTextAlign(Qt::AlignmentFlag align)
{ textAlign = align; }

void Text::setTextPointSize(int size)
{ textPointSize = size; }

void Text::setTextFontFam(QString text)
{ textFontFam = text; }

void Text::setTextFontStyle(QFont::Style style)
{ textFontStyle = style; }

void Text::setTextFontWeight(QFont::Weight weight)
{ textFontWeight = weight; }

QPoint Text::getOrigin() const
{ return origin; }

double Text::getLength() const
{ return length; }

double Text::getWidth() const
{ return width; }

QString Text::getTextString() const
{ return textString; }

Qt::GlobalColor Text::getTextColor() const
{ return textColor; }

Qt::AlignmentFlag Text::getTextAlign() const
{ return textAlign; }

int Text::getTextPointSize() const
{ return textPointSize; }

QString Text::getTextFontFam() const
{ return textFontFam; }

QFont::Style Text::getTextFontStyle() const
{ return textFontStyle; }

QFont::Weight Text::getTextFontWeight() const
{ return textFontWeight; }

void Text::draw() const {}
void Text::move() const {}
double Text::perimeter() const { return 0; }
double Text::area() const { return 0; }

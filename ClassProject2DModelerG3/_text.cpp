#include "_text.h"

Text::Text() : Shape(), origin{0, 0}, length(0), width(0), textString(""),
               textColor(Qt::white), textAlign(Qt::AlignLeft), textPointSize(0), textFontFam(""),
               textFontStyle(QFont::StyleNormal), textFontWeight(QFont::Thin) {}

Text::Text(QString text) : Shape(), origin{0, 0}, length(0), width(0), textString(text),
                           textColor(Qt::white), textAlign(Qt::AlignLeft), textPointSize(0), textFontFam(""),
                           textFontStyle(QFont::StyleNormal), textFontWeight(QFont::Thin) {}

Text::Text(int id, QPoint origin, int length, int width, QString textstring, Qt::GlobalColor textColor, Qt::AlignmentFlag textAlign, int textPointSize, QString textFontFam, QFont::Style textFontStyle, QFont::Weight textFontWeight)
    : origin(origin), length(length), width(width), textString(textstring),
      textColor(textColor), textAlign(textAlign), textPointSize(textPointSize), textFontFam(textFontFam),
      textFontStyle(textFontStyle), textFontWeight(textFontWeight)
{
    setID(id);
}

Text::~Text() {}

void Text::setOrigin(QPoint newOrigin)
{ origin = newOrigin; }

void Text::setLength(int l)
{ length = l; }

void Text::setWidth(int w)
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

int Text::getLength() const
{ return length; }

int Text::getWidth() const
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

double Text::perimeter() const
{ return length + length + width + width; }

double Text::area() const
{ return length * width; }

void Text::draw() const
{
    QFont newFont;
    newFont.setFamily(getTextFontFam());
    newFont.setWeight(getTextFontWeight());
    newFont.setStyle(getTextFontStyle());
    newFont.setPointSize(getTextPointSize());

    getPainter()->setPen(getTextColor());
    getPainter()->setFont(newFont);

    getPainter()->drawText(getOrigin().x(),getOrigin().y(),getLength(),getWidth(),getTextAlign(),getTextString());
}
void Text::move(int deltaX, int deltaY)
{
    origin.setX(deltaX);
    origin.setY(deltaY);
}

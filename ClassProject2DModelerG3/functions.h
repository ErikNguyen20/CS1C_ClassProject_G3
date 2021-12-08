#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "shapemaster.h"
#include "vector.h"
#include "parserexception.h"
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QRegularExpression>

using std::endl;

/******************** CONSTANTS ********************/

const QStringList SHAPE_LIST = {"Line","Polyline","Polygon","Rectangle","Square","Ellipse","Circle","Text"};
const QStringList GLOBALCOLOR_LIST = {"white","black","red","green","blue","cyan","magenta","yellow","gray"};
const QStringList PENSTYLE_LIST = {"NoPen","SolidLine","DashLine","DotLine","DashDotLine","DashDotDotLine"};
const QStringList PENCAPSTYLE_LIST = {"FlatCap","SquareCap","RoundCap"};
const QStringList PENJOINSTYLE_LIST = {"MiterJoin","BevelJoin","RoundJoin"};
const QStringList BRUSHSTYLE_LIST = {"SolidPattern","HorPattern","VerPattern","NoBrush"};
const QStringList ALIGNMENTFLAG_LIST = {"AlignLeft","AlignRight","AlignTop","AlignBottom","AlignCenter"};
const QStringList QFONTSTYLE_LIST = {"StyleNormal","StyleItalic","StyleOblique"};
const QStringList QFONTWEIGHT_LIST = {"Thin","Light","Normal","Bold"};


/******************** Function Prototypes ********************/

Qt::GlobalColor QStringToGlobalColor(const QString& color,bool& success);
Qt::PenStyle QStringToPenStyle(const QString& penstyle,bool& success);
Qt::PenCapStyle QStringToPenCapStyle(const QString& pencapstyle,bool& success);
Qt::PenJoinStyle QStringToPenJoinStyle(const QString& penjoinstyle,bool& success);
Qt::BrushStyle QStringToBrushStyle(const QString& brushstyle,bool& success);
Qt::AlignmentFlag QStringToAlignmentFlag(const QString& alignmentflag,bool& success);
QFont::Style QStringToQFontStyle(const QString& qfontstyle,bool& success);
QFont::Weight QStringToQFontWeight(const QString& qfontweight,bool& success);
void writeShapesToFile(QTextStream& file, const vector<Shape*> &shapes);
void readShapesFromFile(QTextStream& file, vector<Shape*> &shapes) throw(ParserException);
void printPolyshapeDataToFile(QTextStream& file, PolyShape* polyshape);
void printTextShapeDataToFile(QTextStream& file, Text* text);
QString colorToString(const Qt::GlobalColor& color);
QString penJoinStyleToString(const Qt::PenJoinStyle& penJoinStyleEnum);
QString penCapStyleToString(const Qt::PenCapStyle& capStyle);
QString penStyleToString(const Qt::PenStyle& penStyleEnum);
QString brushStyleToString(const Qt::BrushStyle& brushStyle);
QString textAlignToString(const Qt::AlignmentFlag& alignment);
QString textStyleToString(const QFont::Style& style);
QString textWeightToString(const QFont::Weight& weight);

#endif // FUNCTIONS_H

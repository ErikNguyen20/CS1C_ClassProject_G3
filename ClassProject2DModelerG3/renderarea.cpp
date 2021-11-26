#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    resize(parent->width(),parent->height());
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::SetShapes(const vector<Shape*>& newShapes)
{
    shapes = newShapes;
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);

    //for(int index = 0; index < shapes.size(); index ++)
    //{
        //Shape* shape = shapes[index];

        painter.save();

        //switch(Line/*shapes[index]->shapeEnum*/)
        //{
        QPen newPen;
        QBrush newBrush;
        //case Line:
            //newPen.setCapStyle(Qt::FlatCap/*shape->penCapStyle*/);
            //newPen.setColor(Qt::blue/*shape->penColor*/);
            //newPen.setStyle(Qt::DashDotLine/*shape->penStyle*/);
            //newPen.setJoinStyle(Qt::MiterJoin/*shape->penJoinStyle*/);
            //newPen.setWidth(2/*shape->penWidth*/);
                //QPoint a(20,90);
                //QPoint b(100,20);
            //painter.setPen(newPen);
            //painter.drawLine(a,b/*shape->startPoint,shape->endPoint*/);
            //break;
        /*case Polyline:
            newPen.setCapStyle(shape->penCapStyle);
            newPen.setColor(shape->penColor);
            newPen.setStyle(shape->penStyle);
            newPen.setJoinStyle(shape->penJoinStyle);
            newPen.setWidth(shape->penWidth);

            painter.setPen(newPen);
            painter.drawPolyline(shape->pointVector, shape->pointCount);
            break;
        case Polygon:
            newPen.setCapStyle(shape->penCapStyle);
            newPen.setColor(shape->penColor);
            newPen.setStyle(shape->penStyle);
            newPen.setJoinStyle(shape->penJoinStyle);
            newPen.setWidth(shape->penWidth);

            newBrush.setColor(shape->brushColor);
            newBrush.setStyle(shape->brushStyle);

            painter.setPen(newPen);
            painter.setBrush(newBrush);
            painter.drawPolygon(shape->pointVector, shape->pointCount);
            break;
        case Rectangle:
            newPen.setCapStylpathe(shape->penCapStyle);
            newPen.setColor(shape->penColor);
            newPen.setStyle(shape->penStyle);
            newPen.setJoinStyle(shape->penJoinStyle);
            newPen.setWidth(shape->penWidth);

            newBrush.setColor(shape->brushColor);
            newBrush.setStyle(shape->brushStyle);

            painter.setPen(newPen);
            painter.setBrush(newBrush);
            painter.drawRect(shape->origin.x(),shape->origin.y(),shape->length,shape->width);
            break;
        case Square:
            newPen.setCapStyle(shape->penCapStyle);
            newPen.setColor(shape->penColor);
            newPen.setStyle(shape->penStyle);
            newPen.setJoinStyle(shape->penJoinStyle);
            newPen.setWidth(shape->penWidth);

            newBrush.setColor(shape->brushColor);
            newBrush.setStyle(shape->brushStyle);

            painter.setPen(newPen);
            painter.setBrush(newBrush);
            painter.drawRect(shape->origin.x(),shape->origin.y(),shape->length,shape->width);
            break;
        case Ellipse:
            newPen.setCapStyle(shape->penCapStyle);
            newPen.setColor(shape->penColor);
            newPen.setStyle(shape->penStyle);
            newPen.setJoinStyle(shape->penJoinStyle);
            newPen.setWidth(shape->penWidth);

            newBrush.setColor(shape->brushColor);
            newBrush.setStyle(shape->brushStyle);

            painter.setPen(newPen);
            painter.setBrush(newBrush);
            painter.drawEllipse(shape->origin,shape->a,shape->b);
            break;
        case Circle:
            newPen.setCapStyle(shape->penCapStyle);
            newPen.setColor(shape->penColor);
            newPen.setStyle(shape->penStyle);
            newPen.setJoinStyle(shape->penJoinStyle);
            newPen.setWidth(shape->penWidth);

            newBrush.setColor(shape->brushColor);
            newBrush.setStyle(shape->brushStyle);

            painter.setPen(newPen);
            painter.setBrush(newBrush);
            painter.drawEllipse(shape->origin,shape->a,shape->b);
            break;
        case Text:*/
            QFont newFont;
            newFont.setFamily("Comic Sans MS" /*shape->textFontFam*/);
            newFont.setWeight(QFont::Normal/*shape->textFontWeight*/);
            newFont.setStyle(QFont::StyleItalic/*shape->textFontStyle*/);
            newFont.setPointSize(10/*shape->textPointSize*/);

            painter.setPen(Qt::blue/*shape->textColor*/);
            painter.setFont(newFont);

            painter.drawText(240,425,500,50,Qt::AlignCenter,"Class Project 2 - 2D Graphics Modeler" /*shape->origin.x(),shape->origin.y(),shape->length,shape->width,shape->textAlign,shape->textString*/);
            //break;
        //}

        painter.restore();
    //}

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

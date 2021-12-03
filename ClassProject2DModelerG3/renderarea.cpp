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
    return QSize(200, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(2000, 1000);
}

void RenderArea::SetShapes(vector<Shape*> newShapes)
{
    shapes = std::move(newShapes);
    update();
}

vector<Shape*> RenderArea::GetShapes() const
{
    return shapes;
}

/******************** Paint Event (Triggers on update) ********************/

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);

    for(int index = 0; index < shapes.size(); index ++)
    {
        shapes[index]->setPainter(&painter);
        shapes[index]->draw();
    }
}

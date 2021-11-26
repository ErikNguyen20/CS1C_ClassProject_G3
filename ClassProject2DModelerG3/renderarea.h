#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include "vector.h"
#include "shapes.h"

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape {Line, Polyline, Polygon, Rectangle, Square, Ellipse, Circle, Text};

    RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void SetShapes(const vector<Shape*>& newShapes);

protected:

    void paintEvent(QPaintEvent *event) override;

private:
    vector<Shape*> shapes;

};


#endif // RENDERAREA_H

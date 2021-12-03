#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include "vector.h"
#include "shapemaster.h"

class RenderArea : public QWidget
{
    Q_OBJECT

public:

    RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void SetShapes(vector<Shape*> newShapes);

    vector<Shape*> GetShapes() const;

protected:

    void paintEvent(QPaintEvent *event) override;

private:
    vector<Shape*> shapes;

};


#endif // RENDERAREA_H

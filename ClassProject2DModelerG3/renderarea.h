#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include "vector.h"
#include "shapemaster.h"

//! Render Area Class
/*! Class that uses QPainter to render an area on a widget. */
class RenderArea : public QWidget
{
    Q_OBJECT

public:

    //! Alternate Constructor
    /*! Constructs a new render area object.
        \param parent a QWidget argument for the parent widget.
    */
    RenderArea(QWidget *parent = 0);

    //! Member function that returns the minium size of the widget.
    /*!
        \return QSize for the minium widget size.
    */
    QSize minimumSizeHint() const override;

    //! Member function that returns the maximum size of the widget.
    /*!
        \return QSize of the maximum widget size.
    */
    QSize sizeHint() const override;

    //! Member function that sets the shapes that are being rendered.
    /*!
        \param newShape a vector of shape pointers.
    */
    void SetShapes(vector<Shape*> newShapes);

    //! Member function that returns the shapes currently rendered by the object.
    /*!
        \return A vector of shape pointers.
    */
    vector<Shape*> GetShapes() const;

protected:
    //! Member function that updates the render area.
    /*!
        \param event a QPaintEvent pointer.
    */
    void paintEvent(QPaintEvent *event) override;

private:
    //! A private variable data member.
    /*! Contains the shapes currently rendered by the render area object. */
    vector<Shape*> shapes;

};


#endif // RENDERAREA_H

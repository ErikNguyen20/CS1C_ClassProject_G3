#ifndef ADDELLIPSEDETAILS_H
#define ADDELLIPSEDETAILS_H

#include <QDialog>
#include "renderarea.h"

namespace Ui {
class addEllipseDetails;
}

//! addEllipseDetails Class
/*! Derived from QDialog. */
class addEllipseDetails : public QDialog
{
    Q_OBJECT

public:

    //! Alternate Constructor
    /*! Constructs a new object.
        \param parent a QWidget argument for the parent widget.
    */
    explicit addEllipseDetails(QWidget *parent = nullptr);

    //! Destructor
    /*! Destructs the dialog window. */
    ~addEllipseDetails();

    //! Member function that returns the shape.
    /*!
        \return Pointer to the created shape.
    */
    Shape* GetShape();

    //! Member function that returns the status of the shape creation.
    /*!
        \return A boolean value (true or false).
    */
    bool GetSuccessBool();

private slots:

    void on_buttonBox_accepted(); //!< Triggers when the confirm button is activated.

private:
    Ui::addEllipseDetails *ui; //!< The ui belonging to this widget.
    Shape *newEllipse;         //!< A shape pointer to the created shape.
    bool isSuccessful;         //!< Status of the shape creation.
};

#endif // ADDELLIPSEDETAILS_H

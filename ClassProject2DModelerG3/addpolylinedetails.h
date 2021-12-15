#ifndef ADDPOLYLINEDETAILS_H
#define ADDPOLYLINEDETAILS_H

#include <QDialog>
#include "renderarea.h"

namespace Ui {
class addPolylineDetails;
}

//! addPolylineDetails Class
/*! Derived from QDialog. */
class addPolylineDetails : public QDialog
{
    Q_OBJECT

public:

    //! Alternate Constructor
    /*! Constructs a new object.
        \param parent a QWidget argument for the parent widget.
    */
    explicit addPolylineDetails(QWidget *parent = nullptr);

    //! Destructor
    /*! Destructs the dialog window. */
    ~addPolylineDetails();

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
    Ui::addPolylineDetails *ui; //!< The ui belonging to this widget.
    Shape *newPolyline;         //!< A shape pointer to the created shape.
    bool isSuccessful;          //!< Status of the shape creation.
};

#endif // ADDPOLYLINEDETAILS_H

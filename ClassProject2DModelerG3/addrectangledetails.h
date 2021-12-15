#ifndef ADDRECTANGLEDETAILS_H
#define ADDRECTANGLEDETAILS_H

#include <QDialog>
#include "renderarea.h"

namespace Ui {
class addRectangleDetails;
}
//! addRectangleDetails Class
/*! Derived from QDialog. */
class addRectangleDetails : public QDialog
{
    Q_OBJECT

public:
    //! Alternate Constructor
    /*! Constructs a new object.
        \param parent a QWidget argument for the parent widget.
    */
    explicit addRectangleDetails(QWidget *parent = nullptr);

    //! Destructor
    /*! Destructs the dialog window. */
    ~addRectangleDetails();

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
    Ui::addRectangleDetails *ui; //!< The ui belonging to this widget.
    Shape *newRectangle;         //!< A shape pointer to the created shape.
    bool isSuccessful;           //!< Status of the shape creation.
};

#endif // ADDRECTANGLEDETAILS_H

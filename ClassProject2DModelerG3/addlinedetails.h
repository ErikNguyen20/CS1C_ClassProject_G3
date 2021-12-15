#ifndef ADDLINEDETAILS_H
#define ADDLINEDETAILS_H

#include <QDialog>
#include "renderarea.h"

namespace Ui {
class addLineDetails;
}

//! addLineDetails Class
/*! Derived from QDialog. */
class addLineDetails : public QDialog
{
    Q_OBJECT

public:
    //! Alternate Constructor
    /*! Constructs a new object.
        \param parent a QWidget argument for the parent widget.
    */
    explicit addLineDetails(QWidget *parent = nullptr);

    //! Destructor
    /*! Destructs the dialog window. */
    ~addLineDetails();

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
    Ui::addLineDetails *ui; //!< The ui belonging to this widget.
    Shape *newLine;         //!< A shape pointer to the created shape.
    bool isSuccessful;      //!< Status of the shape creation.
};


#endif // ADDLINEDETAILS_H

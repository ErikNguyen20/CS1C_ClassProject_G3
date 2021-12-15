#ifndef ADDTEXTDETAILS_H
#define ADDTEXTDETAILS_H

#include <QDialog>
#include "renderarea.h"

namespace Ui {
class addTextDetails;
}

//! addTextDetails Class
/*! Derived from QDialog. */
class addTextDetails : public QDialog
{
    Q_OBJECT

public:

    //! Alternate Constructor
    /*! Constructs a new object.
        \param parent a QWidget argument for the parent widget.
    */
    explicit addTextDetails(QWidget *parent = nullptr);

    //! Destructor
    /*! Destructs the dialog window. */
    ~addTextDetails();

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
    Ui::addTextDetails *ui; //!< The ui belonging to this widget.
    Shape *newText;         //!< A shape pointer to the created shape.
    bool isSuccessful;      //!< Status of the shape creation.
};

#endif // ADDTEXTDETAILS_H

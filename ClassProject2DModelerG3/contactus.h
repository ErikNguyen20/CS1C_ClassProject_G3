#ifndef CONTACTUS_H
#define CONTACTUS_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class contactus;
}
//! contactus Class
/*! Derived from QDialog. */
class contactus : public QDialog
{
    Q_OBJECT

public:
    //! Alternate Constructor
    /*! Constructs a new object.
        \param parent a QWidget argument for the parent widget.
    */
    explicit contactus(QWidget *parent = nullptr);

    //! Destructor
    /*! Destructs the dialog window. */
    ~contactus();

private:
    Ui::contactus *ui; //!< The ui belonging to this widget.
};

#endif // CONTACTUS_H

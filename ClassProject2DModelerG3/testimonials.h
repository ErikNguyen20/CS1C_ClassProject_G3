#ifndef TESTIMONIALS_H
#define TESTIMONIALS_H

#include <QDialog>

namespace Ui {
class testimonials;
}

//! testimonials Class
/*! Derived from QDialog. */
class testimonials : public QDialog
{
    Q_OBJECT

public:
    //! Alternate Constructor
    /*! Constructs a new object.
        \param parent a QWidget argument for the parent widget.
    */
    explicit testimonials(QWidget *parent = nullptr);

    //! Destructor
    /*! Destructs the dialog window. */
    ~testimonials();

private slots:

    void on_buttonBox_accepted(); //!< Triggers when the confirm button is activated.

private:
    Ui::testimonials *ui;                               //!< The ui belonging to this widget.
    const QString testimonialFile = "testimonials.txt"; //!< The testimonial file.
};

#endif // TESTIMONIALS_H

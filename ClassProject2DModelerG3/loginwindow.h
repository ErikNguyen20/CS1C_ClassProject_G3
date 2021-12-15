#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QString>


const QString ADMINISTRATOR_USERNAME = "Admin";
const QString ADMINISTRATOR_PASSWORD = "Password";

namespace Ui {
class loginwindow;
}

//! loginwindow Class
/*! Derived from QWidget. */
class loginwindow : public QWidget
{
    Q_OBJECT

public:
    //! Alternate Constructor
    /*! Constructs a new object.
        \param parent a QWidget argument for the parent widget.
    */
    explicit loginwindow(QWidget *parent = 0);

    //! Destructor
    /*! Destructs the dialog window. */
    ~loginwindow();

signals:
    void loginSuccessful(); //!< Triggers when the login is successful.

private slots:
    void on_loginButton_clicked(); //!< Triggers when the confirm button is activated.

private:
    Ui::loginwindow *ui; //!< The ui belonging to this widget.
};

#endif // LOGINWINDOW_H

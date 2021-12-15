#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "renderarea.h"
#include "loginwindow.h"
#include "testimonials.h"
#include "contactus.h"
#include "addlinedetails.h"
#include "addpolylinedetails.h"
#include "addpolygondetails.h"
#include "addrectangledetails.h"
#include "addellipsedetails.h"
#include "addtextdetails.h"

namespace Ui {
class MainWindow;
}

//! MainWindow Class
/*! Derived from QMainWindow. */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Alternate Constructor
    /*! Constructs a new object.
        \param parent a QWidget argument for the parent widget.
    */
    explicit MainWindow(QWidget *parent = 0);

    //! Destructor
    /*! Destructs the dialog window. */
    ~MainWindow();

private slots:
    void on_actionLogin_triggered();        //!< Triggers when the login button in the actionbar is activated.

    void on_actionOpen_triggered();         //!< Triggers when the open button in the actionbar is activated.

    void on_actionSave_triggered();         //!< Triggers when the save button in the actionbar is activated.

    void on_actionSave_As_triggered();      //!< Triggers when the save-as button in the actionbar is activated.

    void on_actionNew_triggered();          //!< Triggers when the new button in the actionbar is activated.

    void Login();                           //!< Triggers when the login was successful.

    void on_actionTestimonials_triggered(); //!< Triggers when the testimonial button in the actionbar is activated.

    void on_actionContact_Us_triggered();   //!< Triggers when the contact-us button in the actionbar is activated.

    void on_actionAddLine_triggered();      //!< Triggers when the add line in the toolbar is activated.

    void on_actionAddPolyline_triggered();  //!< Triggers when the add polyline in the toolbar is activated.

    void on_actionAddPolygon_triggered();   //!< Triggers when the add polygon in the toolbar is activated.

    void on_actionAddRectangle_triggered(); //!< Triggers when the add rectangle in the toolbar is activated.

    void on_actionAddEllipse_triggered();   //!< Triggers when the add ellipse in the toolbar is activated.

    void on_actionAddText_triggered();      //!< Triggers when the add text in the toolbar is activated.

    void closeEvent(QCloseEvent *event);    //!< Triggers when the window is closing.

    void on_pushButton_clicked();           //!< Triggers when the remove shapes button is activated.

    void on_pushButton_2_clicked();         //!< Triggers when the move shapes button is activated.

private:
    Ui::MainWindow *ui;                         //!< The ui belonging to this widget.
    RenderArea *renderArea;                     //!< The area the shapes are rendered onto.
    loginwindow *loginWindow;                   //!< The login window.
    QString currentFilePath;                    //!< The current file path of the loaded shape file.
    testimonials *Testimonials;                 //!< The testimonial window.
    contactus *ContactUs;                       //!< The contact us window.
    addLineDetails *addLineWindow;              //!< The add line window.
    addPolylineDetails *addPolylineWindow;      //!< The add polyline window.
    addPolygonDetails *addPolygonWindow;        //!< The add polygon window.
    addRectangleDetails *addRectangleWindow;    //!< The add rectangle window.
    addEllipseDetails *addEllipseWindow;        //!< The add ellipse window.
    addTextDetails *addTextWindow;              //!< The add text window.
    bool needsSave;                             //!< Whether or not the current project needs to be saved.
};

#endif // MAINWINDOW_H

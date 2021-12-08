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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLogin_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionNew_triggered();

    void Login();

    void on_actionTestimonials_triggered();

    void on_actionContact_Us_triggered();

    void on_actionAddLine_triggered();

    void on_actionAddPolyline_triggered();

    void on_actionAddPolygon_triggered();

    void on_actionAddRectangle_triggered();

    void on_actionAddEllipse_triggered();

    void on_actionAddText_triggered();

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;
    loginwindow *loginWindow;
    QString currentFilePath;
    testimonials *Testimonials;
    contactus *ContactUs;
    addLineDetails *addLineWindow;
    addPolylineDetails *addPolylineWindow;
    addPolygonDetails *addPolygonWindow;
    addRectangleDetails *addRectangleWindow;
    addEllipseDetails *addEllipseWindow;
    addTextDetails *addTextWindow;
    bool needsSave;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "renderarea.h"
#include "loginwindow.h"
#include "testimonials.h"
#include "contactus.h"

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

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;
    loginwindow *loginWindow;
    QString currentFilePath;
    vector<Shape*> currentShapes;
    testimonials *Testimonials;
    contactus *ContactUs;
};

#endif // MAINWINDOW_H

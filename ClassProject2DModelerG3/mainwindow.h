#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "renderarea.h"
#include "loginwindow.h"

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

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;
    loginwindow *loginWindow;
    QString currentFilePath;
    vector<Shape*> currentShapes;
};

#endif // MAINWINDOW_H

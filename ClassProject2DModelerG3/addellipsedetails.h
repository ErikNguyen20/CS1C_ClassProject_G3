#ifndef ADDELLIPSEDETAILS_H
#define ADDELLIPSEDETAILS_H

#include <QDialog>
#include "renderarea.h"

namespace Ui {
class addEllipseDetails;
}

class addEllipseDetails : public QDialog
{
    Q_OBJECT

public:
    explicit addEllipseDetails(QWidget *parent = nullptr);
    ~addEllipseDetails();

    Shape* GetShape();

    bool GetSuccessBool();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addEllipseDetails *ui;
    Shape *newEllipse;
    bool isSuccessful;
};

#endif // ADDELLIPSEDETAILS_H

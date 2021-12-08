#ifndef ADDPOLYLINEDETAILS_H
#define ADDPOLYLINEDETAILS_H

#include <QDialog>
#include "renderarea.h"

namespace Ui {
class addPolylineDetails;
}

class addPolylineDetails : public QDialog
{
    Q_OBJECT

public:
    explicit addPolylineDetails(QWidget *parent = nullptr);
    ~addPolylineDetails();

    Shape* GetShape();

    bool GetSuccessBool();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addPolylineDetails *ui;
    Shape *newPolyline;
    bool isSuccessful;
};

#endif // ADDPOLYLINEDETAILS_H

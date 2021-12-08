#ifndef ADDPOLYGONDETAILS_H
#define ADDPOLYGONDETAILS_H

#include <QDialog>
#include "renderarea.h"

namespace Ui {
class addPolygonDetails;
}

class addPolygonDetails : public QDialog
{
    Q_OBJECT

public:
    explicit addPolygonDetails(QWidget *parent = nullptr);
    ~addPolygonDetails();

    Shape* GetShape();

    bool GetSuccessBool();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addPolygonDetails *ui;
    Shape *newPolygon;
    bool isSuccessful;
};

#endif // ADDPOLYGONDETAILS_H

#ifndef ADDRECTANGLEDETAILS_H
#define ADDRECTANGLEDETAILS_H

#include <QDialog>
#include "renderarea.h"

namespace Ui {
class addRectangleDetails;
}

class addRectangleDetails : public QDialog
{
    Q_OBJECT

public:
    explicit addRectangleDetails(QWidget *parent = nullptr);
    ~addRectangleDetails();

    Shape* GetShape();

    bool GetSuccessBool();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addRectangleDetails *ui;
    Shape *newRectangle;
    bool isSuccessful;
};

#endif // ADDRECTANGLEDETAILS_H

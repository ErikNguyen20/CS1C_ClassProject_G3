#ifndef ADDLINEDETAILS_H
#define ADDLINEDETAILS_H

#include <QDialog>
#include "renderarea.h"

namespace Ui {
class addLineDetails;
}

class addLineDetails : public QDialog
{
    Q_OBJECT

public:
    explicit addLineDetails(QWidget *parent = nullptr);
    ~addLineDetails();

    Shape* GetShape();

    bool GetSuccessBool();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addLineDetails *ui;
    Shape *newLine;
    bool isSuccessful;
};


#endif // ADDLINEDETAILS_H

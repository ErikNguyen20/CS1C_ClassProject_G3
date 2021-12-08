#ifndef ADDTEXTDETAILS_H
#define ADDTEXTDETAILS_H

#include <QDialog>
#include "renderarea.h"

namespace Ui {
class addTextDetails;
}

class addTextDetails : public QDialog
{
    Q_OBJECT

public:
    explicit addTextDetails(QWidget *parent = nullptr);
    ~addTextDetails();

    Shape* GetShape();

    bool GetSuccessBool();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addTextDetails *ui;
    Shape *newText;
    bool isSuccessful;
};

#endif // ADDTEXTDETAILS_H

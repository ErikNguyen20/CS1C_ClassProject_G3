#ifndef CONTACTUS_H
#define CONTACTUS_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class contactus;
}

class contactus : public QDialog
{
    Q_OBJECT

public:
    explicit contactus(QWidget *parent = nullptr);
    ~contactus();

private:
    Ui::contactus *ui;
};

#endif // CONTACTUS_H

#ifndef TESTIMONIALS_H
#define TESTIMONIALS_H

#include <QDialog>

namespace Ui {
class testimonials;
}

class testimonials : public QDialog
{
    Q_OBJECT

public:
    explicit testimonials(QWidget *parent = nullptr);
    ~testimonials();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::testimonials *ui;
    const QString testimonialFile = "testimonials.txt";
};

#endif // TESTIMONIALS_H

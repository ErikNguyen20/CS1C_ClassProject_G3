#include "contactus.h"
#include "ui_contactus.h"
#include <iostream>

contactus::contactus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contactus)
{
    ui -> setupUi(this);
    setWindowTitle("Contact Us");
    ui -> urlLabel -> setText("<a href=\"https://github.com/ErikNguyen20/CS1C_ClassProject_G3\">https://github.com/ErikNguyen20/CS1C_ClassProject_G3</a>");
    ui -> urlLabel -> setTextFormat(Qt::RichText);
    ui -> urlLabel -> setTextInteractionFlags(Qt::TextBrowserInteraction);
    QString fileName = ":images/midnight-oil.jpg";
    QPixmap image;
    ui -> label -> setAlignment(Qt::AlignCenter);
    if(image.load(fileName))
    {
        image = image.scaled(ui -> label -> size(), Qt::KeepAspectRatio);
        ui -> label -> setPixmap(image);
    }
    else
    {
        std::cerr << "Error loading image.";
    }
}

contactus::~contactus()
{
    delete ui;
}

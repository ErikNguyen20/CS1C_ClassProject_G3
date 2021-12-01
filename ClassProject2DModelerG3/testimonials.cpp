#include "testimonials.h"
#include "ui_testimonials.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include <iomanip>

testimonials::testimonials(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testimonials)
{
    ui -> setupUi(this);
    setWindowTitle("Testimonials");

    // Read the current testimonials
    // (from a .txt within the .exe or .app)
    QFile testFile(testimonialFile);
    QString currentTestimonials = "";
    if(testFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream inFile(&testFile);
        while(!inFile.atEnd())
        {
            currentTestimonials += inFile.readLine() + "\n";
        }
        if(!currentTestimonials.trimmed().isEmpty())
        {
            ui -> textDisplay -> insertPlainText(currentTestimonials);
        }
        else
        {
            QString placeholder = "There haven't been any testimonials submitted yet.";
            ui -> textDisplay -> insertPlainText(placeholder);
        }
        testFile.close();
    }
}

testimonials::~testimonials()
{
    delete ui;
}

void testimonials::on_buttonBox_accepted()
{
    // User message
    QMessageBox::information(this, "Testimonials", "Thank you for your feedback!");

    // Write to a file within the application file
    // (a .txt within the .exe or .app)
    QFile testFile(testimonialFile);
    if(testFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream outFile(&testFile);
        QString name;
        QString experience;
        name = ui -> lineEdit -> text();
        experience = ui -> plainTextEdit -> toPlainText();
        outFile << name.trimmed() << " said:\n";
        outFile << experience.trimmed() << "\n\n";
        testFile.close();
    }
    else
    {
        std::cerr << "Failed to save testimonials.";
    }
}


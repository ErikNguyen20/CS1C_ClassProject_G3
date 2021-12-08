#include "addellipsedetails.h"
#include "ui_addellipsedetails.h"
#include <QMessageBox>

/******************** Function Prototypes ********************/

Qt::GlobalColor QStringToGlobalColor(const QString& color,bool& success);
Qt::PenStyle QStringToPenStyle(const QString& penstyle,bool& success);
Qt::PenCapStyle QStringToPenCapStyle(const QString& pencapstyle,bool& success);
Qt::PenJoinStyle QStringToPenJoinStyle(const QString& penjoinstyle,bool& success);
Qt::BrushStyle QStringToBrushStyle(const QString& brushstyle,bool& success);
Qt::AlignmentFlag QStringToAlignmentFlag(const QString& alignmentflag,bool& success);
QFont::Style QStringToQFontStyle(const QString& qfontstyle,bool& success);
QFont::Weight QStringToQFontWeight(const QString& qfontweight,bool& success);

addEllipseDetails::addEllipseDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addEllipseDetails),
    newEllipse(nullptr),
    isSuccessful(true)
{
    ui->setupUi(this);
    setWindowTitle("Add Ellipse");
}

addEllipseDetails::~addEllipseDetails()
{
    delete ui;
    delete newEllipse;
}

Shape* addEllipseDetails::GetShape()
{
    return newEllipse;
}

bool addEllipseDetails::GetSuccessBool()
{
    return isSuccessful;
}

void addEllipseDetails::on_buttonBox_accepted()
{
    QPoint origin(ui->textEdit->toPlainText().toInt(),ui->textEdit_2->toPlainText().toInt());
    int semiMajorAxis = ui->textEdit_3->toPlainText().toInt();
    int semiMinorAxis = ui->textEdit_4->toPlainText().toInt();
    QString penColor = ui->textEdit_5->toPlainText();
    Qt::GlobalColor qtPenColor = QStringToGlobalColor(penColor, isSuccessful);
    int penWidth = ui->textEdit_6->toPlainText().toInt();
    QString penStyle = ui->textEdit_7->toPlainText();
    Qt::PenStyle qtPenStyle = QStringToPenStyle(penStyle, isSuccessful);
    QString penCapStyle = ui->textEdit_8->toPlainText();
    Qt::PenCapStyle qtPenCapStyle = QStringToPenCapStyle(penCapStyle, isSuccessful);
    QString penJoinStyle = ui->textEdit_9->toPlainText();
    Qt::PenJoinStyle qtPenJoinStyle = QStringToPenJoinStyle(penJoinStyle, isSuccessful);
    QString brushColor = ui->textEdit_10->toPlainText();
    Qt::GlobalColor qtBrushColor = QStringToGlobalColor(brushColor, isSuccessful);
    QString brushStyle = ui->textEdit_11->toPlainText();
    Qt::BrushStyle qtBrushStyle = QStringToBrushStyle(brushStyle, isSuccessful);

    if(!isSuccessful)
    {
        QMessageBox::information(this, "Failed to add line", "incorrect input");
    }
    else
    {
        newEllipse = new Ellipse(0, origin, semiMajorAxis, semiMinorAxis, qtPenColor, penWidth, qtPenStyle, qtPenCapStyle, qtPenJoinStyle, qtBrushColor, qtBrushStyle);
    }
}


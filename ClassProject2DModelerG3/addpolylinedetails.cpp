#include "addpolylinedetails.h"
#include "ui_addpolylinedetails.h"
#include <QMessageBox>
#include "vector.h"

/******************** Function Prototypes ********************/

Qt::GlobalColor QStringToGlobalColor(const QString& color,bool& success);
Qt::PenStyle QStringToPenStyle(const QString& penstyle,bool& success);
Qt::PenCapStyle QStringToPenCapStyle(const QString& pencapstyle,bool& success);
Qt::PenJoinStyle QStringToPenJoinStyle(const QString& penjoinstyle,bool& success);
Qt::BrushStyle QStringToBrushStyle(const QString& brushstyle,bool& success);
Qt::AlignmentFlag QStringToAlignmentFlag(const QString& alignmentflag,bool& success);
QFont::Style QStringToQFontStyle(const QString& qfontstyle,bool& success);
QFont::Weight QStringToQFontWeight(const QString& qfontweight,bool& success);

addPolylineDetails::addPolylineDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addPolylineDetails),
    newPolyline(nullptr),
    isSuccessful(true)
{
    ui->setupUi(this);
    setWindowTitle("Add Polyline");
}

addPolylineDetails::~addPolylineDetails()
{
    delete ui;
    delete newPolyline;
}

Shape* addPolylineDetails::GetShape()
{
    return newPolyline;
}

bool addPolylineDetails::GetSuccessBool()
{
    return isSuccessful;
}

void addPolylineDetails::on_buttonBox_accepted()
{
    vector<QPoint> points;
    points.push_back(QPoint(ui->textEdit->toPlainText().toInt(), ui->textEdit_2->toPlainText().toInt()));
    points.push_back(QPoint(ui->textEdit_3->toPlainText().toInt(), ui->textEdit_4->toPlainText().toInt()));
    points.push_back(QPoint(ui->textEdit_5->toPlainText().toInt(), ui->textEdit_6->toPlainText().toInt()));
    points.push_back(QPoint(ui->textEdit_7->toPlainText().toInt(), ui->textEdit_8->toPlainText().toInt()));
    QString penColor = ui->textEdit_9->toPlainText();
    Qt::GlobalColor qtPenColor = QStringToGlobalColor(penColor, isSuccessful);
    int penWidth = ui->textEdit_10->toPlainText().toInt();
    QString penStyle = ui->textEdit_11->toPlainText();
    Qt::PenStyle qtPenStyle = QStringToPenStyle(penStyle, isSuccessful);
    QString penCapStyle = ui->textEdit_12->toPlainText();
    Qt::PenCapStyle qtPenCapStyle = QStringToPenCapStyle(penCapStyle, isSuccessful);
    QString penJoinStyle = ui->textEdit_13->toPlainText();
    Qt::PenJoinStyle qtPenJoinStyle = QStringToPenJoinStyle(penJoinStyle, isSuccessful);

    if(!isSuccessful)
    {
        QMessageBox::information(this, "Failed to add line", "incorrect input");
    }
    else
    {
        newPolyline = new Polyline(0, points, qtPenColor, penWidth, qtPenStyle, qtPenCapStyle, qtPenJoinStyle);
    }
}


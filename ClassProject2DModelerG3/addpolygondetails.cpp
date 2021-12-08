#include "addpolygondetails.h"
#include "ui_addpolygondetails.h"
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

addPolygonDetails::addPolygonDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addPolygonDetails),
    newPolygon(nullptr),
    isSuccessful(true)
{
    ui->setupUi(this);
    setWindowTitle("Add Polygon");
}

addPolygonDetails::~addPolygonDetails()
{
    delete ui;
    delete newPolygon;
}

Shape* addPolygonDetails::GetShape()
{
    return newPolygon;
}

bool addPolygonDetails::GetSuccessBool()
{
    return isSuccessful;
}

void addPolygonDetails::on_buttonBox_accepted()
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
    QString brushColor = ui->textEdit_14->toPlainText();
    Qt::GlobalColor qtBrushColor = QStringToGlobalColor(brushColor, isSuccessful);
    QString brushStyle = ui->textEdit_15->toPlainText();
    Qt::BrushStyle qtBrushStyle = QStringToBrushStyle(brushStyle, isSuccessful);

    if(!isSuccessful)
    {
        QMessageBox::information(this, "Failed to add line", "incorrect input");
    }
    else
    {
        newPolygon = new Polygon(0, points, qtPenColor, penWidth, qtPenStyle, qtPenCapStyle, qtPenJoinStyle, qtBrushColor, qtBrushStyle);
    }
}


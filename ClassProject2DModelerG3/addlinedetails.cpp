#include "addlinedetails.h"
#include "ui_addlinedetails.h"
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

addLineDetails::addLineDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addLineDetails),
    newLine(nullptr),
    isSuccessful(true)
{
    ui->setupUi(this);
    setWindowTitle("Add Line");
}

addLineDetails::~addLineDetails()
{
    delete ui;
    delete newLine;
}

Shape* addLineDetails::GetShape()
{
    return newLine;
}

bool addLineDetails::GetSuccessBool()
{
    return isSuccessful;
}

void addLineDetails::on_buttonBox_accepted()
{
    QPoint start(ui->textEdit->toPlainText().toInt(),ui->textEdit_2->toPlainText().toInt());
    QPoint end(ui->textEdit_3->toPlainText().toInt(),ui->textEdit_4->toPlainText().toInt());
    QString penColor = ui->textEdit_5->toPlainText();
    Qt::GlobalColor qtPenColor = QStringToGlobalColor(penColor, isSuccessful);
    int penWidth = ui->textEdit_6->toPlainText().toInt();
    QString penStyle = ui->textEdit_7->toPlainText();
    Qt::PenStyle qtPenStyle = QStringToPenStyle(penStyle, isSuccessful);
    QString penCapStyle = ui->textEdit_8->toPlainText();
    Qt::PenCapStyle qtPenCapStyle = QStringToPenCapStyle(penCapStyle, isSuccessful);
    QString penJoinStyle = ui->textEdit_9->toPlainText();
    Qt::PenJoinStyle qtPenJoinStyle = QStringToPenJoinStyle(penJoinStyle, isSuccessful);

    if(!isSuccessful)
    {
        QMessageBox::information(this, "Failed to add line", "incorrect input");
    }
    else
    {
        newLine = new Line(0, start, end, qtPenColor, penWidth, qtPenStyle, qtPenCapStyle, qtPenJoinStyle);
    }
}

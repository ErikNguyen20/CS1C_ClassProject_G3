#include "addtextdetails.h"
#include "ui_addtextdetails.h"
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

addTextDetails::addTextDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTextDetails),
    newText(nullptr),
    isSuccessful(true)
{
    ui->setupUi(this);
    setWindowTitle("Add Text");
}

addTextDetails::~addTextDetails()
{
    delete ui;
    delete newText;
}

Shape* addTextDetails::GetShape()
{
    return newText;
}

bool addTextDetails::GetSuccessBool()
{
    return isSuccessful;
}

void addTextDetails::on_buttonBox_accepted()
{
    QPoint origin(ui->textEdit->toPlainText().toInt(),ui->textEdit_2->toPlainText().toInt());
    int length = ui->textEdit_3->toPlainText().toInt();
    int width = ui->textEdit_4->toPlainText().toInt();
    QString textString = ui->plainTextEdit->toPlainText();
    QString textColor = ui->textEdit_5->toPlainText();
    Qt::GlobalColor qtTextColor = QStringToGlobalColor(textColor, isSuccessful);
    QString textAlignment = ui->textEdit_6->toPlainText();
    Qt::AlignmentFlag qtAlignment = QStringToAlignmentFlag(textAlignment, isSuccessful);
    int textPointSize = ui->textEdit_7->toPlainText().toInt();
    QString textFontFamily = ui->textEdit_8->toPlainText();
    QString textFontStyle = ui->textEdit_9->toPlainText();
    QFont::Style qtFontStyle = QStringToQFontStyle(textFontStyle, isSuccessful);
    QString textFontWeight = ui->textEdit_10->toPlainText();
    QFont::Weight qtFontWeight = QStringToQFontWeight(textFontWeight, isSuccessful);

    if(!isSuccessful)
    {
        QMessageBox::information(this, "Failed to add text", "incorrect input");
    }
    else
    {
        newText = new Text(0, origin, length, width, textString, qtTextColor, qtAlignment, textPointSize, textFontFamily, qtFontStyle, qtFontWeight);
    }
}


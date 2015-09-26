#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QPlainTextEdit *textEdit,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    this->textEdit=textEdit;

}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_buttonBox_accepted()
{


    this->setResult(0);
    QString str=this->textEdit->toPlainText();
    QString find=ui->textEdit->toPlainText();
    QRegExp rx(find);
    int pos=str.indexOf(rx,QRegExp::FixedString);
    if(pos!=-1){

        QTextCursor t=  this->textEdit->textCursor();
        t.setPosition(pos,QTextCursor::MoveAnchor);

        t.setPosition(pos+find.length(),QTextCursor::KeepAnchor);
        this->textEdit->setTextCursor(t);
    }}

void FindDialog::on_buttonBox_clicked(QAbstractButton *button)
{

}

void FindDialog::on_buttonBox_rejected()
{
     this->close();
}

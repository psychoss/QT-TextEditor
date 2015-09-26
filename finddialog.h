#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>
#include <QAbstractButton>
namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QPlainTextEdit *textEdit ,QWidget *parent = 0);
    ~FindDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_buttonBox_rejected();

private:
    Ui::FindDialog *ui;
    QPlainTextEdit *textEdit;
};

#endif // FINDDIALOG_H

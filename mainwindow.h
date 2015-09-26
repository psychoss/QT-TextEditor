#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextDocumentFragment>
#include <QProcess>
#include <QLabel>
#include <QTextStream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_actionOpen_triggered();

    void on_actionIndentIncrease_triggered();

    void on_plainTextEdit_textChanged();

    void on_actionInsertLinks_triggered();

    void on_actionRun_triggered();



    void on_actionSave_triggered();

    void on_actionNewFile_triggered();

    void on_actionList_triggered();

    void on_actionHr_triggered();

    void on_actionImage_triggered();

    void on_plainTextEdit_customContextMenuRequested(const QPoint &pos);

    void on_editredo_triggered();

    void on_actionEditundo_triggered();

    void on_actionEditselectall_triggered();

    void on_actionEditcut_triggered();

    void on_actionEditpast_triggered();

    void on_actionCopy_triggered();

    void on_actionFind_triggered();

    void on_actionBlod_triggered();

private:
    Ui::MainWindow *ui;
    QFileDialog *fileDialog;
    QLabel *statusLabel;

    void openFile();
    void resizeEvent ( QResizeEvent * event );
    QString currentFileName;
    int findPos=0;
};

#endif // MAINWINDOW_H

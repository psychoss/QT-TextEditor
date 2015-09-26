#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finddialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusLabel=new QLabel;
    statusLabel->setMinimumSize(statusLabel->sizeHint());
    ui->statusBar->addWidget(statusLabel);
}
//打开文件
void MainWindow::openFile(){
    QString userFile=QFileDialog::getOpenFileName(this,"Open Document"
                                                  ,"./psycho","All Files(*.* *)");
    QFile file(userFile);

    if(file.open(QIODevice::ReadWrite |  QIODevice::Text))
    {
        this->currentFileName=userFile;
        QByteArray content=file.readAll();
        QString stringContent(content);
        ui->plainTextEdit->document()->clear();
        ui->plainTextEdit->appendPlainText(stringContent);
        file.close();
        this->setWindowTitle(this->currentFileName);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent ( QResizeEvent * event ){
    ui->plainTextEdit->resize(this->width(),this->height()-62);
}

void MainWindow::on_actionOpen_triggered()
{
    this->openFile();

}

void MainWindow::on_actionIndentIncrease_triggered()
{

    QString selected= ui->plainTextEdit->textCursor().selection().toPlainText();
    QString content="";

    if(selected.length()>0){
        const QStringList & result=  selected.split("\n",QString::SkipEmptyParts);
        QString str;
        foreach(str,result){
            content+="\t"+str+"\n";
        }
        QTextCursor cursor= ui->plainTextEdit->textCursor();
        cursor.insertText(content);
    }


}

void MainWindow::on_plainTextEdit_textChanged()
{
    statusLabel->setText(tr("Content Length: %1").arg(ui->plainTextEdit->toPlainText().length()));
}

void MainWindow::on_actionInsertLinks_triggered()
{
    QTextCursor cursor=  ui->plainTextEdit->textCursor();
    cursor.insertText("[]("+cursor.selectedText().trimmed()+")");

}

void MainWindow::on_actionRun_triggered()
{
    QProcess *process = new QProcess();
    QTextCursor cursor=  ui->plainTextEdit->textCursor();
    QStringList arguments;
    arguments<<tr("/home/psycho/Downloads/sass-stable/bin/scss")<<tr("/home/psycho/go/src/app/tools/update/index.scss")<<tr("/home/psycho/go/src/app/tools/update/index.css");
    process->start("ruby",arguments);

}

void MainWindow::on_actionSave_triggered()
{
    QString str=ui->plainTextEdit->toPlainText().toUtf8();
    if(str.isEmpty())return;
    const QStringList & result= str.split("\n",QString::SkipEmptyParts);
    if(result.length()<1)return;
    QString filename=result.value(0).trimmed();
    QRegExp rx("/&?!:'\"");
    filename=filename.replace(rx,"-");
    if(this->currentFileName.isEmpty()){
        QString userFile=QFileDialog::getSaveFileName(this,"Open Document"
                                                      ,"./psycho/"+filename,"All Files(*.* *)");
        this->currentFileName=userFile;
    }
    if(this->currentFileName.isEmpty())
        return;
    QFile file(this->currentFileName);

    if(file.open(QIODevice::ReadWrite | QIODevice::Text)){

        QTextStream out(&file);
        out <<str;
        file.close();
        setWindowTitle(this->currentFileName);
    }
}

void MainWindow::on_actionNewFile_triggered()
{
    this->currentFileName="";
    ui->plainTextEdit->document()->clear();
    setWindowTitle("网页开发助手");
}

void MainWindow::on_actionList_triggered()
{
    QTextCursor cursor=  ui->plainTextEdit->textCursor();
    cursor.insertText("- []("+cursor.selectedText().trimmed()+")");
}

void MainWindow::on_actionHr_triggered()
{
    QTextCursor cursor=  ui->plainTextEdit->textCursor();
    cursor.insertText("------"+cursor.selectedText().trimmed());
}

void MainWindow::on_actionImage_triggered()
{
    QString userFile=QFileDialog::getOpenFileName(this,"Open Document"
                                                  ,"./psycho","All Files(*.* *)");

    QFile file(userFile);

    if(file.open(QIODevice::ReadOnly)){

        QByteArray image = file.readAll();
        QString encoded = QString(image.toBase64());
        file.close();

        QFile outputFile(userFile+"-base64.txt");

        if(outputFile.open(QIODevice::ReadWrite)){

            QTextStream out(&outputFile);
            out <<encoded.toUtf8();
            outputFile.close();
        }
    }




}

void MainWindow::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{

    QMenu *popMenu =new QMenu(this);

    popMenu->addAction(ui->actionCopy);
    popMenu->addAction(ui->actionEditcut);
    popMenu->addAction(ui->actionEditpast);

    popMenu->addSeparator();
    popMenu->addAction(ui->actionEditselectall);
    popMenu->exec(QCursor::pos());

}

void MainWindow::on_editredo_triggered()
{
    ui->plainTextEdit->redo();
}

void MainWindow::on_actionEditundo_triggered()
{
    ui->plainTextEdit->undo();
}

void MainWindow::on_actionEditselectall_triggered()
{
    ui->plainTextEdit->selectAll();
}

void MainWindow::on_actionEditcut_triggered()
{
    ui->plainTextEdit->cut();
}
void MainWindow::on_actionEditpast_triggered()
{
    ui->plainTextEdit->paste();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}

void MainWindow::on_actionFind_triggered()
{
    FindDialog *findDlg=new FindDialog(ui->plainTextEdit);
    findDlg->show();
}

void MainWindow::on_actionBlod_triggered()
{

    QString str=ui->plainTextEdit->toPlainText();
    QTextCursor t=     ui->plainTextEdit->textCursor();
    QString find=t.selectedText();



    int pos=str.indexOf(find,this->findPos);
    if(pos!=-1){

        t.setPosition(pos,QTextCursor::MoveAnchor);
        t.setPosition(pos+find.length(),QTextCursor::KeepAnchor);
        this->findPos=pos+find.length();
        ui->plainTextEdit->setTextCursor(t);
    }else{
        this->findPos=0;
        pos=str.indexOf(find,this->findPos);

        if(pos!=-1){

            t.setPosition(pos,QTextCursor::MoveAnchor);
            t.setPosition(pos+find.length(),QTextCursor::KeepAnchor);
            this->findPos=pos+find.length();
            ui->plainTextEdit->setTextCursor(t);
        }
    }
}

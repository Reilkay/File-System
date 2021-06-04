#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "instruction.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    d_inputpass = new Dialog_inputPass;
    d_inputyn = new Dialog_inputyn;
    connect(d_inputpass, SIGNAL(sendPass(QString)), this, SLOT(savePass(QString)));
    connect(d_inputyn, SIGNAL(sendPass(QString)), this, SLOT(saveYN(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::waitUserInputPass()
{
    QString pass;
    Dialog_inputPass *dlgInputPass = new Dialog_inputPass(this);
    Qt::WindowFlags flags = dlgInputPass->windowFlags();
    dlgInputPass->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dlgInputPass->exec () ; // 以模态方式显示对话框
    if (ret == QDialog::Accepted || ret == QDialog::Rejected) {
        //OK按钮被按下，获取对话框上的输入，设置行数和列数
        pass = dlgInputPass->passWord;
    }
    delete dlgInputPass;
    return pass;
}

QString MainWindow::waitUserInputYN()
{
    QString yn;
    Dialog_inputyn *dlgInputYN = new Dialog_inputyn(this);
    Qt::WindowFlags flags = dlgInputYN->windowFlags();
    dlgInputYN->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dlgInputYN->exec () ; // 以模态方式显示对话框
    if (ret == QDialog::Accepted || ret == QDialog::Rejected) {
        //OK按钮被按下，获取对话框上的输入，设置行数和列数
        yn = dlgInputYN->YorN;
    }
    delete dlgInputYN;
    return yn;
}


void MainWindow::on_Excute_clicked()
{
    choose(Command);
    qDebug() << waitUserInputPass();
}


void MainWindow::on_CommandEdit_textChanged()
{
    Command = ui->CommandEdit->toPlainText();
}

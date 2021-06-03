#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->CommandEditor
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Excute_clicked()
{
    Command = ui->CommandEdit->toPlainText();
}


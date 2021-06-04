#include "dialog_inputpass.h"
#include "ui_dialog_inputpass.h"
#include <QDebug>

Dialog_inputPass::Dialog_inputPass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_inputPass)
{
    ui->setupUi(this);
}

Dialog_inputPass::~Dialog_inputPass()
{
    delete ui;
}

void Dialog_inputPass::on_buttonBox_accepted()
{
    passWord = ui->passWordEdit->text();
    qDebug() << "Passwordinin";
}


void Dialog_inputPass::on_buttonBox_rejected()
{
    passWord = "";
}


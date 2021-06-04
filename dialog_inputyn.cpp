#include "dialog_inputyn.h"
#include "ui_dialog_inputyn.h"

Dialog_inputyn::Dialog_inputyn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_inputyn)
{
    ui->setupUi(this);
}

Dialog_inputyn::~Dialog_inputyn()
{
    delete ui;
}

void Dialog_inputyn::on_buttonBox_accepted()
{
    YorN = "y";
}


void Dialog_inputyn::on_buttonBox_rejected()
{
    YorN = "n";
}


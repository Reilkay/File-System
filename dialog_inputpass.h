#ifndef DIALOG_INPUTPASS_H
#define DIALOG_INPUTPASS_H

#include <QDialog>

namespace Ui
{
    class Dialog_inputPass;
}

class Dialog_inputPass : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_inputPass(QWidget *parent = nullptr);
    ~Dialog_inputPass();
    QString passWord;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog_inputPass *ui;
};

#endif // DIALOG_INPUTPASS_H

#ifndef DIALOG_INPUTYN_H
#define DIALOG_INPUTYN_H

#include <QDialog>

namespace Ui
{
    class Dialog_inputyn;
}

class Dialog_inputyn : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_inputyn(QWidget *parent = nullptr);
    ~Dialog_inputyn();
    QString YorN;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog_inputyn *ui;
};

#endif // DIALOG_INPUTYN_H

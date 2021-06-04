#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog_inputpass.h"
#include "dialog_inputyn.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Dialog_inputPass *d_inputpass;
    Dialog_inputyn *d_inputyn;
    QString waitUserInputPass();
    QString waitUserInputYN();

private slots:
    void on_Excute_clicked();
    void on_CommandEdit_textChanged();

private:
    Ui::MainWindow *ui;
    QString Command;
};
#endif // MAINWINDOW_H

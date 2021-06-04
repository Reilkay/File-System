#include "mainwindow.h"
#include "disk.h"
#include "superblock.h"
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//    qDebug()<<"start";
    SUPER_BLOCK impl= SUPER_BLOCK();
    impl.Init();
    qDebug()<<"start2";
    qDebug()<<impl.get_all_disk_free_block().size();
    for(auto i : impl.get_all_disk_free_block())
    {
        qDebug() << i;
    }
//    DISK impl=DISK();
//    impl.createNewFile("/1.txt",0);
//    QString temp  = "1/2/3/";
//    QStringList tem = temp.split("/", QString::SkipEmptyParts);
//    for(auto i : tem)
//    {
//        qDebug() << i << "gah";
//    }

}

#include "mainwindow.h"
#include "disk.h"
#include "superblock.h"
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    //    qDebug()<<"start";
    //    SUPER_BLOCK impl= SUPER_BLOCK();
    //    impl.Init();
    //    qDebug()<<"start2";
    //    qDebug()<<impl.get_all_disk_free_block().size();
    //    for(auto i : impl.get_all_disk_free_block())
    //    {
    //        qDebug() << i;
    //    }
    //    DISK impl=DISK();
    //    impl.createNewFile("/1.txt",0);
    //    QString temp  = "1/2/3/";
    //    QStringList tem = temp.split("/", QString::SkipEmptyParts);
    //    for(auto i : tem)
    //    {
    //        qDebug() << i << "gah";
    //    }
    DISK impl = DISK();
    impl.Init();
    impl.createNewDirectory("/dir1", 0);
    impl.createNewDirectory("/dir1/dir2", 0);
    impl.createNewFile("/dir1/dir2/1.txt", 0);
    impl.saveFile(impl.findFile("/dir1/dir2/1.txt"), "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    qDebug() << impl.readFile("/dir1/dir2/1.txt");
    impl.EditFile("/dir1/dir2/1.txt", "hello?");
    qDebug() << "after:"
             << "   " << impl.readFile("/dir1/dir2/1.txt") << "   "
             << "   ";
    impl.delFile("/dir1/dir2/1.txt");
    //impl.EditFile("/dir1/dir2/1.txt", "hello222222?");
    //qDebug() << "after:" << "   " << impl.readFile("/dir1/dir2/1.txt") << "   " << "   ";
    qDebug() << impl.getFileList("/dir1/dir2/");
}

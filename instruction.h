#ifndef INSTRUCTION_H
#define INSTRUCTION_H

//#include <QString>
#include <QDebug>
#include <QCharRef>
#include <string>
#include "disk.h"
class CMD
{
public:
    QString Global_path = "/";
    QString Global_user = "";
    DISK disk;

    void ls(QStringList strList);

    void cd(QStringList strList);

    void pwd();

    void mkdir(QStringList strList);

    void rmdir(QStringList strList);

    void rm(QStringList strList);

    void mv(QStringList strList);

    void cp(QStringList strList);

    void cat(QStringList strList);

    void find(QStringList strList);

    void add_permission(QString filename, int mum[3], QString p);

    void sub_permission(QString filename, int mum[3], QString p);

    void update_permission(QString filename, int mum[3], QString p);

    void chmod(QStringList strList);

    void login(QStringList strList);

    void logout();

    void open(QStringList strList);

    void close(QStringList strList);

    void adduser(QStringList strList);

    void passwd(QStringList strList);

    void rmuser(QStringList strList);

    void touch(QStringList strList);

    void read(QStringList strList);

    void write(QStringList strList);

    void help(QStringList strList);

    void clear();

    void format();

    void choose(QString str);

    string q2s(const QString &s);
    QString s2q(const string &s);
    bool ifDirHaveFile(QString source_file, QString dest_file);
    QString get_true_path(QString str);
    QStringList get_true_path_list(QString str);
    void rm_del(QString filename, int ask);
};

#endif // INSTRUCTION_H

#ifndef DISK_H
#define DISK_H

#include "superblock.h"
#include "diskblock.h"
#include "dinode.h"
#include "user.h"
#include "sfd.h"
#include <QString>
#include <QAbstractItemModel>
#include "dinode.h"

// TODO: DISK
class DISK
{
public:
    // 避免关机 恢复任务
    bool Recovery();
    // 第一次使用
    void Init();

    SUPER_BLOCK getSuper_block() const;
    void setSuper_block(const SUPER_BLOCK &value);

    BFD_DISK getD_inodes() const;
    void setD_inodes(const BFD_DISK &value);

    vector<DISK_BLOCK> getD_block() const;
    void setD_block(const vector<DISK_BLOCK> &value);

    bool createNewFile(string path, unsigned int master_ID);
    bool saveFile(int inode_id, char *content);
    bool createNewDirectory(string path, unsigned int master_ID);
    USER_TABLE getUser_table() const;
    void setUser_table(const USER_TABLE &value);

    // fixed:做多文件
    void delFile(QString file_path);

    vector<SFD> getAll_sfd() const;

    // 从所有SFD中寻找文件 返回inode索引 否则返回-1
    int findFile(QString file_path);

    void setAll_sfd(const vector<SFD> &value);

    // void Dfs_del_dir(int cur_layer, int max_layer);

    int findSfdIndexInTotalSfd(SFD temp_sfd);

    // tool : 根据sfd_id寻找sfd
    int findSfd(int sfd_id);
    // tool : 返回文件当前路径(总vector<sfd>的下标)
    int getFileCurPathIndex(QString file_path);
    // tool : 在全是文件夹的时候 返回文件当前路径(总vector<sfd>的下标)
    int nofilenameGetFileCurPathIndex(QString file_path);

    //*************************************************************
    // TODO:在给定dir下查找file

    // 文件是否为空 为空返回true
    bool fileIsEmpty(QString file_path);
    // fixed:将文件移动到指定文件夹
    void moveFileToDir(QString source, QString dest);
    // 全局查找file

    // 获取子文件列表
    QStringList getFileList(QString file_path);

    // 获取文件类型
    file_type getFileType(QString file_path);
    // fixed:更改文件名
    void changeFileName(QString source, QString dest);
    // 获取文件修改时间
    time_t getFileChangeTime(QString file_path);
    // 获取文件创建者
    string getFileCreater(QString file_path);
    // 获取文件创建时间
    time_t getFileCreateTime(QString file_path);
    // 获取用户密码
    string getUserPass(string user_name);
    // 根据用户名寻找用户id
    int getUserIdByUsenName(string user_name);

    // fixed:新增用户
    void addUser(string user_name);
    // fixed:删除用户
    void delUser(string user_name);
    // 获取用户对应的用户组
    int getUserGroup(string user_name);
    // fixed:更改用户密码
    void changeUserPass(string user_name, string pass);
    // 判断用户是否存在 存在返回true
    bool userExist(string user_name);
    // 获取root密码
    string getRootPass();
    // 读取指定文件
    QString readFile(QString path);
    // 读取指定文件的一行
    QString readFileByLine(QString path);
    // 编辑文件
    bool EditFile(QString path, QString content);
    // 写入文件尾（追加）
    bool addLineInFile(QString path, QString content);
    // 获取文件权限
    QString getFileAuth(QString path);
    // 修改文件权限
    void changeFileAuth(QString path, QString auth);
    // 复制文件 1表示需要复制原文件修改时间和权限 0表示新文件拥有自己的修改时间和权限
    void copy_file(QString source,QString dest,int flag);


    //*****************************************
    // 成组链接法-持久化存储
    void save_chengzu();
    void load_chengzu();
    // bfd持久化存储
    void save_bfd();
    void load_bfd();

private:
    // 成组链接的首个超级块
    SUPER_BLOCK Super_block;
    // 根目录/首个SFD
    vector<SFD> all_sfd;
    // i结点信息
    BFD_DISK d_inodes;
    // 块信息
    vector<DISK_BLOCK> d_block;
    // 用户表
    USER_TABLE user_table;
    // 返回文件所用的磁盘块
    vector<int> getBlocksUsedByFile(int inode_id);
};

#endif // DISK_H

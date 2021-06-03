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
    bool saveFile(char* content);
    bool createNewDirectory(string path, unsigned int master_ID);
    USER_TABLE getUser_table() const;
    void setUser_table(const USER_TABLE &value);


    // TODO:做多文件
    void delFile(QString file_path);


    vector<SFD> getAll_sfd() const;

    // 从所有SFD中寻找文件 返回inode索引 否则返回-1
    int findFile(QString file_path);

    void setAll_sfd(const vector<SFD> &value);

    void Dfs_del_dir(int cur_layer, int max_layer);

    int find_sfd_index_in_total_sfd(SFD temp_sfd);

    // 根据sfd_id寻找sfd
    int find_sfd(int sfd_id);

    // 文件是否为空 为空返回true
    bool file_is_empty(QString file_path);
    // 获取文件类型
    file_type get_file_type(QString file_path);
    // 更改文件名
    void change_file_name(QString source,QString dest);
    // 获取文件修改时间
    time_t get_file_change_time(QString file_path);
    // 获取用户密码
    string get_user_pass(string user_name);
    // 新增用户
    void add_user(string user_name);
    // 删除用户
    void del_user(string user_name);
    // 获取用户对应的用户组
    int get_user_group(string user_name);
    //





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
};

#endif // DISK_H

#ifndef DISK_H
#define DISK_H

#include "superblock.h"
#include "diskblock.h"
#include "dinode.h"
#include "user.h"
#include "sfd.h"


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

    USER getUser_table() const;
    void setUser_table(const USER &value);

    bool saveFile(char* content);

    // TODO:做多文件
    bool delFile(string file_name);

    SFD getRoot_sfd() const;
    void setRoot_sfd(const SFD &value);

private:
    // 成组链接的首个超级块
    SUPER_BLOCK Super_block;
    // 根目录/首个SFD
    SFD root_sfd;
    // i结点信息
    BFD_DISK d_inodes;
    // 块信息
    vector<DISK_BLOCK> d_block;
    // 用户表
    USER user_table;
};

#endif // DISK_H

#ifndef FILESTRUCT_H
#define FILESTRUCT_H

#include <vector>
#include <string>
#include <map>
#include "configure.h"

using namespace std;

class SFD_ITEM
{
public:
    string getFile_name() const;
    void setFile_name(const string &value);

    int getID() const;
    void setID(int value);

private:
    string file_name;
    int ID;
};

// 文件目录结构SFD
class SFD
{
private:
    vector<SFD_ITEM> SFD_list;
public:
    SFD();
    // 在SFD中通过文件名寻找索引序号 返回-1表示没有
    int findSfd_item(string file_name);
};

enum file_type
{
    directory,common,special
};


class BFD_ITEM_DISK
{
private:
    unsigned int disk_ID;
    unsigned int master_ID;     // 文件拥有者ID
    file_type f_type;           // 文件类型
    char auth[3];               // 权限（三位十进制数表示）
    unsigned long long f_size;  // 文件大小
    unsigned int f_addr;        // 文件地址（物理地址/下级目录ID）
    unsigned int f_link_num;    // 文件链接计数
    time_t f_time;              // 文件存取时间
};

// BFD_DISK
class BFD_DISK
{
private:
    vector<BFD_ITEM_DISK> BFD_DISK_list;
public:
    BFD_DISK();
};

class BFD_ITEM_MEMORY:public BFD_ITEM_DISK
{
private:
    unsigned int memory_ID;
    bool f_lock;                    // 文件锁定状态（true为锁定）
    unsigned int f_access_num;      // 文件访问计数
    BFD_ITEM_MEMORY* node1;
    BFD_ITEM_MEMORY* node2;
};

// BFD_MEMORY
class BFD_MEMORY
{
private:
    vector<BFD_ITEM_MEMORY> BFD_MEMORY_list;
public:
    BFD_MEMORY();
};

// TODO: 超级块SUPER_BLOCK
class SUPER_BLOCK
{
public:
    //TODO: 文件恢复 避免开机重启
    static bool file_recovery()
    {
        return false;
    }

    // 重构默认构造
    SUPER_BLOCK()
    {
        this->super_block_num = SUPERFREEBLOCK;
        this->disk_num_list.resize(50);

    }
    int getSuper_block_size() const;
    void setSuper_block_size(int value);

    SUPER_BLOCK *getNext_super_block() const;
    void setNext_super_block(SUPER_BLOCK *value);

    int getSuper_block_num() const;
    void setSuper_block_num(int value);

    vector<int> getDisk_num_list() const;
    void setDisk_num_list(const vector<int> &value);

private:
    // 存放空块号，默认为50个
    int super_block_size;
    // 存放盘块的序号，相当于索引
    vector<int> disk_num_list;
    // 存放下一个超级块的指针
    SUPER_BLOCK* next_super_block;
    // 存放超级块序号（或许用不到）
    int super_block_num;

};

// TODO: 磁盘块
class DISK_BLOCK
{
public:
    int getBlock_num() const;
    void setBlock_num(int value);

    bool getIs_full() const;
    void setIs_full(bool value);

    string getFile_name() const;
    void setFile_name(const string &value);

private:
    // 在磁盘中的序号即为索引
    int block_num;
    // bool判断是否为空 true即为非空
    bool is_full;
    // 对应的文件名
    string file_name;
};

// 用户表USER
class USER
{
public:
    unsigned int getId() const;
    void setId(unsigned int value);

    string getUsername() const;
    void setUsername(const string &value);

    string getUserpwd() const;
    void setUserpwd(const string &value);

    int getUsergrp() const;
    void setUsergrp(int value);

    bool getIsManager() const;
    void setIsManager(bool value);

private:
    unsigned int id;    //用户id号
    string username;
    string userpwd;
    int usergrp;        //用户组
    bool isManager;     //管理员
};

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

private:
    // 成组链接的首个超级块
    SUPER_BLOCK Super_block;
    // i结点信息
    BFD_DISK d_inodes;
    // 块信息
    vector<DISK_BLOCK> d_block;
    // 用户表
    USER user_table;
};


// 方法实现
int SUPER_BLOCK::getSuper_block_size() const
{
return super_block_size;
}

void SUPER_BLOCK::setSuper_block_size(int value)
{
super_block_size = value;
}

SUPER_BLOCK *SUPER_BLOCK::getNext_super_block() const
{
return next_super_block;
}

void SUPER_BLOCK::setNext_super_block(SUPER_BLOCK *value)
{
next_super_block = value;
}

int SUPER_BLOCK::getSuper_block_num() const
{
return super_block_num;
}

void SUPER_BLOCK::setSuper_block_num(int value)
{
super_block_num = value;
}

vector<int> SUPER_BLOCK::getDisk_num_list() const
{
return disk_num_list;
}

void SUPER_BLOCK::setDisk_num_list(const vector<int> &value)
{
disk_num_list = value;
}

string SFD_ITEM::getFile_name() const
{
return file_name;
}

void SFD_ITEM::setFile_name(const string &value)
{
file_name = value;
}

int SFD_ITEM::getID() const
{
return ID;
}

void SFD_ITEM::setID(int value)
{
ID = value;
}

int SFD::findSfd_item(string file_name)
{
    for(auto i:SFD_list)
    {
        if(i.getFile_name() == file_name)
            return i.getID();
    }
    return -1;
}
int DISK_BLOCK::getBlock_num() const
{
return block_num;
}

void DISK_BLOCK::setBlock_num(int value)
{
block_num = value;
}

bool DISK_BLOCK::getIs_full() const
{
return is_full;
}

void DISK_BLOCK::setIs_full(bool value)
{
is_full = value;
}

string DISK_BLOCK::getFile_name() const
{
return file_name;
}

void DISK_BLOCK::setFile_name(const string &value)
{
file_name = value;
}

unsigned int USER::getId() const
{
return id;
}

void USER::setId(unsigned int value)
{
id = value;
}

string USER::getUsername() const
{
return username;
}

void USER::setUsername(const string &value)
{
username = value;
}

string USER::getUserpwd() const
{
return userpwd;
}

void USER::setUserpwd(const string &value)
{
userpwd = value;
}

int USER::getUsergrp() const
{
return usergrp;
}

void USER::setUsergrp(int value)
{
usergrp = value;
}

bool USER::getIsManager() const
{
return isManager;
}

void USER::setIsManager(bool value)
{
isManager = value;
}

#endif // FILESTRUCT_H
SUPER_BLOCK DISK::getSuper_block() const
{
return Super_block;
}

bool DISK::Recovery()
{

}

void DISK::Init()
{

}

void DISK::setSuper_block(const SUPER_BLOCK &value)
{
Super_block = value;
}

BFD_DISK DISK::getD_inodes() const
{
return d_inodes;
}

void DISK::setD_inodes(const BFD_DISK &value)
{
d_inodes = value;
}

vector<DISK_BLOCK> DISK::getD_block() const
{
return d_block;
}

void DISK::setD_block(const vector<DISK_BLOCK> &value)
{
d_block = value;
}

USER DISK::getUser_table() const
{
return user_table;
}

void DISK::setUser_table(const USER &value)
{
user_table = value;
}

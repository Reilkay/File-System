#ifndef DINODE_H
#define DINODE_H

#include <string>
#include <vector>
using namespace std;

enum file_type
{
    directory,
    common,
    special
};

class BFD_ITEM_DISK
{
public:
    // 设置默认构造
    BFD_ITEM_DISK(unsigned int dinode_ID,    // i结点的id
                  unsigned int master_ID,    // 文件拥有者ID
                  file_type f_type,          // 文件类型
                  vector<char> auth,         // 权限（三位十进制数表示）
                  unsigned long long f_size, // 文件大小
                  unsigned int f_addr,       // 文件地址（物理地址/下级目录ID）
                  unsigned int f_link_num,   // 文件链接计数
                  time_t f_creat_time,       // 文件创建时间
                  time_t f_change_time);     // 文件存取时间

    unsigned int getMaster_ID() const;
    void setMaster_ID(unsigned int value);

    file_type getF_type() const;
    void setF_type(const file_type &value);

    unsigned long long getF_size() const;
    void setF_size(unsigned long long value);

    unsigned int getF_addr() const;
    void setF_addr(unsigned int value);

    unsigned int getF_link_num() const;
    void setF_link_num(unsigned int value);

    time_t getF_creat_time() const;
    void setF_creat_time(const time_t &value);

    time_t getF_change_time() const;
    void setF_change_time(const time_t &value);

    unsigned int getDinode_ID() const;
    void setDinode_ID(unsigned int value);

    vector<char> getAuth() const;
    void setAuth(const vector<char> &value);

private:
    unsigned int dinode_ID;    // i结点的id
    unsigned int master_ID;    // 文件拥有者ID
    file_type f_type;          // 文件类型
    vector<char> auth;         // 权限（三位十进制数表示）
    unsigned long long f_size; // 文件大小
    unsigned int f_addr;       // 文件地址（物理地址/下级目录ID）
    unsigned int f_link_num;   // 文件链接计数
    time_t f_creat_time;       // 文件创建时间
    time_t f_change_time;      // 文件存取时间
};

// BFD_DISK
class BFD_DISK
{
private:
    vector<BFD_ITEM_DISK> BFD_DISK_list;

public:
    BFD_DISK();
};

#endif // DINODE_H

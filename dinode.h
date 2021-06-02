#ifndef DINODE_H
#define DINODE_H

#include <string>
#include <vector>
using namespace std;

enum file_type {
    directory,
    common,
    special
};

class BFD_ITEM_DISK
{
private:
    unsigned int dinode_ID;    // i结点的id
    unsigned int master_ID;    // 文件拥有者ID
    file_type f_type;          // 文件类型
    char auth[3];              // 权限（三位十进制数表示）
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

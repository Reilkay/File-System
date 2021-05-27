#ifndef FILESTRUCT_H
#define FILESTRUCT_H

#include <vector>
#include <string>
#include <map>

using namespace std;

class SFD_ITEM
{
private:
   string file_name;
   unsigned int ID;
};

// 文件目录结构SFD
class SFD
{
private:
    vector<SFD_ITEM> SFD_list;
public:
    SFD();
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

#endif // FILESTRUCT_H

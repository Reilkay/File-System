#ifndef INODE_H
#define INODE_H

#include <string>
#include <vector>

#include "dinode.h"
using namespace std;

class BFD_ITEM_MEMORY: public BFD_ITEM_DISK
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

#endif // INODE_H

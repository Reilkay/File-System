#ifndef INODE_H
#define INODE_H

#include <string>
#include <vector>

#include "dinode.h"
using namespace std;

class BFD_ITEM_MEMORY: public BFD_ITEM_DISK
{
public:
    // D-inode向M-inode转化
    BFD_ITEM_MEMORY(BFD_ITEM_DISK pre_dinode,
                    unsigned int inode_ID,
                    bool f_lock,                    // 文件锁定状态（true为锁定）
                    unsigned int f_access_num,      // 文件访问计数
                    BFD_ITEM_MEMORY* node1,
                    BFD_ITEM_MEMORY* node2);

    unsigned int getInode_ID() const;
    void setInode_ID(unsigned int value);

    bool getF_lock() const;
    void setF_lock(bool value);

    unsigned int getF_access_num() const;
    void setF_access_num(unsigned int value);

    BFD_ITEM_MEMORY *getNode1() const;
    void setNode1(BFD_ITEM_MEMORY *value);

    BFD_ITEM_MEMORY *getNode2() const;
    void setNode2(BFD_ITEM_MEMORY *value);

private:
    unsigned int inode_ID;          // 内存索引结点
    bool f_lock;                    // 文件锁定状态（true为锁定）
    unsigned int f_access_num;      // 文件访问计数
    BFD_ITEM_MEMORY* node1;         // 指向空闲链表的指针
    BFD_ITEM_MEMORY* node2;         // 指向散列队列的指针
};

// BFD_MEMORY
class BFD_MEMORY
{
public:
    BFD_MEMORY();
    vector<BFD_ITEM_MEMORY> getBFD_MEMORY_list() const;
    void setBFD_MEMORY_list(const vector<BFD_ITEM_MEMORY> &value);
private:
    vector<BFD_ITEM_MEMORY> BFD_MEMORY_list;
};

#endif // INODE_H

#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include <string>
#include<vector>

#include"configure.h"
using namespace std;

// 超级块SUPER_BLOCK
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


#endif // SUPERBLOCK_H

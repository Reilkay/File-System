#include "superblock.h"

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

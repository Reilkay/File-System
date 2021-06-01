#include "diskblock.h"

// 方法实现
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
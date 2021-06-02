#include "diskblock.h"
#include "configure.h"
#include<cstring>

// 方法实现
DISK_BLOCK::DISK_BLOCK()
{
    this->index.resize(BLOCKSIZE / sizeof (int));
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

void DISK_BLOCK::setData(char* content)
{
    strcpy_s(this->data, content);
}

vector<int> DISK_BLOCK::getIndex() const
{
    return index;
}

void DISK_BLOCK::setIndex(const vector<int> &value)
{
    index = value;
}

int DISK_BLOCK::getIndex_num() const
{
    return index_num;
}

void DISK_BLOCK::setIndex_num(int value)
{
    index_num = value;
}

diskblock_type DISK_BLOCK::getBlock_type() const
{
    return block_type;
}

void DISK_BLOCK::setBlock_type(const diskblock_type &value)
{
    block_type = value;
}

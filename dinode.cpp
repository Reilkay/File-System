#include "dinode.h"

BFD_ITEM_DISK::BFD_ITEM_DISK(unsigned int dinode_ID,     // i结点的id
                             unsigned int master_ID,     // 文件拥有者ID
                             file_type f_type,           // 文件类型
                             vector<char> auth,          // 权限（三位十进制数表示）
                             unsigned long long f_size,  // 文件大小
                             unsigned int f_addr,        // 文件地址（物理地址/下级目录ID）
                             unsigned int f_link_num,    // 文件链接计数
                             time_t f_creat_time,        // 文件创建时间
                             time_t f_change_time)       // 文件存取时间
{
    // 默认权限是755
    this->auth.resize(3);
    this->setDinode_ID(dinode_ID);
    this->setMaster_ID(master_ID);
    this->setF_type(f_type);
    this->setAuth(auth);
    this->setF_size(f_size);
    this->setF_addr(f_addr);
    this->setF_link_num(f_link_num);
    this->setF_creat_time(f_creat_time);
    this->setF_change_time(f_change_time);
}

unsigned int BFD_ITEM_DISK::getMaster_ID() const
{
    return master_ID;
}

void BFD_ITEM_DISK::setMaster_ID(unsigned int value)
{
    master_ID = value;
}

file_type BFD_ITEM_DISK::getF_type() const
{
    return f_type;
}

void BFD_ITEM_DISK::setF_type(const file_type &value)
{
    f_type = value;
}

unsigned long long BFD_ITEM_DISK::getF_size() const
{
    return f_size;
}

void BFD_ITEM_DISK::setF_size(unsigned long long value)
{
    f_size = value;
}

unsigned int BFD_ITEM_DISK::getF_addr() const
{
    return f_addr;
}

void BFD_ITEM_DISK::setF_addr(unsigned int value)
{
    f_addr = value;
}

unsigned int BFD_ITEM_DISK::getF_link_num() const
{
    return f_link_num;
}

void BFD_ITEM_DISK::setF_link_num(unsigned int value)
{
    f_link_num = value;
}

time_t BFD_ITEM_DISK::getF_creat_time() const
{
    return f_creat_time;
}

void BFD_ITEM_DISK::setF_creat_time(const time_t &value)
{
    f_creat_time = value;
}

time_t BFD_ITEM_DISK::getF_change_time() const
{
    return f_change_time;
}

void BFD_ITEM_DISK::setF_change_time(const time_t &value)
{
    f_change_time = value;
}

int BFD_ITEM_DISK::getDinode_ID() const
{
    return dinode_ID;
}

void BFD_ITEM_DISK::setDinode_ID(int value)
{
    dinode_ID = value;
}

vector<char> BFD_ITEM_DISK::getAuth() const
{
    return auth;
}

void BFD_ITEM_DISK::setAuth(const vector<char> &value)
{
    auth = value;
}

BFD_ITEM_DISK BFD_DISK::findInodeByNum(int need_num)
{
    for(BFD_ITEM_DISK temp : this->BFD_DISK_list)
    {
        if(temp.getDinode_ID() == need_num)
            return temp;
        else
        {
            BFD_ITEM_DISK temp = BFD_ITEM_DISK();
            temp.setDinode_ID(-1);
            return temp;
        }
    }

}

bool BFD_DISK::addInode(BFD_ITEM_DISK item)
{
    this->BFD_DISK_list.push_back(item);
    return true;
}

bool BFD_DISK::delInode(BFD_ITEM_DISK item)
{
    for(vector<BFD_ITEM_DISK>::iterator it = this->BFD_DISK_list.begin();
        it != this->BFD_DISK_list.end();
        it ++)
    {
        if(item.getDinode_ID() == it->getDinode_ID())
        {
            this->BFD_DISK_list.erase(it);
            return true;
        }
    }
    return false;
}

#include"minode.h"

BFD_ITEM_MEMORY::BFD_ITEM_MEMORY(BFD_ITEM_DISK pre_dinode,
                                 unsigned int inode_ID,
                                 bool f_lock,                    // 文件锁定状态（true为锁定）
                                 unsigned int f_access_num,      // 文件访问计数
                                 BFD_ITEM_MEMORY* node1,
                                 BFD_ITEM_MEMORY* node2)
{

    this->setDinode_ID(pre_dinode.getDinode_ID());
    this->setMaster_ID(pre_dinode.getMaster_ID());
    this->setF_type(pre_dinode.getF_type());
    this->setAuth(pre_dinode.getAuth());
    this->setF_size(pre_dinode.getF_size());
    this->setF_addr(pre_dinode.getF_addr());
    this->setF_link_num(pre_dinode.getF_link_num());
    this->setF_creat_time(pre_dinode.getF_creat_time());
    this->setF_change_time(pre_dinode.getF_change_time());
    // 新增内容
    this->setInode_ID(inode_ID);
    this->setF_lock(f_lock);
    this->setF_access_num(f_access_num);
    this->setNode1(node1);
    this->setNode2(node2);
}


unsigned int BFD_ITEM_MEMORY::getInode_ID() const
{
    return inode_ID;
}

void BFD_ITEM_MEMORY::setInode_ID(unsigned int value)
{
    inode_ID = value;
}

bool BFD_ITEM_MEMORY::getF_lock() const
{
    return f_lock;
}

void BFD_ITEM_MEMORY::setF_lock(bool value)
{
    f_lock = value;
}

unsigned int BFD_ITEM_MEMORY::getF_access_num() const
{
    return f_access_num;
}

void BFD_ITEM_MEMORY::setF_access_num(unsigned int value)
{
    f_access_num = value;
}

BFD_ITEM_MEMORY *BFD_ITEM_MEMORY::getNode1() const
{
    return node1;
}

void BFD_ITEM_MEMORY::setNode1(BFD_ITEM_MEMORY *value)
{
    node1 = value;
}

BFD_ITEM_MEMORY *BFD_ITEM_MEMORY::getNode2() const
{
    return node2;
}

void BFD_ITEM_MEMORY::setNode2(BFD_ITEM_MEMORY *value)
{
    node2 = value;
}



vector<BFD_ITEM_MEMORY> BFD_MEMORY::getBFD_MEMORY_list() const
{
    return BFD_MEMORY_list;
}

void BFD_MEMORY::setBFD_MEMORY_list(const vector<BFD_ITEM_MEMORY> &value)
{
    BFD_MEMORY_list = value;
}



vector<BFD_ITEM_MEMORY> BFD_MEMORY::getBFD_MEMORY_list() const
{
    return BFD_MEMORY_list;
}

void BFD_MEMORY::setBFD_MEMORY_list(const vector<BFD_ITEM_MEMORY> &value)
{
    BFD_MEMORY_list = value;
}

#include "minode.h"

#include "sfd.h"
// 方法实现
string SFD_ITEM::getFile_name() const
{
    return file_name;
}

void SFD_ITEM::setFile_name(const string &value)
{
    file_name = value;
}

int SFD_ITEM::getID() const
{
    return ID;
}

void SFD_ITEM::setID(int value)
{
    ID = value;
}

int SFD::getSFD_ID() const
{
    return SFD_ID;
}

void SFD::setSFD_ID(int value)
{
    SFD_ID = value;
}

int SFD::findSfd_item(string file_name)
{
    for(SFD_ITEM i : SFD_list)
    {
        if(i.getFile_name() == file_name)
        {
            return i.getID();
        }
    }
    return -1;
}

bool SFD::addSfd_item(SFD_ITEM temp)
{
    this->SFD_list.push_back(temp);
    return true;
}

// 注意 在SFD删除的同时 也在BFD删除了
// TODO:在磁盘删除:ZRZ
bool SFD::delSfd_item(string file_name)
{
    for(vector<SFD_ITEM>::iterator it = this->SFD_list.begin();
        it != this->SFD_list.end();
        it ++)
    {
        if(it->getFile_name() == file_name)
        {
           this->SFD_list.erase(it);
           return true;
        }
    }
    return false;
}

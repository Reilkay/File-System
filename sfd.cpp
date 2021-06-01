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

int SFD::findSfd_item(string file_name)
{
    for(SFD_ITEM i : SFD_list) {
        if(i.getFile_name() == file_name) {
            return i.getID();
        }
    }
    return -1;
}

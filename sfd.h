#ifndef SFD_H
#define SFD_H

#include <string>
#include <vector>
using namespace std;

class SFD_ITEM
{
public:
    SFD_ITEM();
    SFD_ITEM(const string &file_name, int ID);

    string getFile_name() const;
    void setFile_name(const string &value);

    int getID() const;
    void setID(int value);

private:
    string file_name;
    int ID;
};

// 文件目录结构SFD
class SFD
{
private:
    int SFD_ID;
    vector<SFD_ITEM> SFD_list;
public:
    SFD();
    // 在SFD中通过文件名寻找inode索引序号 返回-1表示没有
    int findSfd_item(string file_name);
    // 添加SFD表项 默认为真？？？
    bool addSfd_item(SFD_ITEM temp);
    // 删除SFD表项目 删除成功为true
    bool delSfd_item(string file_name);

    int getSFD_ID() const;
    void setSFD_ID(int value);

    vector<SFD_ITEM> getSFD_list() const;
    void setSFD_list(const vector<SFD_ITEM> &value);
};

#endif // SFD_H

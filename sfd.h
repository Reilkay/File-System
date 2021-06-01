#ifndef SFD_H
#define SFD_H

#include <string>
#include <vector>
using namespace std;

class SFD_ITEM
{
public:
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
    vector<SFD_ITEM> SFD_list;
public:
    SFD();
    // 在SFD中通过文件名寻找索引序号 返回-1表示没有
    int findSfd_item(string file_name);
};

#endif // SFD_H

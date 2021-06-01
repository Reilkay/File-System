#ifndef DISKBLOCK_H
#define DISKBLOCK_H

#include <string>
using namespace std;

// TODO: 磁盘块
class DISK_BLOCK
{
public:
    int getBlock_num() const;
    void setBlock_num(int value);

    bool getIs_full() const;
    void setIs_full(bool value);

    string getFile_name() const;
    void setFile_name(const string &value);

private:
    // 在磁盘中的序号即为索引
    int block_num;
    // bool判断是否为空 true即为非空
    bool is_full;
    // 对应的文件名
    string file_name;
};

#endif // DISKBLOCK_H

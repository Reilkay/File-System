#ifndef DISKBLOCK_H
#define DISKBLOCK_H

#include <string>
#include <vector>
#include "configure.h"
using namespace std;

enum diskblock_type {
    CONTENT, INDEX
};

// TODO: 磁盘块
class DISK_BLOCK
{
public:
    DISK_BLOCK();
    DISK_BLOCK(int block_num,bool is_full);

    int getBlock_num() const;
    void setBlock_num(int value);

    bool getIs_full() const;
    void setIs_full(bool value);

    string getFile_name() const;
    void setFile_name(const string & value);

    char* getData();
    void setData(char* content);

    vector<int> getIndex() const;
    void setIndex(const vector<int> &value);
    void addIndex(int value);
    void clearIndex();

    int getIndex_num() const;

    diskblock_type getBlock_type() const;
    void setBlock_type(const diskblock_type &value);

private:
    // 在磁盘中的序号即为索引
    int block_num;
    // bool判断是否为空 true即为非空
    bool is_full;
    // 对应的文件名(???)
    string file_name;
    // 磁盘块类型
    diskblock_type block_type;
    // 文件内容
    char data[BLOCKSIZE];
    // 占用空间
    int space_used;
    // 索引
    vector<int> index;
    // 索引个数
    int index_num;
};

#endif // DISKBLOCK_H

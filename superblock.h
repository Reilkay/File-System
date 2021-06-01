#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include <string>
#include<vector>

#include"configure.h"
using namespace std;

// 超级块SUPER_BLOCK
class SUPER_BLOCK
{
public:
    //TODO: 文件恢复 避免开机重启
    static bool file_recovery();

    // 初始化超级块
    void Init();

    // 根据文件所需的数据块数目 返回对应的磁盘块序号 vector
    // 扩展：当磁盘不够分时 返回空的vector
    vector<int> distri_disk_free_block(int need_block_numbers);

    // 增加磁盘块
    bool add_disk_free_block(vector<int> free_disk_numbers);

    // 返回所有的空闲磁盘块序号
    vector<int> get_all_disk_free_block();

    // 默认构造函数
    SUPER_BLOCK();

    int getSuper_block_size() const;
    void setSuper_block_size(int value);

    SUPER_BLOCK *getNext_super_block() const;
    void setNext_super_block(SUPER_BLOCK *value);

    int getSuper_block_num() const;
    void setSuper_block_num(int value);

    vector<int> getDisk_num_list() const;
    void setDisk_num_list(const vector<int> &value);

    int getAdmin_num() const;
    void setAdmin_num(int value);

    int getTotal_free_block_num() const;
    void setTotal_free_block_num(int value);

private:
    // 存放空块号，默认为50个
    int super_block_size;
    // 存放下一个超级块的指针
    SUPER_BLOCK* next_super_block;
    // 存放超级块序号（或许用不到）
    int super_block_num;
    // 组长块序号
    int admin_num;
    // 所有的空闲块总数 只有初始块才做统计 分块不做统计即为0
    int total_free_block_num;

protected:
    // 存放盘块的序号，相当于索引
    vector<int> disk_num_list;

};


#endif // SUPERBLOCK_H

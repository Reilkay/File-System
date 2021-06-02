#include "disk.h"
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

// 方法实现

SUPER_BLOCK DISK::getSuper_block() const
{
    return Super_block;
}

// 序列化与反序列化
bool DISK::Recovery()
{
}

void DISK::Init()
{
}

void DISK::setSuper_block(const SUPER_BLOCK &value)
{
    Super_block = value;
}

BFD_DISK DISK::getD_inodes() const
{
    return d_inodes;
}

void DISK::setD_inodes(const BFD_DISK &value)
{
    d_inodes = value;
}

vector<DISK_BLOCK> DISK::getD_block() const
{
    return d_block;
}

void DISK::setD_block(const vector<DISK_BLOCK> &value)
{
    d_block = value;
}

USER DISK::getUser_table() const
{
    return user_table;
}

void DISK::setUser_table(const USER &value)
{
    user_table = value;
}

bool DISK::saveFile(char* content)
{
    int content_len = strlen(content);
    // 数据块个数
    int data_block_num = ceil(float(content_len) / BLOCKSIZE);
    // 索引级数
    int need_index_rank = 0;
    float temp_shang = data_block_num;
    while(1) {
        temp_shang = temp_shang / (BLOCKSIZE / sizeof(int));
        if(temp_shang < 1) {
            break;
        } else {
            need_index_rank += 1;
        }
    }
    int temp_rank = need_index_rank;
    // 各级索引所需块数
    vector<int> index_rank_num;
    index_rank_num.resize(need_index_rank);
    temp_shang = data_block_num;
    // 所需总块数
    int sum_num = data_block_num;
    while(temp_rank --) {
        temp_shang = ceil(temp_shang / pow(BLOCKSIZE / sizeof(int), temp_rank));
        index_rank_num[temp_rank - 1] = temp_shang;
        sum_num += temp_shang;
    }
    // 申请的块序号
    vector<int> blocks_index = this->Super_block.distri_disk_free_block(sum_num);
    if(blocks_index.size()) {
        if(index_rank_num.size() == 0) {// 无需索引
            d_block[blocks_index[0]].setData(content);
        } else {
            int in = 0;
            for(in = 0; in < data_block_num; in++) {// 保存数据块
                char tmp_content[BLOCKSIZE];
                int tmp_len = min(int(BLOCKSIZE), int(strlen(content) - in * BLOCKSIZE + 1));
                strncpy(tmp_content, content + in * BLOCKSIZE, tmp_len);
                this->d_block[blocks_index[in]].setData(tmp_content);
                this->d_block[blocks_index[in]].setBlock_type(CONTENT);
            }
            for(unsigned int rank = 0; rank < index_rank_num.size(); rank++) {// 保存各级索引块
                int unsaved_index_num;
                if(rank == 0) {
                    unsaved_index_num = data_block_num;
                } else {
                    unsaved_index_num = index_rank_num[rank - 1];
                }
                int saved_index_num = 0;
                for(int i = 0; i < index_rank_num[rank]; i++) {
                    vector<int> tmp_index;
                    int tmp_len = min(int(BLOCKSIZE), int(unsaved_index_num));
                    tmp_index.resize(tmp_len);
                    for(int it = saved_index_num; it < saved_index_num + tmp_len; it++) {
                        tmp_index.push_back(blocks_index[it]);
                    }
                    d_block[blocks_index[in]].setIndex(tmp_index);
                    saved_index_num += tmp_len;
                    unsaved_index_num -= tmp_len;
                }
            }
        }
        return true;
    } else {
        return false;
    }
}

// TODO
bool DISK::createNewFile(string path)
{
}

bool DISK::delFile(string file_name)
{
    // 从sfd中删除一项
    int inode_num = this->root_sfd.findSfd_item(file_name);
    this->root_sfd.delSfd_item(file_name);
    // 从bfd中删除一项 因为需要从硬盘删除 所以保存临时的inode信息
    BFD_ITEM_DISK temp_inode = this->d_inodes.findInodeByNum(inode_num);
    this->d_inodes.delInode(temp_inode);
    // TODO:从硬盘删除 ZRZ
    return true;
}

SFD DISK::getRoot_sfd() const
{
    return root_sfd;
}

void DISK::setRoot_sfd(const SFD &value)
{
    root_sfd = value;
}

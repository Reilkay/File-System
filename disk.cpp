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
    int block_num = ceil(float(content_len) / BLOCKSIZE);
    int need_index_rank = 0;
    float temp_shang = block_num;
    while(1) {
        temp_shang = temp_shang / (BLOCKSIZE / sizeof(int));
        if(temp_shang < 1) {
            break;
        } else {
            need_index_rank += 1;
        }
    }
    int temp_rank = need_index_rank;
    vector<int> index_rank_num;
    index_rank_num.resize(need_index_rank);
    temp_shang = block_num;
    int sum_num = block_num;
    while(temp_rank --) {
        temp_shang = ceil(temp_shang / pow(BLOCKSIZE / sizeof(int), temp_rank));
        index_rank_num[temp_rank - 1] = temp_shang;
        sum_num += temp_shang;
    }
    vector<int> blocks_index = this->Super_block.distri_disk_free_block(sum_num);
    if(blocks_index.size()) {
        if(index_rank_num.size() == 0) {
            d_block[blocks_index[0]].setData(content);
        } else {
            for(int in = 0; in < sum_num - block_num; in++) {
                char tmp_content[BLOCKSIZE];
                int tmp_len = min(int(BLOCKSIZE), int(strlen(content) - in * BLOCKSIZE + 1));
                strncpy(tmp_content, content + in * BLOCKSIZE, tmp_len);
                d_block[blocks_index[in]].setData(tmp_content);
            }
        }
    } else {
        return false;
    }
}

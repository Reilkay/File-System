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

vector<SFD> DISK::getAll_sfd() const
{
    return all_sfd;
}




// 寻找文件 返回inode的id 非常非常重要
int DISK::findFile(QString file_path)
{
    QStringList split_path = file_path.split("/");
    // 层数
    int layer = 0;
    int layer_max = split_path.size();
    int total_layer = this->all_sfd.size();
    int cur_layer = 0;
    // 防止超出系统层数
    while(layer++ && layer <= layer_max)
    {
        // 重要的是 更新cur_layer
        // 从all_SFD中遍历搜索
        for(SFD_ITEM i:this->all_sfd[cur_layer].getSFD_list())
        {
            if(i.getFile_name() == split_path[layer].toStdString())
            {
                // 如果找到 且当前是最后一级目录 就返回id
                if(layer==layer_max)
                {
                    return i.getID();
                }
                // 如果不是最后一级目录 分两种情况 可能是文件夹 可能是文件
                // 不是最后一级目录 却找到了文件 直接返回-1
                else if(layer != layer_max && this->d_inodes.findInodeByNum(i.getID()).getF_type()!=directory)
                {
                    return -1;
                }
                // 不是最后一级目录 找到了文件夹 更新cur_layer
                else if(layer != layer_max && this->d_inodes.findInodeByNum(i.getID()).getF_type()==directory)
                {
                    cur_layer = this->find_sfd_index_in_total_sfd(all_sfd[cur_layer]);
                }
                continue;
            }
        }
    }
    return -1;
}


bool DISK::delFile(QString file_path)
{
    QStringList split_path = file_path.split("/");
    // ------------------------------如果是文件夹 需要根据SFD的层数进行DFS------------------------------------
    int dir_dfs_layer_begin = split_path.size();

    int inode_id = this->findFile(file_path);
    // 当没有这个文件的时候 删除失败 直接返回-1
    if(inode_id == -1)
    {
        return false;
    }
    else
    {
        // 当寻找到的文件类型为文件夹 涉及到递归级联删除
        if(this->d_inodes.findInodeByNum(inode_id).getF_type() == directory)
        {
            // 解除DFS循环
            if()
            // 根据层数进行DFS
            for()
            {
                // TODO:
                delFile(file_path + "");
            }
        }
        // 不是文件夹 直接删除就行 不用动磁盘块内容 只需要删除SFD和BFD即可
        else
        {
            // 找到对应的SFD
            unsigned long long layer = 0;
            int layer_max = split_path.size();
            unsigned long long total_layer = this->all_sfd.size();
            // 防止超出系统层数
            while(layer++ && layer <= total_layer)
            {
                for(vector<SFD_ITEM>::iterator it = this->all_sfd[layer].getSFD_list().begin();
                    it != this->all_sfd[layer].getSFD_list().end();
                    it++)
                {
                    if(it->getFile_name() == split_path[(int)layer].toStdString())
                    {
                        // 如果找到 直接删除 TODO:归还空块
                        if(layer == (unsigned long long)layer_max)
                        {
                            // 删除SFD信息
                            this->all_sfd[layer].getSFD_list().erase(it);
                            // 删除BFD信息
                            for(vector<BFD_ITEM_DISK>::iterator it2 = this->d_inodes.getBFD_DISK_list().begin();
                                it2 != this->d_inodes.getBFD_DISK_list().end();
                                it2++)
                            {
                                if(it2->getDinode_ID() == inode_id)
                                {
                                    this->d_inodes.getBFD_DISK_list().erase(it2);
                                }
                            }
                            return true;
                        }
                        else
                            continue;
                    }
                }
            }
        }
    }
    return false;
}

//void DISK::Dfs_del_dir(int cur_layer,int max_layer)
//{
//    // 达到最深的目录
//    if(cur_layer >= max_layer)
//    {
//        return;
//    }
//    else
//    {
//        if()=]
//        Dfs_del_dir(cur_layer+1,max_layer);
//    }
//}

void DISK::setAll_sfd(const vector<SFD> &value)
{
    all_sfd = value;
}

int DISK::find_sfd_index_in_total_sfd(SFD temp_sfd)
{
    for(unsigned long long i=0;i<this->all_sfd.size();i++)
    {
        if(this->all_sfd[i].getSFD_ID() == temp_sfd.getSFD_ID())
            return i;
    }
    return -1;
}


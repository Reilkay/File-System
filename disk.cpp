#include "disk.h"
#include <cstring>
#include <cmath>
#include <algorithm>
#include <QDebug>

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
    Super_block.Init();
    SFD root_SFD;
    root_SFD.setSFD_ID(0);
    all_sfd.push_back(root_SFD);
    vector<char> auth = {'7', '5', '5'};
    time_t tmp_time;
    time(&tmp_time);                        //当前time_t类型UTC时间
    BFD_ITEM_DISK root_dinode(0, // i结点的id
                              0,     // 文件拥有者ID
                              DIRECTORY,     // 文件类型
                              auth,          // 权限（三位十进制数表示）
                              0,             // 文件大小
                              0,    // 文件地址（物理地址/下级目录ID）
                              0,             // 文件链接计数
                              tmp_time,      // 文件创建时间
                              tmp_time);
    d_inodes.addInode(root_dinode);
    for (int i = 0; i < DATABLOCKNUM; i++) {
        d_block.push_back(DISK_BLOCK(i, false));
    }
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

// 保存文件
bool DISK::saveFile(int inode_id, char *content)
{
    int content_len = strlen(content);
    // 数据块个数
    int data_block_num = ceil(float(content_len) / BLOCKSIZE);
    // 首块地址
    int first_addr = 0;
    // 索引级数
    int need_index_rank = 0;
    float temp_shang = data_block_num;
    while (1) {
        temp_shang = temp_shang / (BLOCKSIZE / sizeof(int));
        if (temp_shang < 1) {
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
    while (temp_rank--) {
        temp_shang = ceil(temp_shang / pow(BLOCKSIZE / sizeof(int), temp_rank));
        index_rank_num[temp_rank - 1] = temp_shang;
        sum_num += temp_shang;
    }
    // 申请的块序号
    vector<int> blocks_index = this->Super_block.distri_disk_free_block(sum_num);
    if (blocks_index.size()) {
        if (index_rank_num.size() == 0) {
            // 无需索引
            this->d_block[blocks_index[0]].setData(content);
            this->d_block[blocks_index[0]].setBlock_type(CONTENT);
            first_addr = blocks_index[0];
        } else {
            int in = 0;
            for (in = 0; in < data_block_num; in++) {
                // 保存数据块
                char tmp_content[BLOCKSIZE];
                int tmp_len = min(int(BLOCKSIZE), int(strlen(content) - in * BLOCKSIZE + 1));
                strncpy(tmp_content, content + in * BLOCKSIZE, tmp_len);
                this->d_block[blocks_index[in]].setData(tmp_content);
                this->d_block[blocks_index[in]].setBlock_type(CONTENT);
            }
            for (unsigned int rank = 0; rank < index_rank_num.size(); rank++) {
                // 保存各级索引块
                if (int(rank) == in - 1) {
                    // 最高级索引首块地址
                    first_addr = in;
                }
                int unsaved_index_num;
                if (rank == 0) {
                    unsaved_index_num = data_block_num;
                } else {
                    unsaved_index_num = index_rank_num[rank - 1];
                }
                int saved_index_num = 0;
                for (int i = 0; i < index_rank_num[rank]; i++) {
                    vector<int> tmp_index;
                    int tmp_len = min(int(BLOCKSIZE), int(unsaved_index_num));
                    tmp_index.resize(tmp_len);
                    for (int it = saved_index_num; it < saved_index_num + tmp_len; it++) {
                        tmp_index.push_back(blocks_index[it]);
                    }
                    d_block[blocks_index[in]].clearIndex();
                    d_block[blocks_index[in]].setIndex(tmp_index);
                    d_block[blocks_index[in]].setBlock_type(INDEX);
                    saved_index_num += tmp_len;
                    unsaved_index_num -= tmp_len;
                }
            }
        }
        BFD_ITEM_DISK tmp_bfd_item = d_inodes.findInodeByNum(inode_id);
        tmp_bfd_item.setF_addr(first_addr);
        time_t tmp_time;
        time(&tmp_time); // 当前time_t类型UTC时间
        tmp_bfd_item.setF_change_time(tmp_time);
        tmp_bfd_item.setF_size(sum_num * BLOCKSIZE);
        d_inodes.changeInodeByNum(inode_id, tmp_bfd_item);
        return true;
    } else {
        return false;
    }
}

bool DISK::createNewDirectory(string path, unsigned int master_ID)
{
    string dirpath, directoryname;
    //划分目录和文件
    int split_index = path.length() - 1;
    for (; split_index >= 0; split_index--) {
        if (path[split_index] == '/') {
            break;
        }
    }
    dirpath = path.substr(0, split_index + 1);
    directoryname = path.substr(split_index + 1, path.length());
    int dir_inode_id = findFile(QString::fromStdString(dirpath));
    if (dir_inode_id < 0) {
        // 文件目录不存在
        return false;
    }
    BFD_ITEM_DISK tmp_bfd_item = d_inodes.findInodeByNum(dir_inode_id);
    // 检查重名问题
    if (all_sfd[tmp_bfd_item.getF_addr()].findSfd_item(directoryname) != -1) {
        // 有同名文件
        return false;
    }
    // 检测是否有空闲i节点
    int free_inode_id = d_inodes.getFreeInode();
    if (free_inode_id < 0) {
        // i节点用尽
        return false;
    }
    // 创建新SFD
    SFD new_SFD = SFD();
    int new_SFD_id = all_sfd.back().getSFD_ID() + 1;
    new_SFD.setSFD_ID(new_SFD_id);
    all_sfd.push_back(new_SFD);
    vector<char> auth = {'7', '5', '5'};
    time_t tmp_time;
    time(&tmp_time);                        //当前time_t类型UTC时间
    BFD_ITEM_DISK tmp_dinode(free_inode_id, // i结点的id
                             master_ID,     // 文件拥有者ID
                             DIRECTORY,     // 文件类型
                             auth,          // 权限（三位十进制数表示）
                             0,             // 文件大小
                             new_SFD_id,    // 文件地址（物理地址/下级目录ID）
                             0,             // 文件链接计数
                             tmp_time,      // 文件创建时间
                             tmp_time);
    // 保存i节点
    d_inodes.addInode(tmp_dinode);
    //添加至目录下
    SFD_ITEM tmp_sfd_item(directoryname, free_inode_id);
    all_sfd[tmp_bfd_item.getF_addr()].addSfd_item(tmp_sfd_item);
    return true;
}

vector<SFD> DISK::getAll_sfd() const
{
    return all_sfd;
}

// 寻找文件 返回inode的id 非常非常重要
int DISK::findFile(QString file_path)
{
    QStringList split_path = file_path.split("/", QString::SkipEmptyParts);
//    for(QString i : split_path)
//    {
//        qDebug() << i;
//    }
    // 特判根目录
    if(file_path == "/") {
        return 0;
    }
    // 层数
    int layer = 0;
    int layer_max = split_path.size();
    int total_layer = this->all_sfd.size();
    int cur_layer = 0;
    // 防止超出系统层数
    while (layer < layer_max) {
        // 重要的是 更新cur_layer
        // 从all_SFD中遍历搜索
        for (SFD_ITEM i : this->all_sfd[cur_layer].getSFD_list()) {
            if (i.getFile_name() == split_path[layer].toStdString()) {
                // 如果找到 且当前是最后一级目录 就返回id
                if (layer == layer_max - 1) {
                    return i.getID();
                }
                // 如果不是最后一级目录 分两种情况 可能是文件夹 可能是文件
                // 不是最后一级目录 却找到了文件 直接返回-1
                else if (layer != layer_max - 1 && this->d_inodes.findInodeByNum(i.getID()).getF_type() != DIRECTORY) {
                    return -1;
                }
                // 不是最后一级目录 找到了文件夹 更新cur_layer
                else if (layer != layer_max - 1 && this->d_inodes.findInodeByNum(i.getID()).getF_type() == DIRECTORY) {
                    cur_layer = this->findSfdIndexInTotalSfd(
                                    this->all_sfd[this->findSfd(this->d_inodes.findInodeByNum(i.getID()).getF_addr())]);
                }
            }
        }
        layer++;
    }
    return -1;
}

// 创建新文件
bool DISK::createNewFile(string path, unsigned int master_ID)
{
    string dirpath, filename;
    //划分目录和文件
    int split_index = path.length() - 1;
    for (; split_index >= 0; split_index--) {
        if (path[split_index] == '/') {
            break;
        }
    }
    dirpath = path.substr(0, split_index + 1);
    filename = path.substr(split_index + 1, path.length());
    int dir_inode_id = findFile(QString::fromStdString(dirpath));
    if (dir_inode_id < 0) {
        // 文件目录不存在
        return false;
    }
    BFD_ITEM_DISK tmp_bfd_item = d_inodes.findInodeByNum(dir_inode_id);
    // 检查重名问题
    if (all_sfd[tmp_bfd_item.getF_addr()].findSfd_item(filename) != -1) {
        // 有同名文件
        return false;
    }
    // 检测是否有空闲i节点
    int free_inode_id = d_inodes.getFreeInode();
    if (free_inode_id < 0) {
        // i节点用尽
        return false;
    }
    vector<char> auth = {'7', '5', '5'};
    time_t tmp_time;
    time(&tmp_time);                        //当前time_t类型UTC时间
    BFD_ITEM_DISK tmp_dinode(free_inode_id, // i结点的id
                             master_ID,     // 文件拥有者ID
                             COMMON,        // 文件类型
                             auth,          // 权限（三位十进制数表示）
                             0,             // 文件大小
                             -1,            // 文件地址（物理地址/下级目录ID）
                             0,             // 文件链接计数
                             tmp_time,      // 文件创建时间
                             tmp_time);     // 文件修改时间
    // 保存i节点
    d_inodes.addInode(tmp_dinode);
    //添加至目录下
    SFD_ITEM tmp_sfd_item(filename, free_inode_id);
    all_sfd[tmp_bfd_item.getF_addr()].addSfd_item(tmp_sfd_item);
    return true;
}

void DISK::delFile(QString file_path)
{
    // 递归在前台做
    int inode_id = this->findFile(file_path);
    // 回收磁盘块
    Super_block.add_disk_free_block(getBlocksUsedByFile(inode_id));
    // 从BFD中删除
    vector<BFD_ITEM_DISK> temp_all_bfd = this->d_inodes.getBFD_DISK_list();
    for (vector<BFD_ITEM_DISK>::iterator it = temp_all_bfd.begin();
         it != temp_all_bfd.end();
         it++) {
        if (it->getDinode_ID() == inode_id) {
            temp_all_bfd.erase(it);
            break;
        }
    }
    this->d_inodes.setBFD_DISK_list(temp_all_bfd);
    // 从SFD中删除
    int cur_layer = getFileCurPathIndex(file_path);
    vector<SFD_ITEM> temp = this->all_sfd[cur_layer].getSFD_list();
    for (vector<SFD_ITEM>::iterator it = temp.begin();
         it != temp.end();
         it++) {
        if (it->getID() == inode_id) {
            temp.erase(it);
            break;
        }
    }
    this->all_sfd[cur_layer].setSFD_list(temp);

    //    int dir_dfs_layer_begin = split_path.size();
    //    // 找到这个文件的inode的id
    //    int inode_id = this->findFile(file_path);
    //    // 当没有这个文件的时候 删除失败 直接返回-1
    //    if (inode_id == -1)
    //    {
    //        return false;
    //    }
    //    // 当找到这个文件 分为两种情况 一种是文件夹 一种是文件
    //    else
    //    {
    //        // 当寻找到的文件类型为文件夹 涉及到递归级联删除
    //        if (this->d_inodes.findInodeByNum(inode_id).getF_type() == directory)
    //        {
    //           // 找到该文件夹在all_sfd下的下标 然后再遍历
    //           // ------------------------------------------------------------------
    //           // 层数
    //            int layer = 0;
    //            int layer_max = split_path.size();
    //            int total_layer = this->all_sfd.size();
    //            int cur_layer = 0;
    //            // 防止超出系统层数
    //            while (layer++ && layer <= layer_max) {
    //                // 重要的是 更新cur_layer
    //                // 从all_SFD中遍历搜索
    //                for (SFD_ITEM i : this->all_sfd[cur_layer].getSFD_list()) {
    //                    if (i.getFile_name() == split_path[layer].toStdString()) {
    //                        // 如果找到 且当前是最后一级目录 就返回id
    //                        if (layer == layer_max) {
    //                            return i.getID();
    //                        }
    //                        // 如果不是最后一级目录 分两种情况 可能是文件夹 可能是文件
    //                        // 不是最后一级目录 却找到了文件 直接返回-1
    //                        else if (layer != layer_max && this->d_inodes.findInodeByNum(i.getID()).getF_type() != directory) {
    //                            return -1;
    //                        }
    //                        // 不是最后一级目录 找到了文件夹 更新cur_layer
    //                        else if (layer != layer_max && this->d_inodes.findInodeByNum(i.getID()).getF_type() == directory) {
    //                            cur_layer = this->find_sfd_index_in_total_sfd(all_sfd[cur_layer]);
    //                        }
    //                        continue;
    //                    }
    //                }
    //            }
    //           // ------------------------------------------------------------------
    //            int all_sfd_index = this->find_sfd_index_in_total_sfd()
    //           // 递归+回溯
    //        }
    //        // 如果是文件 直接删除就行 不用动磁盘块内容 只需要删除SFD和BFD即可
    //        else
    //        {
    //            // 找到对应的SFD
    //            unsigned long long layer = 0;
    //            int layer_max = split_path.size();
    //            unsigned long long total_layer = this->all_sfd.size();
    //            // 防止超出系统层数
    //            while (layer++ && layer <= total_layer)
    //            {
    //                for (vector<SFD_ITEM>::iterator it = this->all_sfd[layer].getSFD_list().begin();
    //                     it != this->all_sfd[layer].getSFD_list().end();
    //                     it++)
    //                {
    //                    if (it->getFile_name() == split_path[(int)layer].toStdString())
    //                    {
    //                        // 如果找到 直接删除 TODO:归还空块
    //                        if (layer == (unsigned long long)layer_max)
    //                        {
    //                            // 删除SFD信息
    //                            this->all_sfd[layer].getSFD_list().erase(it);
    //                            // 删除BFD信息
    //                            for (vector<BFD_ITEM_DISK>::iterator it2 = this->d_inodes.getBFD_DISK_list().begin();
    //                                 it2 != this->d_inodes.getBFD_DISK_list().end();
    //                                 it2++)
    //                            {
    //                                if (it2->getDinode_ID() == inode_id)
    //                                {
    //                                    this->d_inodes.getBFD_DISK_list().erase(it2);
    //                                }
    //                            }
    //                            return true;
    //                        } else
    //                        {
    //                            continue;
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    }
    return;
}

void DISK::setAll_sfd(const vector<SFD> &value)
{
    all_sfd = value;
}

int DISK::findSfdIndexInTotalSfd(SFD temp_sfd)
{
    for (unsigned long long i = 0; i < this->all_sfd.size(); i++) {
        if (this->all_sfd[i].getSFD_ID() == temp_sfd.getSFD_ID()) {
            return i;
        }
    }
    return -1;
}

int DISK::findSfd(int sfd_id)
{
    for (unsigned int i = 0; i < all_sfd.size(); i++) {
        if (all_sfd[i].getSFD_ID() == sfd_id) {
            return i;
        }
    }
    return -1;
}

QString DISK::getFileAuth(QString path)
{
    QString resu;
    if (getFileType(path) == DIRECTORY) {
        resu += "d";
    } else {
        resu += "-";
    }
    for (int i = 0; i < 3; i++) {
        int tmp_auth = d_inodes.findInodeByNum(findFile(path)).getAuth()[i] - '0';
        switch (tmp_auth) {
            case 1:
                resu += "--x";
                break;
            case 2:
                resu += "-w-";
                break;
            case 3:
                resu += "-wx";
                break;
            case 4:
                resu += "r--";
                break;
            case 5:
                resu += "r-x";
                break;
            case 6:
                resu += "rw-";
                break;
            case 7:
                resu += "rwx";
                break;
        }
    }
    return resu;
}

void DISK::changeFileAuth(QString path, QString auth)
{
    vector<char> tmp_auth;
    QString auth2num[] = {"--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
    for (int i = 0; i < 3; i++) {
        int j;
        for (j = 0; j < auth2num->length(); j++) {
            if (auth2num[j] == auth.mid(i * 3, 3)) {
                break;
            }
        }
        tmp_auth[i] = j + '0';
    }
    BFD_ITEM_DISK tmp = d_inodes.findInodeByNum(findFile(path));
    tmp.setAuth(tmp_auth);
    d_inodes.changeInodeByNum(findFile(path), tmp);
}

void DISK::copy_file(QString source, QString dest, int flag)
{
    int file_layer = getFileCurPathIndex(source);
    int dir_layer = nofilenameGetFileCurPathIndex(dest);
    QStringList split_path1 = source.split("/", QString::SkipEmptyParts);
    string old_file_name = split_path1.back().toStdString();
    dest = dest + QString::fromStdString(old_file_name);
    string string_source = source.toStdString();
    string string_dest = dest.toStdString();
    // 寻找旧文件 源文件
    BFD_ITEM_DISK temp_bfd_item = d_inodes.findInodeByNum(findFile(source));
    createNewFile(string_dest, temp_bfd_item.getMaster_ID());
    BFD_ITEM_DISK new_bfd_item = d_inodes.findInodeByNum(findFile(dest));
    string tmp = readFile(dest).toStdString();
    const char* ch = tmp.c_str();
    saveFile(new_bfd_item.getDinode_ID(), const_cast<char*>(ch));
}

int DISK::getFileCurPathIndex(QString file_path)
{
    QStringList split_path = file_path.split("/",QString::SkipEmptyParts);
    if(file_path == "/")
        return 0;
    // 层数
    int layer = 0;
    int layer_max = split_path.size();
    int total_layer = this->all_sfd.size();
    int cur_layer = 0;
    // 防止超出系统层数
    while (layer < layer_max) {
        // 重要的是 更新cur_layer 第一层必定是根目录
        // 从all_SFD中遍历搜索
        for (SFD_ITEM i : this->all_sfd[cur_layer].getSFD_list()) {
            if (i.getFile_name() == split_path[layer].toStdString()) {
                // 如果找到 且当前是最后一级目录 就返回id
                if (layer == layer_max - 1) {
                    break;
                }
                // 进入文件夹下
                else if (layer != layer_max - 1 && this->d_inodes.findInodeByNum(i.getID()).getF_type() == DIRECTORY) {
                    cur_layer = this->findSfdIndexInTotalSfd(
                                    this->all_sfd[this->findSfd(this->d_inodes.findInodeByNum(i.getID()).getF_addr())]);
                }
            }
        }
        layer++;
    }
    return cur_layer;
}

int DISK::nofilenameGetFileCurPathIndex(QString file_path)
{
    QStringList split_path = file_path.split("/", QString::SkipEmptyParts);
    if(file_path == "/") {
        return 0;
    }
    // 层数
    int layer = 0;
    int layer_max = split_path.size();
    int total_layer = this->all_sfd.size();
    int cur_layer = 0;
    // 防止超出系统层数
    while (layer < layer_max) {
        // 重要的是 更新cur_layer 第一层必定是根目录
        // 从all_SFD中遍历搜索
        for (SFD_ITEM i : this->all_sfd[cur_layer].getSFD_list()) {
            if (i.getFile_name() == split_path[layer].toStdString()) {
                // 如果找到 且当前是最后一级目录 就返回id
                if (layer == layer_max - 1) {
                    cur_layer = this->findSfdIndexInTotalSfd(
                                    this->all_sfd[this->findSfd(this->d_inodes.findInodeByNum(i.getID()).getF_addr())]);
                    break;
                }
                // 进入文件夹下
                else if (layer != layer_max - 1 && this->d_inodes.findInodeByNum(i.getID()).getF_type() == DIRECTORY) {
                    cur_layer = this->findSfdIndexInTotalSfd(
                                    this->all_sfd[this->findSfd(this->d_inodes.findInodeByNum(i.getID()).getF_addr())]);
                }
            }
        }
        layer++;
    }
    return cur_layer;
}

bool DISK::fileIsEmpty(QString file_path)
{
    int temp_inode_index = findFile(file_path);
    if (this->d_inodes.findInodeByNum(temp_inode_index).getF_size() == 0) {
        return true;
    } else {
        return false;
    }
}

void DISK::moveFileToDir(QString source, QString dest)
{
    int file_layer = getFileCurPathIndex(source);
    int dir_layer = nofilenameGetFileCurPathIndex(dest);
    QStringList split_path = source.split("/", QString::SkipEmptyParts);
    string old_file_name = split_path.back().toStdString();
    vector<SFD_ITEM> temp = this->all_sfd[file_layer].getSFD_list();
    vector<SFD_ITEM> temp_dir = this->all_sfd[dir_layer].getSFD_list();
    // 找到文件 然后填在文件夹里 同时删除
    for (vector<SFD_ITEM>::iterator it = temp.begin();
         it != temp.end();
         it++) {
        if (it->getFile_name() == old_file_name) {
            temp_dir.push_back(*it);
            // 删除这个表项
            temp.erase(it);
            break;
        }
    }
    this->all_sfd[file_layer].setSFD_list(temp);
    this->all_sfd[dir_layer].setSFD_list(temp_dir);
}

QStringList DISK::getFileList(QString file_path)
{
    int sfd_index = nofilenameGetFileCurPathIndex(file_path);
    QStringList ans_list;
    for (SFD_ITEM i : all_sfd[sfd_index].getSFD_list()) {
        ans_list.append(QString::fromStdString(i.getFile_name()));
    }
    return ans_list;
}

file_type DISK::getFileType(QString file_path)
{
    int temp_inode_index = findFile(file_path);
    return this->d_inodes.findInodeByNum(temp_inode_index).getF_type();
}

void DISK::changeFileName(QString source, QString dest)
{
    int sfd_index = getFileCurPathIndex(source);
    QStringList split_path = dest.split("/", QString::SkipEmptyParts);
    QStringList split_path2 = source.split("/", QString::SkipEmptyParts);
    string new_file_name = split_path.back().toStdString();
    string old_file_name = split_path2.back().toStdString();
    vector<SFD_ITEM> temp = this->all_sfd[sfd_index].getSFD_list();
    for (vector<SFD_ITEM>::iterator it = temp.begin();
         it != temp.end();
         it++) {
        if (it->getFile_name() == old_file_name) {
            it->setFile_name(new_file_name);
            break;
        }
    }
    this->all_sfd[sfd_index].setSFD_list(temp);

    return;
}

time_t DISK::getFileChangeTime(QString file_path)
{
    int temp_inode_index = findFile(file_path);
    return this->d_inodes.findInodeByNum(temp_inode_index).getF_change_time();
}

string DISK::getFileCreater(QString file_path)
{
    int temp_inode_index = findFile(file_path);
    BFD_ITEM_DISK temp = d_inodes.findInodeByNum(temp_inode_index);
    int creater_id = temp.getMaster_ID();
    for (USER i : this->user_table.getUser_table()) {
        if (i.getId() == creater_id) {
            return i.getUsername();
        }
    }
}

time_t DISK::getFileCreateTime(QString file_path)
{
    int temp_inode_index = findFile(file_path);
    return this->d_inodes.findInodeByNum(temp_inode_index).getF_creat_time();
}

string DISK::getUserPass(string user_name)
{
    return this->user_table.find_user(user_name).getUserpwd();
}

int DISK::getUserIdByUsenName(string user_name)
{
    for(USER user : this->user_table.getUser_table()) {
        if(user.getUsername() == user_name) {
            return user.getId();
        }
    }
    return -1;
}

void DISK::addUser(string user_name)
{
    USER *temp_user = new USER();
    temp_user->setId(this->user_table.getUser_table().back().getId() + 1);
    temp_user->setUserpwd("123456");
    temp_user->setUsergrp(1);
    temp_user->setUsername(user_name);
    this->user_table.add_user(*temp_user);
}

void DISK::delUser(string user_name)
{
    vector<USER> temp = this->getUser_table().getUser_table();
    for (vector<USER>::iterator it = temp.begin();
         it != temp.end();
         it++) {
        if (it->getUsername() == user_name) {
            this->user_table.getUser_table().erase(it);
            break;
        }
    }
    this->user_table.setUser_table(temp);
}

int DISK::getUserGroup(string user_name)
{
    for (vector<USER>::iterator it = this->user_table.getUser_table().begin();
         it != this->user_table.getUser_table().end();
         it++) {
        if (it->getUsername() == user_name) {
            return it->getUsergrp();
        }
    }
}

QString DISK::readFile(QString path)
{
    int tmp_inode_index = findFile(path);
    unsigned int addr_first = this->d_inodes.findInodeByNum(tmp_inode_index).getF_addr();
    if(d_block[addr_first].getBlock_type() == CONTENT) {
        return QString(QLatin1String(d_block[addr_first].getData()));
    } else {
        QString tmp_content;
        vector<int> addr_seconds = d_block[addr_first].getIndex();
        for(int i = 0; i < d_block[addr_first].getIndex_num(); i++) {
            if(d_block[addr_seconds[i]].getBlock_type() == CONTENT) {
                tmp_content += QString(QLatin1String(d_block[addr_seconds[i]].getData()));
            } else {
                vector<int> addr_thirds = d_block[addr_seconds[i]].getIndex();
                for(int j = 0; i < d_block[addr_seconds[i]].getIndex_num(); j++) {
                    if(d_block[addr_thirds[j]].getBlock_type() == CONTENT) {
                        tmp_content += QString(QLatin1String(d_block[addr_thirds[j]].getData()));
                    }
                }
            }
        }
        return tmp_content;
    }
}

QString DISK::readFileByLine(QString path)
{
    int tmp_inode_index = findFile(path);
    unsigned int addr_first = this->d_inodes.findInodeByNum(tmp_inode_index).getF_addr();
    if(d_block[addr_first].getBlock_type() == CONTENT) {
        return QString(QLatin1String(d_block[addr_first].getData()));
    } else {
        diskblock_type tmp_type = INDEX;
        unsigned int tmp_addr = addr_first;
        while(tmp_type == INDEX) {
            tmp_addr = d_block[tmp_addr].getIndex()[0];
            tmp_type = d_block[tmp_addr].getBlock_type();
        }
        return QString(QLatin1String(d_block[tmp_addr].getData()));
    }
}

void DISK::changeUserPass(string user_name, string pass)
{
    USER_TABLE temp = this->getUser_table();
    for (vector<USER>::iterator it = temp.getUser_table().begin();
         it != temp.getUser_table().end();
         it++) {
        if (it->getUsername() == user_name) {
            it->setUserpwd(pass);
            break;
        }
    }
    this->setUser_table(temp);
    return;
}

bool DISK::userExist(string user_name)
{
    for (vector<USER>::iterator it = this->user_table.getUser_table().begin();
         it != this->user_table.getUser_table().end();
         it++) {
        if (it->getUsername() == user_name) {
            return true;
        }
    }
    return false;
}

bool DISK::EditFile(QString path, QString content)
{
    int tmp_inode_index = findFile(path);
    Super_block.add_disk_free_block(getBlocksUsedByFile(tmp_inode_index));
    string tmp = content.toStdString();
    const char *ch = tmp.c_str();
    saveFile(tmp_inode_index, const_cast<char *>(ch));
}

bool DISK::addLineInFile(QString path, QString content)
{
    try {
        QString total_content = readFile(path) + content;
        EditFile(path, total_content);
    }  catch (exception e) {
        return false;
    }
    return true;
}

vector<int> DISK::getBlocksUsedByFile(int inode_id)
{
    vector<int> resu;
    unsigned int addr_first = this->d_inodes.findInodeByNum(inode_id).getF_addr();
    if (d_block[addr_first].getBlock_type() == CONTENT) {
        resu.push_back(addr_first);
    } else {
        vector<int> addr_seconds = d_block[addr_first].getIndex();
        if (d_block[addr_seconds[0]].getBlock_type() == CONTENT) {
            resu.insert(resu.end(), addr_seconds.begin(), addr_seconds.end());
        } else {
            for (int i = 0; i < d_block[addr_first].getIndex_num(); i++) {
                vector<int> addr_thirds = d_block[addr_seconds[i]].getIndex();
                if (d_block[addr_thirds[0]].getBlock_type() == CONTENT) {
                    resu.insert(resu.end(), addr_thirds.begin(), addr_thirds.end());
                }
            }
        }
    }
    return resu;
}
string DISK::getRootPass()
{
    for (vector<USER>::iterator it = this->user_table.getUser_table().begin();
         it != this->user_table.getUser_table().end();
         it++) {
        if (it->getUsergrp() == 0) {
            return it->getUserpwd();
        }
    }
    return "";
}

USER_TABLE DISK::getUser_table() const
{
    return user_table;
}

void DISK::setUser_table(const USER_TABLE &value)
{
    user_table = value;
}

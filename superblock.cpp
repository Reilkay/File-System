#include "superblock.h"
#include "configure.h"
#include <QDebug>

// 方法实现
// 重构默认构造
SUPER_BLOCK::SUPER_BLOCK()
{
    // 写0比较保险
    // this->super_block_num = SUPERFREEBLOCK;
    this->super_block_size = 0;
    this->disk_num_list.reserve(SUPERFREEBLOCK);
    this->next_super_block = nullptr;
    this->total_free_block_num = 0;
}

void SUPER_BLOCK::Init()
{
    // 每个数据块
    int per_disk_block_size = BLOCKSIZE;
    // 数据块数目
    int data_block_num = DATABLOCKNUM;

    // 每组有50个空节点
    int stack_data_block_size = SUPERFREEBLOCK;
    int cur_size = 0;
    // 或许可以用到超级块序号??? 先写上
    int super_block_num_flag = 0;
    // 类似头插法
    SUPER_BLOCK* tail = nullptr;
    // cur_size用于记录当前的分配块号

    qDebug() << "loops start";

    while(cur_size < DATABLOCKNUM)
    {
//       qDebug() << cur_size;
       // 在new的时候 就已经vector-resize-50 next=null了
       SUPER_BLOCK* temp_super_block = new SUPER_BLOCK();
       temp_super_block->setSuper_block_num(super_block_num_flag++);
       // 说明尾巴已经生成
       if(tail != nullptr)
       {
         temp_super_block->setNext_super_block(tail);
       }
       // 初始块的next本来就是null
       for(int j=0;
           cur_size < DATABLOCKNUM && j< SUPERFREEBLOCK;
           j++)
       {
          // 因为0号不存东西 所以不设置组长块
          if(j == 0 && cur_size != 0)
          {
              temp_super_block->setAdmin_num(cur_size);
          }
          temp_super_block->disk_num_list.push_back(cur_size);
          cur_size += 1;
          temp_super_block->setSuper_block_size(j+1);
       }
       tail = temp_super_block;
    }
    qDebug() << "loops end";
    this->setNext_super_block(tail);
    this->next_super_block->setTotal_free_block_num(cur_size);

}

// 根据文件所需的数据块数目 返回对应的磁盘块序号 vector
// 扩展：当磁盘不够分时 返回空的vector
vector<int> SUPER_BLOCK::distri_disk_free_block(int need_block_numbers)
{
   vector<int> ans;
   if(this->next_super_block->getTotal_free_block_num() < need_block_numbers)
       return ans;
   else
   {
       while(need_block_numbers --)
       {
           ans.push_back(this->next_super_block->disk_num_list.back());
           this->next_super_block->disk_num_list.pop_back();
           this->next_super_block->total_free_block_num--;
           this->next_super_block->super_block_size--;
           // 当前用完则发生替换
           if(this->next_super_block->super_block_size == 0)
           {
               // 替换全部第一个超级块内容 其实只替换所有空闲块总数就行
               this->next_super_block->next_super_block->total_free_block_num = this->next_super_block->total_free_block_num;
               // 直接覆盖掉当前节点
               this->next_super_block = this->next_super_block->next_super_block;
           }
       }
   }
   return ans;
}

// 增加磁盘块
bool SUPER_BLOCK::add_disk_free_block(vector<int> free_disk_numbers)
{
    if(this->next_super_block->total_free_block_num+free_disk_numbers.size() >= DATABLOCKNUM)
        return false;
    SUPER_BLOCK* tail = this->next_super_block;
    for(auto i:free_disk_numbers)
    {
       // 满了就再创建一个super-block
       if(this->next_super_block->super_block_size >= 50)
       {
           SUPER_BLOCK* new_super_block = new SUPER_BLOCK();
           new_super_block->next_super_block = tail;
           // 替换全部参数---------------------------------------------
           new_super_block->super_block_num = this->next_super_block->super_block_num+1;
           new_super_block->total_free_block_num = this->next_super_block->total_free_block_num+1;
           // 替换全部参数---------------------------------------------
           // 指针替换
           this->next_super_block = new_super_block;
           tail = this->next_super_block;
           // 然后再添加
           this->next_super_block->disk_num_list.push_back(i);
           // 选择组长块
           this->next_super_block->admin_num = i;
           // 长度++
           this->next_super_block->super_block_size++;
       }
       // 没满就往当前的super-block添加
       else
       {
            this->next_super_block->disk_num_list.push_back(i);
            this->next_super_block->total_free_block_num++;
            this->next_super_block->super_block_size++;
       }
    }
    return true;
}

// 返回所有的空闲磁盘块序号
vector<int> SUPER_BLOCK::get_all_disk_free_block()
{
    vector<int> ans;
    SUPER_BLOCK* temp_point = this->next_super_block;
    while(temp_point != nullptr)
    {
        for(auto i:temp_point->disk_num_list)
        {
           ans.push_back(i);
        }
        temp_point = temp_point->next_super_block;
    }
    return ans;
}



int SUPER_BLOCK::getSuper_block_size() const
{
    return super_block_size;
}

void SUPER_BLOCK::setSuper_block_size(int value)
{
    super_block_size = value;
}

SUPER_BLOCK *SUPER_BLOCK::getNext_super_block() const
{
    return next_super_block;
}

void SUPER_BLOCK::setNext_super_block(SUPER_BLOCK *value)
{
    next_super_block = value;
}

int SUPER_BLOCK::getSuper_block_num() const
{
    return super_block_num;
}

void SUPER_BLOCK::setSuper_block_num(int value)
{
    super_block_num = value;
}

vector<int> SUPER_BLOCK::getDisk_num_list() const
{
    return disk_num_list;
}

void SUPER_BLOCK::setDisk_num_list(const vector<int> &value)
{
    disk_num_list = value;
}

int SUPER_BLOCK::getAdmin_num() const
{
    return admin_num;
}

void SUPER_BLOCK::setAdmin_num(int value)
{
    admin_num = value;
}

int SUPER_BLOCK::getTotal_free_block_num() const
{
    return total_free_block_num;
}

void SUPER_BLOCK::setTotal_free_block_num(int value)
{
    total_free_block_num = value;
}

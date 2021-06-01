#ifndef CONFIGURE_H
#define CONFIGURE_H

// 每磁盘块大小
#define BLOCKSIZE   512
// 磁盘块(数据块)数目
#define DATABLOCKNUM  512
// 系统打开文件的最大项数
#define SYSOPENFILE 40
// 每个目录包含的最大文件项数
#define DIRNUM      128
// 每个目录项名字所占字节数，另加i节点号（指针）2个字节
#define DIRSIZ      14
// 口令字
#define PWDSIZ      12
// 最多可设32个口令登录
#define PWDNUM      32
// 每个用户最多可打开20个文件，即用户打开文件最大次数
#define NOFILE      20
// 每个i节点最多指向10块，addr[0]~addr[9]
#define NADDR       10
// 共128个Hash链表，提供索引i节点（必须为2的幂）
#define NHINO       128
// 最多允许10个用户登录
#define USERNUM     10
// 每个磁盘i节点所占字节
#define DINODESIZE   32
// 所有磁盘i节点共占32个物理块
#define DINODEBLK   32
// 共有512个目录文件物理块
#define FILEBLK     512
// 超级块中空闲块数组的最大块数
#define SUPERFREEBLOCK     50
// 超级块中空闲节点的最大块数
#define NICINODE     50
// i节点起始地址 i节点连续存储
#define DINODESTART 2*BLOCKSIZE
// 目录、文件区起始地址
#define DATASTART   (2+DINODEBLK)*BLOCKSIZE
#define DIEMPTY     00000
#define DIFILE      01000
#define DIDIR       02000
#define UDIREAD     00001
#define UDIWRITE    00002
#define UDIEXICUTE  00004
#define GDIREAD     00010
#define GDIWRITE    00020
#define GDIEXICUTE  00040
#define ODIREAD     00100
#define ODIWRITE    00200
#define ODIEXICUTE  00400
#define READ        1
#define WRITE       2
#define EXICUTE     3
#define DEFAULTMODE 00777
#define IUPDATE     00002
#define SUPDATE     00001
#define FREAD       00001
#define FWRITE      00002
#define FAPPEND     00004
#define DISKFULL    65535
#define SEEK_SET    0

#endif // CONFIGURE_H

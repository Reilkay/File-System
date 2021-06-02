#include "instruction.h"
/*
Instruction::Instruction(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant Instruction::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex Instruction::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex Instruction::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int Instruction::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int Instruction::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant Instruction::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
*/

/*
 * NAME
 *      ls - Displays the contents of the specified working directory
 * SYNOPSIS
 *      ls [-alrtAFR] [name...]
 */
void ls(QStringList strList)
{
    int length = strList.count();
    if(length > 1 && strList[1] == "--help")
    {
        qDebug()<<"Usage: ls [OPTION]... [FILE]...";
        qDebug()<<"List information about the FILEs (the current directory by default).";
        qDebug()<<"Sort entries alphabetically if none of -cftuvSUX nor --sort is specified."<<Qt::endl;

        qDebug()<<"Mandatory arguments to long options are mandatory for short options too.";
        qDebug()<<"  -a, --all                  do not ignore entries starting with .";
        qDebug()<<"  -A, --almost-all           do not list implied . and ..";
        qDebug()<<"      --author               with -l, print the author of each file";
        qDebug()<<"  -b, --escape               print C-style escapes for nongraphic characters";
        qDebug()<<"      --block-size=SIZE      scale sizes by SIZE before printing them; e.g.,";
        qDebug()<<"                               '--block-size=M' prints sizes in units of";
        qDebug()<<"                               1,048,576 bytes; see SIZE format below";
        qDebug()<<"  -B, --ignore-backups       do not list implied entries ending with ~";
        qDebug()<<"  -c                         with -lt: sort by, and show, ctime (time of last";
        qDebug()<<"                               modification of file status information);";
        qDebug()<<"                               with -l: show ctime and sort by name;";
        qDebug()<<"                               otherwise: sort by ctime, newest first";
        qDebug()<<"  -C                         list entries by columns";
        qDebug()<<"      --color[=WHEN]         colorize the output; WHEN can be 'never', 'auto',";
        qDebug()<<"                               or 'always' (the default); more info below";
        qDebug()<<"  -d, --directory            list directories themselves, not their contents";
        qDebug()<<"  -D, --dired                generate output designed for Emacs' dired mode";
        qDebug()<<"  -f                         do not sort, enable -aU, disable -ls --color";
        qDebug()<<"  -F, --classify             append indicator (one of */=>@|) to entries";
        qDebug()<<"      --file-type            likewise, except do not append '*'";
        qDebug()<<"      --format=WORD          across -x, commas -m, horizontal -x, long -l,";
        qDebug()<<"                               single-column -1, verbose -l, vertical -C";
        qDebug()<<"      --full-time            like -l --time-style=full-iso";
        qDebug()<<"  -g                         like -l, but do not list owner";
        qDebug()<<"      --group-directories-first";
        qDebug()<<"                             group directories before files;";
        qDebug()<<"                               can be augmented with a --sort option, but any";
        qDebug()<<"                               use of --sort=none (-U) disables grouping";
        qDebug()<<"  -G, --no-group             in a long listing, don't print group names";
        qDebug()<<"  -h, --human-readable       with -l, print sizes in human readable format";
        qDebug()<<"                               (e.g., 1K 234M 2G)";
        qDebug()<<"      --si                   likewise, but use powers of 1000 not 1024";
        qDebug()<<"  -H, --dereference-command-line";
        qDebug()<<"                             follow symbolic links listed on the command line";
        qDebug()<<"      --dereference-command-line-symlink-to-dir";
        qDebug()<<"                             follow each command line symbolic link";
        qDebug()<<"                               that points to a directory";
        qDebug()<<"      --hide=PATTERN         do not list implied entries matching shell PATTERN";
        qDebug()<<"                               (overridden by -a or -A)";
        qDebug()<<"      --indicator-style=WORD  append indicator with style WORD to entry names:";
        qDebug()<<"                               none (default), slash (-p),";
        qDebug()<<"                               file-type (--file-type), classify (-F)";
        qDebug()<<"  -i, --inode                print the index number of each file";
        qDebug()<<"  -I, --ignore=PATTERN       do not list implied entries matching shell PATTERN";
        qDebug()<<"  -k, --kibibytes            default to 1024-byte blocks for disk usage";
        qDebug()<<"  -l                         use a long listing format";
        qDebug()<<"  -L, --dereference          when showing file information for a symbolic";
        qDebug()<<"                               link, show information for the file the link";
        qDebug()<<"                               references rather than for the link itself";
        qDebug()<<"  -m                         fill width with a comma separated list of entries";
        qDebug()<<"  -n, --numeric-uid-gid      like -l, but list numeric user and group IDs";
        qDebug()<<"  -N, --literal              print raw entry names (don't treat e.g. control";
        qDebug()<<"                               characters specially)";
        qDebug()<<"  -o                         like -l, but do not list group information";
        qDebug()<<"  -p, --indicator-style=slash";
        qDebug()<<"                             append / indicator to directories";
        qDebug()<<"  -q, --hide-control-chars   print ? instead of nongraphic characters";
        qDebug()<<"      --show-control-chars   show nongraphic characters as-is (the default,";
        qDebug()<<"                               unless program is 'ls' and output is a terminal)";
        qDebug()<<"  -Q, --quote-name           enclose entry names in double quotes";
        qDebug()<<"      --quoting-style=WORD   use quoting style WORD for entry names:";
        qDebug()<<"                               literal, locale, shell, shell-always, c, escape";
        qDebug()<<"  -r, --reverse              reverse order while sorting";
        qDebug()<<"  -R, --recursive            list subdirectories recursively";
        qDebug()<<"  -s, --size                 print the allocated size of each file, in blocks";
        qDebug()<<"  -S                         sort by file size";
        qDebug()<<"      --sort=WORD            sort by WORD instead of name: none (-U), size (-S),";
        qDebug()<<"                               time (-t), version (-v), extension (-X)";
        qDebug()<<"      --time=WORD            with -l, show time as WORD instead of default";
        qDebug()<<"                               modification time: atime or access or use (-u)";
        qDebug()<<"                               ctime or status (-c); also use specified time";
        qDebug()<<"                               as sort key if --sort=time";
        qDebug()<<"      --time-style=STYLE     with -l, show times using style STYLE:";
        qDebug()<<"                               full-iso, long-iso, iso, locale, or +FORMAT;";
        qDebug()<<"                               FORMAT is interpreted like in 'date'; if FORMAT";
        qDebug()<<"                               is FORMAT1<newline>FORMAT2, then FORMAT1 applies";
        qDebug()<<"                               to non-recent files and FORMAT2 to recent files;";
        qDebug()<<"                               if STYLE is prefixed with 'posix-', STYLE";
        qDebug()<<"                               takes effect only outside the POSIX locale";
        qDebug()<<"  -t                         sort by modification time, newest first";
        qDebug()<<"  -T, --tabsize=COLS         assume tab stops at each COLS instead of 8";
        qDebug()<<"  -u                         with -lt: sort by, and show, access time;";
        qDebug()<<"                               with -l: show access time and sort by name;";
        qDebug()<<"                               otherwise: sort by access time";
        qDebug()<<"  -U                         do not sort; list entries in directory order";
        qDebug()<<"  -v                         natural sort of (version) numbers within text";
        qDebug()<<"  -w, --width=COLS           assume screen width instead of current value";
        qDebug()<<"  -x                         list entries by lines instead of by columns";
        qDebug()<<"  -X                         sort alphabetically by entry extension";
        qDebug()<<"  -1                         list one file per line"<<Qt::endl;

        qDebug()<<"SELinux options:"<<Qt::endl;

        qDebug()<<"  --lcontext                 Display security context.   Enable -l. Lines";
        qDebug()<<"                             will probably be too wide for most displays.";
        qDebug()<<"  -Z, --context              Display security context so it fits on most";
        qDebug()<<"                             displays.  Displays only mode, user, group,";
        qDebug()<<"                             security context and file name.";
        qDebug()<<"  --scontext                 Display only security context and file name.";
        qDebug()<<"      --help     display this help and exit";
        qDebug()<<"      --version  output version information and exit"<<Qt::endl;

        qDebug()<<"SIZE is an integer and optional unit (example: 10M is 10*1024*1024).  Units";
        qDebug()<<"are K, M, G, T, P, E, Z, Y (powers of 1024) or KB, MB, ... (powers of 1000).";

        qDebug()<<"Using color to distinguish file types is disabled both by default and";
        qDebug()<<"with --color=never.  With --color=auto, ls emits color codes only when";
        qDebug()<<"standard output is connected to a terminal.  The LS_COLORS environment";
        qDebug()<<"variable can change the settings.  Use the dircolors command to set it."<<Qt::endl;

        qDebug()<<"Exit status:";
        qDebug()<<" 0  if OK,";
        qDebug()<<" 1  if minor problems (e.g., cannot access subdirectory),";
        qDebug()<<" 2  if serious trouble (e.g., cannot access command-line argument)."<<Qt::endl;

        qDebug()<<"GNU coreutils online help: <http://www.gnu.org/software/coreutils/>";
        qDebug()<<"For complete documentation, run: info coreutils 'ls invocation'";
    }
    else
    {
//        file_node* fi;
//        if(length == 1)
//            fi=get_fi("当前路径");
//        else if(strList[1][0] != '-')
//            fi=get_fi(strList[1]);

//        if(fi=nullptr)
//        {
//            qDebug().nospace()<<"ls: cannot access "<<qPrintable(strList[1])<<": No such file or directory";
//            return ;
//        }

//        QStringList ansList;
//        QStringList functionList = strList[1].split("",QString::SkipEmptyParts);

//        if(functionList.indexOf("a") != -1)
//            ansList<<"."<<"..";
//        if(functionList.indexOf("a") != -1 || functionList.indexOf("A") != -1)
//        {
//            while(fi!=nullptr)
//            {
//                ansList<<fi->getname();
//                fi=fi->next;
//            }
//        }
//        else
    }
}

/*
 *NAME
 *    cd - Change the shell working directory.
 *SYNOPSIS
 *    cd [dir]
 */
void cd(QStringList strList)
{
    //bool if_success = 调用切换路径函数(strList[1])
    //if(!if_success)
        qDebug().nospace()<<"-bash: cd: " << qPrintable(strList[1]) << ": No such file or directory";
}

/*
 * NAME
 *      Show working directory
 * SYNOPSIS
 *      pwd
 */
void pwd()
{
    qDebug()<<qPrintable("当前工作路径");
}

/*
 * NAME
 *      Create directory
 * SYNOPSIS
 *      mkdir [-p] dirName
 */
void mkdir(QStringList strList, QString user)
{
    int length = strList.count();
    if(length == 1)  //e.g. mkdir
    {
        qDebug()<<"mkdir: missing operand";
        qDebug()<<"Try 'mkdir --help' for more information.";
    }
    else if(strList[1] == "--help")
    {
        qDebug()<<"Usage: mkdir [OPTION]... DIRECTORY...";
        qDebug()<<"Create the DIRECTORY(ies), if they do not already exist."<<Qt::endl;

        qDebug()<<"Mandatory arguments to long options are mandatory for short options too.";
        qDebug()<<"  -m, --mode=MODE   set file mode (as in chmod), not a=rwx - umask";
        qDebug()<<"  -p, --parents     no error if existing, make parent directories as needed";
        qDebug()<<"  -v, --verbose     print a message for each created directory";
        qDebug()<<"  -Z                   set SELinux security context of each created directory";
        qDebug()<<"                         to the default type";
        qDebug()<<"      --context[=CTX]  like -Z, or if CTX is specified then set the SELinux";
        qDebug()<<"                         or SMACK security context to CTX";
        qDebug()<<"      --help     display this help and exit";
        qDebug()<<"      --version  output version information and exit"<<Qt::endl;

        qDebug()<<"GNU coreutils online help: <http://www.gnu.org/software/coreutils/>";
        qDebug()<<"For complete documentation, run: info coreutils 'mkdir invocation'";
    }
    else if(strList[1].length() > 1 && strList[1][0] == '-' && strList[1][1] != 'p')
    {
        if(strList[1].length() == 2 && strList[1][1] == '-')    //e.g. mkdir --
        {
            qDebug()<<"mkdir: missing operand";
            qDebug()<<"Try 'mkdir --help' for more information.";
        }
        else if(strList[1].length() == 2)   //e.g. mkdir -a
        {
            qDebug().nospace()<<"mkdir: invalid option -- '"<<strList[1][1]<<"'";
            qDebug()<<"Try 'mkdir --help' for more information.";
        }
        else    //e.g. mkdir --- || mkdir --a
        {
            qDebug().nospace()<<"mkdir: unrecognized option -- '"<<qPrintable(strList[1])<<"'";
            qDebug()<<"Try 'mkdir --help' for more information.";
        }
    }
    else
    {
        int file_place = 1;
        if(strList[1].mid(0,2) == "-p")
        {
            if(length <= 2)
            {
                qDebug()<<"mkdir: missing operand";
                qDebug()<<"Try 'mkdir --help' for more information.";
                return ;
            }

            file_place += 1;
        }
        QString file_name = strList[file_place];

        if(file_if_exist(file_name))    //判断是否存在
        {
            if(file_place == 1)
            {
                qDebug().nospace()<<"mkdir: cannot create directory ‘"<<qPrintable(file_name)<<"’: File exists";
            }
            return ;
        }

        //获取当前工作的路径，以判断当前所拥有的权限
        QStringList work_path_list = strList[1].split("/");
        QString work_path;
        if(work_path_list.count() == 1)
        {
            work_path = "当前路径";
        }
        else
        {
            work_path_list.removeLast();
            work_path = work_path_list.join("/");
        }

        QString permission = file_permission("work_path");

        //permission 格式为 ‘drwxrwxrwx'
        //权限判断
        if(user=="sudo")    //owner
        {
            if(permission[1] == 'r')
                create_file(file_name);
            else
                qDebug()<<"Permission denied";
        }
        else if(get_uesr_permissions(user))   //获取权限，group
        {
            if(permission[4] == 'r')
                create_file(file_name);
            else
                qDebug()<<"Permission denied";
        }
        else    //others
        {
            if(permission[7] == 'r')
                create_file(file_name);
            else
                qDebug()<<"Permission denied";
        }
    }
}

/*
 * NAME
 *      Delete empty directory
 * SYNOPSIS
 *      rmdir [-p] dirName
 */
void rmdir(QStringList strList, QString user)
{
    int length = strList.count();
    if(length == 1)
    {
        qDebug()<<"rmdir: missing operand";
        qDebug()<<"Try 'rmdir --help' for more information.";
    }
    else if(strList[1] == "--help")
    {
        qDebug()<<"Usage: rmkdir [OPTION]... DIRECTORY...";
        qDebug()<<"Remove the DIRECTORY(ies), if they are empty."<<Qt::endl;

        qDebug()<<"      --ignore-fail-on-non-empty";
        qDebug()<<"                  ignore each failure that is solely because a directory";
        qDebug()<<"                    is non-empty";
        qDebug()<<"  -p, --parents   remove DIRECTORY and its ancestors; e.g., 'rmdir -p a/b/c' is";
        qDebug()<<"                    similar to 'rmdir a/b/c a/b a'";
        qDebug()<<"  -v, --verbose   output a diagnostic for every directory processed";
        qDebug()<<"      --help     display this help and exit";
        qDebug()<<"      --version  output version information and exit"<<Qt::endl;

        qDebug()<<"GNU coreutils online help: <http://www.gnu.org/software/coreutils/>";
        qDebug()<<"For complete documentation, run: info coreutils 'rmdir invocation'";
    }
    else if(strList[1].length() > 1 && strList[1][0] == '-' && strList[1][1] != 'p')
    {
        if(strList[1].length() == 2 && strList[1][1] == '-')
        {
            qDebug()<<"rmdir: missing operand";
            qDebug()<<"Try 'rmdir --help' for more information.";
        }
        else if(strList[1].length() == 2)
        {
            qDebug().nospace()<<"rmdir: invalid option -- '"<<strList[1][1]<<"'";
            qDebug()<<"Try 'rmdir --help' for more information.";
        }
        else
        {
            qDebug().nospace()<<"rmdir: unrecognized option -- '"<<qPrintable(strList[1])<<"'";
            qDebug()<<"Try 'rmdir --help' for more information.";
        }
    }
    else
    {
        int file_place = 1;
        if(strList[1].mid(0,2) == "-p")
        {
            if(length <= 2)
            {
                qDebug()<<"rmdir: missing operand";
                qDebug()<<"Try 'rmdir --help' for more information.";
                return ;
            }
            file_place += 1;
        }
        QString file_name = strList[file_place];

        if(file_if_exist(file_name))  //判断文件是否存在
        {
            qDebug().nospace()<<"rmdir: cannot create directory ‘"<<qPrintable(file_name)<<"’: File exists";
            return ;
        }

        if(!if_empty(file_name))    //判断文件目录是否为空
        {
            qDebug().nospace()<<"rmdir: failed to remove ‘"<<qPrintable(file_name)<<"’: Directory not empty";
            return ;
        }

        //含'-p'时 若删除当前目录会造成上级目录为空，则逐级删除 直至删除至当前工作目录
        do
        {
            QStringList work_path_list = strList[1].split("/");
            QString work_path;
            if(work_path_list.count() == 1)
            {
                work_path = "当前路径";
            }
            else
            {
                work_path_list.removeLast();
                work_path = work_path_list.join("/");
            }

            QString permission = file_permission(file_name);    //删除为获取所删除的目录的权限
            //permission 格式为 ‘drwxrwxrwx'
            if(user=="sudo")    //owner
            {
                if(permission[2] == 'w')
                    delete_file(file_name);
                else
                    qDebug()<<"Permission denied";
            }
            else if(get_uesr_permissions(user))   //获取权限，group
            {
                if(permission[5] == 'w')
                    delete_file(file_name);
                else
                    qDebug()<<"Permission denied";
            }
            else    //others
            {
                if(permission[8] == 'w')
                    delete_file(file_name);
                else
                    qDebug()<<"Permission denied";
            }

            file_name = work_path;

        }while(!if_empty(file_name) && file_name != "当前路径" && file_place == 2);
    }
}

/*rm对文件目录进行递归删除*/
void rm_del(QString filename,int ask,QString user)
{
    while(!if_empty(filename))
    {
        QStringList file_list = get_file_list(filename);
        for(int i=0;i<file_list.count();i++)
        {
            if(file_type(file_list[i]) == "文件目录")
                rm_del(file_list[i],ask,user);
            else
            {
                QString delete_answer;
                if(ask)
                {
                    qDebug().nospace()<<"rm: remove "<<file_type(file_list[i])<<" ‘"<<file_list[i]<<"’?";
                    delete_answer = get_delete_answer();    //获取用户输入
                }

                if(!ask || delete_answer == 'y')
                {

                    QString permission = file_permission(file_list[i]);
                    //permission 格式为 ‘drwxrwxrwx'
                    if(user=="sudo")    //owner
                    {
                        if(permission[2] == 'w')
                            delete_file(file_list[i]);
                        else
                            qDebug()<<"Permission denied";
                    }
                    else if(get_uesr_permissions(user))   //获取权限，group
                    {
                        if(permission[5] == 'w')
                            delete_file(file_list[i]);
                        else
                            qDebug()<<"Permission denied";
                    }
                    else    //others
                    {
                        if(permission[8] == 'w')
                            delete_file(file_list[i]);
                        else
                            qDebug()<<"Permission denied";
                    }

                }
            }

        }
    }

    QString delete_answer;
    if(ask)
    {
        qDebug().nospace()<<"rm: remove "<<file_type(filename)<<" ‘"<<filename<<"’?";
        delete_answer = get_delete_answer();    //获取用户输入
    }

    if(!ask || delete_answer == 'y')
    {

        QString permission = file_permission(filename);
        //permission 格式为 ‘drwxrwxrwx'
        if(user=="sudo")    //owner
        {
            if(permission[2] == 'w')
                delete_file(filename);
            else
                qDebug()<<"Permission denied";
        }
        else if(get_uesr_permissions(user))   //获取权限，group
        {
            if(permission[5] == 'w')
                delete_file(filename);
            else
                qDebug()<<"Permission denied";
        }
        else    //others
        {
            if(permission[8] == 'w')
                delete_file(filename);
            else
                qDebug()<<"Permission denied";
        }

    }
}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [-ri] name
 */
void rm(QStringList strList, QString user)
{
    int length = strList.count();
    if(length == 1)
    {
        qDebug()<<"rm: missing operand";
        qDebug()<<"Try 'rm --help' for more information.";
    }
    else if(strList[1] == "--help")
    {
        qDebug()<<"Usage: rm [OPTION]... FILE...";
        qDebug()<<"Remove (unlink) the FILE(s)."<<Qt::endl;

        qDebug()<<"  -f, --force           ignore nonexistent files and arguments, never prompt";
        qDebug()<<"  -i                    prompt before every removal";
        qDebug()<<"  -I                    prompt once before removing more than three files, or";
        qDebug()<<"                          when removing recursively; less intrusive than -i,";
        qDebug()<<"                          while still giving protection against most mistakes";
        qDebug()<<"      --interactive[=WHEN]  prompt according to WHEN: never, once (-I), or";
        qDebug()<<"                          always (-i); without WHEN, prompt always";
        qDebug()<<"      --one-file-system  when removing a hierarchy recursively, skip any";
        qDebug()<<"                          directory that is on a file system different from";
        qDebug()<<"                          that of the corresponding command line argument";
        qDebug()<<"      --no-preserve-root  do not treat '/' specially";
        qDebug()<<"      --preserve-root   do not remove '/' (default)";
        qDebug()<<"  -r, -R, --recursive   remove directories and their contents recursively";
        qDebug()<<"  -d, --dir             remove empty directories";
        qDebug()<<"  -v, --verbose         explain what is being done";
        qDebug()<<"      --help     display this help and exit";
        qDebug()<<"      --version  output version information and exit"<<Qt::endl;

        qDebug()<<"By default, rm does not remove directories.  Use the --recursive (-r or -R)";
        qDebug()<<"option to remove each listed directory, too, along with all of its contents."<<Qt::endl;

        qDebug()<<"To remove a file whose name starts with a '-', for example '-foo',";
        qDebug()<<"use one of these commands:";
        qDebug()<<"  rm -- -foo"<<Qt::endl;

        qDebug()<<"  rm ./-foo"<<Qt::endl;

        qDebug()<<"Note that if you use rm to remove a file, it might be possible to recover";
        qDebug()<<"some of its contents, given sufficient expertise and/or time.  For greater";
        qDebug()<<"assurance that the contents are truly unrecoverable, consider using shred."<<Qt::endl;

        qDebug()<<"GNU coreutils online help: <http://www.gnu.org/software/coreutils/>";
        qDebug()<<"For complete documentation, run: info coreutils 'rm invocation'";
        qDebug()<<"[root@izj6cgr1bsxia8v3az6ft7z 1]# rm";
        qDebug()<<"rm: missing operand";
        qDebug()<<"Try 'rm --help' for more information.";
    }
    else if(strList[1].length() > 1 && strList[1][0] == '-' && (strList[1][1] != 'r' || strList[1][1] != 'i'))
    {
        if(strList[1].length() == 2 && strList[1][1] == '-')
        {
            qDebug()<<"rm: missing operand";
            qDebug()<<"Try 'rm --help' for more information.";
        }
        else if(strList[1].length() == 2)
        {
            qDebug().nospace()<<"rm: invalid option -- '"<<strList[1][1]<<"'";
            qDebug()<<"Try 'rm --help' for more information.";
        }
        else
        {
            qDebug().nospace()<<"rm: unrecognized option -- '"<<qPrintable(strList[1])<<"'";
            qDebug()<<"Try 'rm --help' for more information.";
        }
    }
    else
    {
        int file_place = 1;
        if(strList[1][0] == '-')
        {
            if(length <= 2)
            {
                qDebug()<<"rm: missing operand";
                qDebug()<<"Try 'rm --help' for more information.";
                return ;
            }
            file_place += 1;
        }
        QString file_name = strList[file_place];

        if(file_if_exist(file_name))
        {
            qDebug().nospace()<<"rm: cannot create directory ‘"<<qPrintable(file_name)<<"’: File exists";
            return ;
        }

        int status[2]={0,0};    //命令行的附加功能格式为“组合”+“存在”形式  以附加功能数组进行对应功能存储
        for(int i=1;i<strList[1].length();i++)
        {
            if(strList[1][i] == 'r')
                status[0] = 1;
            else if(strList[1][i] == 'i')
                status[1] = 1;
            else    //命令行会对第一个遇到的非附加功能符号进行报错
            {
                qDebug().nospace()<<"rm: invalid option -- '"<<strList[1][i]<<"'";
                qDebug()<<"Try 'rm --help' for more information.";
                return ;
            }
        }

        if(file_type(file_name) != "文件")    // 文件目录需以'-r'命令删除
        {
            qDebug().nospace()<<"rm: remove regular file ‘"<<file_name<<"’?";
            QString delete_answer = get_delete_answer();    //获取用户输入
            if(delete_answer == 'y')
            {
                QString permission = file_permission(file_name);
                //permission 格式为 ‘drwxrwxrwx'
                if(user=="sudo")    //owner
                {
                    if(permission[2] == 'w')
                        delete_file(file_name);
                    else
                        qDebug()<<"Permission denied";
                }
                else if(get_uesr_permissions(user))   //获取权限，group
                {
                    if(permission[5] == 'w')
                        delete_file(file_name);
                    else
                        qDebug()<<"Permission denied";
                }
                else    //others
                {
                    if(permission[8] == 'w')
                        delete_file(file_name);
                    else
                        qDebug()<<"Permission denied";
            }

            }
        }
        else
        {
            if(status[0] == 0)
            {
                qDebug().nospace()<<"rm: cannot remove ‘"<<file_name<<"’: Is a directory";
            }
            else
            {
                qDebug().nospace()<<"rm: remove regular file ‘"<<file_name<<"’?";
                QString delete_answer = get_delete_answer();    //获取用户输入
                if(delete_answer == 'y')
                {
                    rm_del(file_name,status[1],user);
                }
            }
        }
    }
}

/*
 * NAME
 *      Rename or move a file or directory to another location
 * SYNOPSIS
 *      mv [-bifnu] source dest
 *      mv [-bifnu] source directory
 */
void mv(QStringList strList, QString user)
{
    int length = strList.count();
    if(length == 1)
    {
        qDebug()<<"mv: missing operand";
        qDebug()<<"Try 'mv --help' for more information.";
    }
    else if(strList[1] == "--help")
    {
        qDebug()<<"Usage: mv [OPTION]... [-T] SOURCE DEST";
        qDebug()<<"  or:  mv [OPTION]... SOURCE... DIRECTORY";
        qDebug()<<"  or:  mv [OPTION]... -t DIRECTORY SOURCE...";
        qDebug()<<"Rename SOURCE to DEST, or move SOURCE(s) to DIRECTORY."<<Qt::endl;

        qDebug()<<"Mandatory arguments to long options are mandatory for short options too.";
        qDebug()<<"      --backup[=CONTROL]       make a backup of each existing destination file";
        qDebug()<<"  -b                           like --backup but does not accept an argument";
        qDebug()<<"  -f, --force                  do not prompt before overwriting";
        qDebug()<<"  -i, --interactive            prompt before overwrite";
        qDebug()<<"  -n, --no-clobber             do not overwrite an existing file";
        qDebug()<<"If you specify more than one of -i, -f, -n, only the final one takes effect.";
        qDebug()<<"      --strip-trailing-slashes  remove any trailing slashes from each SOURCE";
        qDebug()<<"                                 argument";
        qDebug()<<"  -S, --suffix=SUFFIX          override the usual backup suffix";
        qDebug()<<"  -t, --target-directory=DIRECTORY  move all SOURCE arguments into DIRECTORY";
        qDebug()<<"  -T, --no-target-directory    treat DEST as a normal file";
        qDebug()<<"  -u, --update                 move only when the SOURCE file is newer";
        qDebug()<<"                                 than the destination file or when the";
        qDebug()<<"                                 destination file is missing";
        qDebug()<<"  -v, --verbose                explain what is being done";
        qDebug()<<"  -Z, --context                set SELinux security context of destination";
        qDebug()<<"                                 file to default type";
        qDebug()<<"      --help     display this help and exit";
        qDebug()<<"      --version  output version information and exit"<<Qt::endl;

        qDebug()<<"The backup suffix is '~', unless set with --suffix or SIMPLE_BACKUP_SUFFIX.";
        qDebug()<<"The version control method may be selected via the --backup option or through";
        qDebug()<<"the VERSION_CONTROL environment variable.  Here are the values"<<Qt::endl;

        qDebug()<<"  none, off       never make backups (even if --backup is given)";
        qDebug()<<"  numbered, t     make numbered backups";
        qDebug()<<"  existing, nil   numbered if numbered backups exist, simple otherwise";
        qDebug()<<"  simple, never   always make simple backups"<<Qt::endl;

        qDebug()<<"GNU coreutils online help: <http://www.gnu.org/software/coreutils/>";
        qDebug()<<"For complete documentation, run: info coreutils 'mv invocation'";
    }
    else if(strList[1].length() > 1 && strList[1][0] == '-' && (strList[1][1] != 'b' || strList[1][1] != 'i' || strList[1][1] != 'f' || strList[1][1] != 'n' || strList[1][1] != 'u'))
    {
        if(strList[1].length() == 2 && strList[1][1] == '-')
        {
            qDebug()<<"mv: missing operand";
            qDebug()<<"Try 'mv --help' for more information.";
        }
        else if(strList[1].length() == 2)
        {
            qDebug().nospace()<<"mv: invalid option -- '"<<strList[1][1]<<"'";
            qDebug()<<"Try 'mv --help' for more information.";
        }
        else
        {
            qDebug().nospace()<<"mv: unrecognized option -- '"<<qPrintable(strList[1])<<"'";
            qDebug()<<"Try 'mv --help' for more information.";
        }
    }
    else
    {
        int file_place = 1;
        if(strList[1][0] == '-')
        {
            if(length <= 2)
            {
                qDebug()<<"rm: missing operand";
                qDebug()<<"Try 'rm --help' for more information.";
                return ;
            }
            file_place += 1;
        }
        if(length <= file_place+1)
        {
            qDebug()<<"mv: missing operand";
            qDebug()<<"Try 'mv --help' for more information.";
            return ;
        }
        QString source_file = strList[file_place];
        QString dest_file = strList[file_place + 1];

        if(file_if_exist(source_file))    //判断是否存在
        {
            if(file_place == 1)
            {
                qDebug().nospace()<<"mv: cannot create directory ‘"<<qPrintable(file_name)<<"’: File exists";
            }
            return ;
        }

        int status[5]={0,0,0,0,0};    //命令行的附加功能格式为“组合”+“存在”形式  以附加功能数组进行对应功能存储
        for(int i=1;i<strList[1].length();i++)
        {
            if(strList[1][i] == 'b')
                status[0] = 1;
            else if(strList[1][i] == 'i')
                status[1] = 1;
            else if(strList[1][i] == 'f')
                status[2] = 1;
            else if(strList[1][i] == 'n')
                status[3] = 1;
            else if(strList[1][i] == 'u')
                status[4] = 1;
            else    //命令行会对第一个遇到的非附加功能符号进行报错
            {
                qDebug().nospace()<<"rm: invalid option -- '"<<strList[1][i]<<"'";
                qDebug()<<"Try 'rm --help' for more information.";
                return ;
            }
        }

        QString type1 = get_file_type(source_file);

        if(file_if_exist(dest_file))
        {
            QString permission1 = file_permission(source_file);
            QString permission2 = file_permission(dest_file);

            if(status[4] == 1)  //当源文件比目标文件新或者目标文件不存在时，才执行移动操作
            {
                if(get_filetime(source_file) < get_filetime(dest_file))
                    return ;
            }

            //permission 格式为 ‘drwxrwxrwx'
            if(user=="sudo")    //owner
            {
                if(permission1[2] != 'w' || permission2[2] != 'w')
                {
                    qDebug()<<"Permission denied";
                    return ;
                }
            }
            else if(get_uesr_permissions(user))   //获取权限，group
            {
                if(permission1[5] != 'w' || permission2[5] != 'w')
                {
                    qDebug()<<"Permission denied";
                    return ;
                }
            }
            else    //others
            {
                if(permission1[8] != 'w' || permission2[8] != 'w')
                {
                    qDebug()<<"Permission denied";
                    return ;
                }
            }

            QString type2 = get_file_type(dest_file);

            if(type1 == "文件" && type2 == "文件")  //对文件重命名
            {
                if(status[3] == 1)return ;  //-n不执行覆盖操作

                Qstring delete_answer = 'y';
                if(status[2] != 1)  //-f无需询问
                {
                    qDebug().nospace()<<"mv: overwrite ‘"<<qPrintable(dest_file)<<"’?";
                    delete_answer = get_delete_answer();
                }
                if(delete_answer == 'y')
                {
                    if(status[0] == 1)  //-b对原文件备份
                        change_name(dest_file,dest_file+'~');
                    else
                        delete_file(dest_file);
                    change_name(source_file,dest_file);
                }
            }
            else if(type1 == "文件" && type2 == "目录") //将文件移动到目录下
            {
                if(directory_have_file(source_file,dest_file))  //判断目录下是否有同名文件
                {
                    if(status[3] == 1)return ;  //-n不执行覆盖操作

                    Qstring delete_answer = 'y';
                    if(status[2] != 1)  //-f无需询问
                    {
                        qDebug().nospace()<<"mv: overwrite ‘"<<qPrintable(dest_file+"/"+source_file)<<"’?";
                        delete_answer = get_delete_answer();
                    }
                    if(delete_answer == 'y')
                    {
                        if(status[0] == 1)  //-b对原文件备份
                            change_name(dest_file,dest_file+'~');
                        else
                            delete_file(dest_file);
                        change_name(source_file,dest_file);
                    }
                }
                else
                    move_file_to Directory(source_file,dest_file);
            }
            else if(type1 == "目录" && type2 == "目录")  //将目录移动到目录type2下
            {
                if(directory_have_file(source_file,dest_file))  //判断目录下是否有同名文件
                {
                    if(status[3] == 1)return ;  //-n不执行覆盖操作

                    Qstring delete_answer = 'y';
                    if(status[2] != 1)  //-f无需询问
                    {
                        qDebug().nospace()<<"mv: overwrite ‘"<<qPrintable(dest_file+"/"+source_file)<<"’?";
                        delete_answer = get_delete_answer();
                    }
                    if(delete_answer == 'y')
                    {
                        if(status[0] == 1)  //-b对原文件备份
                            change_name(dest_file,dest_file+'~');
                        else
                            delete_file(dest_file);
                        change_name(source_file,dest_file);
                    }
                }
                else
                    move_file_to Directory(source_file,dest_file);
            }
            else if(type1 == "目录" && type1 == "文件")    //error
            {
                if(status[3] == 1)return ;  //-n不执行覆盖操作

                Qstring delete_answer = 'y';
                if(status[2] != 1)  //-f无需询问
                {
                    qDebug().nospace()<<"mv: overwrite ‘"<<qPrintable(dest_file)<<"’?";
                    delete_answer = get_delete_answer();
                }
                if(delete_answer == 'y')
                {
                    qDebug().nospace()<<"mv: cannot overwrite non-directory ‘"<<qPrintable(dest_file)<<"’ with directory ‘"<<qPrintable(source_file)<<"’";
                }
            }
        }
        else
        {
            QString permission = file_permission(file_name);    //删除为获取所删除的目录的权限
            //permission 格式为 ‘drwxrwxrwx'
            if(user=="sudo")    //owner
            {
                if(permission[2] == 'w')
                    change_file_name(source_file,dest_file);
                else
                    qDebug()<<"Permission denied";
            }
            else if(get_uesr_permissions(user))   //获取权限，group
            {
                if(permission[5] == 'w')
                    change_file_name(source_file,dest_file);
                else
                    qDebug()<<"Permission denied";
            }
            else    //others
            {
                if(permission[8] == 'w')
                    change_file_name(source_file,dest_file);
                else
                    qDebug()<<"Permission denied";
            }

        }
    }
}

/*
 * NAME
 *      Used to copy files or directories
 * SYNOPSIS
 *      cp [-fpr] source... directory
 */
void cp(QStringList strList, QString user)
{
    int length = strList.count();
    if(length == 1)
    {
        qDebug()<<"cp: missing operand";
        qDebug()<<"Try 'cp --help' for more information.";
    }
    else if(strList[1] == "--help")
    {
        qDebug()<<"Usage: cp [OPTION]... [-T] SOURCE DEST";
        qDebug()<<"  or:  cp [OPTION]... SOURCE... DIRECTORY";
        qDebug()<<"  or:  cp [OPTION]... -t DIRECTORY SOURCE...";
        qDebug()<<"Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY."<<Qt::endl;

        qDebug()<<"Mandatory arguments to long options are mandatory for short options too.";
        qDebug()<<"  -a, --archive                same as -dR --preserve=all";
        qDebug()<<"      --attributes-only        don't copy the file data, just the attributes";
        qDebug()<<"      --backup[=CONTROL]       make a backup of each existing destination file";
        qDebug()<<"  -b                           like --backup but does not accept an argument";
        qDebug()<<"      --copy-contents          copy contents of special files when recursive";
        qDebug()<<"  -d                           same as --no-dereference --preserve=links";
        qDebug()<<"  -f, --force                  if an existing destination file cannot be";
        qDebug()<<"                                 opened, remove it and try again (this option";
        qDebug()<<"                                 is ignored when the -n option is also used)";
        qDebug()<<"  -i, --interactive            prompt before overwrite (overrides a previous -n";
        qDebug()<<"                                  option)";
        qDebug()<<"  -H                           follow command-line symbolic links in SOURCE";
        qDebug()<<"  -l, --link                   hard link files instead of copying";
        qDebug()<<"  -L, --dereference            always follow symbolic links in SOURCE";
        qDebug()<<"  -n, --no-clobber             do not overwrite an existing file (overrides";
        qDebug()<<"                                 a previous -i option)";
        qDebug()<<"  -P, --no-dereference         never follow symbolic links in SOURCE";
        qDebug()<<"  -p                           same as --preserve=mode,ownership,timestamps";
        qDebug()<<"      --preserve[=ATTR_LIST]   preserve the specified attributes (default:";
        qDebug()<<"                                 mode,ownership,timestamps), if possible";
        qDebug()<<"                                 additional attributes: context, links, xattr,";
        qDebug()<<"                                 all";
        qDebug()<<"  -c                           deprecated, same as --preserve=context";
        qDebug()<<"      --no-preserve=ATTR_LIST  don't preserve the specified attributes";
        qDebug()<<"      --parents                use full source file name under DIRECTORY";
        qDebug()<<"  -R, -r, --recursive          copy directories recursively";
        qDebug()<<"      --reflink[=WHEN]         control clone/CoW copies. See below";
        qDebug()<<"      --remove-destination     remove each existing destination file before";
        qDebug()<<"                                 attempting to open it (contrast with --force)";
        qDebug()<<"      --sparse=WHEN            control creation of sparse files. See below";
        qDebug()<<"      --strip-trailing-slashes  remove any trailing slashes from each SOURCE";
        qDebug()<<"                                 argument";
        qDebug()<<"  -s, --symbolic-link          make symbolic links instead of copying";
        qDebug()<<"  -S, --suffix=SUFFIX          override the usual backup suffix";
        qDebug()<<"  -t, --target-directory=DIRECTORY  copy all SOURCE arguments into DIRECTORY";
        qDebug()<<"  -T, --no-target-directory    treat DEST as a normal file";
        qDebug()<<"  -u, --update                 copy only when the SOURCE file is newer";
        qDebug()<<"                                 than the destination file or when the";
        qDebug()<<"                                 destination file is missing";
        qDebug()<<"  -v, --verbose                explain what is being done";
        qDebug()<<"  -x, --one-file-system        stay on this file system";
        qDebug()<<"  -Z                           set SELinux security context of destination";
        qDebug()<<"                                 file to default type";
        qDebug()<<"      --context[=CTX]          like -Z, or if CTX is specified then set the";
        qDebug()<<"                                 SELinux or SMACK security context to CTX";
        qDebug()<<"      --help     display this help and exit";
        qDebug()<<"      --version  output version information and exit"<<Qt::endl;

        qDebug()<<"By default, sparse SOURCE files are detected by a crude heuristic and the";
        qDebug()<<"corresponding DEST file is made sparse as well.  That is the behavior";
        qDebug()<<"selected by --sparse=auto.  Specify --sparse=always to create a sparse DEST";
        qDebug()<<"file whenever the SOURCE file contains a long enough sequence of zero bytes.";
        qDebug()<<"Use --sparse=never to inhibit creation of sparse files."<<Qt::endl;

        qDebug()<<"When --reflink[=always] is specified, perform a lightweight copy, where the";
        qDebug()<<"data blocks are copied only when modified.  If this is not possible the copy";
        qDebug()<<"fails, or if --reflink=auto is specified, fall back to a standard copy."<<Qt::endl;

        qDebug()<<"The backup suffix is '~', unless set with --suffix or SIMPLE_BACKUP_SUFFIX.";
        qDebug()<<"The version control method may be selected via the --backup option or through";
        qDebug()<<"the VERSION_CONTROL environment variable.  Here are the values:"<<Qt::endl;

        qDebug()<<"  none, off       never make backups (even if --backup is given)";
        qDebug()<<"  numbered, t     make numbered backups";
        qDebug()<<"  existing, nil   numbered if numbered backups exist, simple otherwise";
        qDebug()<<"  simple, never   always make simple backups"<<Qt::endl;

        qDebug()<<"As a special case, cp makes a backup of SOURCE when the force and backup";
        qDebug()<<"options are given and SOURCE and DEST are the same name for an existing,";
        qDebug()<<"regular file."<<Qt::endl;

        qDebug()<<"GNU coreutils online help: <http://www.gnu.org/software/coreutils/>";
        qDebug()<<"For complete documentation, run: info coreutils 'cp invocation'";
    }
    else if(strList[1].length() > 1 && strList[1][0] == '-' && (strList[1][1] != 'f' || strList[1][1] != 'p' || strList[1][1] != 'r'))
    {
        if(strList[1].length() == 2 && strList[1][1] == '-')
        {
            qDebug()<<"cp: missing operand";
            qDebug()<<"Try 'cp --help' for more information.";
        }
        else if(strList[1].length() == 2)
        {
            qDebug().nospace()<<"cp: invalid option -- '"<<strList[1][1]<<"'";
            qDebug()<<"Try 'cp --help' for more information.";
        }
        else
        {
            qDebug().nospace()<<"cp: unrecognized option -- '"<<qPrintable(strList[1])<<"'";
            qDebug()<<"Try 'cp --help' for more information.";
        }
    }
    else
    {
        int file_place = 1;
        if(strList[1].mid(0,2) == "-p")file_place += 1;
        if(length <= file_place+1)
        {
            qDebug()<<"cp: missing operand";
            qDebug()<<"Try 'cp --help' for more information.";
            return ;
        }
        QString source_file = strList[file_place];
        QString dest_file = strList[file_place + 1];

        if(file_if_exist(source_file))    //判断是否存在
        {
            if(file_place == 1)
            {
                qDebug().nospace()<<"mv: cannot create directory ‘"<<qPrintable(file_name)<<"’: File exists";
            }
            return ;
        }

        int status[3]={0,0,0};    //命令行的附加功能格式为“组合”+“存在”形式  以附加功能数组进行对应功能存储
        for(int i=1;i<strList[1].length();i++)
        {
            if(strList[1][i] == 'f')
                status[0] = 1;
            else if(strList[1][i] == 'p')
                status[1] = 1;
            else if(strList[1][i] == 'r')
                status[2] = 1;
            else    //命令行会对第一个遇到的非附加功能符号进行报错
            {
                qDebug().nospace()<<"rm: invalid option -- '"<<strList[1][i]<<"'";
                qDebug()<<"Try 'rm --help' for more information.";
                return ;
            }
        }

        QString type1 = get_file_type(source_file);

        if(file_if_exist(dest_file))
        {
            QString permission1 = file_permission(source_file);
            QString permission2 = file_permission(dest_file);

            if(status[4] == 1)  //当源文件比目标文件新或者目标文件不存在时，才执行移动操作
            {
                if(get_filetime(source_file) < get_filetime(dest_file))
                    return ;
            }

            //permission 格式为 ‘drwxrwxrwx'
            if(user=="sudo")    //owner
            {
                if(permission1[2] != 'w' || permission2[2] != 'w')
                {
                    qDebug()<<"Permission denied";
                    return ;
                }
            }
            else if(get_uesr_permissions(user))   //获取权限，group
            {
                if(permission1[5] != 'w' || permission2[5] != 'w')
                {
                    qDebug()<<"Permission denied";
                    return ;
                }
            }
            else    //others
            {
                if(permission1[8] != 'w' || permission2[8] != 'w')
                {
                    qDebug()<<"Permission denied";
                    return ;
                }
            }

            QString type2 = get_file_type(dest_file);

            if(type1 == "文件" && type2 == "文件")  //对文件重命名
            {
                if(status[3] == 1)return ;  //-n不执行覆盖操作

                Qstring delete_answer = 'y';
                if(status[2] != 1)  //-f无需询问
                {
                    qDebug().nospace()<<"mv: overwrite ‘"<<qPrintable(dest_file)<<"’?";
                    delete_answer = get_delete_answer();
                }
                if(delete_answer == 'y')
                {
                    if(status[0] == 1)  //-b对原文件备份
                        change_name(dest_file,dest_file+'~');
                    else
                        delete_file(dest_file);
                    change_name(source_file,dest_file);
                }
            }
            else if(type1 == "文件" && type2 == "目录") //将文件移动到目录下
            {
                if(directory_have_file(source_file,dest_file))  //判断目录下是否有同名文件
                {
                    if(status[3] == 1)return ;  //-n不执行覆盖操作

                    Qstring delete_answer = 'y';
                    if(status[2] != 1)  //-f无需询问
                    {
                        qDebug().nospace()<<"mv: overwrite ‘"<<qPrintable(dest_file+"/"+source_file)<<"’?";
                        delete_answer = get_delete_answer();
                    }
                    if(delete_answer == 'y')
                    {
                        if(status[0] == 1)  //-b对原文件备份
                            change_name(dest_file,dest_file+'~');
                        else
                            delete_file(dest_file);
                        change_name(source_file,dest_file);
                    }
                }
                else
                    move_file_to Directory(source_file,dest_file);
            }
            else if(type1 == "目录" && type2 == "目录")  //将目录移动到目录type2下
            {
                if(directory_have_file(source_file,dest_file))  //判断目录下是否有同名文件
                {
                    if(status[3] == 1)return ;  //-n不执行覆盖操作

                    Qstring delete_answer = 'y';
                    if(status[2] != 1)  //-f无需询问
                    {
                        qDebug().nospace()<<"mv: overwrite ‘"<<qPrintable(dest_file+"/"+source_file)<<"’?";
                        delete_answer = get_delete_answer();
                    }
                    if(delete_answer == 'y')
                    {
                        if(status[0] == 1)  //-b对原文件备份
                            change_name(dest_file,dest_file+'~');
                        else
                            delete_file(dest_file);
                        change_name(source_file,dest_file);
                    }
                }
                else
                    move_file_to Directory(source_file,dest_file);
            }
            else if(type1 == "目录" && type1 == "文件")    //error
            {
                if(status[3] == 1)return ;  //-n不执行覆盖操作

                Qstring delete_answer = 'y';
                if(status[2] != 1)  //-f无需询问
                {
                    qDebug().nospace()<<"mv: overwrite ‘"<<qPrintable(dest_file)<<"’?";
                    delete_answer = get_delete_answer();
                }
                if(delete_answer == 'y')
                {
                    qDebug().nospace()<<"mv: cannot overwrite non-directory ‘"<<qPrintable(dest_file)<<"’ with directory ‘"<<qPrintable(source_file)<<"’";
                }
            }
        }
        else
        {
            QString permission1 = file_permission(source_file);

            //获取当前工作的路径，以判断当前所拥有的权限
            QStringList work_path_list = dest_file.split("/");
            QString work_path;
            if(work_path_list.count() == 1)
            {
                work_path = "当前路径";
            }
            else
            {
                work_path_list.removeLast();
                work_path = work_path_list.join("/");
            }

            QString permission2 = file_permission(work_path);

            if(status[4] == 1)  //当源文件比目标文件新或者目标文件不存在时，才执行移动操作
            {
                if(get_filetime(source_file) < get_filetime(dest_file))
                    return ;
            }

            //permission 格式为 ‘drwxrwxrwx'
            if(user=="sudo")    //owner
            {
                if(permission1[2] != 'w' || permission2[2] != 'w')
                {
                    qDebug()<<"Permission denied";
                    return ;
                }
            }
            else if(get_uesr_permissions(user))   //获取权限，group
            {
                if(permission1[5] != 'w' || permission2[5] != 'w')
                {
                    qDebug()<<"Permission denied";
                    return ;
                }
            }
            else    //others
            {
                if(permission1[8] != 'w' || permission2[8] != 'w')
                {
                    qDebug()<<"Permission denied";
                    return ;
                }
            }

            change_file_name(source_file,dest_file);
        }
    }
}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void cat(QStringList strList, QString user)
{

}

/*
void more(QStringList strList,QString user)
{

}


void less(QStringList strList,QString user)
{

}

void head(QStringList strList,QString user)
{

}

void tail(QStringList strList,QString user)
{

}

void which(QStringList strList,QString user)
{

}

void locate(QStringList strList,QString user)
{

}
*/

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void whereis(QStringList strList, QString user)
{

}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void find(QStringList strList, QString user)
{

}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void chmod(QStringList strList, QString user)
{

}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void chown(QStringList strList, QString user)
{

}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void tar(QStringList strList, QString user)
{

}

/*
void df(QStringList strList,QString user)
{

}

void du(QStringList strList,QString user)
{

}

void ln(QStringList strList,QString user)
{

}
*/

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void login(QStringList strList, QString user)
{

}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void logout(QStringList strList, QString user)
{

}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void vi(QStringList strList, QString user)
{

}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void touch(QStringList strList, QString user)
{

}

/*
void grep(QStringList strList,QString user)
{

}

void kill(QStringList strList,QString user)
{

}
*/

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void top(QStringList strList, QString user)
{

}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void read(QStringList strList, QString user)
{

}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      rm [options] name
 */
void write(QStringList strList, QString user)
{

}

/*
 * NAME
 *     help - Display information about builtin commands.
 * SYNOPSIS
 *     help [-dms] [pattern]
 */
void help(QStringList strList)
{
    //qDebug()<<strList;
    //qDebug()<<strList.count();
    int length = strList.count();
    bool flag1 = true;
    bool flag2 = true;
    int next_place = 1;
    if (length == 1 || (length == 2 && strList[1][0] == '-'))
    {

        if (length == 1 || strList[1].length() > 1)   //help || help -d || help -m || help -s
        {
            if (length == 1 || strList[1][1] == 'd' || strList[1][1] == 'm' || strList[1][1] == 's')
            {
                qDebug() << "GNU bash, version 4.2.46(2)-release (x86_64-redhat-linux-gnu)";
                qDebug() << "These shell commands are defined internally.  Type `help' to see this list.";
                qDebug() << "Type `help name' to find out more about the function `name'.";
                qDebug() << "Use `info bash' to find out more about the shell in general.";
                qDebug() << "Use `man -k' or `info' to find out more about commands not in this list." << Qt::endl;

                qDebug() << "A star (*) next to a name means that the command is disabled.";

                qDebug() << "job_spec [&]                                                                                 history [-c] [-d offset] [n] or history -anrw [filename] or history -ps arg [arg...]";
                qDebug() << " (( expression ))                                                                             if COMMANDS; then COMMANDS; [ elif COMMANDS; then COMMANDS; ]... [ else COMMANDS; ] fi";
                qDebug() << ". filename [arguments]                                                                       jobs [-lnprs] [jobspec ...] or jobs -x command [args]";
                qDebug() << ":                                                                                            kill [-s sigspec | -n signum | -sigspec] pid | jobspec ... or kill -l [sigspec]";
                qDebug() << "[ arg... ]                                                                                   let arg [arg ...]";
                qDebug() << "[[ expression ]]                                                                             local [option] name[=value] ...";
                qDebug() << "alias [-p] [name[=value] ... ]                                                               logout [n]";
                qDebug() << "bg [job_spec ...]                                                                            mapfile [-n count] [-O origin] [-s count] [-t] [-u fd] [-C callback] [-c quantum] [array]>";
                qDebug() << "bind [-lpvsPVS] [-m keymap] [-f filename] [-q name] [-u name] [-r keyseq] [-x keyseq:shell>  popd [-n] [+N | -N]";
                qDebug() << "break [n]                                                                                    printf [-v var] format [arguments]";
                qDebug() << "builtin [shell-builtin [arg ...]]                                                            pushd [-n] [+N | -N | dir]";
                qDebug() << "caller [expr]                                                                                pwd [-LP]";
                qDebug() << "case WORD in [PATTERN [| PATTERN]...) COMMANDS ;;]... esac                                   read [-ers] [-a array] [-d delim] [-i text] [-n nchars] [-N nchars] [-p prompt] [-t timeo>";
                qDebug() << "cd [-L|[-P [-e]]] [dir]                                                                      readarray [-n count] [-O origin] [-s count] [-t] [-u fd] [-C callback] [-c quantum] [arra>";
                qDebug() << "command [-pVv] command [arg ...]                                                             readonly [-aAf] [name[=value] ...] or readonly -p";
                qDebug() << "compgen [-abcdefgjksuv] [-o option]  [-A action] [-G globpat] [-W wordlist]  [-F function]>  return [n]";
                qDebug() << "complete [-abcdefgjksuv] [-pr] [-DE] [-o option] [-A action] [-G globpat] [-W wordlist]  [>  select NAME [in WORDS ... ;] do COMMANDS; done";
                qDebug() << "compopt [-o|+o option] [-DE] [name ...]                                                      set [-abefhkmnptuvxBCHP] [-o option-name] [--] [arg ...]";
                qDebug() << "continue [n]                                                                                 shift [n]";
                qDebug() << "coproc [NAME] command [redirections]                                                         shopt [-pqsu] [-o] [optname ...]";
                qDebug() << "declare [-aAfFgilrtux] [-p] [name[=value] ...]                                               source filename [arguments]";
                qDebug() << "dirs [-clpv] [+N] [-N]                                                                       suspend [-f]";
                qDebug() << "disown [-h] [-ar] [jobspec ...]                                                              test [expr]";
                qDebug() << "echo [-neE] [arg ...]                                                                        time [-p] pipeline";
                qDebug() << "enable [-a] [-dnps] [-f filename] [name ...]                                                 times";
                qDebug() << "eval [arg ...]                                                                               trap [-lp] [[arg] signal_spec ...]";
                qDebug() << "exec [-cl] [-a name] [command [arguments ...]] [redirection ...]                             true";
                qDebug() << "exit [n]                                                                                     type [-afptP] name [name ...]";
                qDebug() << "export [-fn] [name[=value] ...] or export -p                                                 typeset [-aAfFgilrtux] [-p] name[=value] ...";
                qDebug() << "false                                                                                        ulimit [-SHacdefilmnpqrstuvx] [limit]";
                qDebug() << "fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]                             umask [-p] [-S] [mode]";
                qDebug() << "fg [job_spec]                                                                                unalias [-a] name [name ...]";
                qDebug() << "for NAME [in WORDS ... ] ; do COMMANDS; done                                                 unset [-f] [-v] [name ...]";
                qDebug() << "for (( exp1; exp2; exp3 )); do COMMANDS; done                                                until COMMANDS; do COMMANDS; done";
                qDebug() << "function name { COMMANDS ; } or name () { COMMANDS ; }                                       variables - Names and meanings of some shell variables";
                qDebug() << "getopts optstring name [arg]                                                                 wait [id]";
                qDebug() << "hash [-lr] [-p pathname] [-dt] [name ...]                                                    while COMMANDS; do COMMANDS; done";
                qDebug() << "help [-dms] [pattern ...] ";
            }
            else    //e.g. help -a
                flag1 = false;
        }
        else    //e.g. help -
            flag2 = false;
    }
    else
    {
        if (strList[1] == "-d" || strList[1] == "-m" || strList[1] == "-s")
            next_place += 1;

        if (strList[next_place] == "cd")
        {
            if (next_place == 1)
            {
                qDebug() << "cd: cd [-L|[-P [-e]]] [dir]";
                qDebug() << " Change the shell working directory." << Qt::endl;

                qDebug() << " Change the current directory to DIR.  The default DIR is the value of the";
                qDebug() << " HOME shell variable." << Qt::endl;

                qDebug() << " The variable CDPATH defines the search path for the directory containing";
                qDebug() << " DIR.  Alternative directory names in CDPATH are separated by a colon (:).";
                qDebug() << " A null directory name is the same as the current directory.  If DIR begins";                    qDebug() << " with a slash (/), then CDPATH is not used." << Qt::endl;

                qDebug() << " If the directory is not found, and the shell option `cdable_vars' is set,";
                qDebug() << " the word is assumed to be  a variable name.  If that variable has a value,";
                qDebug() << " its value is used for DIR." << Qt::endl;

                qDebug() << " Options:";
                qDebug() << "     -L	force symbolic links to be followed";
                qDebug() << "     -P	use the physical directory structure without following symbolic";
                qDebug() << "     links";
                qDebug() << "     -e	if the -P option is supplied, and the current working directory";
                qDebug() << "     cannot be determined successfully, exit with a non-zero status" << Qt::endl;

                qDebug() << " The default is to follow symbolic links, as if `-L' were specified." << Qt::endl;

                qDebug() << " Exit Status:";
                qDebug() << " Returns 0 if the directory is changed, and if $PWD is set successfully when";
                qDebug() << " -P is used; non-zero otherwise.";
            }
            else if (next_place == 2 && strList[1][0] == '-')
            {
                if (strList[1][1] == 'd')
                {
                    qDebug() << "cd - Change the shell working directory.";
                }
                else if (strList[1][1] == 'm')
                {
                    qDebug() << "NAME";
                    qDebug() << "    cd - Change the shell working directory." << Qt::endl;

                    qDebug() << "SYNOPSIS";
                    qDebug() << "    cd [-L|[-P [-e]]] [dir]" << Qt::endl;

                    qDebug() << "DESCRIPTION";
                    qDebug() << "    Change the shell working directory." << Qt::endl;

                    qDebug() << "    Change the current directory to DIR.  The default DIR is the value of the";
                    qDebug() << "    HOME shell variable." << Qt::endl;

                    qDebug() << "    The variable CDPATH defines the search path for the directory containing";
                    qDebug() << "    DIR.  Alternative directory names in CDPATH are separated by a colon (:).";
                    qDebug() << "    A null directory name is the same as the current directory.  If DIR begins";
                    qDebug() << "    with a slash (/), then CDPATH is not used." << Qt::endl;

                    qDebug() << "    If the directory is not found, and the shell option `cdable_vars' is set,";
                    qDebug() << "    the word is assumed to be  a variable name.  If that variable has a value,";
                    qDebug() << "    its value is used for DIR." << Qt::endl;

                    qDebug() << "    Options:";
                    qDebug() << "        -L	force symbolic links to be followed";
                    qDebug() << "        -P	use the physical directory structure without following symbolic";
                    qDebug() << "        links";
                    qDebug() << "        -e	if the -P option is supplied, and the current working directory";
                    qDebug() << "        cannot be determined successfully, exit with a non-zero status" << Qt::endl;

                    qDebug() << "    The default is to follow symbolic links, as if `-L' were specified." << Qt::endl;

                    qDebug() << "    Exit Status:";
                    qDebug() << "    Returns 0 if the directory is changed, and if $PWD is set successfully when";
                    qDebug() << "    -P is used; non-zero otherwise." << Qt::endl;

                    qDebug() << "SEE ALSO";
                    qDebug() << "    bash(1)" << Qt::endl;

                    qDebug() << "IMPLEMENTATION";
                    qDebug() << "    GNU bash, version 4.2.46(2)-release (x86_64-redhat-linux-gnu)";
                    qDebug() << "    Copyright (C) 2011 Free Software Foundation, Inc.";
                    qDebug() << "    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << Qt::endl;

                }
                else if (strList[1][1] == 's')
                {
                    qDebug() << "cd: cd [-L|[-P [-e]]] [dir]";
                }
            }
        }
        else if (strList[next_place] == "help")
        {
            if (next_place == 1)
            {
                qDebug() << "help: help [-dms] [pattern ...]";
                qDebug() << " Display information about builtin commands." << Qt::endl;

                qDebug() << " Displays brief summaries of builtin commands.  If PATTERN is";
                qDebug() << " specified, gives detailed help on all commands matching PATTERN,";
                qDebug() << " otherwise the list of help topics is printed." << Qt::endl;

                qDebug() << " Options:";
                qDebug() << "    -d	output short description for each topic";
                qDebug() << "    -m	display usage in pseudo-manpage format";
                qDebug() << "    -s	output only a short usage synopsis for each topic matching";
                qDebug() << " 	 PATTERN" << Qt::endl;

                qDebug() << " Arguments:";
                qDebug() << "    PATTERN	Pattern specifiying a help topic" << Qt::endl;

                qDebug() << " Exit Status:";
                qDebug() << " Returns success unless PATTERN is not found or an invalid option is given.";

            }
            else if (next_place == 2 && strList[1][0] == '-')
            {
                if (strList[1][1] == 'd')
                {
                    qDebug() << "help - Display information about builtin commands.";
                }
                else if (strList[1][1] == 'm')
                {
                    qDebug() << "NAME";
                    qDebug() << "    help - Display information about builtin commands." << Qt::endl;

                    qDebug() << "SYNOPSIS";
                    qDebug() << "    help [-dms] [pattern ...]" << Qt::endl;

                    qDebug() << "DESCRIPTION";
                    qDebug() << "    Display information about builtin commands." << Qt::endl;

                    qDebug() << "    Displays brief summaries of builtin commands.  If PATTERN is";
                    qDebug() << "    specified, gives detailed help on all commands matching PATTERN,";
                    qDebug() << "    otherwise the list of help topics is printed." << Qt::endl;

                    qDebug() << "    Options:";
                    qDebug() << "      -d	output short description for each topic";
                    qDebug() << "      -m	display usage in pseudo-manpage format";
                    qDebug() << "      -s	output only a short usage synopsis for each topic matching";
                    qDebug() << "        PATTERN" << Qt::endl;

                    qDebug() << "    Arguments:";
                    qDebug() << "      PATTERN	Pattern specifiying a help topic" << Qt::endl;

                    qDebug() << "    Exit Status:";
                    qDebug() << "    Returns success unless PATTERN is not found or an invalid option is given." << Qt::endl;

                    qDebug() << "SEE ALSO";
                    qDebug() << "    bash(1)" << Qt::endl;

                    qDebug() << "IMPLEMENTATION";
                    qDebug() << "    GNU bash, version 4.2.46(2)-release (x86_64-redhat-linux-gnu)";
                    qDebug() << "    Copyright (C) 2011 Free Software Foundation, Inc.";
                    qDebug() << "    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << Qt::endl;

                }
                else if (strList[1][1] == 's')
                {
                    qDebug() << "help: help [-dms] [pattern ...]";
                }
            }
        }
        else if (strList[next_place] == "pwd")
        {
            if (next_place == 1)
            {
                qDebug() << "pwd: pwd [-LP]";
                qDebug() << " Print the name of the current working directory." << Qt::endl;

                qDebug() << " Options:";
                qDebug() << "    -L	print the value of $PWD if it names the current working";
                qDebug() << "     directory";
                qDebug() << "    -P	print the physical directory, without any symbolic links" << Qt::endl;

                qDebug() << " By default, `pwd' behaves as if `-L' were specified." << Qt::endl;

                qDebug() << " Exit Status:";
                qDebug() << " Returns 0 unless an invalid option is given or the current directory";
                qDebug() << " cannot be read.";

            }
            else if (next_place == 2 && strList[1][0] == '-')
            {
                if (strList[1][1] == 'd')
                {
                    qDebug() << "pwd - Print the name of the current working directory.";
                }
                else if (strList[1][1] == 'm')
                {
                    qDebug() << "NAME";
                    qDebug() << " pwd - Print the name of the current working directory." << Qt::endl;

                    qDebug() << "SYNOPSIS";
                    qDebug() << " pwd [-LP]" << Qt::endl;

                    qDebug() << "DESCRIPTION";
                    qDebug() << " Print the name of the current working directory." << Qt::endl;

                    qDebug() << " Options:";
                    qDebug() << "   -L	print the value of $PWD if it names the current working";
                    qDebug() << "     directory";
                    qDebug() << "   -P	print the physical directory, without any symbolic links" << Qt::endl;

                    qDebug() << " By default, `pwd' behaves as if `-L' were specified." << Qt::endl;

                    qDebug() << " Exit Status:";
                    qDebug() << " Returns 0 unless an invalid option is given or the current directory";
                    qDebug() << " cannot be read." << Qt::endl;

                    qDebug() << "SEE ALSO";
                    qDebug() << " bash(1)" << Qt::endl;

                    qDebug() << "IMPLEMENTATION";
                    qDebug() << " GNU bash, version 4.2.46(2)-release (x86_64-redhat-linux-gnu)";
                    qDebug() << " Copyright (C) 2011 Free Software Foundation, Inc.";
                    qDebug() << " License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << Qt::endl;

                }
                else if (strList[1][1] == 's')
                {
                    qDebug() << "pwd: pwd [-LP]";
                }
            }
        }
        else if (strList[next_place] == "read")
        {
            if (next_place == 1)
            {
                qDebug() << "read: read [-ers] [-a array] [-d delim] [-i text] [-n nchars] [-N nchars] [-p prompt] [-t timeout] [-u fd] [name ...]";
                qDebug() << "    Read a line from the standard input and split it into fields." << Qt::endl;

                qDebug() << "    Reads a single line from the standard input, or from file descriptor FD";
                qDebug() << "    if the -u option is supplied.  The line is split into fields as with word";
                qDebug() << "    splitting, and the first word is assigned to the first NAME, the second";
                qDebug() << "    word to the second NAME, and so on, with any leftover words assigned to";
                qDebug() << "    the last NAME.  Only the characters found in $IFS are recognized as word";
                qDebug() << "    delimiters." << Qt::endl;

                qDebug() << "    If no NAMEs are supplied, the line read is stored in the REPLY variable." << Qt::endl;

                qDebug() << "    Options:";
                qDebug() << "      -a array	assign the words read to sequential indices of the array";
                qDebug() << "    		variable ARRAY, starting at zero";
                qDebug() << "      -d delim	continue until the first character of DELIM is read, rather";
                qDebug() << "    		than newline";
                qDebug() << "      -e		use Readline to obtain the line in an interactive shell";
                qDebug() << "      -i text	Use TEXT as the initial text for Readline";
                qDebug() << "      -n nchars	return after reading NCHARS characters rather than waiting";
                qDebug() << "    		for a newline, but honor a delimiter if fewer than NCHARS";
                qDebug() << "    		characters are read before the delimiter";
                qDebug() << "      -N nchars	return only after reading exactly NCHARS characters, unless";
                qDebug() << "    		EOF is encountered or read times out, ignoring any delimiter";
                qDebug() << "      -p prompt	output the string PROMPT without a trailing newline before";
                qDebug() << "    		attempting to read";
                qDebug() << "      -r		do not allow backslashes to escape any characters";
                qDebug() << "      -s		do not echo input coming from a terminal";
                qDebug() << "      -t timeout	time out and return failure if a complete line of input is";
                qDebug() << "    		not read withint TIMEOUT seconds.  The value of the TMOUT";
                qDebug() << "    		variable is the default timeout.  TIMEOUT may be a";
                qDebug() << "    		fractional number.  If TIMEOUT is 0, read returns success only";
                qDebug() << "    		if input is available on the specified file descriptor.  The";
                qDebug() << "    		exit status is greater than 128 if the timeout is exceeded";
                qDebug() << "      -u fd		read from file descriptor FD instead of the standard input" << Qt::endl;

                qDebug() << "    Exit Status:";
                qDebug() << "    The return code is zero, unless end-of-file is encountered, read times out,";
                qDebug() << "    or an invalid file descriptor is supplied as the argument to -u.";
                qDebug() << "readarray: readarray [-n count] [-O origin] [-s count] [-t] [-u fd] [-C callback] [-c quantum] [array]";
                qDebug() << "    Read lines from a file into an array variable." << Qt::endl;

                qDebug() << "    A synonym for `mapfile'.";
                qDebug() << "readonly: readonly [-aAf] [name[=value] ...] or readonly -p";
                qDebug() << "    Mark shell variables as unchangeable." << Qt::endl;

                qDebug() << "    Mark each NAME as read-only; the values of these NAMEs may not be";
                qDebug() << "    changed by subsequent assignment.  If VALUE is supplied, assign VALUE";
                qDebug() << "    before marking as read-only." << Qt::endl;

                qDebug() << "    Options:";
                qDebug() << "      -a	refer to indexed array variables";
                qDebug() << "      -A	refer to associative array variables";
                qDebug() << "      -f	refer to shell functions";
                qDebug() << "      -p	display a list of all readonly variables and functions" << Qt::endl;

                qDebug() << "    An argument of `--' disables further option processing." << Qt::endl;

                qDebug() << "    Exit Status:";
                qDebug() << "    Returns success unless an invalid option is given or NAME is invalid.";

            }
            else if (next_place == 2 && strList[1][0] == '-')
            {
                if (strList[1][1] == 'd')
                {
                    qDebug() << "read - Read a line from the standard input and split it into fields.";
                    qDebug() << "readarray - Read lines from a file into an array variable.";
                    qDebug() << "readonly - Mark shell variables as unchangeable.";
                }
                else if (strList[1][1] == 'm')
                {
                    qDebug() << "NAME";
                    qDebug() << "    read - Read a line from the standard input and split it into fields." << Qt::endl;

                    qDebug() << "SYNOPSIS";
                    qDebug() << "    read [-ers] [-a array] [-d delim] [-i text] [-n nchars] [-N nchars] [-p prompt] [-t timeout] [-u fd] [name ...]" << Qt::endl;

                    qDebug() << "DESCRIPTION";
                    qDebug() << "    Read a line from the standard input and split it into fields." << Qt::endl;

                    qDebug() << "    Reads a single line from the standard input, or from file descriptor FD";
                    qDebug() << "    if the -u option is supplied.  The line is split into fields as with word";
                    qDebug() << "    splitting, and the first word is assigned to the first NAME, the second";
                    qDebug() << "    word to the second NAME, and so on, with any leftover words assigned to";
                    qDebug() << "    the last NAME.  Only the characters found in $IFS are recognized as word";
                    qDebug() << "    delimiters." << Qt::endl;

                    qDebug() << "    If no NAMEs are supplied, the line read is stored in the REPLY variable." << Qt::endl;

                    qDebug() << "    Options:";
                    qDebug() << "      -a array	assign the words read to sequential indices of the array";
                    qDebug() << "            variable ARRAY, starting at zero";
                    qDebug() << "      -d delim	continue until the first character of DELIM is read, rather";
                    qDebug() << "            than newline";
                    qDebug() << "      -e		use Readline to obtain the line in an interactive shell";
                    qDebug() << "      -i text	Use TEXT as the initial text for Readline";
                    qDebug() << "      -n nchars	return after reading NCHARS characters rather than waiting";
                    qDebug() << "            for a newline, but honor a delimiter if fewer than NCHARS";
                    qDebug() << "            characters are read before the delimiter";
                    qDebug() << "      -N nchars	return only after reading exactly NCHARS characters, unless";
                    qDebug() << "            EOF is encountered or read times out, ignoring any delimiter";
                    qDebug() << "      -p prompt	output the string PROMPT without a trailing newline before";
                    qDebug() << "            attempting to read";
                    qDebug() << "      -r		do not allow backslashes to escape any characters";
                    qDebug() << "      -s		do not echo input coming from a terminal";
                    qDebug() << "      -t timeout	time out and return failure if a complete line of input is";
                    qDebug() << "            not read withint TIMEOUT seconds.  The value of the TMOUT";
                    qDebug() << "            variable is the default timeout.  TIMEOUT may be a";
                    qDebug() << "            fractional number.  If TIMEOUT is 0, read returns success only";
                    qDebug() << "            if input is available on the specified file descriptor.  The";
                    qDebug() << "            exit status is greater than 128 if the timeout is exceeded";
                    qDebug() << "      -u fd		read from file descriptor FD instead of the standard input" << Qt::endl;

                    qDebug() << "    Exit Status:";
                    qDebug() << "    The return code is zero, unless end-of-file is encountered, read times out,";
                    qDebug() << "    or an invalid file descriptor is supplied as the argument to -u." << Qt::endl;

                    qDebug() << "SEE ALSO";
                    qDebug() << "    bash(1)" << Qt::endl;

                    qDebug() << "IMPLEMENTATION";
                    qDebug() << "    GNU bash, version 4.2.46(2)-release (x86_64-redhat-linux-gnu)";
                    qDebug() << "    Copyright (C) 2011 Free Software Foundation, Inc.";
                    qDebug() << "    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << Qt::endl;

                    qDebug() << "NAME";
                    qDebug() << "    readarray - Read lines from a file into an array variable." << Qt::endl;

                    qDebug() << "SYNOPSIS";
                    qDebug() << "    readarray [-n count] [-O origin] [-s count] [-t] [-u fd] [-C callback] [-c quantum] [array]" << Qt::endl;

                    qDebug() << "DESCRIPTION";
                    qDebug() << "    Read lines from a file into an array variable." << Qt::endl;

                    qDebug() << "    A synonym for `mapfile'." << Qt::endl;

                    qDebug() << "SEE ALSO:";
                    qDebug() << "    bash(1)" << Qt::endl;

                    qDebug() << "IMPLEMENTATION";
                    qDebug() << "    GNU bash, version 4.2.46(2)-release (x86_64-redhat-linux-gnu)";
                    qDebug() << "    Copyright (C) 2011 Free Software Foundation, Inc.";
                    qDebug() << "    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << Qt::endl;

                    qDebug() << "NAME";
                    qDebug() << "    readonly - Mark shell variables as unchangeable." << Qt::endl;

                    qDebug() << "SYNOPSIS";
                    qDebug() << "    readonly [-aAf] [name[=value] ...] or readonly -p" << Qt::endl;

                    qDebug() << "DESCRIPTION";
                    qDebug() << "    Mark shell variables as unchangeable." << Qt::endl;

                    qDebug() << "    Mark each NAME as read-only; the values of these NAMEs may not be";
                    qDebug() << "    changed by subsequent assignment.  If VALUE is supplied, assign VALUE";
                    qDebug() << "    before marking as read-only." << Qt::endl;

                    qDebug() << "    Options:";
                    qDebug() << "      -a	refer to indexed array variables";
                    qDebug() << "      -A	refer to associative array variables";
                    qDebug() << "      -f	refer to shell functions";
                    qDebug() << "      -p	display a list of all readonly variables and functions" << Qt::endl;

                    qDebug() << "    An argument of `--' disables further option processing." << Qt::endl;

                    qDebug() << "    Exit Status:";
                    qDebug() << "    Returns success unless an invalid option is given or NAME is invalid." << Qt::endl;

                    qDebug() << "SEE ALSO";
                    qDebug() << "    bash(1)" << Qt::endl;

                    qDebug() << "IMPLEMENTATION";
                    qDebug() << "    GNU bash, version 4.2.46(2)-release (x86_64-redhat-linux-gnu)";
                    qDebug() << "    Copyright (C) 2011 Free Software Foundation, Inc.";
                    qDebug() << "    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << Qt::endl;

                }
                else if (strList[1][1] == 's')
                {
                    qDebug() << "read: read [-ers] [-a array] [-d delim] [-i text] [-n nchars] [-N nchars] [-p prompt] [-t timeout] [-u fd] [name ...]";
                    qDebug() << "readarray: readarray [-n count] [-O origin] [-s count] [-t] [-u fd] [-C callback] [-c quantum] [array]";
                    qDebug() << "readonly: readonly [-aAf] [name[=value] ...] or readonly -p";
                }
            }
        }
        else
        {
            if (strList[1].length() > 2 && strList[1][0] == '-' && strList[1][1] != ('d' || 'm' || 's')) //e.g. help -a ls
                flag1 = false;
            else    //e.g. help ls || help - ls || help -l ls
                flag2 = false;
        }

    }

    if (!(flag1 && flag2))
    {
        if (!flag1)   //  error: [-dms]
            qDebug().nospace() << "-bash: help: " << qPrintable(strList[1]) << ": invalid option";
        else if (!flag2)  // error: [pattern]
            qDebug().nospace() << "-bash: help: no help topics match `" << qPrintable(strList[next_place]) << "'.  Try `help help' or `man -k " << qPrintable(strList[next_place]) << "' or `info " << qPrintable(strList[next_place]) << "'.";
    }
}

/*
 * NAME
 *      Clear screen
 * SYNOPSIS
 *      clear
 */
void clear()
{
    system ("clear");
}

/*
 * NAME
 *      Format the disk of MS-DOS file system
 * SYNOPSIS
 *      rm [options] name
 */
void format(QStringList strList, QString user)
{

}

/*
 * Judgment instruction function
 */
void choose(QString str, QString user)
{
    QStringList strList = str.split(" ");
    if (strList[0] == "ls")
        ls(strList);
    else if (strList[0]== "cd")
        cd(strList);
    else if (strList[0] == "pwd")
        pwd();
    else if (strList[0] == "mkdir")
        mkdir(strList, user);
    else if (strList[0] == "rmdir")
        rmdir(strList, user);
    else if (strList[0] == "rm")
        rm(strList, user);
    else if (strList[0] == "mv")
        mv(strList, user);
    else if (strList[0] == "cp")
    else if (strList[0] == "cat")
    else if (strList[0] == "whereis")
    else if (strList[0] == "find")
    else if (strList[0] == "chomd")
    else if (strList[0] == "chown")
    else if (strList[0] == "tar")
    else if (strList[0] == "login")
        login(strList, user);
    else if (strList[0] == "logout")
        logout(strList, user);
    else if (strList[0] == "vi")
    else if (strList[0] == "touch")
    else if (strList[0] == "top")
    else if (strList[0] == "read")
        read(strList, user);
    else if (strList[0] == "write")
        write(strList, user);
    else if (strList[0] == "help")
        help(strList);
    else if (strList[0] == "clear")
        clear();
    else if (strList[0] == "format")

    else if (strList[0] == "sudo")
    {
        str = str.mid(5);
        choose(str, "sudo");
    }
    else
        qDebug().nospace()<<"-bash: " << qPrintable(strList[0]) << ": command not found";
}


int main()
{
    QString str = "c://lal/ao/lin";
    QStringList strList = str.split("/");
    //help(strList);
    qDebug()<<strList;
    strList.removeLast();
    str = strList.join("/");
    qDebug()<<str;
//    system("pause");
    return 0;
}


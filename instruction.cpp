#include "instruction.h"
#include "disk.h"
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

QString Global_path = "/";
QString Global_user = "";
DISK disk;

//QString 转 string
string q2s(const QString &s)
{
return string((const char *)s.toLocal8Bit());
}

//获取用户输入文件名对应的路径
QString get_true_path(QString str)
{
    QStringList path_list = str.split('/', QString::SkipEmptyParts);
    QString new_path = Global_path;
    for(int i=0;i<path_list.count();i++)
    {
        if(path_list[i] == "..")
        {
            QStringList temp_path_list = new_path.split('/',QString::SkipEmptyParts);
            if(temp_path_list.count() == 0)
            {
                new_path = "/";
            }
            else
            {
                temp_path_list.removeLast();
                new_path = temp_path_list.join("/");
                new_path = "/" + new_path;
            }
        }
        else if(path_list[i] == ".")
            continue;
        else
        {
            new_path = new_path + "/" + path_list[i];
        }
    }
    return new_path;
}

//获取用户输入文件名对应的路径列表（应对rm用出现的*符号）
QStringList get_true_path_list(QString str)
{
    QStringList path_list = str.split('/', QString::SkipEmptyParts);
    QString new_path = Global_path;
    QStringList new_path_list;
    for(int i=0;i<path_list.count();i++)
    {
        if(path_list[i] == "..")
        {
            QStringList temp_path_list = new_path.split('/',QString::SkipEmptyParts);
            if(temp_path_list.count() == 0)
            {
                new_path = "/";
            }
            else
            {
                temp_path_list.removeLast();
                new_path = temp_path_list.join("/");
                new_path = "/" + new_path;
            }
        }
        else if(path_list[i] == ".")
            continue;
        else if(path_list[i] == "*")
        {
            QStringList file_list;
            if(disk.findFile(new_path) == -1)
                return file_list;
            file_list = disk.getFileList(new_path);
            for(int j=0;j<file_list.count();j++)
            {
                new_path_list<<file_list[j];
            }
            return new_path_list;
        }
        else
        {
            new_path = new_path + "/" + path_list[i];
        }
    }
    new_path_list<<new_path;
    return new_path_list;
}

/*
 * NAME
 *      ls - Displays the contents of the specified working directory
 * SYNOPSIS
 *      ls [-alrt] [name...]
 */
void ls(QStringList strList)
{
    int length = strList.count();
    if(length >= 2 && strList[1] == "--help")
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
        qDebug()<<"  -n, --numeric-uid-gid      like -l, but list numeric Global_user and group IDs";
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
        qDebug()<<"                             displays.  Displays only mode, Global_user, group,";
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
    else if(length >= 2 && strList[1].length() > 1 && strList[1][0] == '-' && (strList[1][1] != 'a'|| strList[1][1] != 'l'|| strList[1][1] != 'r'|| strList[1][1] != 't'))
    {
        if(strList[1].length() == 2 && strList[1][1] == '-')
        {
            qDebug()<<"ls: missing operand";
            qDebug()<<"Try 'ls --help' for more information.";
        }
        else if(strList[1].length() == 2)
        {
            qDebug().nospace()<<"ls: invalid option -- '"<<strList[1][1]<<"'";
            qDebug()<<"Try 'ls --help' for more information.";
        }
        else
        {
            qDebug().nospace()<<"ls: unrecognized option -- '"<<qPrintable(strList[1])<<"'";
            qDebug()<<"Try 'ls --help' for more information.";
        }
    }
    else
    {
        QString file_name;
        int status[4]={0,0,0,0};    //命令行的附加功能格式为“组合”+“存在”形式  以附加功能数组进行对应功能存储
        if(length == 1)
            file_name = Global_path;
        else
        {
            if(strList[1][0] == '-')
            {
                for(int i=1;i<strList[1].length();i++)
                {
                    if(strList[1][i] == 'a')    //+父+本身+隐藏
                        status[0] = 1;
                    else if(strList[1][i] == 'l')   //详细信息
                        status[1] = 1;
                    else if(strList[1][i] == 'r')   //反序
                        status[2] = 1;
                    else if(strList[1][i] == 't')   //时间先后
                        status[3] = 1;
                    else    //命令行会对第一个遇到的非附加功能符号进行报错
                    {
                        qDebug().nospace()<<"rm: invalid option -- '"<<strList[1][i]<<"'";
                        qDebug()<<"Try 'rm --help' for more information.";
                        return ;
                    }
                }
                file_name = strList[2];
                file_name = get_true_path(file_name);
            }
            else
            {
                file_name = strList[1];
                file_name = get_true_path(file_name);
            }
        }

        QStringList file_list = disk.getFileList(file_name);
        QStringList ans_list;
        QString ans1 = "";
        QString ans2 = "";
        if(status[0] == 1)
        {
            QStringList work_path_list = file_name.split("/", QString::SkipEmptyParts);
            QString work_path;
            if(work_path_list.count() == 0)
            {
                work_path = "/";
            }
            else
            {
                work_path_list.removeLast();
                if(work_path_list.count() == 0)
                    work_path = "/";
                else
                    work_path = work_path_list.join("/");
            }
            if(status[2] == 1)
            {
                if(work_path != Global_path)
                    ans1 = ans1 + disk.get(work_path) + QString(get_file_list(work_path).count()) + get_creator(work_path) + Global_user + get_filetime(work_path) +"..";
                ans2 = ans2 + get_permission(Global_path) + QString(get_file_list(Global_path).count()) + get_creator(Global_path) + Global_user + get_filetime(Global_path) +".";
            }
            else
            {
                if(work_path != Global_path)
                    ans1 = "..";
                ans2 = ".";
            }
            ans_list << ans1 << ans2;
        }
        if(status[3] == 1)
            qSort(file_list.begin(), file_list.end(), [](const QString& s1, const QString& s2){return get_file_create_time(s1) < get_file_create_time(s1); });

        for(int i=0;i<file_list.count();i++)
        {
            QString ans = "";
            QStringList temp_filename_list = file_list[i].split('/');
            QString only_filename = temp_filename_list[temp_filename_list.count()-1];
            if(only_filename[0] == '.' && status[0] != 1 )
                continue ;
            if(status[2] == 1)
                ans = ans + get_permission(file_list[i]) + QString(get_file_list(file_list[i]).count()) + get_creator(file_list[i]) + Global_user + get_filetime(file_list[i]) + only_filename;
            else
                ans = only_filename;
            ans_list << ans ;
        }
        if(status[3] == 1)
        {
            for(int i=ans_list.count()-1;i>=0;i++)
                qDebug()<<ans_list[i];
        }
        else
        {
            for(int i=0;i<ans_list.count();i++)
                qDebug()<<ans_list[i];
        }

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
    if(strList.count() == 1)
    {
        Global_path = "/" + Global_user;
        return ;
    }
    QString filename=strList[1];

    filename=get_true_path(filename);
    int file_id = disk.findFile(filename);
    if(file_id == -1)
    {
        qDebug().nospace()<<"-bash: cd: " << qPrintable(strList[1]) << ": No such file or directory";
        return ;
    }

    Global_path = filename;
}


/*
 * NAME
 *      Show working directory
 * SYNOPSIS
 *      pwd
 */
void pwd()
{
    qDebug()<<qPrintable(Global_path);
}

/*
 * NAME
 *      Create directory
 * SYNOPSIS
 *      mkdir [-p] dirName
 */
void mkdir(QStringList strList)
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
        file_name = get_true_path(file_name);

        int file_id = disk.findFile(file_name);
        if(file_id != -1)    //判断是否存在
        {
            if(file_place == 1) //-p会确保文件存在，所以当存在时不报错
            {
                qDebug().nospace()<<"mkdir: cannot create directory ‘"<<qPrintable(strList[1])<<"’: File exists";
            }
            return ;
        }

        //获取当前工作的路径，以判断当前所拥有的权限
        QStringList work_path_list = file_name.split("/", QString::SkipEmptyParts);
        QString work_path;
        if(work_path_list.count() == 0)
        {
            work_path = "/";
        }
        else
        {
            work_path_list.removeLast();
            if(work_path_list.count() == 0)
                work_path = "/";
            else
                work_path = work_path_list.join("/");
        }

        QString permission = file_permission(work_path);

        //permission 格式为 ‘drwxrwxrwx'
        //权限判断
        QString creator = get_creator(work_path);
        if(Global_user == "root" || Global_user == creator)    //owner
        {
            if(permission[1] == 'r')
                create_directory(file_name);
            else
                qDebug()<<"Permission denied";
        }
        else if(get_uesr_permissions(Global_user))   //获取权限，group
        {
            if(permission[4] == 'r')
                create_directory(file_name);
            else
                qDebug()<<"Permission denied";
        }
        else    //others
        {
            if(permission[7] == 'r')
                create_directory(file_name);
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
void rmdir(QStringList strList)
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

        int file_id = disk.findFile(file_name);

        if(file_id == -1)  //判断文件是否存在
        {
            qDebug().nospace()<<"rmdir: failed to remove directory ‘"<<qPrintable(strList[file_place])<<"’: No such file or directory";
            return ;
        }

        if(get_file_type(file_name) != "directory")
        {
            qDebug().nospace()<<"rmdir: failed to remove ‘"<<qPrintable(strList[file_place])<<"’: Not a directory";
            return ;
        }

        if(!if_empty(file_name))    //判断文件目录是否为空
        {
            qDebug().nospace()<<"rmdir: failed to remove ‘"<<qPrintable(strList[file_place])<<"’: Directory not empty";
            return ;
        }

        //含'-p'时 若删除当前目录会造成上级目录为空，则逐级删除 直至非空或删除至当前工作目录
        do
        {
            QStringList work_path_list = file_name.split("/");
            QString work_path;
            if(work_path_list.count() == 0)
            {
                work_path = "/";
            }
            else
            {
                work_path_list.removeLast();
                if(work_path_list.count() == 0)
                    work_path = "/";
                else
                    work_path = work_path_list.join("/");
            }

            QString permission = file_permission(file_name);    //删除为获取所删除的目录的权限
            //permission 格式为 ‘drwxrwxrwx'
            QString creator = get_creator(file_name);
            if(Global_user == "root" || Global_user == creator)    //owner
            {
                if(permission[2] == 'w')
                    delete_file(file_name);
                else
                    qDebug()<<"Permission denied";
            }
            else if(get_uesr_permissions(Global_user))   //获取权限，group
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
void rm_del(QString filename,int ask)
{
    while(!if_empty(filename))
    {
        QStringList file_list = get_file_list(filename);
        for(int i=0;i<file_list.count();i++)
        {
            if(get_file_type(file_list[i]) == "文件目录")
                rm_del(file_list[i],ask);
            else
            {
                char delete_answer;
                if(ask)
                {
                    qDebug().nospace()<<"rm: remove file or directory ‘"<<file_list[i]<<"’?";
                    delete_answer = get_delete_answer();    //获取用户输入
                }

                if(!ask || delete_answer == 'y')
                {

                    QString permission = file_permission(file_list[i]);
                    //permission 格式为 ‘drwxrwxrwx'
                    QString creator = get_creator(file_list[i]);
                    if(Global_user == "root" || Global_user == creator)    //owner
                    {
                        if(permission[2] == 'w')
                            delete_file(file_list[i]);
                        else
                            qDebug()<<"Permission denied";
                    }
                    else if(get_uesr_permissions(Global_user))   //获取权限，group
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

    char delete_answer;
    if(ask)
    {
        qDebug().nospace()<<"rm: remove file or directory ‘"<<filename<<"’?";
        delete_answer = get_delete_answer();    //获取用户输入
    }

    if(!ask || delete_answer == 'y')
    {

        QString permission = file_permission(filename);
        //permission 格式为 ‘drwxrwxrwx'
        QString creator = get_creator(filename);
        if(Global_user == "root" || Global_user == creator)    //owner
        {
            if(permission[2] == 'w')
                delete_file(filename);
            else
                qDebug()<<"Permission denied";
        }
        else if(get_uesr_permissions(Global_user))   //获取权限，group
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
void rm(QStringList strList)
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

        int status[2]={0,0};    //命令行的附加功能格式为“组合”+“存在”形式  以附加功能数组进行对应功能存储
        if(file_place == 2)
        {
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
        }

        QStringList file_name_list = get_true_path_list(strList[file_place]);
        if(file_name_list.count() == 0)
        {
            qDebug().nospace()<<"rm: failed to remove file or directory ‘"<<qPrintable(strList[file_place])<<"’: File not exists";
            return ;
        }


        for(int i=0;i<file_name_list.count();i++)
        {
            QString file_name =file_name_list[i];
            if(disk.findFile(file_name) == -1)
            {
                qDebug().nospace()<<"rm: failed to remove file or directory ‘"<<qPrintable(strList[file_place])<<"’: File not exists";
                return ;
            }

            if(get_file_type(file_name) != "文件")    // 文件目录需以'-r'命令删除
            {
                qDebug().nospace()<<"rm: remove regular file ‘"<<file_name<<"’?";
                QString delete_answer = get_delete_answer();    //获取用户输入
                if(delete_answer == 'y')
                {
                    QString permission = file_permission(file_name);
                    //permission 格式为 ‘drwxrwxrwx'
                    QString creator = get_creator(file_name);
                    if(Global_user == "root" || Global_user == creator)    //owner
                    {
                        if(permission[2] == 'w')
                            delete_file(file_name);
                        else
                            qDebug()<<"Permission denied";
                    }
                    else if(get_uesr_permissions(Global_user))   //获取权限，group
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
                    qDebug().nospace()<<"rm: cannot remove ‘"<<strList[file_place]<<"’: Is a directory";
                }
                else
                {
                    qDebug().nospace()<<"rm: remove regular file ‘"<<file_name<<"’?";
                    QString delete_answer = get_delete_answer();    //获取用户输入
                    if(delete_answer == 'y')
                    {
                        rm_del(file_name,status[1]);       //-i需依次获取用户询问
                    }
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
void mv(QStringList strList)
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
                qDebug()<<"mv: missing operand";
                qDebug()<<"Try 'mv --help' for more information.";
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

        int status[5]={0,0,0,0,0};    //命令行的附加功能格式为“组合”+“存在”形式  以附加功能数组进行对应功能存储
        if(file_place == 2)
        {
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
        }

        QStringList source_file_list = get_true_path_list(strList[file_place]);
        QString dest_file = strList[file_place + 1];
        dest_file = get_true_path(dest_file);
        int dest_file_id = disk.findFile(dest_file);

        if(source_file_list.count() == 0)
        {
            qDebug().nospace()<<"mv: failed to move file or directory ‘"<<qPrintable(strList[file_place])<<"’: File not exists";
            return ;
        }

        for(int i=0;i<source_file_list.count();i++)
        {
            QString source_file = source_file_list[i];
            QString type1;
            if(source_file_list.count() == 1)
            {
                if(disk.findFile(source_file) == -1)    //判断是否存在
                {
                    qDebug().nospace()<<"mv: failed to move file or directory ‘"<<qPrintable(strList[file_place])<<"’: File not exists";
                    return ;
                }

                type1 = get_file_type(source_file);
            }
            else
                type1 = "directory";

            if(dest_file_id == -1)
            {
                QString permission1 = file_permission(source_file);
                QString permission2 = file_permission(dest_file);

                if(status[4] == 1)  //当源文件比目标文件新或者目标文件不存在时，才执行移动操作
                {
                    if(get_filetime(source_file) < get_filetime(dest_file))
                        return ;
                }

                //permission 格式为 ‘drwxrwxrwx'
                QString creator1 = get_creator(source_file);
                QString creator2 = get_creator(dest_file);
                if(Global_user == "root" || (Global_user == creator1 && Global_user == creator2))    //owner
                {
                    if(permission1[2] != 'w' || permission2[2] != 'w')
                    {
                        qDebug()<<"Permission denied";
                        return ;
                    }
                }
                else if(get_uesr_permissions(Global_user))   //获取权限，group
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

                if(type1 == "file" && type2 == "file")  //对文件重命名
                {
                    if(status[3] == 1)return ;  //-n不执行覆盖操作

                    char delete_answer = 'y';
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
                else if(type1 == "file" && type2 == "directory") //将文件移动到目录下
                {
                    if(directory_have_file(source_file,dest_file))  //判断目录下是否有同名文件
                    {
                        if(status[3] == 1)return ;  //-n不执行覆盖操作

                        char delete_answer = 'y';
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
                        move_file_to_Directory(source_file,dest_file);
                }
                else if(type1 == "directory" && type2 == "directory")  //将目录移动到目录type2下
                {
                    if(directory_have_file(source_file,dest_file))  //判断目录下是否有同名文件
                    {
                        if(status[3] == 1)return ;  //-n不执行覆盖操作

                        char delete_answer = 'y';
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
                        move_file_to_Directory(source_file,dest_file);
                }
                else if(type1 == "directory" && type2 == "file")    //error
                {
                    if(status[3] == 1)return ;  //-n不执行覆盖操作

                    char delete_answer = 'y';
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
            else    //改名
            {
                QString permission = file_permission(source_file);    //删除为获取所删除的目录的权限
                //permission 格式为 ‘drwxrwxrwx'
                QString creator = get_creator(source_file);
                if(Global_user == "root" || Global_user == creator)    //owner
                {
                    if(permission[2] == 'w')
                        change_name(source_file,dest_file);
                    else
                        qDebug()<<"Permission denied";
                }
                else if(get_uesr_permissions(Global_user))   //获取权限，group
                {
                    if(permission[5] == 'w')
                        change_name(source_file,dest_file);
                    else
                        qDebug()<<"Permission denied";
                }
                else    //others
                {
                    if(permission[8] == 'w')
                        change_name(source_file,dest_file);
                    else
                        qDebug()<<"Permission denied";
                }

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
void cp(QStringList strList)
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

        int status[3]={0,0,0};    //命令行的附加功能格式为“组合”+“存在”形式  以附加功能数组进行对应功能存储
        if(file_place == 2)
        {
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
        }


        QStringList source_file_list = get_true_path_list(strList[file_place]);
        QString dest_file = strList[file_place + 1];
        dest_file = get_true_path(dest_file);

        if(source_file_list.count() == 0)
        {
            qDebug().nospace()<<"mv: failed to move file or directory ‘"<<qPrintable(strList[file_place])<<"’: File not exists";
            return ;
        }

        for(int i=0;i<source_file_list.count();i++)
        {
            QString source_file = source_file_list[i];
            QString type1;
            if(source_file_list.count() == 1)
            {
                if(disk.findFile(source_file) == -1)    //判断是否存在
                {
                    qDebug().nospace()<<"mv: failed to move file or directory ‘"<<qPrintable(strList[file_place])<<"’: File not exists";
                    return ;
                }
            }

            if(disk.findFile(dest_file) == -1)
            {
                if(directory_have_file(source_file,dest_file))  //des下是否有与source同名文件
                {
                    if(status[0] == 0)
                    {
                        QString delete_answer = get_delete_answer();
                        if(delete_answer == 'n')
                            return ;
                    }
                }
            }
            else
            {
                create_directory(dest_file);
            }

            QString permission1 = file_permission(source_file);

            //获取工作的路径，以判断所拥有的权限
            QStringList work_path_list = dest_file.split("/");
            QString work_path;
            if(work_path_list.count() == 0)
            {
                work_path = "/";
            }
            else
            {
                work_path_list.removeLast();
                if(work_path_list.count()==0)
                    work_path = "/";
                else
                    work_path = work_path_list.join("/");
            }

            QString permission2 = file_permission(work_path);

            //permission 格式为 ‘drwxrwxrwx'
            QString creator = get_creator(work_path);
            if(Global_user == "root" || Global_user == creator)    //owner
            {
                if(permission1[2] != 'w' || permission2[2] != 'w')
                {
                    qDebug()<<"Permission denied";
                    return ;
                }
            }
            else if(get_uesr_permissions(Global_user))   //获取权限，group
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

            QString type1 = get_file_type(source_file);

            if(type1 == "目录" && status[2] == 0)
            {
                qDebug().nospace()<<"cp: omitting directory ‘"<<qPrintable(source_file)<<"’";
                return ;
            }

            int flag_p = 0; //1代表-p：需要复制原文件修改时间和权限  0代表新五文件拥有自己的修改时间和权限
            if(status[1] == 1)flag_p = 1;
            copy(source_file,dest_file,flag_p);
        }
    }
}

/*
 * NAME
 *      read all context in a file
 * SYNOPSIS
 *      cat file
 */
void cat(QStringList strList)
{
    int length = strList.count();
    if(length == 1)
    {
        qDebug()<<"read: missing operand";
    }
    else
    {
        QString file_name = strList[1];
        file_name = get_true_path(file_name);

        if(disk.findFile(file_name) == -1)    //判断是否存在
        {
            qDebug().nospace()<<"read: failed to find directory ‘"<<qPrintable(strList[1])<<"’: File not exists";
            return ;
        }

        QString permission = file_permission(file_name);

        //permission 格式为 ‘drwxrwxrwx'
        //权限判断
        QString creator = get_creator(file_name);
        if(Global_user == "root" || Global_user == creator)    //owner
        {
            if(permission[1] != 'r')
            {
                qDebug()<<"Permission denied";
                return ;
            }
        }
        else if(get_uesr_permissions(Global_user))   //获取权限，group
        {
            if(permission[4] != 'r')
            {
                qDebug()<<"Permission denied";
                return ;
            }
        }
        else    //others
        {
            if(permission[7] != 'r')
            {
                qDebug()<<"Permission denied";
                return ;
            }
        }

        QString message = read_all_line(file_name);

        qDebug()<< message;
    }
}

/*
void more(QStringList strList,QString Global_user)
{

}


void less(QStringList strList,QString Global_user)
{

}

void head(QStringList strList,QString Global_user)
{

}

void tail(QStringList strList,QString Global_user)
{

}

void which(QStringList strList,QString Global_user)
{

}

void locate(QStringList strList,QString Global_user)
{

}
*/

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      whereis file
 */
void whereis(QStringList strList)
{
    int length = strList.count();
    if(length == 1)
    {
        qDebug()<<"whereis: missing operand";
    }
    else
    {
        QString file_name = strList[1]; //模糊文件名，非全局路径
        QStringList ans_list = whereis_file(file_name);
        for(int i=0;i<ans_list.count();i++)
            qDebug()<<ans_list[i];
    }
}

/*
 * NAME
 *      Delete a file or directory
 * SYNOPSIS
 *      find directory file
 */
void find(QStringList strList)
{
    int length = strList.count();
    if(length <= 2)
    {
        qDebug()<<"find: missing operand";
    }
    else
    {
        QString directory_name = strList[1];
        directory_name = get_true_path(directory_name);
        QString file_name = strList[2]; //模糊文件名，非全局路径

        if(disk.findFile(directory_name) == -1)    //判断是否存在
        {
            qDebug().nospace()<<"find: directory ‘"<<qPrintable(directory_name)<<"’: not exists";
            return ;
        }

        QStringList ans_list = find_file_path(directory_name,file_name);
        for(int i=0;i<ans_list.count();i++)
            qDebug()<<ans_list[i];
    }
}

void add_permission(QString filename,int mum[3],QString p)
{
    QString n_p = get_permission(filename);
    for(int i=0;i<3;i++)
    {
        if(mum[i] != 0)
        {
            if(p.indexOf('r') != -1)
                n_p[i*3 + 1] = 'r';
            if(p.indexOf('w') != -1)
                n_p[i*3 + 2] = 'w';
            if(p.indexOf('x') != -1)
                n_p[i*3 + 3] = 'x';
        }
    }
    change_permission(filename,n_p);
}

void sub_permission(QString filename,int mum[3],QString p)
{
    QString n_p = get_permission(filename);
    for(int i=0;i<3;i++)
    {
        if(mum[i] != 0)
        {
            if(p.indexOf('r') != -1)
                n_p[i*3 + 1] = 'r';
            if(p.indexOf('w') != -1)
                n_p[i*3 + 2] = 'w';
            if(p.indexOf('x') != -1)
                n_p[i*3 + 3] = 'x';
        }
    }
    change_permission(filename,n_p);
}

void update_permission(QString filename,int mum[3],QString p)
{
    QString n_p = "";
    if(get_file_type(filename) == "directory")
        n_p = n_p + "d";
    else
        n_p = n_p + "-";
    for(int i=0;i<3;i++)
    {
        if(mum[i] == 0)
            n_p += "---";
        else
        {
            if(p.indexOf('r') == -1)
                n_p += "-";
            else
                n_p += 'r';
            if(p.indexOf('w') == -1)
                n_p += "-";
            else
                n_p += 'w';
            if(p.indexOf('x') == -1)
                n_p += "-";
            else
                n_p += 'x';
        }
    }
    change_permission(filename,n_p);
}

/*
 * NAME
 *      A command that controls the user's permissions on a file
 * SYNOPSIS
 *      chmod [ugoa...][[+-=][rwxX]...][,...] file
 */
void chmod(QStringList strList)
{
    if(Global_user != "root")return ;
    int length = strList.count();
    if(length == 1)
    {
        qDebug()<<"chmod: missing operand";
        qDebug()<<"Try 'chmod --help' for more information.";
    }
    else if(strList[1] == "--help")
    {
        qDebug()<<"Usage: chmod [OPTION]... MODE[,MODE]... FILE...";
        qDebug()<<"  or:  chmod [OPTION]... OCTAL-MODE FILE...";
        qDebug()<<"  or:  chmod [OPTION]... --reference=RFILE FILE...";
        qDebug()<<"Change the mode of each FILE to MODE.";
        qDebug()<<"With --reference, change the mode of each FILE to that of RFILE."<<Qt::endl;

        qDebug()<<"  -c, --changes          like verbose but report only when a change is made";
        qDebug()<<"  -f, --silent, --quiet  suppress most error messages";
        qDebug()<<"  -v, --verbose          output a diagnostic for every file processed";
        qDebug()<<"      --no-preserve-root  do not treat '/' specially (the default)";
        qDebug()<<"      --preserve-root    fail to operate recursively on '/'";
        qDebug()<<"      --reference=RFILE  use RFILE's mode instead of MODE values";
        qDebug()<<"  -R, --recursive        change files and directories recursively";
        qDebug()<<"      --help     display this help and exit";
        qDebug()<<"      --version  output version information and exit"<<Qt::endl;

        qDebug()<<"Each MODE is of the form '[ugoa]*([-+=]([rwxXst]*|[ugo]))+|[-+=][0-7]+'."<<Qt::endl;

        qDebug()<<"GNU coreutils online help: <http://www.gnu.org/software/coreutils/>";
        qDebug()<<"For complete documentation, run: info coreutils 'chmod invocation'";
    }
    else
    {
        if(length < 3)  //e.g. chmod 777  ||  chmod 7.txt
        {
            qDebug().nospace()<<"chmod: missing operand after ‘"<<qPrintable(strList[1])<<"’";
            qDebug().nospace()<<"Try 'chmod --help' for more information.";
        }
        QString file_name[10];
        int file_num=0;
        for(int i=2;i<length;i++)   //首先获取所有文件
        {
            file_name[i-2] = get_true_path(strList[i]);
            if(disk.findFile(file_name[i-2]) == -1)
            {
                qDebug().nospace()<<"chmod: failed to change mode ‘"<<qPrintable(file_name[i-2])<<"’: file not exits";
                return ;
            }
            file_num += 1;
        }

        if(strList[1][0] >= '0' && strList[1][0] <= '9')
        {
            int new_permission[3]={-1,-1,-1};
            for(int i=0;i<=strList[1].length();i++)
            {
                if(i >= 3)break;
                if(strList[1][i] == '0')
                    new_permission[i] = 0;
                else if(strList[1][i] == '1')
                    new_permission[i] = 1;
                else if(strList[1][i] == '2')
                    new_permission[i] = 2;
                else if(strList[1][i] == '3')
                    new_permission[i] = 3;
                else if(strList[1][i] == '4')
                    new_permission[i] = 4;
                else if(strList[1][i] == '5')
                    new_permission[i] = 5;
                else if(strList[1][i] == '6')
                    new_permission[i] = 6;
                else if(strList[1][i] == '7')
                    new_permission[i] = 7;
                else
                {
                    qDebug().nospace()<<"chmod: unrecognized option -- '"<<qPrintable(strList[1])<<"'";
                    qDebug()<<"Try 'chmod --help' for more information.";
                }
            }

            for(int i=0;i<3;i++)
            {
                QString n_p="";
                if((new_permission[i] & 4) != 0) n_p += "r";
                else n_p += "-";
                if((new_permission[i] & 2) != 0) n_p += "w";
                else n_p += "-";
                if((new_permission[i] & 1) != 0) n_p += "x";
                else n_p += "-";

                for(int j=0;j<file_num;j++)
                {
                    if(get_file_type(file_name[j]) == "directory")
                        n_p = "d" + n_p;
                    else
                        n_p = "-" + n_p;
                    change_permission(file_name[j],n_p);
                }
            }
        }
        else
        {
            QStringList group=strList[1].split(',',QString::SkipEmptyParts);
            for(int i=0;i<group.count();i++)
            {
                int mumber[3] = {0,0,0};    //u g o
                int flag_add_sub = -1;
                int user_or_permission = true;
                QString groupi = group[i];

                for(int j=0;j<groupi.length();j++)
                {
                    QString n_p = "";
                    if(user_or_permission)
                    {
                        if(groupi[j] == 'a')
                        {
                            mumber[0] = 1;
                            mumber[1] = 1;
                            mumber[2] = 1;
                        }
                        else if(groupi[j] == 'u')
                            mumber[0] = 1;
                        else if(groupi[j] == 'g')
                            mumber[1] = 1;
                        else if(groupi[j] == 'o')
                            mumber[2] = 1;
                        else if(groupi[j] == '+')
                        {
                            flag_add_sub = 0;
                            user_or_permission = false;
                        }
                        else if(groupi[j] == '-')
                        {
                            flag_add_sub = 1;
                            user_or_permission = false;
                        }
                        else if(groupi[j] == '=')
                        {
                            flag_add_sub = 2;
                            user_or_permission = false;
                        }
                        else
                        {
                            qDebug().nospace()<<"chmod: invalid mode: ‘"<<strList[1]<<"’";
                            qDebug().nospace()<<"Try 'chmod --help' for more information.";
                            return ;
                        }
                    }
                    else
                    {
                        if(groupi[j] == 'r')
                        {
                            n_p += 'r';
                        }
                        else if(groupi[j] == 'w')
                        {
                            n_p += 'w';
                        }
                        else if(groupi[j] == 'x')
                        {
                            n_p += 'x';
                        }
                        else
                        {
                            qDebug().nospace()<<"chmod: invalid mode: ‘"<<strList[1]<<"’";
                            qDebug().nospace()<<"Try 'chmod --help' for more information.";
                            return ;
                        }
                    }

                    if(user_or_permission)
                    {
                        qDebug().nospace()<<"chmod: invalid mode: ‘"<<strList[1]<<"’";
                        qDebug().nospace()<<"Try 'chmod --help' for more information.";
                        return ;
                    }


                    if(flag_add_sub == 0)
                        for(int j=0;j<file_num;j++)
                            add_permission(file_name[j],mumber,n_p);
                    else if(flag_add_sub == 1)
                        for(int j=0;j<file_num;j++)
                            sub_permission(file_name[j],mumber,n_p);
                    else if(flag_add_sub == 2)
                        for(int j=0;j<file_num;j++)
                            update_permission(file_name[j],mumber,n_p);
                }
            }
        }
    }

}

/*
void tar(QStringList strList, QString Global_user)
{

}


void df(QStringList strList,QString Global_user)
{

}

void du(QStringList strList,QString Global_user)
{

}

void ln(QStringList strList,QString Global_user)
{

}
*/

/*
 * NAME
 *      Log in to the system
 * SYNOPSIS
 *      login username
 */
void login(QStringList strList)
{
    if(strList.count() == 1)
    {
        qDebug()<<"login: missing operand";
        return ;
    }
    QString user_name = strList[1];
    if(ues_exist(user_name) == -1)
    {
        qDebug().nospace()<<"login: failed to login '"<<qPrintable(user_name)<<"': user not exists.";
        return ;
    }
    QString psword = get_password();    //输入
    QString password = get_user_password(user_name);

    if(psword == password)
        Global_user = user_name;
}

/*
 * NAME
 *      Exit the system
 * SYNOPSIS
 *      logout
 */
void logout()
{
    if(Global_user == "")
    {
        qDebug().nospace()<<"rmdir: failed to logout : No user is logged in.";
        return ;
    }
    Global_user = "";
}

/*
 * NAME
 *      open a file
 * SYNOPSIS
 *      open file
 */
void open(QStringList strList)
{
    if(strList.count() == 1)
    {
        qDebug()<<"open: missing operand";
        return ;
    }
    QString filename=strList[1];
    filename = get_true_path(filename);
    int file_id = disk.findFile(filename);
    if(file_id == -1)
    {
        qDebug().nospace()<<"open: failed to open ‘"<<qPrintable(filename)<<"’: file not exists.";
        return ;
    }

    open_file(filename);
}

/*
 * NAME
 *      close a file
 * SYNOPSIS
 *      close file
 */
void close(QStringList strList)
{
    if(strList.count() == 1)
    {
        qDebug()<<"login: missing operand";
        return ;
    }
    QString filename = strList[1];
    filename = get_true_path(filename);
    int file_id = disk.findFile(filename);
    if(file_id == -1)
    {
        qDebug().nospace()<<"open: failed to open ‘"<<qPrintable(filename)<<"’: file not exists.";
        return ;
    }

    if(if_file_open(filename))
    {
        close_file(filename);
    }
}

/*
 * NAME
 *      create a new user
 * SYNOPSIS
 *      adduser username
 */
void adduser(QStringList strList)
{
    if(Global_user != "root")
    {
        qDebug()<<"Permission denied";
        return ;
    }
    if(strList.count() == 1)
    {
        qDebug()<<"addGlobal_user: missing operand";
        return ;
    }
    QString username = strList[1];
    if(user_exist(username))
    {
        qDebug().nospace()<<"adduser: failed to add user '"<<qPrintable(username)<<"': user exists.";
        return ;
    }
    add_user(username);
}

/*
 * NAME
 *      Change Global_user password
 * SYNOPSIS
 *      passwd Global_username
 */
void passwd(QStringList strList)
{
    if(Global_user != "root")
    {
        qDebug()<<"Permission denied";
        return ;
    }
    if(strList.count() == 1)
    {
        qDebug()<<"passwd: missing operand";
        return ;
    }
    QString username = strList[1];
    if(!user_exist(username))
    {
        qDebug().nospace()<<"passwd: failed to input password '"<<qPrintable(username)<<"': user not exists.";
        return ;
    }
    qDebug().nospace()<<"Changing password for user "<<username<<".";
    qDebug()<<"New password:";
    QString get_pw1 = getpw();
    qDebug()<<"Retype new password:";
    QString get_pw2 = getpw();
    if(get_pw1 == get_pw2)
        qDebug()<<"passwd: all authentication tokens updated sucefully.";
    else
        qDebug()<<"passwd: the two passwords are inconsistent, modification failed";
    set_password(Global_user,get_pw1);
}

/*
 * NAME
 *      delete a user
 * SYNOPSIS
 *      rmuser username
 */
void rmuser(QStringList strList)
{
    if(Global_user != "root")
    {
        qDebug()<<"Permission denied";
        return ;
    }
    if(strList.count() == 1)
    {
        qDebug()<<"rmuser: missing operand";
        return ;
    }
    QString username = strList[1];
    if(!user_exist(username))
    {
        qDebug().nospace()<<"rmuser: failed to remove user '"<<qPrintable(username)<<"': user not exists.";
        return ;
    }
    remove_user(username);
}


/*
 * NAME
 *      create a new file
 * SYNOPSIS
 *      touch file
 */
void touch(QStringList strList)
{
    if(strList.count() == 1)
    {
        qDebug()<<"login: missing operand";
        return ;
    }
    QString filename=strList[1];
    filename = get_true_path(filename);
    int file_id = disk.findFile(filename);
    if(file_id == -1)
    {
        //获取当前工作的路径，以判断当前所拥有的权限
        QStringList work_path_list = filename.split("/",QString::SkipEmptyParts);
        QString work_path;
        if(work_path_list.count() == 0)
        {
            work_path = "/";
        }
        else
        {
            work_path_list.removeLast();
            if(work_path_list.count() == 0)
                work_path = "/";
            else
                work_path = work_path_list.join("/");
        }

        QString permission = file_permission(work_path);

        //permission 格式为 ‘drwxrwxrwx'
        //权限判断
        QString creator = get_creator(work_path);
        if(Global_user == "root" || Global_user == creator)    //owner
        {
            if(permission[1] == 'r')
                create_file(filename);
            else
                qDebug()<<"Permission denied";
        }
        else if(get_uesr_permissions(Global_user))   //获取权限，group
        {
            if(permission[4] == 'r')
                create_file(filename);
            else
                qDebug()<<"Permission denied";
        }
        else    //others
        {
            if(permission[7] == 'r')
                create_file(filename);
            else
                qDebug()<<"Permission denied";
        }
    }
}

/*
void grep(QStringList strList,QString Global_user)
{

}

void kill(QStringList strList,QString Global_user)
{

}
*/

/*
 * NAME
 *      Read a line of file
 * SYNOPSIS
 *      read filename
 */
void read(QStringList strList)
{
    int length = strList.count();
    if(length == 1)
    {
        qDebug()<<"read: missing operand";
    }
    else
    {
        QString file_name = strList[1];
        file_name = get_true_path(file_name);
        int file_id = disk.findFile(file_name);
        if(file_id == -1)    //判断是否存在
        {
            qDebug().nospace()<<"read: failed to read ‘"<<qPrintable(file_name)<<"’: File not exists";
            return ;
        }

        QString permission = file_permission(file_name);

        //permission 格式为 ‘drwxrwxrwx'
        //权限判断
        QString creator = get_creator(file_name);
        if(Global_user == "root" || Global_user == creator)    //owner
        {
            if(permission[1] != 'r')
            {
                qDebug()<<"Permission denied";
                return ;
            }
        }
        else if(get_uesr_permissions(Global_user))   //获取权限，group
        {
            if(permission[4] != 'r')
            {
                qDebug()<<"Permission denied";
                return ;
            }
        }
        else    //others
        {
            if(permission[7] != 'r')
            {
                qDebug()<<"Permission denied";
                return ;
            }
        }

        QString message = read_one_line(file_name);

        qDebug()<< message;
    }
}

/*
 * NAME
 *      Write a line of filename
 * SYNOPSIS
 *      write filename context
 */
void write(QStringList strList)
{

    int length = strList.count();
    if(length <= 2)
    {
        qDebug()<<"write: missing operand";
    }
    else
    {
        QString file_name = strList[1];
        file_name = get_true_path(file_name);
        int file_id = disk.findFile(file_name);
        if(file_id == -1)    //判断是否存在
        {
            qDebug().nospace()<<"write: failed to write ‘"<<qPrintable(file_name)<<"’: File not exists";
            return ;
        }

        QString permission = file_permission(file_name);

        //permission 格式为 ‘drwxrwxrwx'
        //权限判断
        QString creator = get_creator(file_name);
        if(Global_user == "root" || Global_user == creator)    //owner
        {
            if(permission[2] != 'w')
            {
                qDebug()<<"Permission denied";
                return ;
            }
        }
        else if(get_uesr_permissions(Global_user))   //获取权限，group
        {
            if(permission[5] != 'w')
            {
                qDebug()<<"Permission denied";
                return ;
            }
        }
        else    //others
        {
            if(permission[8] != 'w')
            {
                qDebug()<<"Permission denied";
                return ;
            }
        }

        QString context = strList[2];
        write_one_line(file_name,context);  //写入文件尾

    }
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
 *      [sudo] format
 */
void format()
{
    if(Global_user == "root")
        disk.Init();
    else
        qDebug()<<"Permission denied";
}

/*
 * Judgment instruction function
 */
void choose(QString str)
{
    QStringList strList = str.split(" ");
    if (strList[0] == "ls")
        ls(strList);
    else if (strList[0]== "cd")
        cd(strList);
    else if (strList[0] == "pwd")
        pwd();
    else if (strList[0] == "mkdir")
        mkdir(strList);                 //Global_user
    else if (strList[0] == "rmdir")
        rmdir(strList);                 //Global_user
    else if (strList[0] == "rm")
        rm(strList);                    //Global_user
    else if (strList[0] == "mv")
        mv(strList);                    //Global_user
    else if (strList[0] == "cp")
        cp(strList);                    //Global_user
    else if (strList[0] == "cat")
        cat(strList);                   //Global_user
    else if (strList[0] == "whereis")
        whereis(strList);
    else if (strList[0] == "find")
        find(strList);
    else if (strList[0] == "chomd")
        chmod(strList);                 //Global_user
    else if (strList[0] == "login")
        login(strList);
    else if (strList[0] == "logout")
        logout();
    else if (strList[0] == "open")
        open(strList);
    else if (strList[0] == "close")
        close(strList);
    else if (strList[0] == "addGlobal_user")
        adduser(strList);        //Global_user
    else if (strList[0] == "passwd")
        passwd(strList);
    else if (strList[0] == "rmGlobal_user")
        rmuser(strList);      //Global_user
    else if (strList[0] == "touch")
        touch(strList);                 //Global_user
    else if (strList[0] == "read")
        read(strList);                  //Global_user
    else if (strList[0] == "write")
        write(strList);                 //Global_user
    else if (strList[0] == "help")
        help(strList);
    else if (strList[0] == "clear")
        clear();
    else if (strList[0] == "format")
        format();
    else if (strList[0] == "sudo")
    {
        QString psword = get_root_password();
        if(psword == "root")
        {
            str = str.mid(5);
            Global_user = "root";
            choose(str);
        }
        else
            qDebug()<<"password error";
    }
    else
        qDebug().nospace()<<"-bash: " << qPrintable(strList[0]) << ": command not found";
}

/*
int main()
{
    int file_id = disk.findFile(file_name);
    QString str = "c://lal/ao/lin";
    QStringList strList = str.split("/", QString::SkipEmptyParts);
    //help(strList);
    qDebug()<<strList;
    strList.removeLast();
    str = strList.join("/");
    qDebug()<<str;
//    system("pause");
    return 0;
}
*/

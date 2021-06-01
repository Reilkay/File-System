#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

// 用户表USER
class USER
{
public:
    unsigned int getId() const;
    void setId(unsigned int value);

    string getUsername() const;
    void setUsername(const string &value);

    string getUserpwd() const;
    void setUserpwd(const string &value);

    int getUsergrp() const;
    void setUsergrp(int value);

    bool getIsManager() const;
    void setIsManager(bool value);

private:
    unsigned int id;    //用户id号
    string username;
    string userpwd;
    int usergrp;        //用户组
    bool isManager;     //管理员
};

#endif // USER_H

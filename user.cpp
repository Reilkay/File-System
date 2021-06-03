#include "user.h"

// 方法实现
unsigned int USER::getId() const
{
    return id;
}

void USER::setId(unsigned int value)
{
    id = value;
}

string USER::getUsername() const
{
    return username;
}

void USER::setUsername(const string &value)
{
    username = value;
}

string USER::getUserpwd() const
{
    return userpwd;
}

void USER::setUserpwd(const string &value)
{
    userpwd = value;
}

int USER::getUsergrp() const
{
    return usergrp;
}

void USER::setUsergrp(int value)
{
    usergrp = value;
}

bool USER::getIsManager() const
{
    return isManager;
}

void USER::setIsManager(bool value)
{
    isManager = value;
}

void USER_TABLE::add_user(USER temp_user)
{
    this->user_table.push_back(temp_user);
}

bool USER_TABLE::del_user(USER temp_user)
{

}


vector<USER> USER_TABLE::getUser_table() const
{
    return user_table;
}

void USER_TABLE::setUser_table(const vector<USER> &value)
{
    user_table = value;
}

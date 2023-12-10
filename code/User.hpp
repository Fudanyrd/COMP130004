#pragma once
#ifndef USER_HPP
#define USER_HPP

#include <fstream>
#include <stdexcept>
#include "HashTable.hpp"

namespace SocialNet{

/*
    *实现UserList类,保存用户的身份(id)信息.
*/
class UserList{
private:
    SocialNet::HashTable lists;
public:
    UserList():lists(TABLE_LENGTH){}
    /*load user data from filename, return the number of users.*/
};

};

#endif//USER_HPP
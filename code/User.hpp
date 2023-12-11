#pragma once
#ifndef USER_HPP
#define USER_HPP

#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>
#include "HashTable.hpp"

namespace SocialNet{

/*
    *实现UserList类,保存用户的身份(id)信息.
*/
class UserList{
private:
    SocialNet::HashTable lists;
    std::vector<int>          identity;      
    //某些时候也要求从矩阵行号rowNum推导出用户
    //身份,所以引入向量identity.
public:
    UserList():lists(TABLE_LENGTH){}
    UserList(unsigned int n):lists(n){}

    /*load user data from filename, return the number of users.*/
    int load(const std::string& filename){
        int a, num=0;
        std::ifstream fin(filename.c_str());
        while(fin >> a){
            if(lists.insert(a,num)){ //a has not turned up, OK, insert into table.
                identity.push_back(a);
                ++num;
            }
            //else, a has been in the list, abort.
        } 
        fin.close();
        return num;
    }

    //get the row numberr of an user.
    int rowNumOf(int id){ return lists.rowNumOf(id); }
    //get the id of a user(given row number)
    int idOfRow(int rowNum){
        if(rowNum<0||rowNum>=(int)identity.size()) throw std::domain_error("in class UserList::idOfRow "
        "array out of bounds");
        return identity[rowNum];
    }

    //number of users.
    int size()const{
        return identity.size();
    }
};

};

#endif//USER_HPP
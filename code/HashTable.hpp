#pragma once
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#define TABLE_LENGTH 4373   //length of hash table; large prime number to avoid collision.

namespace SocialNet{

/*单个用户类*/
struct User{
    int id;         //用户id,同时也是关键码.
    int rowNum;     //在邻接表中的行号.
    User* link;     //link to the next user;
    User():link(0){}
    User(int i,int r):id(i),rowNum(r),link(0){}
    //除留余数法建立散列函数.
    static int hash(int id,int len){ return id%len; }
};

//为了高效查找用户id和在邻接矩阵中的行号而设立.
//采用开散列法解决冲突.
class HashTable{
private:
    User** users;
    unsigned int len;       //length of hash table.
public:
    HashTable():len(TABLE_LENGTH){
        users = new User*[TABLE_LENGTH];
        for(int i=0;i!=TABLE_LENGTH;++i) users[i]=0;
    }
    HashTable(unsigned int l):len(l){
        users = new User*[l];
        for(int i=0;i!=l;++i) users[i]=0;
    }
    ~HashTable(){ delete[] users;}

    //insert a element with key id.
    //if exists, return false, otherwise return true.
    bool insert(int id,int rowNum){
        int pos = User::hash(id,len);
        User* iter = users[pos];
        if(iter==0){
            users[pos] = new User(id,rowNum); return true;
        }
        else{
            while(iter->link!=0){
                if(iter->id==id) return false;
                iter = iter->link;
            }
            iter->link = new User(id,rowNum);
        }
    }
    //return the row number of user(id)
    //return -1 if not found.
    int rowNumOf(int id){
        int pos = User::hash(id,this->len);
        User* iter = users[pos];
        while(iter&&iter->id!=id){
            iter = iter->link;
        }
        return iter?iter->rowNum:-1;
    }
};

};

#endif//HASHTABLE_HPP
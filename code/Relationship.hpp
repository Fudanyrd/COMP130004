#pragma once
#ifndef RELATIONSHIP_HPP
#define RELATIONSHIP_HPP

#include "Matrix.hpp"
#include "User.hpp"
#include <fstream>

/*社交网络名称空间.*/
namespace SocialNet{

/*布尔矩阵表示的图结果,节点代表用户,边代表用户之间的
 *关系.
*/
class Relationship{
private:
    Matrix data;
    SocialNet::UserList* list_ptr;
public:
    Relationship(){
        list_ptr = new UserList();
    }

    //load users' relationship from file.
    void load(const std::string& filename){
        int N=list_ptr->load(filename);
        data.construct(N);
        std::ifstream fin(filename.c_str());
        int a, b;
        while(fin >> a){
            fin >> b;
            data.elementAt(list_ptr->rowNumOf(a),list_ptr->rowNumOf(b)) = 1;
        }
        fin.close(); return;
    }

    //display adjacent matrix.
    void display(){
        for(int i=0;i!=list_ptr->size();++i){
            std::cout << list_ptr->idOfRow(i) << ',';
        }
        std::cout << std::endl;
        data.display();
        std::cout << std::endl;
    }

    //查询用户的直接和间接朋友数量
    int numOfFriend(int id){
        const int r = list_ptr->rowNumOf(id);
        if(r==-1){
            throw std::domain_error("in class SocialNet::Relationship::numOfFriend "
            "unrecogized user");
        }
        int count = 0;
        for(int col=0;col!=list_ptr->size();++col){
            count += data.elementAt(r,col);
        }
        return count;
    }
};

};

#endif//RELATIONSHIP_HPP
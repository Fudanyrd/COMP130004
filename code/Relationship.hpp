#pragma once
#ifndef RELATIONSHIP_HPP
#define RELATIONSHIP_HPP

#include "Matrix.hpp"
#include "User.hpp"
#include <fstream>
#include <queue>

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

    //计算两个用户之间的最短社交距离;使用广度优先搜索.
    //若不存在间接朋友(即没有路径),返回-1.
    int distanceOf(int id1,int id2){
        const int r1 = list_ptr->rowNumOf(id1),r2=list_ptr->rowNumOf(id2);
        if(r1==r2) return 0;
        //如果两个用户是直接的朋友，他们之间的社交距离就是1；
        if(data.elementAt(r1,r2)) return 1; 

        int* pathTo = new int[list_ptr->size()];
        bool* visited = new bool[list_ptr->size()];
        for(int i=0;i!=list_ptr->size();++i){
            pathTo[i] = -1; visited[i] = false;
        }
        visited[r1] = true;     //from r1, try to find r2.
        std::queue<int> path;
        path.push(r1);
        int temp;
        while(!path.empty()){
            temp = path.front(); path.pop();
            if(temp==r2){
                break;
            }            
            for(int col=0;col!=list_ptr->size();++col){
                if(data.elementAt(temp,col)&&!visited[col]){
                    visited[col] = true; path.push(col); pathTo[col] = temp;
                }
            }
        }
        if(!visited[r2]){
            //r2 is not marked, so there's no path between r1 and r2.
            return -1;
        }
        int count = 0;
        temp = pathTo[r2];
        while(temp>=0){
            temp = pathTo[temp]; ++count;
        }
        return count;
    }
};

};

#endif//RELATIONSHIP_HPP
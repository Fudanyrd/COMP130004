#pragma once
#ifndef RELATIONSHIP_HPP
#define RELATIONSHIP_HPP

// it is your choice which matrix lib to use.
// #include "Matrix.hpp"
#include "Parallel.h"
#include "User.hpp"
#include <fstream>
#include <queue>

/*社交网络名称空间.*/
namespace SocialNet{

/*布尔矩阵表示的图结果,节点代表用户,边代表用户之间的
 *关系.
*/

//will be useful to find indirect friend.
struct tuple{
    int level;      //the level of a friend
    int rowNum;     //row number of current user visited.
    tuple():level(0),rowNum(-1){}
    tuple(int r,int l=0):level(l),rowNum(r){}
};

class Relationship{
private:
    Matrix data;
    SocialNet::UserList* list_ptr;

    //单个节点的聚集系数,给定行号
    double coefficient(int r){
        //step 1: find all its neighbors, time: O(N), space O(N).
        std::vector<int> neighbors;
        for(int c=0;c!=list_ptr->size();++c){
            if(data.elementAt(r,c)) neighbors.push_back(c);
        }
        //step 2: count all edges and possible edges.
        //time: O(N^2). space: O(1)
        long count = 0, total = 0;
        if(neighbors.size()<=1) return 0.0;//only have one neighbor
        for(unsigned int i=0;i!=neighbors.size();++i){
            for(unsigned int j=i+1;j<neighbors.size();++j){
                count+=data.elementAt(neighbors[i],neighbors[j]);
                total+=1.0;
            }
        }
        return (double)count/(double)total;
    }
    //get the number of common friends for user id1 and id2.
    //return -1 if (a) id1==id2; (b) id1 and id2 are direct friends
    //time: O(N). space: O(1)
    int commonNum(int id1,int id2){
        const int r1=id1,r2=id2;
        if(id1==id2||data.elementAt(r1,r2)) return -1;
        int count = 0;
        for(int c=0;c!=list_ptr->size();++c){
            count+=data.elementAt(r1,c)&data.elementAt(r2,c);
        }
        return count;
    }
public:
    Relationship(){
        list_ptr = new UserList();
    }
    void findCommonFriend(int id1,int id2){
        const int r1=list_ptr->rowNumOf(id1),r2=list_ptr->rowNumOf(id2);
        if(id1==id2||data.elementAt(r1,r2)){
            std::cout << -1 << std::endl; return;
        }
        for(int c=0;c!=list_ptr->size();++c){
            if(data.elementAt(r1,c)&&data.elementAt(r2,c)){
                std::cout << list_ptr->idOfRow(c) << ',';
            }
        }
        std::cout << std::endl;
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
            data.elementAt(list_ptr->rowNumOf(b),list_ptr->rowNumOf(a)) = 1;
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

    //查询用户的直接朋友数量
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
    //查询用户的间接朋友数量,广度优先搜索找出所有朋友数量减去
    //直接朋友数量.
    int numOfSubFriend(int id){
        const int r1 = list_ptr->rowNumOf(id);
        int count = 0;
        bool* visited = new bool[list_ptr->size()];
        for(int i=0;i!=list_ptr->size();++i){
            visited[i] = false;
        }
        visited[r1] = true;     //from r1, try to find r2.
        SocialNet::tuple temp(r1,0);
        std::queue<SocialNet::tuple> path;
        path.push(temp);
        while(!path.empty()){
            temp = path.front(); path.pop();
            if(temp.level<2){
                for(int col=0;col!=list_ptr->size();++col){
                    if(!visited[col]&&data.elementAt(temp.rowNum,col)){
                        path.push(SocialNet::tuple(col,temp.level+1));
                        visited[col] = true;
                    }
                }
            }
            if(temp.level==2) ++count;
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
            delete[] pathTo; delete[] visited;
            return -1;
        }
        int count = 0;
        temp = pathTo[r2];
        while(temp>=0){
            temp = pathTo[temp]; ++count;
        }
        delete[] pathTo; delete[] visited;
        return count;
    }

    //计算网络中的“超级连接者”,也即拥有最多直接朋友的用户.
    //返回超级连接者id的向量,如果有多个均压进向量.
    //时间复杂度:O(n^2).
    std::vector<int> superUsers(){
        const int sz = list_ptr->size();
        int* counts = new int[list_ptr->size()];
        for(int i=0;i!=sz;++i) counts[i] = 0;
        for(int r=0;r!=sz;++r){
            for(int c=0;c!=sz;++c){
                counts[r]+=data.elementAt(r,c);
            }
        }

        int maxValue = 0;
        for(int r=0;r!=sz;++r){
            if(counts[r]>maxValue) maxValue = counts[r];
        }
        std::vector<int> res;
        for(int r=0;r!=sz;++r){
            if(counts[r]==maxValue) res.push_back(list_ptr->idOfRow(r));
        }
        return res;
    }

    //网络中朋友三角数量,也即即三个人互为朋友.
    //考虑矩阵乘法实现,邻接矩阵的3次幂对角元即为
    //从某一元素出发经长度为3的路径回到自身的路径数目.
    //同一三角形被重复计算了6次.
    int triangles(){
        Matrix res = data.productOf(data);
        return res.traceOfProductOf(data)/6;
    }
    //分析网络的平均聚集系数（Clustering Coefficient）
    //time: O(N^3), space: O(N^2)
    double clusteringCoefficient(){
        double res = 0.0;
        for(int i=0;i!=this->list_ptr->size();++i){
            res += this->coefficient(i);
        }
        return res/list_ptr->size();
    }

    //针对任一用户，基于共同朋友数量，向其推荐三个最有可能的潜在朋友
    std::vector<int> recommodations(int id){
        const int r = list_ptr->rowNumOf(id);
        std::vector<int> res;
        int* dat = new int[list_ptr->size()];
        for(int i=0;i!=list_ptr->size();++i){
            dat[i] = this->commonNum(r,i);
        }
        int maxValue, c;
        for(int i=0;i!=3;++i){
            maxValue = dat[0]; c = 0;
            for(int j=0;j!=list_ptr->size();++j){
                if(maxValue<dat[j]){
                    maxValue = dat[j]; c = j;
                }
            }
            dat[c] = -109;  //visited.
            res.push_back(list_ptr->idOfRow(c));
        }
        delete[] dat;
        return res;
    }
};

};

#endif//RELATIONSHIP_HPP
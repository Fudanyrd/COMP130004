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
    SocialNet::UserList list;
public:
    Relationship(){}
};

};

#endif//RELATIONSHIP_HPP
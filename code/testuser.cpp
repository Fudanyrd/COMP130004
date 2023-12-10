/*
    this is a test for SocialNet::UserList.
    simply ignoring it will be fine.
*/

#include "User.hpp"
using SocialNet::UserList;
#include <iostream>
using namespace std;

int main(int argc,char** argv){
    string filename="sample.txt";
    UserList list;
    list.load(filename);

    int N=4;
    if(N!=list.size()){
        cout << list.size() << endl;
        cout << "size mismatch" << endl;
        return 9;
    }
    for(int i=0;i!=N;++i){
        cout << list.idOfRow(i) << ',';
    }   cout << endl;

    for(int i=0;i!=N;++i){
        cout << list.rowNumOf(i) << ',';
    }   cout << endl;

    return 0;
}
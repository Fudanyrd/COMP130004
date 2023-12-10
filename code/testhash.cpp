/*
    a simple test for HashTable class.
    Simply ignoring it will be fine.
*/

#include "HashTable.hpp"
#include <iostream>
using namespace std;
using namespace SocialNet;

int main(int argc,char** argv){
    HashTable table(3u);
    table.insert(0,34);
    table.insert(1,98);
    table.insert(2,50);
    table.insert(3,12);
    table.insert(4,77);
    table.insert(5,101);
    table.insert(2,-44);//false
    table.insert(4,-98);//false

    for(int i=0;i!=8;++i){
        cout << table.rowNumOf(i) << endl;
    }

    return 0;
}
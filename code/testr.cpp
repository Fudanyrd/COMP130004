/*
    this is a test for class SocialNet::Relationship.
    Simply ignoring it will be fine.
*/

#include "Relationship.hpp"
using namespace std;
using namespace SocialNet;

int main(int argc,char** argv){
    Relationship r1;
    r1.load("sample1.txt");
   int N1 = 4;
   for(int i=0;i!=N1;++i){
       cout << r1.numOfFriend(i) << ','; //should always be 3.
   }   cout << endl;

    Relationship r2;
    r2.load("sample2.txt");
    int N2 = 8;
    for(int i=0;i!=N2;++i){
        cout << r2.numOfFriend(i) << ',';
    }   cout << endl;
    //2,1,1,2,2,2,1,1 expected.

    Relationship r3;
    r3.load("sample3.txt");
    int N3 = 6;
    for(int i=0;i!=N3;++i){
        cout << r3.numOfFriend(i) << ',';
    }   cout << endl;
    //2,3,2,2,3,2 expected.

    return 0;
}
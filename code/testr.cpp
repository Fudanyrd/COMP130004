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
   for(int i=0;i!=N1;++i){
       cout << r1.distanceOf(i,0) << ',';
   }  cout << endl;         //expected 0,1,1,1

    Relationship r2;
    r2.load("sample2.txt");
    int N2 = 8;
    for(int i=0;i!=N2;++i){
        cout << r2.numOfFriend(i) << ',';
    }   cout << endl;
    //2,1,1,2,2,2,1,1 expected.
   cout << r2.distanceOf(1,2) << ',' << r2.distanceOf(3,6) << endl; //2,-1 expected.


    Relationship r3;
    r3.load("sample3.txt");
    int N3 = 6;
    for(int i=0;i!=N3;++i){
        cout << r3.numOfFriend(i) << ',';
    }   cout << endl;
    //2,3,2,2,3,2 expected.
    cout << r3.distanceOf(0,4) << ',' << r3.distanceOf(2,5) << endl; //2,3 expected.

    return 0;
}
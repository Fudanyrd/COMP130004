/*
    this is a test for class SocialNet::Relationship.
    Simply ignoring it will be fine.
*/

#include "Relationship.hpp"
#include <iomanip>
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

    Relationship r4;
    r4.load("sample4.txt");
    int N4 = 8;
    vector<int> res = r4.superUsers();
    for(int r=0;r!=(int)res.size();++r){
        cout << res[r] << ',';
    }   cout << endl;
    //0,5 or 5,0 expected.
    cout << r4.distanceOf(0,5) << ',' << r4.distanceOf(1,7) << endl;//2,4 expected.

    cout << r1.triangles() << endl;         //4 expected
    cout << r2.triangles() << endl;         //1 expected
    cout << r3.triangles() << endl;         //0 expected
    Relationship r5;
    r5.load("sample5.txt");
    int N5 = 11;
    cout << r5.triangles() << endl;     //6 expected.
    cout << r5.numOfFriend(1) << endl;  //2 expected.
    cout << r5.numOfSubFriend(1) << endl;  //11-2-1 = 8 expected.

    Relationship r6;
    r6.load("sample6.txt");
    cout << r6.triangles() << endl; //1 expected.
    cout << setiosflags(ios::fixed) << setprecision(2) << r6.clusteringCoefficient() << endl;//0.47 expected.

    Relationship r7;
    r7.load("sample7.txt");
    res = r7.recommodations(0);
    for(int i=0;i!=res.size();++i){
        cout << res[i] << ',';
    }   cout << endl;//7,3,12 or 7,12,3 expected

    Relationship r9;
    r9.load("sample9.txt");
    cout << r9.distanceOf(0,39) << endl;//7 expected.

    Relationship r10;
    r10.load("sample10.txt");
    cout << r10.triangles() << endl;//4 expected

    Relationship R;
    R.load("data.txt");
    R.findCommonFriend(432,500);

    return 0;
}
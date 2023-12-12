#include "Relationship.hpp"
using namespace SocialNet;
using namespace std;

int main(int argc,char** argv){
    const int N=5000;
    int** a = new int*[N];
    for(int i=0;i!=N;++i){
        a[i] = new int[N];
        for(int j=0;j!=N;++j){
            a[i][j]=0;
        }
    }

    ifstream fin("data.txt");
    int b,c;
    while(fin >> b >> c){
        a[b][c] = a[c][b] = 1;
    }
    fin.close();
    while(cin >> b >> c){
        if(a[b][c]){
            cout << "friends" << endl;
        }
        else cout << "not friends" << endl;
    }

    for(int i=0;i!=N;++i){
        delete[] a[i];
    }
    delete[] a;

    return 0;
}
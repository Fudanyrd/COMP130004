/*
    this is just a test for class Matrix to make sure that 
    Simply ignoring it is fine.
*/

#include "Matrix.hpp"
#include "Matrix.hpp"
using namespace std;

int main(int argc,char** argv){
    const int N=5;
    int dat[N][N]={
        {0,0,1,0,0},
        {0,1,0,1,1},
        {1,0,1,0,0},
        {0,1,0,0,1},
        {0,1,0,1,1}
    };
    Matrix m(N);
    for(int i=0;i!=N;++i){
        for(int j=0;j!=N;++j){
            m.elementAt(i,j) = dat[i][j];
        }
    }
    Matrix s = m.productOf(m);
    Matrix t = m.productOf(s);
    m.display();
    cout << endl;
    s.display();
    cout << endl;
    t.display();

//    system("pause");
    return 0;
}
#pragma once
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

/*布尔矩阵类,用于保存用户关系;利用对称矩阵的上三角存储实现,
 *与课本实现有所不同,仍用二维数组表示
*/
class Matrix{
private:
    int** data; //矩阵元素
    unsigned int rows;
public:
    //initializer
    Matrix():rows(0),data(0){}
    Matrix(unsigned int r):rows(r),data(new int*[r]){
        for(int i=0;i!=r;++i) data[i] = new int[r-i];
    }
    Matrix(const Matrix& m){
        this->rows = m.rows;
        data = new int*[rows];
        for(int i=0;i!=m.rows;++i){
            data[i] = new int[m.rows-i];
            for(int j=0;j!=m.rows-i;++j) data[i][j] = m.data[i][j];
        }
    }
    //destructor
    ~Matrix(){
        for(int i=0;i!=this->rows;++i) delete[] data[i];
        delete[] data;
    }

    //copy constructor
    Matrix& operator=(const Matrix& m){
        //assume that m.rows == this->rows.
        this->rows = m.rows;
        for(int i=0;i!=m.rows;++i){
            data[i] = new int[m.rows-i];
            for(int j=0;j!=m.rows-i;++j) data[i][j] = m.data[i][j];
        }
        return *this;
    }

    void construct(int N){
        this->rows = N;
        data = new int*[N];
        for(int i=0;i!=N;++i){
            data[i] = new int[N-i];
            for(int j=0;j!=N-i;++j){
                data[i][j]=0;
            }
        }
    }

    unsigned int numRows()const{ return this->rows; }

    /* return the matrix element at row r and column c.*/
    int& elementAt(int r=0,int c=0){
        if(r<=c) return data[r][c-r]; 
        else return data[c][r-c];
    }
    const int& elementAt(int r=0,int c=0)const{
        if(r<=c) return data[r][c-r]; 
        else return data[c][r-c];
    }

    //calculate the product of itself and m.
    //time complexity: O(n^3)
    //space complexity: O(n^2)
    Matrix productOf(const Matrix& m)const{
        Matrix res(this->rows);
        int elem = 0;
        for(int i=0;i!=rows;++i){
            for(int j=i;j!=rows;++j){
                elem = 0;
                for(int k=0;k!=rows;++k){
                    elem += this->elementAt(i,k)*m.elementAt(k,j);
                }
                res.data[i][j-i] = elem;
            }
        }
        return res; 
    }

    //for debugging, output a matrix to see if it matches expectation.
    void display()const{
        for(int r=0;r!=rows;++r){
            for(int c=0;c!=rows;++c){
                std::cout << elementAt(r,c) << ' ';
            }
            std::cout << std::endl;
        }
    }
};

#endif//MATRIX_HPP
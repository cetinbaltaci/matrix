#include <iostream>
#include <cassert>
#include "Matrix.h"

using namespace std;

template <typename T>
Matrix<T>::Matrix(unsigned int rowcount, unsigned int colcount) 
{
    createMatrixArray(rowcount, colcount);
};

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &m) {
    mCells = m.mCells;
    mRowCount = m.mRowCount;
    mColCount = m.mColCount;
}

template <typename T>
Matrix<T>::Matrix(const vector<vector<T>> &vec)
{    
    createMatrixArray(vec.size(), vec[0].size());
    for(unsigned int i = 0 ; i < mRowCount ; i++) {
        mCells[i] = vec[i];
    }
}

template <typename T>
Matrix<T>::~Matrix() {
    for (unsigned int i = 0 ; i < mRowCount ; i++)
        mCells[i].clear();
    mCells.clear();
    mRowCount = mColCount = 0 ;
}

template <typename T>
void Matrix<T>::createMatrixArray(unsigned int rowcount, unsigned colCount) {
    mRowCount = rowcount ;
    mColCount = colCount;
    if (mRowCount == 0 || mColCount == 0 ) 
        throw MatrixException("Column count or row count can't be zero !") ;

    mCells = vector<vector<T>>(mRowCount);
    for (unsigned int i = 0 ; i < mRowCount; i++ ) {
        mCells[i] = vector<T>(mColCount);
        mCells[i] = { static_cast<T>(0)};
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &m)  {
    createMatrixArray(m.mRowCount, m.mColCount);

    for(unsigned int i = 0 ; i < mRowCount ; i++) {
        for(unsigned int j = 0 ; j < mColCount ; j++) {
            mCells[i][j] = m.mCells[i][j];
        }
    }

    return *this ;
}

template <typename T>
vector<T>& Matrix<T>::operator[](unsigned int row) {
    if (row >= mRowCount ) throw MatrixException("Out of range !");
    return mCells[row];
}

template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix<T> &m) {
    if (mRowCount != m.mRowCount || mColCount != m.mColCount ) 
        throw MatrixException("Both matrixes must have the same count of columns and rows in additional !"); 
    Matrix<T>res(mRowCount, mColCount);

    for(unsigned int i = 0 ; i < mRowCount ; i++ ) {
        for(unsigned int j = 0 ; j < mColCount ; j++ ) {
            res[i][j] = mCells[i][j] + m.mCells[i][j];
        }
    }
    
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator+ (const T v) {
    Matrix<T>res(mRowCount, mColCount);
    for(unsigned int i = 0 ; i < mRowCount ; i++ ) {
        for(unsigned int j = 0 ; j < mColCount ; j++ ) {
            res[i][j] = mCells[i][j] + v;
        }
    }
    return res ;  
}

template <typename T>
Matrix<T>& Matrix<T>::operator+= (const Matrix<T> &m) {
    (*this) = (*this) + m ;
    return (*this);
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T> &m) {
    if (mColCount != m.mRowCount) 
        throw MatrixException("Column count must be equal to row count of the the other matrix in multiplication !");

    Matrix<T>res(mRowCount, mColCount);
    for(unsigned int i = 0 ; i < mRowCount ; i++ ) {
        for(unsigned int j = 0 ; j < mColCount ; j++ )
            for(unsigned int k = 0 ; k < mRowCount ; k++ ) {
                res[i][j] += mCells[i][k] * m.mCells[k][j];
            }
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const T v)  {
    Matrix<T>res(mRowCount, mColCount);
    for(unsigned int i = 0 ; i < mRowCount ; i++ ) {
        for(unsigned int j = 0 ; j < mColCount ; j++ ) {

            res[i][j] = mCells[i][j] * v;
        }
    }
    return res ;  
}

template <typename T>
Matrix<T>& Matrix<T>::operator*= (const Matrix<T> &m) {
    (*this) = (*this) * m;
    return (*this);
}

template <typename T>
Matrix<T> Matrix<T>::operator- (const Matrix<T> &m) {
    if (mRowCount != m.mRowCount || mColCount != m.mColCount ) 
        throw MatrixException("Both matrixes must have the same count of columns and rows in additional !"); 
    Matrix<T>res(mRowCount, mColCount);

    for(unsigned int i = 0 ; i < mRowCount ; i++ ) {
        for(unsigned int j = 0 ; j < mColCount ; j++ ) {
            res[i][j] = mCells[i][j] - m.mCells[i][j];
        }
    }
    
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator- (const T v)  {
    Matrix<T>res(mRowCount, mColCount);
    for(unsigned int i = 0 ; i < mRowCount ; i++ ) {
        for(unsigned int j = 0 ; j < mColCount ; j++ ) {
            res[i][j] = mCells[i][j] - v;
        }
    }
    return res ;  
}

template <typename T>
Matrix<T>& Matrix<T>::operator-= (const Matrix<T> &m) {
    (*this) = (*this) - m ;
    return (*this);
}

template <typename T>
Matrix<T> Matrix<T>::operator/ (const Matrix<T> &m) {
    if (mRowCount != m.mRowCount || mColCount != m.mColCount ) 
        throw MatrixException("Both matrixes must have the same count of columns and rows in additional !"); 
    Matrix<T>res(mRowCount, mColCount);

    for(unsigned int i = 0 ; i < mRowCount ; i++ ) {
        for(unsigned int j = 0 ; j < mColCount ; j++ ) {
            res[i][j] =mCells[i][j] / m.mCells[i][j];
        }
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator/ (const T v)  {
    Matrix<T>res(mRowCount, mColCount);
    for(unsigned int i = 0 ; i < mRowCount ; i++ ) {
        for(unsigned int j = 0 ; j < mColCount ; j++ ) {
            double val = (double) mCells[i][j]  ;
            val /= v ;
            //if (val < 1E-14) val = 0.0;
            res[i][j] = val;
        }
    }
    return res ;  
}

template <typename T>
Matrix<T>& Matrix<T>::operator/= (const Matrix<T> &m) {
    (*this) = (*this) / m;
    return (*this);
}

template <typename T>
Matrix<T> Matrix<T>::getCoFactor(unsigned int p, unsigned int q) {
    if (mRowCount !=  mColCount ) 
        throw MatrixException("Matix must have the same count of columns and rows in adjoint !"); 
    
    unsigned int n = mRowCount;
    Matrix<T> res(n-1, n-1);
    unsigned int i = 0, j = 0;
    
    for (unsigned int row = 0; row < n; row++) {
        for (unsigned int col = 0; col < n; col++) {
            if (row != p && col != q)  {
                res[i][j++] = mCells[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
    return res ;
}

template <typename T>
T Matrix<T>::determinant() {
    return determinant_(mRowCount);
}

template <typename T>
T Matrix<T>::determinant_(unsigned int n) {
    T D = 0;
    if (n == 1)
        return mCells[0][0];
    int sign = 1;
    for (unsigned int f = 0; f < n; f++) {
        Matrix<T> temp = getCoFactor(0, f);
        D += sign * mCells[0][f] * temp.determinant_(n-1);
        sign = -sign;
    }
    return D;
}

template <typename T>
Matrix<T> Matrix<T>::adjoint(){
    if (mRowCount !=  mColCount ) 
        throw MatrixException("Matix must have the same count of columns and rows in adjoint !"); 
    
    unsigned int n = mRowCount ;
    Matrix<T> res(n, n);
    if ( n == 1) {
        res[0][0] = 1;
        return res;
    }
    for (unsigned int i=0; i<n; i++){
        for (unsigned int j=0; j<n; j++){
            Matrix<T> temp = getCoFactor(i, j);
            int sign = ( (i+j)%2 == 0 )? 1: -1;
            res[j][i] = (sign) * temp.determinant();
        }
    }
    return res ;
}

template <typename T>
Matrix<T> Matrix<T>::inverse() {
    if (mRowCount !=  mColCount ) 
        throw MatrixException("Matix must have the same count of columns and rows in inverse !"); 

    T det = determinant();
    if (det == 0)
        throw MatrixException("Singular matrix, can't find its inverse !"); 
 
    return adjoint() / det;
}

template <typename T>
unsigned int Matrix<T>::getRowCount() const{
    return mRowCount;
}

template <typename T>    
unsigned int Matrix<T>::getColCount() const {
    return mColCount;
}


template class Matrix<int>;
template class Matrix<short>;
template class Matrix<double>;
template class Matrix<float>;

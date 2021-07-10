#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <sstream>
#include <vector>

using namespace std;

class MatrixException: public exception {
private:
    string msg ;
public:
    MatrixException(const string &msg_)
    {
        msg = string("MatrixException: ") ;
        msg += msg_;
    }    

    MatrixException(const char *msg_)
    {
        msg = string("MatrixException: ") ;
        msg += string(msg_) ;
    }

    virtual ~MatrixException() noexcept {}

    virtual const char *what() const throw () {
        return msg.c_str();
    }
};


template<typename T> 
class Matrix {
private:
    unsigned int mRowCount ;
    unsigned int mColCount ;
    vector<vector<T>> mCells;

    void createMatrixArray(unsigned int rowcount, unsigned colCount) ;
    T determinant_(unsigned int n) ; 
    Matrix<T> getCoFactor(unsigned int p, unsigned int q);

public:
    
    Matrix(unsigned int rowcount, unsigned int colcount) ;
    Matrix(const Matrix<T> &m) ;
    Matrix(const vector<vector<T>> &vec) ;

    ~Matrix() ;

    vector<T>& operator[](unsigned int row);
    Matrix<T>& operator= (const Matrix<T> &m) ;
    

    Matrix<T> operator+ (const Matrix<T> &m) ;
    Matrix<T> operator* (const Matrix<T> &m) ;
    Matrix<T> operator- (const Matrix<T> &m) ;
    Matrix<T> operator/ (const Matrix<T> &m) ;

    Matrix<T> operator+ (const T v) ;
    Matrix<T> operator* (const T v) ;
    Matrix<T> operator- (const T v) ;
    Matrix<T> operator/ (const T v) ;


    Matrix<T>& operator+= (const Matrix<T> &m) ;
    Matrix<T>& operator*= (const Matrix<T> &m) ; 
    Matrix<T>& operator-= (const Matrix<T> &m) ;
    Matrix<T>& operator/= (const Matrix<T> &m) ; 
    
    Matrix<T> adjoint();   
    T determinant() ; 
    Matrix<T> inverse();

    unsigned int getRowCount() const;
    unsigned int getColCount() const;

    friend ostream& operator << (ostream &out , const Matrix<T> &m) {
        if (m.mRowCount == 0 || m.mColCount == 0 ) {
            out << "<EMPTY>" ;
        } else {
            for(unsigned int i = 0 ; i < m.mRowCount; i++) {
                for(unsigned int j = 0 ; j < m.mColCount; j++) {
                    if (typeid(T) == typeid(double) || typeid(T) == typeid(float))
                        out << setw(8) << right << fixed << setprecision(4) << m.mCells[i][j] << "\t";
                    else 
                        out << setw(8) << right << fixed <<  m.mCells[i][j] << "\t";
                }
                out << endl ;
            }
        }
        return out ;
    }
};

#endif //CBMATRIX_H
#include <iostream>
#include "Matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<vector<float>> vec = {{5, -2, 2, 7},
                    {1, 0, 0, 3},
                    {-3, 1, 5, 0},
                    {3, -1, -9, 4}} ;
    
    Matrix<float> matrixA(vec);
    cout << "matrixA: \n" << matrixA << endl ;

    Matrix<float> matrixB(4,4);

    
    for(unsigned int i= 0 ; i < matrixB.getRowCount(); i++)
        for(unsigned int j= 0 ; j < matrixB.getColCount(); j++)
            matrixB[i][j] = (i + 1 )* 10 + j + .3;

    cout << "MATRIX : A" << endl ;
    cout << matrixA << endl ;

    cout << "MATRIX : B" << endl ;
    cout << matrixB << endl ;

    try {
        Matrix<float> matrixC = matrixA + matrixB ;
        cout << "MATRIX : C = A + B" << endl ;
        cout << matrixC << endl ;
    }catch (const MatrixException &e){
        cout << e.what() << endl ;
    }

    try {
        Matrix<float> matrixD = matrixA * matrixB ;
        cout << "MATRIX : D = A * B" << endl ;
        cout << matrixD << endl ;
    }catch (const MatrixException &e){
        cout << e.what() << endl ;
    }

    try {
        Matrix<float> matrixAdjoint =  matrixA.adjoint();
        cout << "MATRIX : ADJOINT  A: " << endl ;
        cout << matrixAdjoint << endl ;
    }catch (const MatrixException &e){
        cout << e.what() << endl ;
    }

    cout << "MATRIX : A DETERMINANT : " << matrixA.determinant() << endl ;

    try {
        Matrix<float> matrixInv =  matrixA.inverse();
        cout << "MATRIX : A INVERSE :" << endl ;
        cout << matrixInv << endl ;

        Matrix<float> matrixIdentity =  matrixA * matrixInv ;      
        cout << "MATRIX : A IDENTITY :" << endl ;
        cout << matrixIdentity << endl ;
    }catch (const MatrixException &e){
        cout << e.what() << endl ;
    }

    cout << "FINISHED\n";
    return EXIT_SUCCESS;
}
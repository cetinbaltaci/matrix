#include <iostream>
#include <cmath>
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
    const string varName = string("xyzwq") ;
    const string vars    = string("ABCDE") ;


    int eqCount = 0 ; 
    do {
        cout << "Enter Equation Count (2..5):" << endl ;
        cin >> eqCount ;
    } while (!(eqCount > 1 && eqCount < 6 )) ;

    for (int i = 0 ; i < eqCount ; i++)
        cout << ((i > 0 ) ? " + " : "") <<  vars[i] << varName[i]  ;
    cout << " = R " << endl ;


    Matrix<double> matrixK(eqCount, eqCount);
    Matrix<double> matrixR(eqCount, 1);
    

    for(unsigned int i = 0 ; i < matrixK.getRowCount(); i++  ) {
        for(unsigned int j = 0 ; j < matrixK.getColCount(); j++  ) {
            cout << (i + 1) << ". EQUATION -> " <<  vars[j] << varName[j] << " ----- " <<  vars[j] <<" = " ;
            cin >> matrixK[i][j] ;
        }
        cout << (i + 1) << ". EQUATION -> R = " ;
        cin >> matrixR[i][0];
        cout << endl ;
    }

    cout << "EQUATIONS:" << endl; 
    for(unsigned int i = 0 ; i < matrixK.getRowCount(); i++  ) {
        for(unsigned  int j = 0 ; j < matrixK.getColCount(); j++  ) {
            cout << ( ( j > 0  && matrixK[i][j]  >= 0 ) ? " +" : " " ) << matrixK[i][j] << varName[j]  ;
        }
        cout << " = " <<  matrixR[i][0] << endl ;
    }



    cout << "\nSOLVING....\n" ;
    try{
        Matrix<double> matrixKInverse = matrixK.inverse();
        Matrix<double> matrixResult =  matrixKInverse  * matrixR ;
        cout << "matrixResult: " << matrixResult << endl;
        cout << "Result -> \t" ;
        for(unsigned  int i = 0 ; i < matrixR.getRowCount(); i++  ) {
            cout << "\t" << varName[i]  << "= " << matrixResult[i][0] ;
        }
        cout << endl ;
    }catch (const MatrixException &e){
        cout << e.what() << endl ;
    }


    cout << "FINISHED\n";
    return EXIT_SUCCESS;
}

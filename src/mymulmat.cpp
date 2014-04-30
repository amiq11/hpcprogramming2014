#include "mymulmat.h"
#include <iostream>

MyMulMat::MyMulMat()
{
    std::cout << "mymul constructed" << std::endl;
}

MyMulMat::~MyMulMat()
{
    std::cout << "mymul destructed" << std::endl;
}
void MyMulMat::init(int n, int m, int k,
          int *la, int *lb, int *lc,
          double **A, double **B, double **C)
{
    std::cout << "mymul init" << std::endl;
    *la = k; *lb = m; *lc = m;
    *A = new double[n*k]();
    *B = new double[k*m]();
    *C = new double[n*m]();
    this->n = n; this->m = m; this->k = k;
    this->A = *A; this->B = *B; this->C = *C;
    return;
}

void MyMulMat::multiply()
{
    std::cout << "mymul multiply" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int l = 0; l < k; l++ ) {
                C[i*m+j] += A[i*k+l] * B[l*m+j];
            }
        }
    }
    return;
}

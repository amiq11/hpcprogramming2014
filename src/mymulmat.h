#pragma once
#include "measure/imulmat.h"
class MyMulMat : public IMulMat
{
public:
    MyMulMat();
    ~MyMulMat();
    void init(int n, int m, int k,
              int *la, int *lb, int *lc,
              double **A, double **B, double **C);
    void multiply();
private:
    int n, m, k;
    double *A, *B, *C;
};


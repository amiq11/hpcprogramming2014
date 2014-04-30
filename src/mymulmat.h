#pragma once
#include "measure/imulmat.h"
class MyMulMat : public IMulMat
{
public:
    MyMulMat();
    ~MyMulMat();
    void init(int, int, int);
    void multiply(int, int, int, double *, double *, double *);
};


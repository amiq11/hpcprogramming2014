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
void MyMulMat::init(int j, int k, int l) {
    std::cout << "mymul init" << std::endl;
    return;
}

void MyMulMat::multiply(int j, int k, int l,
                        double *A, double *B, double *C)
{
    std::cout << "mymul mul" << std::endl;
    return;
}

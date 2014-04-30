#pragma once

class IMulMat {
public:
    virtual void init(int, int, int) = 0;
    virtual void multiply(int, int, int, double *, double *, double *) = 0;
};

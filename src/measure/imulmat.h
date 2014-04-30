#pragma once

class IMulMat {
public:
    virtual void init(int, int, int,
                      int *, int *, int *,
                      double **, double **, double **) = 0;
    virtual void multiply() = 0;
};

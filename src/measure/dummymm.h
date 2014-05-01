#ifndef DUMMYMM_H
#define DUMMYMM_H

class DummyMM : public IMulMat
{
public:
    void init(int n, int m, int k,
              int *la, int *lb, int *lc,
              double **A, double **B, double **C) { return };
    void multiply() { return };
};

#endif

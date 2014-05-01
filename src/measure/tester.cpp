#include <iostream>
#include <fstream>
#include <memory>
#include <sys/time.h>
#include <math.h>
#include "tester.h"
#include "dataset.h"
#include "imulmat.h"

using namespace std;

#ifndef MMCLASS
#  define MMCLASS DummyMM
#  include "dummymm.h"
#endif

Tester::Tester()
{
    // cout << "Tester constructed" << endl;
}

Tester::~Tester()
{
    // cout << "Tester destructed" << endl;
}

void Tester::run()
{
    cout << "# 走るぜ(Tester::run())" << endl;
    shared_ptr<IMulMat> mm (new MMCLASS());
    // mm->init(0, 1, 2);
    // mm->multiply(0, 1, 2, nullptr, nullptr, nullptr);

    uint32_t n, m, k;
    int la, lb, lc;
    double *A, *B, *C;

    cout << "# <Problem 0> " << endl;
    // Prepare dataset
    Dataset dataset;
    dataset.prepare(Dataset::square, n, m, k);
    // Allocate the spaces of matrix
    mm->init(n, m, k, &la, &lb, &lc, &A, &B, &C);
    // Set A, B, C
    dataset.set(la, lb, lc, A, B, C);
    
    // Measure
    uint64_t before, after;
    before = getDTime();
    mm->multiply();
    after = getDTime();

    // Check the answer
    int wcount = dataset.check(C);

    // Print result
    uint64_t flop = 2ULL * n * m * k;
    double gflops = (double)flop/(after-before)*1E-3;
    cout << "# Elapsed: " << (double)(after-before)/1E3 << " [ms]" << endl;
    cout << "# Flops:   " << gflops << " [GFLOPS]" << endl;
    cout << "# Wrong:   " << wcount << " / " << n*m << endl; 
}

uint64_t Tester::getDTime()
{
    struct ::timeval tv;
    ::gettimeofday(&tv, NULL);
    return tv.tv_sec*1E6 + tv.tv_usec;
}

#include <iostream>
#include <fstream>
#include <memory>
#include <sys/time.h>
#include <math.h>
#include "tester.h"
#include "imulmat.h"

using namespace std;

#ifndef MMCLASS
#  define MMCLASS DummyMM
#  include "dummymm.h"
#endif

Tester::Tester()
{
    cout << "Tester constructed" << endl;
}

Tester::~Tester()
{
    cout << "Tester destructed" << endl;
}

void Tester::run()
{
    cout << "走るぜ(Tester::run())" << endl;
    shared_ptr<IMulMat> mm (new MMCLASS());
    // mm->init(0, 1, 2);
    // mm->multiply(0, 1, 2, nullptr, nullptr, nullptr);

    int32_t n, m, k;
    int la, lb, lc;
    double *A, *B, *C;

    cout << "<Problem 0> " << endl;
    // Prepare dataset
    ifstream ifs("data/test.dat");
    ifs.read((char*)(&n), sizeof(uint32_t));
    ifs.read((char*)(&m), sizeof(uint32_t));
    ifs.read((char*)(&k), sizeof(uint32_t));
    cout << "n=" << n << " m=" << m << " k=" << k << endl;
    // Allocate the spaces of matrix
    mm->init(n, m, k, &la, &lb, &lc, &A, &B, &C);
    // Fill in A, B, C
    for ( int i = 0; i < n; i++ ) {
        ifs.read((char*)(A+i*la), sizeof(double)*k);
    }
    for ( int i = 0; i < k; i++ ) {
        ifs.read((char*)(B+i*lb), sizeof(double)*m);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            C[i*m+j] = 0;
        }
    }

    // Measure
    uint64_t before, after;
    before = getDTime();
    mm->multiply();
    after = getDTime();
        
    // Check Answer
    double *ans = new double[n*m]();
    ifs.read((char*)ans, sizeof(double)*n*m);
    int wcount = 0;
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < m; j++ ) {
            if ( fabs(C[i*lc+j] - ans[i*m+j]) > 1E-6 ) {
                cerr << "WRONG!: "
                     << "C(" << i << ", " << j << ") != "
                     << "Ans(" << i << ", " << j << ") :: "
                     << "C = " << C[i*lc+j] << ", "
                     << "Ans = " << ans[i*m+j] << endl;
                wcount++;
            }
        }
    }
    uint64_t flop = 2ULL * n * m * k;
    double gflops = (double)flop/(after-before)*1E-3;
    cout << "Elapsed: " << (double)(after-before)/1E3 << " [ms]" << endl;
    cout << "Flops:   " << gflops << " [GFLOPS]" << endl;
    cout << "Wrong:   " << wcount << " / " << n*m << endl; 
}

uint64_t Tester::getDTime()
{
    struct ::timeval tv;
    ::gettimeofday(&tv, NULL);
    return tv.tv_sec*1E6 + tv.tv_usec;
}

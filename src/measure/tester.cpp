#include <iostream>
#include <fstream>
#include <memory>
#include <sys/time.h>
#include <math.h>
#include "tester.h"
#include "dataset.h"
#include "imulmat.h"
#include "cmdline.h"

using namespace std;

#ifndef MMCLASS
#  define MMCLASS DummyMM
#  include "dummymm.h"
#endif

#ifndef VERSION
#  define VERSION undefined
#endif

Tester::Tester()
{
    // cout << "Tester constructed" << endl;
}

Tester::~Tester()
{
    // cout << "Tester destructed" << endl;
}

void Tester::_run(Dataset::DataType type)
{
    cout << "# 走るぜ(Tester::run())" << endl;
    shared_ptr<IMulMat> mm (new MMCLASS());
    
    uint32_t n, m, k;
    int la, lb, lc;
    double *A, *B, *C;
    cout << "# <Problem 0> " << endl;
    
    // Prepare dataset
    Dataset dataset;
    dataset.prepare(type, n, m, k);
    // Allocate the spaces of matrix
    mm->init(n, m, k, &la, &lb, &lc, &A, &B, &C);
    // Set A, B, C
    dataset.set(la, lb, lc, A, B, C);
    
    // Measure
    uint64_t before, after;
    before = getus();
    mm->multiply();
    after = getus();

    // Check the answer
    int wcount = dataset.check(C);

    // Print result
    uint64_t flop = 2ULL * n * m * k;
    double gflops = (double)flop/(after-before)*1E-3;
    cout << "# Elapsed: " << (double)(after-before)/1E3 << " [ms]" << endl;
    cout << "# Flops:   " << gflops << " [GFLOPS]" << endl;
    cout << "# Wrong:   " << wcount << " / " << n*m << endl; 
}

void Tester::run()
{
    _run(Dataset::square);
    
}

void Tester::run(int argc, char *argv[])
{
    Dataset::DataType type = Dataset::square;
    cmdline::parser p;
    p.add<string>("type", 't', "type of input matrix (square, mv, symm, trmm, hemm)", false);
    p.add("help", 'h', "print help");
    p.add("version", 'v', "print version");

    // help
    if (!p.parse(argc, argv)||p.exist("help")) {
        cout << p.error_full() << p.usage();
        return;
    }

    if (p.exist("version")) {
        cout << "MulMat Tester -- version: " << VERSION << endl;
        cout << "by Makoto Shimazu" << endl;
        return;
    }

    if (p.exist("type")) {
        string typeName = p.get<string>("type");
        if (typeName == "square")      type = Dataset::square;
        else if (typeName == "mv")     type = Dataset::mv;
        else if (typeName == "symm")   type = Dataset::symm;
        else if (typeName == "trmm")   type = Dataset::trmm;
        else if (typeName == "hemm")   type = Dataset::hemm;
        else {
            cout << "Unknown type!" << endl;
            cout << p.usage();
            return;
        }
    }
    
    _run(type);
}

uint64_t Tester::getus()
{
    struct ::timeval tv;
    ::gettimeofday(&tv, NULL);
    return tv.tv_sec*1E6 + tv.tv_usec;
}

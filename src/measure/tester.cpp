#include <iostream>
#include <memory>
#include "tester.h"
#include "imulmat.h"

using namespace std;

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
    int n, m, k;

    for ( int ntest = 0; ntest < 3; ntest++ ) {
        n = 2; m = 2; k = 2;

        int la, lb, lc;
        double *A, *B, *C;
        mm->init(n, m, k, &la, &lb, &lc, &A, &B, &C);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                C[i*m+j] = 0;
            }
        }
        A[0] = 1; A[1] = 1;
        A[2] = 0; A[3] = 1;
        B[0] = 1; B[1] = 0;
        B[2] = 1; B[3] = 1;
        mm->multiply();
        // for (int i = 0; i < n; i++ ) {
        //     for (int j = 0; j < m; j++ ) {
        //         cout << C[i*m+j] << " ";
        //     }
        //     cout << endl;
        // }
    }
}

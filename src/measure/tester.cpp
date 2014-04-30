#include <iostream>
#include <memory>
#include "tester.h"
#include "imulmat.h"

using namespace std;

Tester::Tester()
{
    cout << "wei" << endl;
}

Tester::~Tester()
{
    cout << "foo" << endl;
}

void Tester::run()
{
    cout << "走るぜ" << endl;
    shared_ptr<IMulMat> mm (new MMCLASS());
    mm->init(0, 1, 2);
    mm->multiply(0, 1, 2, nullptr, nullptr, nullptr);
}

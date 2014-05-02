#pragma once

#include <iostream>
#include "dataset.h"

class Tester
{
public:
    Tester();
    ~Tester();
    void run();
    void run(int argc, char *argv[]);
private:
    void _run(Dataset::DataType);
    uint64_t getus();
};

#pragma once

#include <iostream>

class Tester
{
public:
    Tester();
    ~Tester();
    void run();
private:
    uint64_t getDTime();
};

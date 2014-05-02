#include "tester.h" 

int main( int argc, char *argv[] )
{
    try {
        Tester test;
        test.run(argc, argv);
    } catch (const char *ex) {
        std::cerr << "# ERROR! ( " << ex << " )" << std::endl;
    }
    return 0;
}

#include "tester.h" 
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

int main( int argc, char *argv[] )
{
    try {
        srand(getpid()*time(NULL));
        Tester test;
        test.run(argc, argv);
    } catch (const char *ex) {
        std::cerr << "# ERROR! ( " << ex << " )" << std::endl;
    }
    return 0;
}

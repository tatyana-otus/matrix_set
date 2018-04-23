//#define DEBUG_INFO_ALL

#include "function.h"


int main(int, char**)
{
    try
    {
        run_main(std::cout);  
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
//#define DEBUG_INFO_ALL

#include "function.h"


int main(int, char**)
{
    try
    {
        endless_sparse2Dmatrix(std::cout);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
#include "matrix.h"


void endless_sparse2Dmatrix(std::ostream& os = std::cout)
{
    using Matrix_2D =  Matrix<int, 0>;

    Matrix_2D matrix;


    for(auto i = 0; i <= 9; i++){
        matrix[i][i] = i;
        matrix[9 - i][i] = i;
    }     

    matrix.print_square(1, 1, 8, os);

    //matrix.sort();
    // output in sorted order
    matrix.print_non_empty(os);

    os << matrix.size() << std::endl;
}
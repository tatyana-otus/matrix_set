#include "matrix.h"
#include <algorithm>

template<typename T, T default_value, size_t dim>
void print_non_empty (const Matrix<T, default_value, dim>& m, std::ostream& os = std::cout)
{
    for(const auto & c: m)
    {
        std::array<size_t, dim> idx;
        T val;
        std::tie(idx, val) = c;

        std::for_each(idx.begin(), idx.end(), [&os](const auto &i){ os << i << " "; });
        os << val << std::endl;
    }
}


template<typename T, T default_value>
static void print_square(Matrix<T, default_value>& m, size_t row_up,  size_t col_left, 
                                               size_t row_down, size_t col_right, 
                                               std::ostream& os = std::cout)
{
    if((row_up > row_down) || (col_left > col_right))
        throw std::invalid_argument("Invalid index");

    for(auto i = row_up; i <= row_down; ++i){
        for(auto j = col_left; j <= col_right; ++j){
            os << m[i][j] << " ";
        } 
        os << "\n";   
    }
}


void run_main(std::ostream& os = std::cout)
{

    using Matrix_2D =  Matrix<int, 0>;

    Matrix_2D matrix;

    for(auto i = 0; i <= 9; i++){
        matrix[i][i] = i;
        matrix[9 - i][i] = i;
    }     

    print_square(matrix, 1, 1, 8, 8, os);

    print_non_empty(matrix, os);

    os << matrix.size() << std::endl;
}
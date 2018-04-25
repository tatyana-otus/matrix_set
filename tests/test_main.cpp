#include "lib.h"
#include <sstream>
#include "function.h"


#define BOOST_TEST_MODULE test_main

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp> 
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;


BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_version_valid)
{
    BOOST_CHECK( (major_version() >= 0) &&  (minor_version() >= 0) && (patch_version() >= 0) );
    BOOST_CHECK( (major_version() >  0) ||  (minor_version() >  0) || (patch_version() >  0) );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(test_suite_matrix)


BOOST_AUTO_TEST_CASE(base_check)
{
    Matrix<int, -1, 2> matrix_2D; 

    BOOST_CHECK(matrix_2D.size() == 0);

    auto a = matrix_2D[0][0];
    BOOST_CHECK(a == -1);
    BOOST_CHECK(matrix_2D.size() == 0);

    matrix_2D[100][100] = 314;
    BOOST_CHECK(matrix_2D[100][100] == 314);
    BOOST_CHECK(matrix_2D.size() == 1);
}


BOOST_AUTO_TEST_CASE(check_dim)
{
    Matrix<int, -1, 2> matrix_2D;

    BOOST_CHECK_NO_THROW(matrix_2D[0][0]);
    BOOST_CHECK_NO_THROW(matrix_2D[0][0] = 8);
    BOOST_CHECK_NO_THROW(matrix_2D[0]);

    //error at compile time
    //BOOST_CHECK_THROW   (matrix_2D[0][0][0],        std::invalid_argument);
    //BOOST_CHECK_THROW   (matrix_2D[0] = 8,          std::invalid_argument);
    //BOOST_CHECK_THROW   (std::cout << matrix_2D[0], std::invalid_argument);


    Matrix<int, -1, 3> matrix_3D; 

    BOOST_CHECK_NO_THROW(matrix_3D[0][0][0]);
    BOOST_CHECK_NO_THROW(matrix_3D[0][0][0] = 8);
    BOOST_CHECK_NO_THROW(matrix_3D[0][0]);

    //error at compile time
    //BOOST_CHECK_THROW   (matrix_3D[0][0][0][0],        std::invalid_argument);
    //BOOST_CHECK_THROW   (matrix_3D[0][0] = 8,          std::invalid_argument);
    //BOOST_CHECK_THROW   (std::cout << matrix_3D[0][0], std::invalid_argument);
}


BOOST_AUTO_TEST_CASE(test_run_main)
{
    std::stringstream oss;
    std::string out_data =
    "1 0 0 0 0 0 0 8 \n"
    "0 2 0 0 0 0 7 0 \n"
    "0 0 3 0 0 6 0 0 \n"
    "0 0 0 4 5 0 0 0 \n"
    "0 0 0 4 5 0 0 0 \n"
    "0 0 3 0 0 6 0 0 \n"
    "0 2 0 0 0 0 7 0 \n"
    "1 0 0 0 0 0 0 8 \n"
    "0 9 9\n"
    "1 1 1\n"
    "1 8 8\n"
    "2 2 2\n"
    "2 7 7\n"
    "3 3 3\n"
    "3 6 6\n"
    "4 4 4\n"
    "4 5 5\n"
    "5 4 4\n"
    "5 5 5\n"
    "6 3 3\n"
    "6 6 6\n"
    "7 2 2\n"
    "7 7 7\n"
    "8 1 1\n"
    "8 8 8\n"
    "9 9 9\n"
    "18\n";

    endless_sparse2Dmatrix(oss); // output in sorted order

    BOOST_CHECK( oss.str() == out_data );
}


BOOST_AUTO_TEST_CASE(print_3D)
{
    std::stringstream oss;
    std::string out_data =
    "0 0 0 0\n"
    "1 1 1 1\n"   
    "2 2 2 2\n"
    "3 3 3 3\n"
    "4 4 4 4\n";

    Matrix<int, -1, 3> matrix_3D; 

    for(auto i = 0; i < 5; i++)
        matrix_3D[i][i][i] = i;

    matrix_3D.print_non_empty(oss);

    BOOST_CHECK( oss.str() == out_data );
}


BOOST_AUTO_TEST_CASE(matrix_size_def_val)
{

    Matrix<int, -1, 3> matrix_3D; 

    BOOST_CHECK( matrix_3D.size() == 0 );

    matrix_3D[15][15][245] = -1;
    BOOST_CHECK( matrix_3D.size() == 0 );

    matrix_3D[15][15][245] = -10;
    BOOST_CHECK( matrix_3D.size() == 1 );
    auto a = matrix_3D[15][15][245];
    BOOST_CHECK( a == -10 );

    matrix_3D[15][15][245] = -8;
    matrix_3D[15][15][246] = -8;
    BOOST_CHECK( matrix_3D.size() == 2 );
    BOOST_CHECK( matrix_3D[15][15][245] == -8 );
    BOOST_CHECK( matrix_3D[15][15][246] == -8 );

    matrix_3D[15][15][245] = -1;
    BOOST_CHECK( matrix_3D.size() == 1 );
    matrix_3D[15][15][246] = -1;
    BOOST_CHECK( matrix_3D.size() == 0 );
}

BOOST_AUTO_TEST_SUITE_END()
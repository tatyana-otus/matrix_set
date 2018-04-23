project(test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_main_cli test_main.cpp)

target_include_directories(test_main_cli PRIVATE ../include)
target_include_directories(test_main_cli PRIVATE ${Boost_INCLUDE_DIR})

set_target_properties(test_main_cli PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

target_link_libraries(test_main_cli
  ${Boost_LIBRARIES}
  version
)

enable_testing()

add_test(test_version_valid      test_main_cli -t test_suite_main/test_version_valid)

add_test(test_base_check      test_main_cli -t test_suite_matrix/base_check)
add_test(test_check_dim       test_main_cli -t test_suite_matrix/check_dim)
add_test(test_run_main        test_main_cli -t test_suite_matrix/test_run_main)
add_test(test_print_3D        test_main_cli -t test_suite_matrix/print_3D)
add_test(test_matrix_size     test_main_cli -t test_suite_matrix/matrix_size_def_val)
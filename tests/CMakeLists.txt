# find_package(GTest REQUIRED)

enable_testing()

# Function to easily add new test executables
function(add_gtest_executable TEST_NAME LIB)
    add_executable(
      ${TEST_NAME}
      ${TEST_NAME}.cc
    )
    target_link_libraries(
      ${TEST_NAME}
      GTest::gtest_main # Provides a main function
      ${LIB} # Link against your LinearAlgebra library
    )
    include(GoogleTest)
    gtest_discover_tests(${TEST_NAME})
endfunction()

add_gtest_executable(vector_test LinearAlgebra)
add_gtest_executable(matrix_test LinearAlgebra)
#include <gtest/gtest.h>
#include "vector.hpp"
#include "matrix.hpp"
#include <vector>
#include <sstream>
#include <iostream>


using namespace FDM;

// Helper function to create a standard 2D vector for testing
template<typename T>
std::vector<std::vector<T>> Create2DVector(size_t rows, size_t cols, T initialValue) {
    return std::vector<std::vector<T>>(rows, std::vector<T>(cols, initialValue));
}

// Test Fixture for Matrix Tests
class MatrixTest : public ::testing::Test {
protected:
    Matrix<int> intMatrixDefault;
    Matrix<int> intMatrix3x3{3, 3, 1}; // 3x3 Matrix with all elements initialized to 1
};

TEST_F(MatrixTest, DefaultConstructor) {
    EXPECT_EQ(intMatrixDefault.rows(), 0);
    EXPECT_EQ(intMatrixDefault.cols(), 0);
}

TEST_F(MatrixTest, ParameterizedConstructor) {
    EXPECT_EQ(intMatrix3x3.rows(), 3);
    EXPECT_EQ(intMatrix3x3.cols(), 3);
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_EQ(intMatrix3x3[i][j], 1);
        }
    }
}

TEST_F(MatrixTest, CopyConstructor) {
    Matrix<int> copy = intMatrix3x3;
    EXPECT_EQ(copy.rows(), 3);
    EXPECT_EQ(copy.cols(), 3);
}

TEST_F(MatrixTest, From2DVector) {
    auto vec2d = Create2DVector<int>(2, 2, 5);
    Matrix<int> matrixFromVec(vec2d);
    EXPECT_EQ(matrixFromVec.rows(), 2);
    EXPECT_EQ(matrixFromVec.cols(), 2);
    EXPECT_EQ(matrixFromVec[0][0], 5);
}

// Test for Access Operators
TEST_F(MatrixTest, AccessOperator) {
    intMatrix3x3[1][1] = 9;
    EXPECT_EQ(intMatrix3x3[1][1], 9);
}

#if __cplusplus < 202101L
TEST_F(MatrixTest, AccessOperatorParens) {
    intMatrix3x3(1, 1) = 9;
    EXPECT_EQ(intMatrix3x3(1, 1), 9);
}
#endif

// Test for Scalar Multiplication
TEST_F(MatrixTest, ScalarMultiplication) {
    auto result = intMatrix3x3 * 2;
    EXPECT_EQ(result[0][0], 2);
    EXPECT_EQ(result[2][2], 2);
}

// Test for Matrix Addition
TEST_F(MatrixTest, MatrixAddition) {
    Matrix<int> anotherMatrix{3, 3, 2};
    auto result = intMatrix3x3 + anotherMatrix;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_EQ(result[i][j], 3); // 1 + 2
        }
    }
}

// Test for Matrix Multiplication
TEST_F(MatrixTest, MatrixMultiplication) {
    Matrix<int> matrixA{2, 3, 1}; // 2x3 Matrix with all elements as 1
    Matrix<int> matrixB{3, 2, 1}; // 3x2 Matrix with all elements as 1
    auto result = matrixA * matrixB;
    EXPECT_EQ(result.rows(), 2);
    EXPECT_EQ(result.cols(), 2);
    EXPECT_EQ(result[0][0], 3); // Sum of products
    EXPECT_EQ(result[1][1], 3);
}

// Test for Vector Multiplication
TEST_F(MatrixTest, VectorMultiplication) {
    Vector<int> vec{3, 1}; // 3-element vector with all elements as 1
    auto result = intMatrix3x3 * vec;
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 3); // Dot product with each row
}

// Test for Scalar Addition
TEST_F(MatrixTest, ScalarAddition) {
    auto result = intMatrix3x3 + 9;
    EXPECT_EQ(result[0][0], 10);
    EXPECT_EQ(result[2][2], 10);
}

// Test for Transpose
TEST_F(MatrixTest, Transpose) {
    Matrix<int> matrix{2, 3, 1}; // 2x3 Matrix
    auto transposed = matrix.transpose();
    EXPECT_EQ(transposed.rows(), 3);
    EXPECT_EQ(transposed.cols(), 2);
}

// Test for Print Function - Utilizes a similar approach as for Vector
TEST_F(MatrixTest, PrintFunction) {
    std::stringstream buffer;
    std::streambuf *prevCoutBuf = std::cout.rdbuf(buffer.rdbuf());

    Matrix<int> smallMatrix{2, 2, 1};
    smallMatrix.print();

    std::cout.rdbuf(prevCoutBuf); // Reset to standard output

    std::string expectedOutput = "Vector(2) : [1, 1]\nVector(2) : [1, 1]\n"; // Adjust based on actual print format
    EXPECT_EQ(buffer.str(), expectedOutput);
}

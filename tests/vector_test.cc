#include <gtest/gtest.h>
#include "vector.hpp"
#include <vector>
#include <sstream>
#include <iostream>


// Alias for convenience
using FDMVector = FDM::Vector<double>;

TEST(VectorTest, DefaultConstructor) {
    FDMVector vec;
    EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, SizeConstructor) {
    FDMVector vec(5);
    EXPECT_EQ(vec.size(), 5);
}

TEST(VectorTest, SizeValueConstructor) {
    FDMVector vec(5, 10);
    EXPECT_EQ(vec.size(), 5);
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], 10);
    }
}

TEST(VectorTest, StdVectorConstructor) {
    std::vector<double> stdVec = {1, 2, 3, 4, 5};
    FDMVector vec(stdVec);
    EXPECT_EQ(vec.size(), stdVec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], stdVec[i]);
    }
}

// Access Operators and Size Test
TEST(VectorTest, AccessOperator) {
    FDMVector vec(3, 5);
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 5);
    EXPECT_EQ(vec[2], 5);
    EXPECT_EQ(vec.size(), 3);
}

// Math Operations Tests
TEST(VectorTest, PlusEqualsOperator) {
    FDMVector vec1(3, 1);
    FDMVector vec2(3, 2);
    vec1 += vec2;
    EXPECT_EQ(vec1[0], 3);
    EXPECT_EQ(vec1[1], 3);
    EXPECT_EQ(vec1[2], 3);
}

TEST(VectorTest, MinusEqualsOperator) {
    FDMVector vec1(3, 5);
    FDMVector vec2(3, 2);
    vec1 -= vec2;
    EXPECT_EQ(vec1[0], 3);
    EXPECT_EQ(vec1[1], 3);
    EXPECT_EQ(vec1[2], 3);
}

TEST(VectorTest, TimesEqualsOperator) {
    FDMVector vec(3, 2);
    vec *= 2;
    EXPECT_EQ(vec[0], 4);
    EXPECT_EQ(vec[1], 4);
    EXPECT_EQ(vec[2], 4);
}

TEST(VectorTest, PlusOperator) {
    FDMVector vec1(3, 1);
    FDMVector vec2(3, 2);
    FDMVector vec3 = vec1 + vec2;
    EXPECT_EQ(vec3[0], 3);
    EXPECT_EQ(vec3[1], 3);
    EXPECT_EQ(vec3[2], 3);
}

TEST(VectorTest, MinusOperator) {
    FDMVector vec1(3, 5);
    FDMVector vec2(3, 2);
    FDMVector vec3 = vec1 - vec2;
    EXPECT_EQ(vec3[0], 3);
    EXPECT_EQ(vec3[1], 3);
    EXPECT_EQ(vec3[2], 3);
}

TEST(VectorTest, TimesOperator) {
    FDMVector vec1(3, 2);
    FDMVector vec2 = vec1 * 2;
    EXPECT_EQ(vec2[0], 4);
    EXPECT_EQ(vec2[1], 4);
    EXPECT_EQ(vec2[2], 4);
}

TEST(VectorTest, ScalarPlusOperator) {
    FDMVector vec1(3, 1);
    int scalar = 2;
    FDMVector vec2 = vec1 + scalar;
    EXPECT_EQ(vec2[0], 3);
    EXPECT_EQ(vec2[1], 3);
    EXPECT_EQ(vec2[2], 3);
}

TEST(VectorTest, DotProduct) {
    FDMVector vec1(3, 1);
    FDMVector vec2(3, 2);
    int dotProduct = vec1.dot(vec2);
    EXPECT_EQ(dotProduct, 6); // 1*2 + 1*2 + 1*2
}

TEST(VectorTest, Norm) {
    FDMVector vec(3, 4); // 3 elements each of value 4
    EXPECT_NEAR(vec.norm(), std::sqrt(48), 1e-5); // Using EXPECT_NEAR for floating point comparison
}

TEST(VectorTest, Print) {
    std::stringstream buffer;
    std::streambuf *prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    FDMVector vec(2, 3);
    vec.print();

    std::cout.rdbuf(prevcoutbuf); // Reset to standard output

    std::string expectedOutput = "Vector(2) : [3, 3]\n";
    EXPECT_EQ(buffer.str(), expectedOutput);
}


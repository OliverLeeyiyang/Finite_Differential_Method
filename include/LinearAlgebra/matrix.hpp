#ifndef FDM_LINEAR_ALGEBRA_MATRIX_HPP
#define FDM_LINEAR_ALGEBRA_MATRIX_HPP

#include "vector.hpp"
#include <cassert>
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

namespace FDM {


template <typename T>
class Matrix {

public:
    using size_t = std::size_t;
    using VV = std::vector<std::vector<T>>;

    Matrix();
    explicit Matrix(const size_t rows, const size_t cols);
    Matrix(const size_t rows, const size_t cols, const T& value);
    Matrix(VV& matrix);

    // Regular Constructors
    Matrix(const Matrix& other) = default;
    Matrix(Matrix&& other) = default;
    Matrix& operator=(const Matrix& other) = default;
    Matrix& operator=(Matrix&& other) = default;

    // Access Operators
    const Vector<T>& operator[] (const size_t index) const;
    Vector<T>& operator[] (const size_t index);
    size_t rows() const;
    size_t cols() const;

#if __cplusplus >= 202101L // C++23
/* C++23 Style access operator for multiple indices*/
    T& operator[] (const size_t row, const size_t col);
    /* C++23 Style access operator for multiple indices*/
    T operator[] (const size_t row, const size_t col) const;
#else // Before C++23
    /* Old Style access operator for multiple indices*/
    T& operator() (const size_t row, const size_t col);
    /* Old Style access operator for multiple indices*/
    T operator() (const size_t row, const size_t col) const ;
#endif // __cplusplus >= 202101L

    // Math Operators
    Matrix operator*(const Matrix& other) const;
    Vector<T> operator*(const Vector<T>& rhs) const;
    Matrix operator*(const T& scalar) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator+(const T& scalar) const;

    // Transpose
    Matrix transpose() const;

    // Print
    void print() const;

private:
    size_t _rows; 
    size_t _cols;
    std::vector<Vector<T>> data;

}; // class Matrix

template <typename T>
Matrix<T>::Matrix() : _rows{0}, _cols{0}, data{} 
{}

template <typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols) : _rows{rows}, _cols{cols}
{
    assert(rows > 0);
    assert(cols > 0);
    this->data = std::vector<Vector<T>>(rows, Vector<T>(cols));
}

template <typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols, const T& value) : _rows{rows}, _cols{cols}
{
    assert(rows > 0);
    assert(cols > 0);
    this->data = std::vector<Vector<T>>(rows, Vector<T>(cols, value));
}

template <typename T>
Matrix<T>::Matrix(VV& matrix) : _rows{matrix.size()}, _cols{matrix[0].size()}
{
    assert(_rows > 0);
    assert(_cols > 0);
    this->data = std::vector<Vector<T>>(_rows);
    for (size_t i = 0; i < _rows; i++) {
        this->data[i] = Vector<T>(matrix[i]);
    }
}

template <typename T>
const Vector<T>& Matrix<T>::operator[] (const size_t index) const
{
    assert(index >= 0 && index < this->_rows);
    return this->data[index];
}

template <typename T>
Vector<T>& Matrix<T>::operator[] (const size_t index)
{
    assert(index >= 0 && index < this->_rows);
    return this->data[index];
}

template <typename T>
typename Matrix<T>::size_t Matrix<T>::rows() const
{
    return this->_rows;
}

template <typename T>
typename Matrix<T>::size_t Matrix<T>::cols() const
{
    return this->_cols;
}

#if __cplusplus >= 202101L // C++23
/* C++23 Style access operator for multiple indices*/
template <typename T>
T& Matrix<T>::operator[] (const size_t row, const size_t col)
{
    assert(row >= 0 && row < this->_rows);
    assert(col >= 0 && col < this->_cols);
    return this->data[row][col];
}
/* C++23 Style access operator for multiple indices*/
template <typename T>
T Matrix<T>::operator[] (const size_t row, const size_t col) const
{
    assert(row >= 0 && row < this->_rows);
    assert(col >= 0 && col < this->_cols);
    return this->data[row][col];
}
#else // Before C++23
/* Old Style access operator for multiple indices*/
template <typename T>
T& Matrix<T>::operator() (const size_t row, const size_t col)
{
    assert(row >= 0 && row < this->_rows);
    assert(col >= 0 && col < this->_cols);
    return this->data[row][col];
}

/* Old Style access operator for multiple indices*/
template <typename T>
T Matrix<T>::operator() (const size_t row, const size_t col) const
{
    assert(row >= 0 && row < this->_rows);
    assert(col >= 0 && col < this->_cols);
    return this->data[row][col];
}
#endif // __cplusplus >= 202101L

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
    assert(this->_cols == other._rows);
    Matrix<T> result(this->_rows, other._cols, 0);
    for (size_t i = 0; i < this->_rows; i++) {
        for (size_t j = 0; j < other._cols; j++) {
            for (size_t k = 0; k < this->_cols; k++) {
                result[i][j] += this->data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

template <typename T>
Vector<T> Matrix<T>::operator*(const Vector<T>& rhs) const
{
    assert(this->_cols == rhs.size());
    Vector<T> result(this->_rows, 0);
    for (size_t i = 0; i < this->_rows; i++) {
        result[i] = this->data[i].dot(rhs);
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar) const
{
    Matrix<T> result(this->_rows, this->_cols, 0);
    for (size_t i = 0; i < this->_rows; i++) {
        result[i] = this->data[i] * scalar;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
    assert(this->_rows == other._rows);
    assert(this->_cols == other._cols);
    Matrix<T> result(this->_rows, this->_cols, 0);
    for (size_t i = 0; i < this->_rows; i++) {
        result[i] = this->data[i] + other.data[i];
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T& scalar) const
{
    Matrix<T> result(this->_rows, this->_cols, 0);
    for (size_t i = 0; i < this->_rows; i++) {
        result[i] = this->data[i] + scalar;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> result(this->_cols, this->_rows, 0);
    for (size_t i = 0; i < this->_rows; i++) {
        for (size_t j = 0; j < this->_cols; j++) {
            result[j][i] = this->data[i][j];
        }
    }
    return result;
}

template <typename T>
void Matrix<T>::print() const
{
    for (size_t i = 0; i < this->_rows; i++) {
        this->data[i].print();
    }
}


} // namespace FDM


#endif // FDM_LINEAR_ALGEBRA_MATRIX_HPP
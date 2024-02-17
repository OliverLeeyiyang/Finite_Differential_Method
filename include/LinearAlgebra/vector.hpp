#ifndef FDM_LINEAR_ALGEBRA_VECTOR_HPP
#define FDM_LINEAR_ALGEBRA_VECTOR_HPP

#include <cassert>
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

namespace FDM {

template <typename T>
class Vector {

public :
    using size_t = std::size_t;

    // Constructors
    Vector();
    explicit Vector(size_t size);
    Vector(size_t size, const T& value);
    Vector(std::vector<T>& vec);

    // Copy and move constructor
    Vector(const Vector<T>& other) = default;
    Vector(Vector<T>&& other) = default;
    Vector& operator=(const Vector<T>& other) = default;
    Vector& operator=(Vector<T>&& other) = default;

    // Destructor
    ~Vector() = default;

    // Access operators
    T& operator[](size_t index);
    T operator[](size_t index) const;
    size_t size() const;

    // Math operators
    Vector<T>& operator+=(const Vector<T>& other);
    Vector<T>& operator-=(const Vector<T>& other);
    Vector<T>& operator*=(const T& scalar);
    Vector<T> operator+(const Vector<T>& other) const;
    Vector<T> operator-(const Vector<T>& other) const;
    Vector<T> operator*(const T& scalar) const;
    Vector<T> operator+(const T& scalar) const;
    T dot(const Vector<T>& other) const;
    T norm() const;

    // Print
    void print() const;

private :
    std::vector<T> data;
    size_t _size;
}; // class Vector


// Constructors
template <typename T>
Vector<T>::Vector() : _size{0}, data{} 
{}

template <typename T>
Vector<T>::Vector(size_t size) : _size{size}
{
    assert(size > 0);
    this->data = std::vector<T>(size);
}

template <typename T>
Vector<T>::Vector(size_t size, const T& value) : _size{size}
{
    assert(size > 0);
    this->data = std::vector<T>(size, value);
}

template <typename T>
Vector<T>::Vector(std::vector<T>& vec) : _size{vec.size()}, data{vec}
{}

// Access operators
template <typename T>
T& Vector<T>::operator[](size_t index)
{
    assert(index >= 0 && index < this->_size);
    return this->data[index];
}

template <typename T>
T Vector<T>::operator[](size_t index) const
{
    assert(index >= 0 && index < this->_size);
    return this->data[index];
}

template <typename T>
typename Vector<T>::size_t Vector<T>::size() const
{
    return this->_size;
}

// Math operators
template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other)
{
    assert(this->_size == other._size);
    std::transform(this->data.begin(), this->data.end(), other.data.begin(), this->data.begin(), std::plus<T>());
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other)
{
    assert(this->_size == other._size);
    std::transform(this->data.begin(), this->data.end(), other.data.begin(), this->data.begin(), std::minus<T>());
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator*=(const T& scalar)
{
    std::transform(this->data.begin(), this->data.end(), this->data.begin(), std::bind(std::multiplies<T>(), std::placeholders::_1, scalar));
    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const
{
    assert(this->_size == other._size);
    Vector<T> result(this->_size);
    std::transform(this->data.begin(), this->data.end(), other.data.begin(), result.data.begin(), std::plus<T>());
    return result;
}

template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) const
{
    assert(this->_size == other._size);
    Vector<T> result(this->_size);
    std::transform(this->data.begin(), this->data.end(), other.data.begin(), result.data.begin(), std::minus<T>());
    return result;
}

template <typename T>
Vector<T> Vector<T>::operator*(const T& scalar) const
{
    Vector<T> result(this->_size);
    std::transform(this->data.begin(), this->data.end(), result.data.begin(), std::bind(std::multiplies<T>(), std::placeholders::_1, scalar));
    return result;
}

template <typename T>
Vector<T> Vector<T>::operator+(const T& scalar) const
{
    Vector<T> result(this->_size);
    std::transform(this->data.begin(), this->data.end(), result.data.begin(), std::bind(std::plus<T>(), std::placeholders::_1, scalar));
    return result;
}

template <typename T>
T Vector<T>::dot(const Vector<T>& other) const
{
    assert(this->_size == other._size);
    return std::inner_product(this->data.begin(), this->data.end(), other.data.begin(), T());
}

template <typename T>
T Vector<T>::norm() const
{
    return std::sqrt(this->dot(*this));
}

// Print
template <typename T>
void Vector<T>::print() const
{
    std::cout << "Vector(" << this->_size << ") : [";
    for (size_t i = 0; i < this->_size; ++i) {
        std::cout << this->data[i];
        if (i < this->_size - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}



// end
} // namespace FDM


#endif // FDM_LINEAR_ALGEBRA_VECTOR_HPP
#include <iostream>
#include <cassert>
#include <vector>

#include "include/LinearAlgebra/vector.hpp"

int main()
{
    FDM::Vector<double> vec1(3, 1.0);
    FDM::Vector<double> vec2(3);
    std::vector<double> vec = {1.0, 2.0, 3.0};
    FDM::Vector<double> vec3(vec);
    FDM::Vector<double> vec4(vec1);

    // Print
    vec1.print();
    vec2.print();
    vec3.print();
    vec4.print();
    
    return 0;
}
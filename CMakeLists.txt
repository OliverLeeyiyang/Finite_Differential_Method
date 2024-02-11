cmake_minimum_required(VERSION 3.23)

project(FDM 
    VERSION 1.0
    DESCRIPTION "Finite Difference Method"
    LANGUAGES CXX)

# set the c++ standard to c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory to the project
add_subdirectory(include)

# Specify the executable and link it with the LinearAlgebra library
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} LinearAlgebra)

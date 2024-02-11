cmake_minimum_required(VERSION 3.23)

project(FDM 
    VERSION 1.0
    DESCRIPTION "Finite Difference Method"
    LANGUAGES CXX)

# set the c++ standard to c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# add gtest dependency
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# Add the include directory to the project
add_subdirectory(include)
add_subdirectory(tests)

# Specify the executable and link it with the LinearAlgebra library
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} LinearAlgebra)

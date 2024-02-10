cmake_minimum_required(VERSION 3.23)

project(FDM LANGUAGES CXX)

# set the c++ standard to c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(include)

set(FDM_LIBS 
    FDM_MATH
)

add_subdirectory(tests)

add_executable(MAIN main.cpp)
target_link_libraries(MAIN PRIVATE FDM_MATH)
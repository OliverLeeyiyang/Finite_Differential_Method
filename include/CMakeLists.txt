# Add source files to FDM_MATH library
add_library(FDM_MATH STATIC clang_dummy.cpp)

add_subdirectory(LinearAlgebra)
add_subdirectory(LinearSolver)
add_subdirectory(FDMSolver)

# Add header files to FDM_MATH library
target_include_directories(FDM_MATH PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set linker language to C++
set_target_properties(FDM_MATH PROPERTIES LINKER_LANGUAGE CXX)
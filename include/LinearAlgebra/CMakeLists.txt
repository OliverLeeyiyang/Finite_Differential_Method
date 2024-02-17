# Create a library named LinearAlgebra
set(LA_SOURCES vector.hpp matrix.hpp)
add_library(LinearAlgebra INTERFACE ${LA_SOURCES})

# Specify that the library includes header files from this directory
target_include_directories(LinearAlgebra INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

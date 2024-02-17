# Create a library named LinearSolver
set(LIA_SOURCES
    GaussSeidel.hpp
    CG_Solver.hpp
    Jacobi.hpp
    Richardson.hpp
    LinearSolverBase.hpp
    )

add_library(LinearSolver INTERFACE ${LIA_SOURCES})

target_include_directories(LinearSolver INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Link to the library LinearAlgebra
target_link_libraries(LinearSolver INTERFACE LinearAlgebra)
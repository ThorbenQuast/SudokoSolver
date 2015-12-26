#nice tutorial: http://www.cmake.org/cmake-tutorial/

cmake_minimum_required (VERSION 2.6)
project (SudokuSolver)
# The version number.
set (SudokuSolver_VERSION_MAJOR 0)
set (SudokuSolver_VERSION_MINOR 1)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config/SudokuSolverConfig.h.in"
  "${PROJECT_BINARY_DIR}/config/SudokuSolverConfig.h"
  )
 


### LIBRARY AND TOOLS #######################################################
# library name
SET( libname ${PROJECT_NAME} )

# include directories
INCLUDE_DIRECTORIES( ./include )
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/config")


# add library
AUX_SOURCE_DIRECTORY( ./src library_sources )
ADD_LIBRARY( ${libname} ${library_sources} )

LINK_LIBRARIES( ${libname} )

# make the executable main
ADD_EXECUTABLE( main main.cc )







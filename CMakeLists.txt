cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project( ABMkit VERSION 1.0.0 LANGUAGES CXX )

# Add ABMkit library
add_subdirectory( src )

# Add demo main source code
add_subdirectory( demo )

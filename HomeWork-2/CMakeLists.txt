cmake_minimum_required(VERSION 3.0.0)
project(tests VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

add_executable(tests tests.cpp
                interface.h
                catch.hpp 
                hierarchy.cpp
                stringTree.cpp           
    )

add_executable(main ./main.cpp
                    ./interface.h
                    ./catch.hpp
                    ./hierarchy.cpp
                    headers/stringTree.h
                    ./stringTree.cpp
                    ./commands.cpp
                    ./commands.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

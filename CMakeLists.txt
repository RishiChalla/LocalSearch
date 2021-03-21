cmake_minimum_required(VERSION 3.0.0)
project(LocalSearch VERSION 0.1.0)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp src/*.h src/*.hpp)

add_executable(LocalSearch ${sources})

target_include_directories(LocalSearch PUBLIC src/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

cmake_minimum_required(VERSION 3.14)
project(intel-amx-experiment)
set(CMAKE_CXX_STANDARD 17)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=sapphirerapids" COMPILER_SUPPORTS_MARCH_SPR)
if(COMPILER_SUPPORTS_MARCH_SPR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=sapphirerapids -mamx-tile -mamx-int8 -mamx-bf16")
else()
    message(FATAL_ERROR "Please upgrade your compiler to support SPR fetaures (GCC11+)")
endif()

file(GLOB_RECURSE ALL_SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${ALL_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

include(cmake/test.cmake)

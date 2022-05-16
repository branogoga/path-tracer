cmake_minimum_required(VERSION 3.10)

# set the project name
project(PathTracer VERSION 0.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# setup Conan dependencies
set(CONAN_DIR .conan)
include(${CONAN_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# add the executable
set(
    GEOMETRY_SOURCES
    geometry/vector.h
    geometry/vector.cpp
    geometry/vector.test.cpp
)

add_executable(PathTracer main.cpp ${GEOMETRY_SOURCES})
conan_target_link_libraries(PathTracer)

# set warning level
if(MSVC)
    target_compile_options(PathTracer PRIVATE /W4 /WX)
else()
    target_compile_options(PathTracer PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()


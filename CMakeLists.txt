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
    geometry/matrix.h
    geometry/matrix.cpp
    geometry/matrix.test.cpp
    geometry/point.h
    geometry/point.cpp
    geometry/point.test.cpp
    geometry/ray.cpp
    geometry/ray.h
    geometry/ray.test.cpp
    geometry/vector.h
    geometry/vector.cpp
    geometry/vector.test.cpp
)

set(
    IMAGE_SOURCES
    image/image.h
    image/image.cpp
    image/image.test.cpp
    image/io/png.h
    image/io/png.cpp
    image/io/png.test.cpp
)

set(
        MATH_SOURCES
        math/quadratic_solver.cpp
        math/quadratic_solver.h
        math/quadratic_solver.test.cpp
)

set(
    SCENE_SOURCES
    scene/camera.h
    scene/camera.cpp
    scene/camera.test.cpp
    scene/color.h
    scene/color.cpp
    scene/color.test.cpp
    scene/material.h
    scene/material.cpp
    scene/material.test.cpp
    scene/plane.cpp
    scene/plane.h
    scene/plane.test.cpp
    scene/sphere.h
    scene/sphere.cpp
    scene/sphere.test.cpp
)

set(
        UTILS_SOURCES
        utils/timer.cpp utils/timer.h)

set(
    SOURCES
    ${GEOMETRY_SOURCES}
    ${IMAGE_SOURCES}
    ${MATH_SOURCES}
    ${SCENE_SOURCES}
    ${UTILS_SOURCES}
)

add_executable(PathTracer main.cpp ${SOURCES})
conan_target_link_libraries(PathTracer)

# set warning level
if(MSVC)
    target_compile_options(PathTracer PRIVATE /W4 /WX)
else()
    target_compile_options(PathTracer PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(PathTracerTest test.cpp ${SOURCES})
conan_target_link_libraries(PathTracerTest)

# set warning level
if(MSVC)
    target_compile_options(PathTracerTest PRIVATE /W4 /WX)
else()
    target_compile_options(PathTracerTest PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()


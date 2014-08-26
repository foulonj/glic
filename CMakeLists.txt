cmake_minimum_required(VERSION 2.8)

project(igl)

set(CMAKE_BUILD_TYPE "Release")

include_directories("./include")

add_executable(test sources/core.c++ test.c++)

set_target_properties(test
  PROPERTIES
  COMPILE_FLAGS
  "-O3"
)

#TARGET_LINK_LIBRARIES(Bezier "-framework GLUT -framework OpenGL")
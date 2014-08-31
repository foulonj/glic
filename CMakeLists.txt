cmake_minimum_required(VERSION 2.8)

project(IGL)

set(CMAKE_BUILD_TYPE "Release")

#Options C++ (-Wno-deprecated: remove glut deprecated)
set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -g3 -Wall -Wno-deprecated -O0")

#Options graphiques
find_package(GLUT)
find_package(OpenGL)
find_package(X11)
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${X11_LIBRARIES})

#Include files
include_directories("include/")

#Recuperation de la liste des fichiers .cpp et .h
file(GLOB_RECURSE source_files sources/* include/igl/*)

#Compiltation
add_library(IGL SHARED ${source_files})

target_link_libraries(IGL ${CORELIBS})

project(main)
include_directories("include/")

add_executable(main ../main.cpp)

target_link_libraries(main IGL)



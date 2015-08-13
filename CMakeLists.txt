cmake_minimum_required(VERSION 2.8)

project(GLIC)

set(CMAKE_BUILD_TYPE "Release")

#Options C++ (-Wno-deprecated: remove glut deprecated)

set (CMAKE_CXX_FLAGS "-std=c++0x -g3 -Wall -Wno-deprecated -O0")
# -stdlib=libc++
#Options graphiques
find_package(GLUT)
find_package(OpenGL)
find_package(X11)
find_package(GLEW)

set(CORELIBS ${GLEW_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${X11_LIBRARIES})

option(VRPN "VRPN" OFF)

#Include files
#include_directories("include/")
include_directories("include/" "libmesh/" "glm/")

if(vrpn)
	list(APPEND CMAKE_MODULE_PATH /Users/Shared/Library/vrpn/cmake)
	find_package(VRPN)
	include_directories("include/glic/")
	include_directories("vrpn/include/")
	include_directories(${VRPN_INCLUDE_DIR})

	get_property(inc_dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
	message("inc_dirs = ${inc_dirs}")
	file(GLOB_RECURSE vrpn_files vrpn/sources/* vrpn/include/*)
	add_library(VRPN SHARED ${vrpn_files})

endif(vrpn)

#Compilation
#Recuperation de la liste des fichiers .cpp et .h
file(GLOB_RECURSE source_files sources/* include/glic/* )
add_library(GLIC SHARED ${source_files})
add_library(mesh SHARED libmesh/libmesh5.h libmesh/libmesh5.c)
target_link_libraries(GLIC ${CORELIBS} mesh)

project(main)
add_executable(main main.cpp)
target_link_libraries(main GLIC)

if(vrpn)
project(mainVRPN)
add_executable(mainVRPN vrpn/mainVRPN.cpp)
target_link_libraries(VRPN ${VRPN_LIBRARY})
target_link_libraries(mainVRPN VRPN)
endif(vrpn)


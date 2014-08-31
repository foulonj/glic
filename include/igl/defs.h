/****************************************************************
*
* IGL: ICS Graphics Library
*
* Original Authors:
*   J. Foulon, P. Frey
*
****************************************************************/
#ifndef IGLDEF_H
#define IGLDEF_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

using namespace std;

#ifdef WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifdef WIN32
  #ifdef IGL_DLL
    #ifdef IGL_LIB
	    #define IGL_API __declspec(dllexport)
    #else
	    #define IGL_API __declspec(dllimport)
    #endif
  #else
    #define IGL_API
  #endif
#else
    #define IGL_API
#endif


#endif
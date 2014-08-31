/****************************************************************
*
* IGL: ICS Graphics Library
*
* Original Authors:
*   J. Foulon, P. Frey
*
* IGL: ICS Graphics Library
* Copyright (C) 2014- ICS graphic team
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later 
* version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General 
* Public License along with this library; if not, write to the
* Free Software Foundation, Inc., 59 Temple Place, Suite 330, 
* Boston, MA 02111-1307 USA
*
****************************************************************/
#ifndef __ICS_GL_h_
#define __ICS_GL_h_

#include <igl/camera.h>
#include <igl/canvas.h>
#include <igl/light.h>
#include <igl/scene.h>
#include <igl/window.h>


/*-- The major/minor/patch version. ---------------------------*/
#define IGL_VERSION_MAJOR    0
#define IGL_VERSION_MINOR    0
#define IGL_VERSION_PATCH    0

/*---------------------------------------------------------------
  Do not modify anything below this line.
 --------------------------------------------------------------*/

/*-- Declare a version string constant ------------------------*/
#define IGL_STR(s)           # s
#define IGL_xSTR(s)          IGL_STR(s)
#define IGL_DOT(a,b)         a ## . ## b
#define IGL_xDOT(a,b)        IGL_DOT(a,b)

#define IGL_VERSION_STRING \
	IGL_xDOT( \
		IGL_xDOT(IGL_VERSION_MAJOR, IGL_VERSION_MINOR), \
		         IGL_VERSION_PATCH)

namespace igl
{
	inline const char* iglGetVersion()
  {
		return IGL_xSTR(IGL_VERSION_STRING);
  }
}

/*-- Cleanup all internal macros ------------------------------*/
#undef IGL_DOT
#undef IGL_xDOT
#undef IGL_STR
#undef IGL_xSTR
#undef IGL_VERSION_STRING
#undef IGL_VERSION_MAJOR
#undef IGL_VERSION_MINOR
#undef IGL_VERSION_PATCH

#endif
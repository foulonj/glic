/****************************************************************
*
* IGL: ICS Graphics Library
*
* Original Authors:
*   J. Foulon, P. Frey
*
****************************************************************/
#ifndef __IGL_CAMERA_H_
#define __IGL_CAMERA_H_

#include "defs.h"


class IGL_API CiglCamera
{
public:
	double    fovy;
	
	CiglCamera();
	virtual ~CiglCamera();
};

typedef CiglCamera * pCiglCamera;


#endif

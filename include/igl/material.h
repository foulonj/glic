/****************************************************************
*
* IGL: ICS Graphics Library
*
* Original Authors:
*   J. Foulon, P. Frey
*
****************************************************************/
#ifndef __IGL_MATERIAL_H_
#define __IGL_MATERIAL_H_

#include <igl/object.h>


class IGL_API CiglMaterial : public CiglObject
{
public:
	enum colType {CL_AMB, CL_DIF, CL_SPE};

private:

public:
	CiglMaterial();
	virtual ~CiglMaterial();
	
protected:
	virtual void iglInit();
};


#endif  /* __iglmaterial_h_ */
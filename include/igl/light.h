/****************************************************************
*
* IGL: ICS Graphics Library
*
* Original Authors:
*   J. Foulon, P. Frey
*
****************************************************************/
#ifndef __IGL_LIGHT_H_
#define __IGL_LIGHT_H_

#include <igl/material.h>
#include <igl/object.h>


class IGL_API CiglLight : public CiglObject
{
public:
	enum litType {LT_POINT, LT_DIRECTION, LT_SPOT};

private:
	int     lid;
	float   amb[4],dif[4],spe[4],pos[4];
	int     cstatt,linatt,quadatt;
	float   spotCutoff,spotDirect[3],spotExp;
	litType ltyp;

public:
  // constructor + destructor
	CiglLight();
	virtual ~CiglLight() { };

  void setCol(CiglMaterial::colType typ, const float r, const float g,const float b, const float a);
	void setPos(const float x, const float y, const float z, const float w);
  void setAtt(const int c, const int l, const int q);
  void setType(litType typ);
  void setSpot(float cutoff, float sx, float sy, float sz, float expo);

	void getCol(CiglMaterial::colType typ, float &r, float &g, float &b, float &a) const;
	void getPos(float &x, float &y, float &z, float &w) const;

protected:
	virtual void iglInit();
};

typedef CiglLight * pCiglLight;


#endif  /* __igllight_h_ */
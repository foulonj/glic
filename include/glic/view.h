/****************************************************************
*
* GLIC: ICS Graphics Library
*
* Original Authors:
*   J. Foulon, P. Frey
*
****************************************************************/
#ifndef __GLIC_VIEW_H_
#define __GLIC_VIEW_H_

#include "defs.h"
#include <glic/math1.h>


class GLIC_API CglicView
{
public:
  enum TViewType {TV_DEF, TV_FLY, TV_LEFT, TV_RIGHT};
	double    m_znear,m_zfar;

private:
	double    m_fovy;

  bool      m_stereo;
  double    m_eyesep;
  TViewType m_ctyp,m_eye;

public:
    vec3d m_center;
    vec3d     m_pos,m_up;
	CglicView();
	virtual ~CglicView();

	void setPos(double x, double y, double z);
	void setPersp(double fovy, double znear, double zfar);
	void getPos(double &x, double &y, double &z);
	void setView();
	void reshape(int w, int h);
	void updateCenter(vec3d v){m_center=v;};
};

typedef CglicView * pCglicView;


#endif

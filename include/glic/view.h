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

class GLIC_API CglicView
{
public:
  enum TViewType {TV_DEF, TV_FLY, TV_LEFT, TV_RIGHT};
	double    m_znear,m_zfar;
	double    m_fovy;
	double    ratio;

private:
  bool      m_stereo;
  double    m_eyesep;
  TViewType m_ctyp,m_eye;

public:
	CglicView();
	virtual ~CglicView();
	void setPersp(double fovy, double znear, double zfar);

	void setView();
	void reshape(int w, int h);
};

typedef CglicView * pCglicView;


#endif

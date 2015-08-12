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

private:
	double    m_fovy;

  bool      m_stereo;
  double    m_eyesep;
  TViewType m_ctyp,m_eye;

public:
  glm::vec3 m_look, m_cam, m_up;
  glm::vec3 m_right;
	CglicView();
	virtual ~CglicView();

	void setPos(glm::vec3 newPos);
	void getPos(glm::vec3 &pos);
	void setPersp(double fovy, double znear, double zfar);

	void setView();
	void reshape(int w, int h);
	void updateCenter(glm::vec3 v){m_look=v;};
};

typedef CglicView * pCglicView;


#endif

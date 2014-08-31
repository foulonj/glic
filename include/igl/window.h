/****************************************************************
*
* IGL: ICS Graphics Library
*
* Original Authors:
*   J. Foulon, P. Frey
*
****************************************************************/
#ifndef __IGL_WINDOW_H_
#define __IGL_WINDOW_H_

#include "defs.h"
#include <igl/camera.h>
#include <igl/light.h>
#include <igl/scene.h>


class IGL_API CiglWindow
{
private:
	int   m_x,m_y,m_w,m_h;

public:
	int   m_id;
  pCiglScene               scene;
	pCiglCamera              camera;
	std::vector<pCiglLight>  light;

	CiglWindow();
	CiglWindow(int x, int y, int w, int h);
	virtual ~CiglWindow();

  void reshape(int w, int h);

	void show();
	void resize(int w, int h);
  void title(const char *title);
};

typedef CiglWindow * pCiglWindow;

#endif


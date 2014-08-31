/****************************************************************
*
* IGL: ICS Graphics Library
*
* Original Authors:
*   J. Foulon, P. Frey
*
****************************************************************/
#ifndef __IGL_CORE_H_
#define __IGL_CORE_H_

#include "defs.h"
#include <igl/light.h>
#include <igl/scene.h>
#include <igl/window.h>


class IGL_API CiglCanvas
{
public:
	std::vector<CiglLight>   light;
  std::vector<CiglScene>   scene;
  std::vector<CiglWindow>  window;

private:
  int winid();

public:
	// graphic engine constructor + destructor
  CiglCanvas();
	CiglCanvas(int argc, char **argv);	
	virtual ~CiglCanvas();

	int  iglWindow(int x, int y, int w, int h);
	int  iglScene();
	void iglSetScene(int ids, int idw);
  void iglMainLoop();

  virtual void reshape(int w, int h);
  static void reshapeWrap(int w, int h);
  virtual void display();
  static void displayWrap();
};


#endif  /* __iglcore_h_ */

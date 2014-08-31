/****************************************************************
*
* IGL: ICS Graphics Library
*
* Original Authors:
*   J. Foulon, P. Frey
*
****************************************************************/
#ifndef __IGL_SCENE_H_
#define __IGL_SCENE_H_

#include "defs.h"

class IGL_API CiglScene
{
public:

private:
	int  idw;
	void resize(int width, int height);

public:
	CiglScene();
	virtual ~CiglScene();
  static void display();

protected:
	virtual void iglInit();
};

typedef CiglScene * pCiglScene;


#endif  /* __iglscene_h_ */


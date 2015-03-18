/****************************************************************
 *
 * GLIC: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 ****************************************************************/
#ifndef __GLIC_SCENE_H_
#define __GLIC_SCENE_H_

#include "defs.h"
#include <glic/object.h>

class GLIC_API CglicScene
{
public:
  
//private:
  //int  ids;
  void resize(int width, int height);
  std::vector<pCglicObject> listObject;
  CglicTransform transform;
public:
  int  ids;
  //int id(){return ids;};
  CglicScene();
  virtual ~CglicScene();
  void display();
  void addObject(pCglicObject object);
protected:
  virtual void glicInit();
};

typedef CglicScene* pCglicScene;


#endif

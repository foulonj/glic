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
  enum TsceState {TO_OFF, TO_ON, TO_SEL, TO_DYN};
  void resize(int width, int height);
  std::vector<pCglicObject> listObject;
  CglicTransform transform;
  double m_rot[16];
public:
  char  state;
  int  ids;
  //int id(){return ids;};
  CglicScene();
  virtual ~CglicScene();
  void display();
  void addObject(pCglicObject object);
  void applyTransformation();
protected:
  virtual void glicInit();
};

typedef CglicScene* pCglicScene;


#endif

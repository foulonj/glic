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
#include <glic/view.h>

class GLIC_API CglicScene
{
public:
  enum TsceState {TO_OFF, TO_ON, TO_SEL, TO_DYN};
  void resize(int width, int height);
  std::vector<pCglicObject> listObject;
  CglicTransform transform;
  double m_rot[16];
  //glm::mat4x4 m_rot;
  glm::vec3 center;

public:
  pCglicView view;

public:
  glm::vec3 m_look, m_cam, m_up;
  glm::vec3 m_right;

  glm::mat4 VIEW;
  glm::mat4 PROJ;

public:
  char  state;
  int  ids;

  CglicScene();
  virtual ~CglicScene();
  void display();
  void addObject(pCglicObject object);
  void applyTransformation();
  void update_matrices();

protected:
  virtual void glicInit();
};

typedef CglicScene* pCglicScene;


#endif

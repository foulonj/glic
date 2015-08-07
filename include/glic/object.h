/****************************************************************
 *
 * GLIC: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 ****************************************************************/
#ifndef __GLIC_OBJECT_H_
#define __GLIC_OBJECT_H_

#include "defs.h"
#include <glic/transform.h>

class GLIC_API CglicObject
{
public:
  enum TobjState {TO_OFF, TO_ON, TO_SEL, TO_DYN};
  glm::vec4 color, mat_diffuse;
  double m_tr[16];
  glm::vec3 center;
public:
  char  state;
  char box;
  char line;
public:
  CglicObject();
  virtual ~CglicObject();
  virtual void display(){};
  CglicTransform transform;
  void applyTransformation();
  void activeBB();
  void activeMesh();
protected:
  virtual void glicInit();
};

typedef CglicObject* pCglicObject;

#endif

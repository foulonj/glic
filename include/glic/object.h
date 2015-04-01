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
  double color[4];
  GLfloat mat_diffuse[4];// = {0.1f, 0.5f, 0.8f, 1.0f};
  double m_tr[16];
public:
  char  state;
public:
  CglicObject();
  virtual ~CglicObject();
  virtual void display(){};
  CglicTransform transform;
  void applyTransformation();
protected:
  virtual void glicInit();
};

typedef CglicObject* pCglicObject;

#endif

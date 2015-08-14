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
#include <glic/shader.h>

class GLIC_API CglicObject
{
public:
  enum TobjState {TO_OFF, TO_ON, TO_SEL, TO_DYN};
  glm::vec4 color, mat_diffuse;
  glm::vec3 center;
  CglicTransform transform;

public:
  SHADER shader;
  void uniformVec3(int ID, glm::vec3 v);

  glm::vec3 R, G, B, WHITE, BLACK;
  glm::vec3 grid_color, face_color, edge_color, select_color;

  glm::mat4 MODEL;
  glm::mat4 *pVIEW;
  glm::mat4 *pPROJ;

public:
  char state;
  char box;
  char line;

public:
  CglicObject();
  virtual ~CglicObject();
  virtual void display(){};

  void applyTransformation();
  void activeBB();
  void activeMesh();



protected:
  virtual void glicInit();
};

typedef CglicObject* pCglicObject;

#endif

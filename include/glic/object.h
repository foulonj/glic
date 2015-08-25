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

//Modifier par un accesseur public set Transform
public:
  CglicTransform transform;

public:
  glm::vec3 R, G, B, WHITE, BLACK;
  glm::vec3 face_color, edge_color;

  int pickingID;
  SHADER pickingShader;
  glm::vec3 pickingColor;
  GLuint meshBuffer;
  GLuint indicesBuffer;
  int nPicking;

  glm::mat4 MODEL;
  glm::vec3 *sceneCenter;
  glm::vec3 *sceneUp;
  glm::mat4 *pMODEL;
  glm::mat4 *pVIEW;
  glm::mat4 *pPROJ;
  bool useSmoothShading;
  //bool useShadows;

  bool      isRotationConstrained,   isTranslationConstrained;
  glm::vec3 constrainedRotationAxis, constrainedTranslationAxis;



public:
  char state;
  char box;
  char line;

public:
  CglicObject();
  virtual ~CglicObject();

  virtual void display(){};

  void pickingDisplay();
  void applyTransformation();
  void activeBB();
  void activeMesh();

  void uniformVec3(int ID, glm::vec3 v);

protected:
  virtual void glicInit();
};

typedef CglicObject* pCglicObject;

#endif

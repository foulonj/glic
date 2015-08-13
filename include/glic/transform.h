/****************************************************************
 *
 * GLIC: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 ****************************************************************/
#ifndef __GLIC_TRANSFORM_H_
#define __GLIC_TRANSFORM_H_

#include "defs.h"

class GLIC_API CglicTransform
{
public:
  glm::vec3 tr;
  glm::mat4 hRot, vRot;

  CglicTransform(){};
  ~CglicTransform(){};
  void setRotation(glm::mat4 hMat, glm::mat4 vMat);
  void setTranslation(glm::vec3 translation);
  void print();
  void reset();
};

#endif

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
  glm::mat4 mat;

  glm::vec3 translation;
  double angle;
  glm::vec3 axe;

  CglicTransform();
  ~CglicTransform(){};
  void setRotation(double ang, glm::vec3 axis);
  void setTranslation(glm::vec3 tr);
  void print();
};

#endif

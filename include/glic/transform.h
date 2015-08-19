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
  glm::mat4 rot;

  CglicTransform(){};
  ~CglicTransform(){};
  void setRotation(glm::mat4 Mat);
  void setTranslation(glm::vec3 translation);
  void print();
  void reset();
};

#endif

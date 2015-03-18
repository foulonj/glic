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
#include <glic/math1.h>

class GLIC_API CglicTransform
{
public:
  mat4x4 mat;
  vec3d translation;
  
  CglicTransform();
  ~CglicTransform(){};
  void setTranslation(double x, double y, double z);
  void print();
};

#endif
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
  glm::quat quat;

  //Retour en arrière
  glm::mat4 lastMatrix;
  std::vector<glm::mat4> lastMatrices;

  CglicTransform(){};
  ~CglicTransform(){};
  void setRotation(glm::mat4 M);
  void setQuaternion(glm::quat Q);
  void setTranslation(glm::vec3 translation);
  void print();
  void reset();
};

#endif

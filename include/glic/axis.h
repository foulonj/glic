/****************************************************************
 *
 * GLIC: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 ****************************************************************/

#ifndef __GLIC_AXIS_H_
#define __GLIC_AXIS_H_

#include <glic/object.h>

#include <glic/shader.h>

class GLIC_API CglicAxis : public CglicObject
{
public:
  float *vertices;
  GLuint buffer;
  SHADER shader;
  vector<glm::vec3> colo;
  vector<glm::vec3> grid;
  vector<glm::vec3> axes;


  CglicAxis();
  void display();
  ~CglicAxis();
};

#endif

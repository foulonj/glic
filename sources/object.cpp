#include <glic/object.h>

void CglicObject::uniformVec3(int ID, glm::vec3 v){
  glUniform3f(ID, v.x, v.y, v.z);
}

// object constructor
CglicObject::CglicObject():transform()
{
  //cout << "  --- [create CglicObject]" << endl;
  state = TO_ON;
  box = TO_OFF;
  line = TO_OFF;
  mat_diffuse[0] = 0.1f;
  mat_diffuse[1] = 0.5f;
  mat_diffuse[2] = 0.8f;
  mat_diffuse[3] = 1.0f;

  MODEL = glm::mat4(1.0f);
  center = glm::vec3(0.0f);
  pPROJ = NULL;
  pVIEW = NULL;

  //Colors
  R = glm::vec3(1, 0, 0);
  G = glm::vec3(0, 1, 0);
  B = glm::vec3(0, 0, 1);
  WHITE = glm::vec3(1, 1, 1);
  BLACK = glm::vec3(0, 0, 0);
  grid_color = glm::vec3(WHITE * 0.5f);
  face_color = glm::vec3(0.8f*R + 0.2f*B);
  edge_color = glm::vec3(0.5f*R + 0.2f*B);
}


CglicObject::~CglicObject(){}

void CglicObject::glicInit()
{}

void CglicObject::activeBB()
{
  if (box == TO_OFF)
    box = TO_ON;
  else
    box = TO_OFF;
}

void CglicObject::activeMesh()
{
  if (line == TO_OFF)
    line = TO_ON;
  else
    line = TO_OFF;
}

void CglicObject::applyTransformation()
{
  MODEL = glm::translate(MODEL, transform.tr);
  MODEL = transform.hRot * transform.vRot * MODEL;
  center += transform.tr;
  transform.reset();
}

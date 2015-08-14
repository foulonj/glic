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
  R          = glm::vec3(1,   0,   0);
  G          = glm::vec3(0,   1,   0);
  B          = glm::vec3(0,   0,   1);
  grid_color = glm::vec3(0.5, 0.5, 0.5);
  face_color = glm::vec3(0.8, 0,   0.2);
  edge_color = glm::vec3(0.5, 0 ,  0.2);
  sele_color = glm::vec3(1,   0.6, 0);
  idle_color = glm::vec3(0.8, 0.8, 0.8);
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

//////////////////////////////////////////////////////////////////////////////////////////
// PAS CORRECT POUR LES ROTATIONS
//////////////////////////////////////////////////////////////////////////////////////////
void CglicObject::applyTransformation()
{
  glm::mat4 ID = glm::mat4(1.0f);
  center += transform.tr;
  //Ainsi, le comportement est bon à l'origine
  MODEL =  transform.hRot * transform.vRot * MODEL;

  MODEL = glm::translate(MODEL, transform.tr);

  transform.reset();
}

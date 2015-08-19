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
  //face_color = glm::vec3(0.8, 0,   0.2);
  //edge_color = glm::vec3(0.5, 0 ,  0.2);
  sele_color = glm::vec3(1,   0.6, 0);
  idle_color = glm::vec3(0.8, 0.8, 0.8);

  //New random implementation
  double a = (rand()/(double)(RAND_MAX + 1)) + 1;
  double b = (rand()/(double)(RAND_MAX + 1)) + 1;
  double c = (rand()/(double)(RAND_MAX + 1)) + 1;
  glm::vec3 rand = glm::vec3(a,b,c);
  face_color = glm::vec3(0.5f) + 0.5f * rand;
  edge_color = 0.5f * rand;
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
  glm::mat4 ID = glm::mat4(1.0f);
  center += transform.tr;
  MODEL =  glm::translate(ID, center) * transform.rot * glm::translate(ID, -center) * glm::translate(ID, transform.tr) * MODEL;
  transform.reset();
}

void CglicObject::pickingDisplay(){
  int shaderID = pickingShader.mProgramID;
  glUseProgram(shaderID);
  int MatrixID = glGetUniformLocation(shaderID, "MVP");
  int colorID  = glGetUniformLocation(shaderID, "COL");

  glm::mat4 MVP = *pPROJ * *pVIEW * *pMODEL * MODEL;

  glUniformMatrix4fv( MatrixID, 1, GL_FALSE, &MVP[0][0]);
  //Mesh buffer binding
  glEnableVertexAttribArray( 0);
  glBindBuffer(              GL_ARRAY_BUFFER, meshBuffer);
  glVertexAttribPointer(     0, 3, GL_FLOAT, GL_FALSE, 0, ( void*)0);
  glBindAttribLocation(      shaderID, 0, "vertex_position");
  //Indices buffer binding
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
  //Faces
  uniformVec3(colorID, pickingColor);
  glPolygonMode(GL_FRONT, GL_FILL);
  glDrawElements(GL_TRIANGLES, nPicking, GL_UNSIGNED_INT, (void*)0);
}

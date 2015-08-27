#include <glic/object.h>
#include <glic/canvas.h>
extern CglicCanvas *pcv;

void CglicObject::uniformVec3(int ID, glm::vec3 v){
  glUniform3f(ID, v.x, v.y, v.z);
}

// object constructor
CglicObject::CglicObject():transform()
{
  //cout << "  --- [create CglicObject]" << endl;
  selected = false;
  box    = false;
  line   = false;
  smooth = true;

  MODEL = glm::mat4(1.0f);
  center = glm::vec3(0.0f);
  pPROJ = NULL;
  pVIEW = NULL;

  //Colors
  /*
  double a = (rand()/(double)(RAND_MAX + 1)) + 1;
  double b = (rand()/(double)(RAND_MAX + 1)) + 1;
  double c = (rand()/(double)(RAND_MAX + 1)) + 1;
  glm::vec3 rand = glm::vec3(a,b,c);
  face_color = glm::vec3(0.7f) + 0.3f * rand;
  edge_color = 0.7f * rand;
  */
  face_color = pcv->profile.color();
  edge_color = 0.5f * face_color;
  idGroup = -1;
}

CglicObject::~CglicObject(){}

void CglicObject::linkSceneParameters(glm::mat4 *MODEL, glm::mat4 *VIEW, glm::mat4 *PROJ, glm::vec3 *Center, glm::vec3 *Up, int ID){
  pPROJ       = PROJ;
  pVIEW       = VIEW;
  pMODEL      = MODEL;
  sceneCenter = Center;
  sceneUp     = Up;
  objectID   = ID;
  pickingColor = glm::vec3(objectID/255.0f, 0, 0);
}

void CglicObject::glicInit()
{}

void CglicObject::applyTransformation()
{
  glm::mat4 ID = glm::mat4(1.0f);
  center += transform.tr;

  //Le rotation center est défini en fonction des groupes
  if(idGroup==-1)
    rotationCenter = &center;
  MODEL =  glm::translate(ID, *rotationCenter) * transform.rot * glm::translate(ID, -*rotationCenter) * glm::translate(ID, transform.tr) * MODEL;

  transform.reset();
}
void CglicObject::saveTransformations(){
  transform.lastMatrices.push_back(MODEL);
}
void CglicObject::undoLast(){
  if(transform.lastMatrices.size()>0){
    MODEL = transform.lastMatrices.back();
    center = glm::vec3(glm::vec4(MODEL[3]));
    transform.lastMatrices.pop_back();
  }
}
void CglicObject::resetAll(){
  while(transform.lastMatrices.size()>0)
    undoLast();
}

void CglicObject::pickingDisplay(){
  int shaderID = pcv->simpleShader.mProgramID;
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
  //glDisable(GL_DEPTH_TEST);
  uniformVec3(colorID, pickingColor);
  glPolygonMode(GL_FRONT, GL_FILL);
  glDrawElements(GL_TRIANGLES, nPicking, GL_UNSIGNED_INT, (void*)0);
  //glEnable(GL_DEPTH_TEST);
}


void CglicObject::setRotationCenter(glm::vec3 &center){
  rotationCenter = &center;
}


int  CglicObject::getID(){return objectID;}
glm::vec3* CglicObject::getCenterPtr(){return &center;}

//Toogle render modes
void CglicObject::toogleBBox()   {box        = !box;}
void CglicObject::toogleMesh()   {line       = !line;}
void CglicObject::toogleSmooth() {smooth     = !smooth;}

//Selection accessors
bool CglicObject::isSelected(){return selected;}
bool CglicObject::isPicked(int ID){return objectID == ID;}
void CglicObject::toogleSelected(){    selected = !selected;}
void CglicObject::select(){    selected = true;}
void CglicObject::unSelect(){  selected = false;}

//Constrained movements accessors
bool CglicObject::isConstrainedInRotation(){return isRotationConstrained;}
bool CglicObject::isConstrainedInTranslation(){return isTranslationConstrained;};
void CglicObject::constrainRotation(glm::vec3 axis){
  isRotationConstrained = true;
  constrainedRotationAxis = axis;
}
void CglicObject::constrainTranslation(glm::vec3 axis){
  isTranslationConstrained = true;
  constrainedTranslationAxis = axis;
}
void CglicObject::unConstrain(){
  isRotationConstrained = isTranslationConstrained = false;
  constrainedRotationAxis = constrainedTranslationAxis = glm::vec3(0);
};
void CglicObject::setConstrainedRotation(float angle){transform.setRotation(glm::rotate(glm::mat4(1), angle, constrainedRotationAxis));}
void CglicObject::setConstrainedTranslation(float tr){transform.tr += tr * constrainedTranslationAxis;}

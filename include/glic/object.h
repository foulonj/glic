/****************************************************************
 *
 * GLIC: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 ****************************************************************/
#ifndef __GLIC_OBJECT_H_
#define __GLIC_OBJECT_H_

#include "defs.h"
#include <glic/transform.h>

class GLIC_API CglicObject
{
  public:
    CglicTransform transform;

  protected:
    //Matrices and vectors
    glm::mat4 MODEL;
    glm::mat4 *pVIEW;
    glm::mat4 *pPROJ;
    glm::vec3 center;
    //Scene parameters
    glm::vec3 *sceneCenter;
    glm::vec3 *sceneUp;
    glm::mat4 *pMODEL;
    //Colors
    glm::vec3 face_color, edge_color;
    glm::vec3 pickingColor;
    //Buffers
    GLuint meshBuffer;
    GLuint indicesBuffer;
    //Render parameters & selection
    int pickingID;
    int nPicking;
    bool selected;
    bool box;
    bool line;
    bool smooth;
    //Constrained movements
    bool      isRotationConstrained,   isTranslationConstrained;
    glm::vec3 constrainedRotationAxis, constrainedTranslationAxis;

  //Public methods
  public:
    CglicObject();
    virtual ~CglicObject();
    void linkSceneParameters(glm::mat4 *MODEL, glm::mat4 *VIEW, glm::mat4 *PROJ, glm::vec3 *Center, glm::vec3 *Up, int ID);
    virtual void display(){};
    void pickingDisplay();
    void applyTransformation();
    void saveTransformations();
    void undoLast();
    void resetAll();
    void uniformVec3(int ID, glm::vec3 v);

  //Public Accessors
  public:
    //Selection & picking
    bool isSelected();
    bool isPicked(int ID);
    void select();
    void unSelect();
    //render modes
    void toogleBBox();
    void toogleMesh();
    void toogleSmooth();
    //Constrained movements
    bool isConstrainedInRotation();
    bool isConstrainedInTranslation();
    void constrainRotation(glm::vec3 axis);
    void constrainTranslation(glm::vec3 axis);
    void setConstrainedRotation(float angle);
    void setConstrainedTranslation(float tr);
    void unConstrain();

protected:
  virtual void glicInit();
};

typedef CglicObject* pCglicObject;

#endif

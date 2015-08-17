/****************************************************************
 *
 * GLIC: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 ****************************************************************/
#ifndef __GLIC_MESH_H_
#define __GLIC_MESH_H_

#include <glic/object.h>

#define FLOAT_MAX  1.e20

typedef struct {
  double    c[3];
  int       ref;
} Point;
//typedef Point * pPoint;

typedef struct {
  int       v[3],ref;
} Tria;
//typedef Tria * pTria;

typedef struct {
  double    n[3];
} Normal;
//typedef Normal * pNormal;

typedef struct {
  int inds[2];
} NormalAtVertex;


class GLIC_API CglicMesh : public CglicObject
{

private:
  int np,nt,nn,dim,ver;
  vector<Point>    point;
  vector<Tria>     tria;
  vector<Normal>   normal;
private:
  //Normals at vertices
  vector<NormalAtVertex> NormalAtVertices;
  int nNAtV;


public:
  //type de rendu: "SMOOTH" ou "FLAT" pour différencier les shaders
  SHADER simpleShader;
  SHADER smoothShader;

  GLuint bboxBuffer;
  GLuint bboxIndBuffer;
  GLuint normalBuffer;

public:
  glm::vec3 bbmin, bbmax;
  glm::vec3 tra;

public:
  CglicMesh(char *name);
  void meshInfo(const int& verbose = 0, ostream& outstr = cout);
  void display();
  void getBBOX();
  void displayBBOX();
  ~CglicMesh(){};
};

#endif

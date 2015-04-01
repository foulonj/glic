#include <glic/cube.h>

CglicCube::CglicCube(double cr, double cg, double cb, double rr):r(rr)
{
  cout << "  --- - [create CglicCube]" << endl;
  color[0]=cr;
  color[1]=cg;
  color[2]=cb;
}

CglicCube::~CglicCube()
{
  cout << "  --- - [destroy CglicCube]" << endl;
}

void CglicCube::display()
{
  
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  
  if (state == TO_SEL ){
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  }
  else
    glColor3f(color[0], color[1], color[2]);
  
  
  glutSolidCube(0.8*r);
  glColor3f(1., 1., 1.);
  if (box == TO_ON)
    glutWireCube(r);
}
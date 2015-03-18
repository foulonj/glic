#include <glic/sphere.h>

CglicSphere::CglicSphere(double cr, double cg, double cb, double rr):r(rr)
{
  cout << "  --- - [create CglicSphere]" << endl;
  color[0]=cr;
  color[1]=cg;
  color[2]=cb;
}

CglicSphere::~CglicSphere()
{
  cout << "  --- - [destroy CglicSphere]" << endl;
}

void CglicSphere::display()
{
  
  if (state == TO_SEL ){
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  }
  else
    glColor3f(color[0], color[1], color[2]);
  
  glutSolidSphere(0.8*r/2., 10., 10.);
  glColor3f(1., 1., 1.);
  glutWireCube(r);
  
}
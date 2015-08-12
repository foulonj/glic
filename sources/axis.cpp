#include <glic/axis.h>

void CglicAxis::display()
{
  // grid
  glLineWidth(1.0);
  glBegin(GL_LINES);
  glColor3f(0.5, 0.5, 0.5);
  float dash_size = 0.05;
  for(float x = -1. ; x <= 1. ; x+=0.05){
    for(float z = -1. ; z <= 1. ; z+=0.05){
      glVertex3f(x-dash_size/2, 0., z);
      glVertex3f(x+dash_size/2, 0., z);
      glVertex3f(x, 0., z-dash_size/2);
      glVertex3f(x, 0., z+dash_size/2);
    }
  }
  glEnd();

  // axes
  glLineWidth(2.0);
  glBegin(GL_LINES);
  //X
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-10,0,0);
  glVertex3f(10,0,0);
  //Y
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0,10,0);
  glVertex3f(0,-10,0);
  //Z
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0,0,10);
  glVertex3f(0,0,-10);
  glEnd();
  glLineWidth(1.0);

  glColor3f(1.0, 0.0, 0.0);
  glRasterPos3f(0.22, 0.0, 0.0);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'x');
  glColor3f(0.0, 1.0, 0.0);
  glRasterPos3f(0.0, 0.22, 0.0);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'y');
  glColor3f(0.0, 0.0, 1.0);
  glRasterPos3f(0.0, 0.0, 0.22);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'z');
}

#include <glic/axis.h>

void CglicAxis::display()
{
  glBegin(GL_LINE_STRIP);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(1.0, 0.0, 0.0);
  glVertex3f(0.95, 0.01, 0.0);
  glVertex3f(0.95, -0.01, 0.0);
  glVertex3f(1.0, 0.0, 0.0);
  glVertex3f(0.95, 0.0, 0.01);
  glVertex3f(0.95, 0.0, -0.01);
  glVertex3f(1.0, 0.0, 0.0);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 1.0, 0.0);
  glVertex3f(0.0, 0.95, 0.01);
  glVertex3f(0.0, 0.95, -0.01);
  glVertex3f(0.0, 1.0, 0.0);
  glVertex3f(0.01, 0.95, 0.0);
  glVertex3f(-0.01, 0.95, 0.0);
  glVertex3f(0.0, 1.0, 0.0);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 1.0);
  glVertex3f(0.01, 0.0, 0.95);
  glVertex3f(-0.01, 0.0, 0.95);
  glVertex3f(0.0, 0.0, 1.0);
  glVertex3f(0.0, 0.01, 0.95);
  glVertex3f(0.0, -0.01, 0.95);
  glVertex3f(0.0, 0.0, 1.0);
  glEnd();
  
  glColor3f(0.0f,1.0f,0.0f);
  glRasterPos3f(1.02, 0.0, 0.0);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'x');
  glRasterPos3f(0.0, 1.02, 0.0);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'y');
  glRasterPos3f(0.0, 0.0, 1.02);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'z');
  
  glLineWidth(1.0);
}

#include <glic/view.h>

#include "glm/gtx/string_cast.hpp"



CglicView::CglicView()
{
  m_stereo = false;
  m_eyesep = 1.0;
  m_eye    = TV_LEFT;
  m_ctyp   = TV_DEF;
  setPersp(70.0, 0.01, 200.0);
}


CglicView::~CglicView()
{
}


void CglicView::setPersp(double fovy, double znear, double zfar)
{
  m_fovy  = fovy;
  m_znear = znear;
  m_zfar  = zfar;
}


void CglicView::reshape(int w, int h)
{
  //cout << "   -- reshapeView " << w << " " << h << endl;
  glViewport(0,0,(GLsizei)w,(GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  //glMatrixMode(GL_PERSPECTIVE_CORRECTION_HINT);
  glLoadIdentity();
  ratio = (double)w/h;
  gluPerspective(m_fovy, ratio, m_znear, m_zfar);
  glTranslatef(0.0, 0.0, -0.5 * m_zfar);
  //glTranslatef(0.0, 0.0, -0.5 * (m_znear + m_zfar));
}


void CglicView::setView()
{
  //cout << "   -- setView\n";
  if ( m_stereo == true ){}
  else{}
}

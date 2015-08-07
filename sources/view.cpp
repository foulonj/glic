#include <glic/view.h>

#include "glm/gtx/string_cast.hpp"



CglicView::CglicView()
{
  m_stereo = false;
  m_eyesep = 1.0;
  m_eye    = TV_LEFT;
  m_ctyp   = TV_DEF;
  setPos(glm::vec3(0., 0., 0.3));
  setPersp(60.0, 0.01, 1.0);
}


CglicView::~CglicView()
{
}


void CglicView::setPos(glm::vec3 newPos)
{
  m_cam = newPos;
}


void CglicView::getPos(glm::vec3 &pos)
{
  pos = m_cam;
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
  gluPerspective(m_fovy, (double)w/h, m_znear, m_zfar);
  glTranslatef(0.0, 0.0, -0.5 * m_zfar);
  //glTranslatef(0.0, 0.0, -0.5 * (m_znear + m_zfar));
}


void CglicView::setView()
{

  //cout << "   -- setView\n";
  if ( m_stereo == true ){

  }
  else
  {
    gluLookAt(m_cam.x, m_cam.y, m_cam.z,
              m_look.x, m_look.y, m_look.z,
              m_up.x, m_up.y, m_up.z);
  }
  m_right = glm::cross(m_cam, -m_up);
  cout << "stereo = " << m_stereo << endl;
  cout << "cam = " << glm::to_string(m_cam) << endl;
  cout << "look = " << glm::to_string(m_look) << endl;
  cout << "right = " << glm::to_string(m_right) << endl;
  cout << " " << endl;
}

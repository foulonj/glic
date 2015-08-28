#include <glic/view.h>
#include "glm/gtx/string_cast.hpp"
#include <glic/canvas.h>
extern CglicCanvas *pcv;


CglicView::CglicView()
{
  m_stereo = false;
  m_eyesep = 1.0;
  m_eye    = TV_LEFT;
  m_ctyp   = TV_DEF;
  setPersp(70.0, 0.01, 3.0);
  persp  = pcv->profile.perspective;
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
  ratio = (double)w/h;
  width  = w;
  height = h;
}


void CglicView::setView()
{
  //cout << "   -- setView\n";
  if ( m_stereo == true ){}
  else{}
}

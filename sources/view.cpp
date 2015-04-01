#include <glic/view.h>


CglicView::CglicView()
{
  m_stereo = false;
  m_eyesep = 1.0;
  m_eye    = TV_LEFT;
  m_ctyp   = TV_DEF;
  
  //setPersp(60.0, 0.01, 50.0);
  //setPos(0.0, 0.0, -10.0);
  
  setPos(0.0, 0.0, 0.3);
  
  //Cube
  setPersp(60.0, 0.01, 1.0);
  //setPos(0.0, 0.0, 0.0);
}


CglicView::~CglicView()
{
}


void CglicView::setPos(double x, double y, double z)
{
  m_pos = vec3d(x,y,z);
}


void CglicView::getPos(double &x, double &y, double &z)
{
  x = m_pos[0];
  y = m_pos[1];
  z = m_pos[2];
}


void CglicView::setPersp(double fovy, double znear, double zfar)
{
  m_fovy  = fovy;
  m_znear = znear;
  m_zfar  = zfar;
}


void CglicView::reshape(int w, int h)
{
  cout << "   -- reshapeView " << w << " " << h << endl;
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
  GLdouble   ex,ey,ez;
  GLdouble   cx,cy,cz;
  GLdouble   upx,upy,upz;
  
  cout << "   -- setView\n";
  ex = m_pos[0];
  ey = m_pos[1];
  ez = m_pos[2];
  cx = m_center[0];
  //cy = m_center[1];
  cy = 1.0;
  cz = m_center[2];
  upx = m_up[0];
  upy = m_up[1];
  upz = m_up[2];
  
  if ( m_stereo == true )
  {
    
  }
  else
  {
    //cout << "\n\n\tGLLOOKAT: " << ex << ", "<< ey << ", "<< ez << endl;
    gluLookAt(ex,ey,ez,cx,cy,cz,upx,upy,upz);
  }
}
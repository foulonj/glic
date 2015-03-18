#include <glic/canvas.h>
#include <glic/mouse.h>
extern CglicCanvas *pcv;


CglicMouse::CglicMouse()
{
  memset((void*)this, 0, sizeof(*this));
  m_ang = 0.0;
  m_trx  = m_try  = 0.0;
  m_otrx = m_otry = 0.0;
  m_lastx = 0;  m_lasty = 0;
  m_button[0] = m_button[1] = m_button[2] = 0;
  m_zoom  = 0.0;
  m_pos[0] = m_pos[1] = m_pos[2] = 0.0;
  m_axe[0] = m_axe[1] = m_axe[2] = 0.0;
  m_key = TM_NONE;
}


CglicMouse::~CglicMouse()
{}


/* project point onto hemi-sphere */
void CglicMouse::projsph(int diffx, int diffy, vec3d &v) {
  double   d1,d2;
  
  v[0] =  2.0*(double)diffx / (float)m_w;
  v[1] = -2.0*(double)diffy / (float)m_h;
  v[2] =  1.0;
  d1 = v[0]*v[0] + v[1]*v[1];
  if ( d1 > 0.0 ) {
    d2 = sqrt(d1);
    if ( d2 > 1.0 )  d2 = 1.0;
    v[2] = cos(M_PI_2 * d2);
    d1  += v[2]*v[2];
    d1   = 1.0 / sqrt(d1);
    v[0] *= d1;
    v[1] *= d1;
    v[2] *= d1;
  }
}


void CglicMouse::motion(int x, int y)
{
  GLuint   tm;
  double   dx,dy,dz;
  vec3d    v;
  
  tm = glutGet(GLUT_ELAPSED_TIME);
  if ( tm < m_tm + 40 )  return;
  m_tm = tm;
  
  int diffx = x - m_lastx;
  int diffy = y - m_lasty;
  
  if ( m_button[0] )
  {
    if ( m_key == TM_SHIFT )
    {
      m_zoom -= (float) 0.0005 * diffy;
    }
    else
    {
      projsph(diffx, diffy, v);
      /* axis of rotation: cross product */
      m_axe.cross(m_pos,v);
      dx = v[0] - m_pos[0];
      dy = v[1] - m_pos[1];
      dz = v[2] - m_pos[2];
      m_ang = 180.0*sqrt(dx*dx + dy*dy + dz*dz);
      m_pos = v;
    }
  }
  else if ( m_button[1] )
  {
    m_trx += (float) 0.05 * diffx;
    m_try -= (float) 0.05 * diffy;
    m_ang   = 0.0;
    m_lastx = x;
    m_lasty = y;
  }
}


void CglicMouse::mouse(int b, int s, int x, int y)
{
  GLint  key;
  m_tm = glutGet(GLUT_ELAPSED_TIME);
  m_lastx = x;
  m_lasty = y;
  
  /*
   cout << "\n\n GLUTGETMODIFIERS: " << glutGetModifiers() << "\n\n";
   
   cout << "\n\n GLUT_ACTIVE_ALT : " << GLUT_ACTIVE_ALT << endl;
   cout << "\n\n GLUT_ACTIVE_CTRL : " << GLUT_ACTIVE_CTRL << endl;
   
   //ALT
   if (glutGetModifiers() & GLUT_ACTIVE_ALT) {
   cout << "\n\n\tGLUTGETMODIFIERS ALT pressed.\n\n";
   }
   
   //CTRL
   if (glutGetModifiers() & GLUT_ACTIVE_CTRL) {
   cout << "\n\n\t GLUTGETMODIFIERS CONTROL pressed.\n\n";
   }
   
   
   if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) {
   cout << "\n\n\tGLUTGETMODIFIERS SHIFT pressed.\n\n";
   }
   */
  
  
  switch(b)
  {
    case GLUT_LEFT_BUTTON:
      m_button[0] = ((GLUT_DOWN==s)?1:0);
      
      m_w = glutGet(GLUT_WINDOW_WIDTH);
      m_h = glutGet(GLUT_WINDOW_HEIGHT);
      projsph(0, 0, m_pos);
      key = glutGetModifiers();
      //cout << "\n\n\tno active shift \n\n";
      m_key = TM_NONE;
      if ( glutGetModifiers() & GLUT_ACTIVE_SHIFT){cout << "\n\n\t Active shift \n\n"; m_key = TM_SHIFT;};
      if (glutGetModifiers() & GLUT_ACTIVE_CTRL){
        cout << "\n GLUT Actve CTRL\n" << endl;
        m_key = TM_CTRL;
        pcv->glicPickObject(x, y);
      };
      
      
      GLint viewport[4];
      GLubyte pixel[3];
      GLubyte item[3];
      
      glGetIntegerv(GL_VIEWPORT,viewport);
      
      glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);
      
      printf("\n\n\tRead Pixel color: %d %d %d\n\n\n",pixel[0],pixel[1],pixel[2]);
      
      
      break;
      
      
    case GLUT_MIDDLE_BUTTON:
      m_button[1] = ((GLUT_DOWN==s)?1:0);
      break;
      
    case GLUT_RIGHT_BUTTON:
      m_button[2] = ((GLUT_DOWN==s)?1:0);
      break;
  }
}


void CglicMouse::transform()
{
  cout << "----- mouse Transform \n";
  if (m_key == TM_SHIFT)
    glTranslatef(0.0, 0.0, -m_zoom);
  glTranslatef(m_trx, m_try, 0.0);
  glRotatef(m_ang, m_axe[0], m_axe[1], m_axe[2]);
  glTranslatef(-m_otrx, -m_otry, 0.0);
  m_otrx = m_trx;
  m_otry = m_try;
  m_ang = 0.0;
}
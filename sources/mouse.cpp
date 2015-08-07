#include <glic/canvas.h>
#include <glic/mouse.h>
#include <glic/cube.h>
extern CglicCanvas *pcv;


CglicMouse::CglicMouse()
{
  memset((void*)this, 0, sizeof(*this));
  m_ang = 0.0;
  m_trx  = m_try  = 0.0;
  m_otrx = m_otry = 0.0;
  m_button[0] = m_button[1] = m_button[2] = 0;
  m_zoom  = 0.0;
  m_pos[0] = m_pos[1] = m_pos[2] = 0.0;
  m_axe[0] = m_axe[1] = m_axe[2] = 0.0;
  m_key = TM_NONE;
}


CglicMouse::~CglicMouse()
{}


/* project point onto hemi-sphere */
glm::vec3 CglicMouse::projsph(glm::vec2 diff) {
  double   d1,d2;
  glm::vec3 v;
  v.x =  2.0*(double)diff.x / (float)currPos.x;
  v.y = -2.0*(double)diff.y / (float)currPos.y;
  d1 = v.x*v.x + v.y*v.y;
  if ( d1 > 0.0 ) {
    d2 = sqrt(d1);
    if ( d2 > 1.0 )
      d2 = 1.0;
    v.z = cos(M_PI_2 * d2);
    v /= glm::length(v);
  }
  return v;
}


void CglicMouse::motion(int x, int y)
{
  pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];

  GLuint   tm;
  glm::vec3    v;

  tm = glutGet(GLUT_ELAPSED_TIME);
  if ( tm < m_tm + 40 )  return;
  m_tm = tm;

  glm::vec2 diffPos = glm::vec2(x,y) - lastPos;

  if ( m_button[0] )
  {
    v = projsph(diffPos);
    /* axis of rotation: cross product */
    m_axe = glm::cross(m_pos,v);
    glm::vec3 d;
    d = v - m_pos;
    d = d*d;
    m_ang = 180.0*sqrt(d.x + d.y + d.z);
    m_pos = v;

    if (scene->state == CglicScene::TO_SEL)
      scene->transform.setRotation(m_ang,m_axe);
    else
      for (unsigned int iObj = 0; iObj < scene->listObject.size(); iObj++){
        if (scene->listObject[iObj]->state == CglicCube::TO_SEL){
          glPushMatrix();
          scene->listObject[iObj]->transform.setRotation(m_ang, m_axe);
          glPopMatrix();
        };
      }
  }
}


void CglicMouse::mouse(int b, int s, int x, int y)
{
  GLint  key;
  m_tm = glutGet(GLUT_ELAPSED_TIME);
  lastPos = glm::vec2(x,y);

  switch(b)
  {
    case GLUT_LEFT_BUTTON:
      m_button[0] = ((GLUT_DOWN==s)?1:0);

      currPos = glm::vec2( glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) );

      m_pos = projsph(glm::vec2(0.));
      key = glutGetModifiers();
      //cout << "\n\n\tno active shift \n\n";
      m_key = TM_NONE;
      if ( glutGetModifiers() & GLUT_ACTIVE_SHIFT){cout << "\n\n\t Active shift \n\n"; m_key = TM_SHIFT;};
      if (glutGetModifiers() & GLUT_ACTIVE_CTRL){
        //cout << "\n GLUT Actve CTRL\n" << endl;
        m_key = TM_CTRL;
        pcv->glicPickObject(x, y);
      };


      GLint viewport[4];
      GLubyte pixel[3];
      //GLubyte item[3];

      glGetIntegerv(GL_VIEWPORT,viewport);

      glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);

      //printf("\n\n\tRead Pixel color: %d %d %d\n\n\n",pixel[0],pixel[1],pixel[2]);

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
{}

#include <glic/object.h>


// object constructor
CglicObject::CglicObject():transform()
{
  //cout << "  --- [create CglicObject]" << endl;
  state = TO_ON;
  box = TO_OFF;
  line = TO_OFF;
  mat_diffuse[0] = 0.1f;
  mat_diffuse[1] = 0.5f;
  mat_diffuse[2] = 0.8f;
  mat_diffuse[3] = 1.0f;

  m_tr[0]=1.;m_tr[1]=0.;m_tr[2]=0.;m_tr[3]=0.;
  m_tr[4]=0.;m_tr[5]=1.;m_tr[6]=0.;m_tr[7]=0.;
  m_tr[8]=0.;m_tr[9]=0.;m_tr[10]=1.;m_tr[11]=0.;
  m_tr[12]=0.;m_tr[13]=0.;m_tr[14]=0.;m_tr[15]=1.;

  center[0] = 0.;
  center[1] = 0.;
  center[2] = 0.;
}


CglicObject::~CglicObject()
{
  //cout << "  --- [destroy CglicObject]" << endl;
  // check if display lists used...
  // glDeleteLists();
}

void CglicObject::glicInit()
{}

void CglicObject::activeBB()
{
  if (box == TO_OFF)
    box = TO_ON;
  else
    box = TO_OFF;
}

void CglicObject::activeMesh()
{
  if (line == TO_OFF)
    line = TO_ON;
  else
    line = TO_OFF;
}

void CglicObject::applyTransformation()
{
  //glLoadIdentity();
  glTranslatef(transform.translation[0],
               transform.translation[1],
               transform.translation[2]);

  center[0] += transform.translation[0];
  center[1] += transform.translation[1];
  center[2] += transform.translation[2];


  glTranslatef(center[0], center[1], center[2]);
  glRotatef(transform.angle,
            transform.axe[0],
            transform.axe[1],
            transform.axe[2]);
  glTranslatef(-center[0], -center[1], -center[2]);

  glm::vec3 null_vec3;
  transform.setTranslation(null_vec3);
  transform.setRotation(0., null_vec3);
}

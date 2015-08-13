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

  MODEL = glm::mat4(1.0f);
  center = glm::vec3(0.0f);
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
  //Remplacent tout ce qui suit

  glm::vec3 tr = transform.translation;
  glm::vec3 ax = transform.axe;

  MODEL = glm::translate(MODEL, tr);
  if(ax != glm::vec3(0.0f))
    MODEL = glm::rotate(MODEL, (float)transform.angle, ax);
  //center += tr;

  glTranslatef(tr.x, tr.y, tr.z);
  center += tr;
  glTranslatef(center.x, center.y, center.z);
  glRotatef(transform.angle, ax.x, ax.y, ax.z);
  glTranslatef(-center.x, -center.y, -center.z);

  transform.reset();
}

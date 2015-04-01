#include <glic/object.h>


// object constructor
CglicObject::CglicObject():transform()
{
  cout << "  --- [create CglicObject]" << endl;
  state = TO_ON;
  
  m_tr[0]=1.;m_tr[1]=0.;m_tr[2]=0.;m_tr[3]=0.;
  m_tr[4]=0.;m_tr[5]=1.;m_tr[6]=0.;m_tr[7]=0.;
  m_tr[8]=0.;m_tr[9]=0.;m_tr[10]=1.;m_tr[11]=0.;
  m_tr[12]=0.;m_tr[13]=0.;m_tr[14]=0.;m_tr[15]=1.;
}

CglicObject::~CglicObject()
{
  cout << "  --- [destroy CglicObject]" << endl;
  // check if display lists used...
  // glDeleteLists();
}

void CglicObject::glicInit()
{}

void CglicObject::applyTransformation()
{
  //glLoadIdentity();
  glTranslatef(transform.translation[0],
               transform.translation[1],
               transform.translation[2]);
  glRotatef(transform.angle,
            transform.axe[0],
            transform.axe[1],
            transform.axe[2]);
  
  transform.setTranslation(0., 0., 0.);
  vec3d axis;
  axis[0]=0.;axis[1]=0.;axis[2]=0.;
  transform.setRotation(0.,axis);
}

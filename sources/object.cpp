#include <glic/object.h>


// object constructor
CglicObject::CglicObject():transform()
{
  cout << "  --- [create CglicObject]" << endl;
  state = TO_ON;
}

CglicObject::~CglicObject()
{
  cout << "  --- [destroy CglicObject]" << endl;
  // check if display lists used...
  // glDeleteLists();
}

void CglicObject::glicInit()
{}

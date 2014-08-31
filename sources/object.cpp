#include <igl/object.h>


// object constructor
CiglObject::CiglObject()
{
	cout << " -- CiglObject\n";
  state = O_ON;
}

CiglObject::~CiglObject()
{
	// check if display lists used...
	// glDeleteLists();
}


void CiglObject::iglInit()
{
}

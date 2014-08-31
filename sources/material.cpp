#include <igl/material.h>


// object constructor
CiglMaterial::CiglMaterial()
{
	cout << " -- cIglMaterial\n";
}

CiglMaterial::~CiglMaterial()
{
	// check if display lists used...
	// glDeleteLists();
}


void CiglMaterial::iglInit()
{
}

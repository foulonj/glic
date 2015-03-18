/****************************************************************
 *
 * GLIC: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 ****************************************************************/

#ifndef __GLIC_AXIS_H_
#define __GLIC_AXIS_H_

#include <glic/object.h>

class GLIC_API CglicAxis : public CglicObject
{
public:
  CglicAxis(){};
  void display();
  ~CglicAxis(){};
};

#endif
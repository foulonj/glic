/****************************************************************
*
* IGL: ICS Graphics Library
*
* Original Authors:
*   J. Foulon, P. Frey
*
****************************************************************/
#ifndef __IGL_OBJECT_H_
#define __IGL_OBJECT_H_

#include <igl/scene.h>


class IGL_API CiglObject : public CiglScene
{
public:
  enum objState {O_OFF, O_ON, O_SEL, O_DYN};

private:
  char  state;

public:
	CiglObject();
	virtual ~CiglObject();

  //void display() {} ;

protected:
	virtual void iglInit();
};


#endif  /* __iglobject_h_ */

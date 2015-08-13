/****************************************************************
 *
 * GLIC: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 ****************************************************************/
#ifndef __GLIC_KEYBOARD_H_
#define __GLIC_KEYBOARD_H_

#include "defs.h"

class GLIC_API CglicKeyboard
{
public:
  int selection;
  CglicKeyboard():selection(-1){};
  virtual ~CglicKeyboard(){};
  void keyboard(unsigned char key, int x, int y);
  void special(unsigned char key, int x, int y);
  void keyColor(unsigned char key,int x,int y);
};

#endif

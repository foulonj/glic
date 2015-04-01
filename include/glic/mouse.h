/****************************************************************
 *
 * GLIC: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 ****************************************************************/
#ifndef __GLIC_MOUSE_H_
#define __GLIC_MOUSE_H_

#include "defs.h"
#include <glic/math1.h>


class GLIC_API CglicMouse
{
private:
  int    m_w,m_h;
  
public:
  enum   TmouseType {TM_NONE, TM_SHIFT, TM_ALT, TM_CTRL};
  
  bool   m_button[3];
  int    m_lastx,m_lasty;
  vec3d  m_axe,m_pos;
  double m_ang,m_trx,m_try,m_otrx,m_otry,m_zoom;
  unsigned int m_tm;
  TmouseType  m_key;
  
public:
  CglicMouse();
  virtual ~CglicMouse();
  
  void motion(int x, int y);
  void mouse(int b, int s, int x, int y);
  void transform();
private:
  void projsph(int x, int y, vec3d &v);
};


#endif

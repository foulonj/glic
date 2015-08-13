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

class GLIC_API CglicMouse
{
private:
  //int    m_w,m_h;
  glm::vec2 currPos;
  glm::vec2 lastPos;

public:
  enum   TmouseType {TM_NONE, TM_SHIFT, TM_ALT, TM_CTRL};

  bool   m_button[3];
  //int    m_lastx,m_lasty;
  glm::vec3  m_axe,m_pos;
  double m_ang,m_trx,m_try,m_otrx,m_otry,m_zoom;
  unsigned int m_tm;
  TmouseType  m_key;

public:
  CglicMouse();
  virtual ~CglicMouse(){};

  void motion(int x, int y);
  void mouse(int b, int s, int x, int y);
  void transform();
private:
  glm::vec3 projsph(glm::vec2 diff);
};


#endif

/****************************************************************
 *
 * IGL: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 * ---------------------------------------------------------------
 * File:          $RCSfile: properties.hpp,v $
 * Date modified: $Date: 2014-08-20 09:37:22 $
 * Version:       $Revision: 0.0 $
 * ---------------------------------------------------------------
 *
 ****************************************************************/

/*!
 \file properties.hpp
 \authors J. Foulon, P. Frey
 \date 26/08/2014
 \brief Manage OpenGL Properties
 */

#ifndef _PROPERTIES_HPP
#define _PROPERTIES_HPP

#include "igl.hpp"

class Properties{
public:
  Properties(){};
  virtual ~Properties();
  
  virtual void display();
  
  //! Fix ambient parameter
  virtual void setAmbient(float a, float b, float c, float d);
  
private:
  float amb[4],dif[4],spe[4],pos[4];
};

#endif
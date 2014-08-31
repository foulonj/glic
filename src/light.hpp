/****************************************************************
 *
 * IGL: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 * ---------------------------------------------------------------
 * File:          $RCSfile: light.hpp,v $
 * Date modified: $Date: 2014-08-20 09:37:22 $
 * Version:       $Revision: 0.0 $
 * ---------------------------------------------------------------
 *
 ****************************************************************/

/*!
 \file properties.hpp
 \authors J. Foulon, P. Frey
 \date 26/08/2014
 \brief Light Properties
 */

#ifndef _LIGHT_HPP
#define _LIGHT_HPP

#include "properties.hpp"

#define IGL_MAX_LIGHTS     64


class Light: public Properties
{
public:
	enum lightType {LT_POINT,LT_DIRECT,LT_SPOT};
  
  //!Constructor
	Light();
  
  Light(float a, float b, float c, float d);
	
  //! Destructor
  virtual ~Light(){};
  
  void display();
  
  void setPosition(float a, float b, float c, float d);
  
private:
	int   lightid;
	float pos[4];
	lightType lighttyp;
  
};

#endif
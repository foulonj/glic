/****************************************************************
 *
 * IGL: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 * ---------------------------------------------------------------
 * File:          $RCSfile: object.hpp,v $
 * Date modified: $Date: 2014-08-20 09:37:22 $
 * Version:       $Revision: 0.0 $
 * ---------------------------------------------------------------
 *
 ****************************************************************/


/*!
 \file object.hpp
 \authors J. Foulon, P. Frey
 \date 26/08/2014
 \brief Object class
 */

#ifndef _OBJECT_HPP
#define _OBJECT_HPP

#include "igl.hpp"
#include "properties.hpp"


class Object
{
public:
  //! Constructor
  Object();
  
  //! Destructor
  virtual ~Object();
  
  //void addProperties(Properties p);
  
  //! Display function for Object
  void display();
  
private:
  //vector <Properties> properties;
  string name;
};

#endif

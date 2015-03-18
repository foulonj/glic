/****************************************************************
 *
 * GLIC: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 ****************************************************************/
#ifndef __GLIC_MATERIAL_H_
#define __GLIC_MATERIAL_H_

#include <glic/object.h>


class GLIC_API CglicMaterial : public CglicObject
{
public:
  enum TcolType {TC_AMB, TC_DIF, TC_SPE};
  
private:
  
public:
  CglicMaterial();
  virtual ~CglicMaterial();
  
protected:
  virtual void glicInit();
};


#endif  /* __glicmaterial_h_ */
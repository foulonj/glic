#include <igl/light.h>
#include <igl/material.h>


// light constructor
CiglLight::CiglLight()
{
	cout << " -- CiglLight\n";
	ltyp = LT_DIRECTION;
  lid  = 0;

	setCol(CiglMaterial::CL_AMB, 0.0, 0.0, 0.0, 1.0);
	setCol(CiglMaterial::CL_DIF, 1.0, 1.0, 1.0, 1.0);
	setCol(CiglMaterial::CL_SPE, 1.0, 1.0, 1.0, 1.0);

	setPos(0, 0, 0, 1);
  setAtt(1, 0, 0);

	spotCutoff   = 45.0;
	spotDirect[0] =  0.0;
	spotDirect[1] =  0.0;
	spotDirect[2] = -1.0;
	spotExp      =  0.0;
}


void CiglLight::setCol(CiglMaterial::colType typ, const float r, const float g,const float b, const float a)
{
	switch (typ) {
	case CiglMaterial::CL_AMB: 
	  amb[0] = r;
	  amb[1] = g;
	  amb[2] = b;
	  amb[3] = a;
    break;
	case CiglMaterial::CL_DIF:
		dif[0] = r;
		dif[1] = g;
		dif[2] = b;
		dif[3] = a;
	  break;
  case CiglMaterial::CL_SPE:
		spe[0] = r;
		spe[1] = g;
		spe[2] = b;
		spe[3] = a;
	  break;
	default:

	  break;
  }
}


void CiglLight::setPos(const float x, const float y, const float z, const float w)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	pos[3] = w;

  ltyp = ( w >=0.9 ) ? LT_POINT : LT_DIRECTION;
}


void CiglLight::setAtt(const int c, const int l, const int q)
{
  cstatt  = c;
	linatt  = l;
	quadatt = q;
}


void CiglLight::setType(litType typ)
{
	ltyp = typ;
}


void CiglLight::setSpot(float cutoff, float sx, float sy, float sz, float expo)
{
	spotCutoff    = cutoff;
	spotDirect[0] = sx;
	spotDirect[1] = sy;
	spotDirect[2] = sz;
	spotExp       = expo;
}


void CiglLight::getCol(CiglMaterial::colType typ, float &r, float &g, float &b, float &a) const
{
	switch (typ) {
	case CiglMaterial::CL_AMB: 
		r = amb[0];
	  g = amb[1];
	  b = amb[2];
	  a = amb[3];
	  break;
	case CiglMaterial::CL_DIF:
		r = dif[0];
	  g = dif[1];
	  b = dif[2];
	  a = dif[3];
	  break;
	case CiglMaterial::CL_SPE:
		r = spe[0];
	  g = spe[1];
	  b = spe[2];
	  a = spe[3];
	  break;
	default:

	  break;
	}
}


void CiglLight::getPos(float &x, float &y, float &z, float &w ) const
{
	x = pos[0];
	y = pos[1];
	z = pos[2];
	w = pos[3];
}


void CiglLight::iglInit()
{
	// check if enabled ...
	/*
	GLenum   light = GL_LIGHT0 + lid;

	glLightfv(light, GL_AMBIENT, amb);
	glLightfv(light, GL_DIFFUSE, dif);
	glLightfv(light, GL_SPECULAR, spe);

	switch (ltyp) {
	case LT_POINT:
	  pos[3] = 1.0;
	  glLightfv(light, GL_POSITION, pos);
	  glLightf(light, GL_SPOT_CUTOFF, 180.0);
    break;
	case LT_DIRECTION:
		pos[3] = 0.0;
		glLightfv(light, GL_POSITION, pos);
		glLightf(light, GL_SPOT_CUTOFF, 180.0);
		break;
	case LT_SPOT:
		pos[3] = 1.0;
		glLightfv(light, GL_POSITION, pos);
		glLightf(light, GL_SPOT_CUTOFF, spotCutoff);
		glLightfv(light, GL_SPOT_DIRECTION, spotDirect);
		glLightf(light, GL_SPOT_EXPONENT, spotExp);
		break;
	default:

	  break;
	}

	glLighti(light, GL_CONSTANT_ATTENUATION, cstatt);
	glLighti(light, GL_LINEAR_ATTENUATION, linatt);
	glLighti(light, GL_QUADRATIC_ATTENUATION, quadatt);
*/
}


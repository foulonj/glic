/****************************************************************
 *
 * GLIC: ICS Graphics Library
 *
 * Original Authors:
 *   J. Foulon, P. Frey
 *
 ****************************************************************/
#ifndef __GLIC_MATH_H_
#define __GLIC_MATH_H_


/* implement a 3d vec4d (3 coordinates) */
class vec3d
{
public:
  double x,y,z;
  
  inline vec3d():x(0.),y(0.),z(0.)
		{ ;};
  inline vec3d(double x0,double y0,double z0)
		{ x = x0; y = y0; z = z0; };
  inline vec3d& operator=(const vec3d &v)
  { x = v.x; y = v.y; z = v.z; return *this; };
  //inline vec3d(vec3d &v)
  //	{ *this = v; };
  inline void null(void)
		{ x = y = z = 0.0; };
  inline double mag(void)
		{ return(double)sqrt(x*x+y*y+z*z); };
  inline void cross(vec3d &u,vec3d &v)
  {
    x = u.y*v.z - u.z*v.y;
    y = u.z*v.x - u.x*v.z;
    z = u.x*v.y - u.y*v.x;
  };
  inline void normalize(void)
  {
    double l = (double)sqrt(x*x+y*y+z*z);
    if ( l == 0.0 )  return;
    x /= l; y /= l; z /= l;
  };
  inline vec3d& operator*=(const double m)
  { x *= m; y *= m; z *= m;  return *this; };
  inline double& operator[](int i)
		{ return (&x)[i]; };
};


/* implement a 3d vec4d (4 coordinates) */
class vec4d
{
public:
  double x,y,z,w;
  
  inline vec4d():x(0.),y(0.),z(0.),w(0.)
		{ ;};
  inline vec4d(double x0=0.,double y0=0.,double z0=0.,double w0=0.)
		{ x = x0; y = y0; z = z0; w = w0; };
  inline vec4d(vec4d &v)
		{ *this = v; };
  inline void null(void)
		{ x = y = z = 0.0; };
  inline double mag(void)
		{ return(double)sqrt(x*x+y*y+z*z); };
  inline void cross(vec4d &u,vec4d &v)
  {
    x = u.y*v.z - u.z*v.y;
    y = u.z*v.x - u.x*v.z;
    z = u.x*v.y - u.y*v.x;
  };
  inline void normalize(void)
  {
    double l = (double)sqrt(x*x+y*y+z*z);
    if ( l == 0.0 )  return;
    x /= l; y /= l; z /= l;
  };
  inline double& operator[](int i)
		{ return (&x)[i]; };
};


/* implement a 4x4 matrix for linear transformations */
class mat4x4
{
public:
  double m[4][4];
  
  mat4x4(){cout << "\n\n Constructor: \n\n";memset(&m,0.,sizeof(m));}
  
  inline void null(void)
		{
      memset(&m,0.,sizeof(m)); }
  
  inline void load_identity(void)
  {
    memset(m,0.,sizeof(m));
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0;
  }
  
  double *array() { return &(m[0][0]); }
  
  
  //void setRotation(double ang,vec4d &dir);
  
  //mat4x4 operator* (mat4x4& m1);
  
  // Opérateurs d'accès :
  inline double & operator()(unsigned short int i,
                             unsigned short int j)
  {
    return m[i][j];
  }
  
  inline double operator()(unsigned short int i,
                           unsigned short int j) const
  {
    return m[i][j];
  }
  
};

#endif  /* __igl_math_h_ */

#include <glic/transform.h>


CglicTransform::CglicTransform():mat()
{
  mat.load_identity();
}

void CglicTransform::setRotation(double ang, vec3d axis)
{
  axe[0]=axis[0];
  axe[1]=axis[1];
  axe[2]=axis[2];
  angle = ang;
}


void CglicTransform::setTranslation(double x, double y, double z)
{
  translation[0] = x;
  translation[1] = y;
  translation[2] = z;
}

void CglicTransform::print()
{
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++)
      cout << mat(i,j) << "  ";
    cout << endl;
  }
}

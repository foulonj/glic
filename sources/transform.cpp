#include <glic/transform.h>


CglicTransform::CglicTransform():mat()
{
  mat.load_identity();
}

void CglicTransform::setTranslation(double x, double y, double z)
{
  mat(3,0) = translation[0] += x;
  mat(3,1) = translation[1] += y;
  mat(3,2) = translation[2] += z;
  
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++)
      cout << mat(i,j) << "  ";
    cout << endl;
  }
}

void CglicTransform::print()
{
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++)
      cout << mat(i,j) << "  ";
    cout << endl;
  }
}

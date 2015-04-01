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
  
  
  cout << "angle set Rotation: " << angle << " axis: " << axe[0] << " , " << axe[1] << " , " << axe[2] <<" " <<  endl;
}


void CglicTransform::setTranslation(double x, double y, double z)
{
  cout << "\n\n\t TRANSLATION\n";
  translation[0] = x;
  translation[1] = y;
  translation[2] = z;
  
  
  /*mat(3,0) = translation[0] += x;
  mat(3,1) = translation[1] += y;
  mat(3,2) = translation[2] += z;
  
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++)
      cout << mat(i,j) << "  ";
    cout << endl;
  }*/
}

void CglicTransform::print()
{
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++)
      cout << mat(i,j) << "  ";
    cout << endl;
  }
}

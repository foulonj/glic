#include <glic/transform.h>


CglicTransform::CglicTransform():mat()
{
  //mat.load_identity();
}

void CglicTransform::setRotation(double ang, glm::vec3 axis)
{
  axe = axis;
  angle = ang;
}


void CglicTransform::setTranslation(glm::vec3 tr)
{
  translation = tr;
}

void CglicTransform::print()
{
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++)
      cout << mat[i][j] << "  ";
    cout << endl;
  }
}

void CglicTransform::reset(){
  glm::vec3 null_vec3;
  setTranslation(null_vec3);
  setRotation(0., null_vec3);
}

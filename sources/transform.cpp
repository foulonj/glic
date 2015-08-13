#include <glic/transform.h>

void CglicTransform::setRotation(glm::mat4 hMat, glm::mat4 vMat)
{
  hRot = hMat;
  vRot = vMat;
}

void CglicTransform::setTranslation(glm::vec3 translation)
{
  tr = translation;
}

void CglicTransform::reset(){
  tr = glm::vec3(0.0f);
  hRot = vRot = glm::mat4(1.0f);
}

void CglicTransform::print()
{
  cout << "horizontal rotation:" << endl;
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++)
      cout << hRot[i][j] << "  ";
    cout << endl;
  }
  cout << "vertical rotation:" << endl;
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++)
      cout << vRot[i][j] << "  ";
    cout << endl;
  }
}

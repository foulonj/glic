#include <glic/canvas.h>
#include <glic/keyboard.h>
#include <glic/cube.h>

extern CglicCanvas *pcv;

void CglicKeyboard::keyColor(unsigned char key,int x,int y) {
  pcv->winid();
}

void CglicKeyboard::special(unsigned char key, int x, int y)
{
  pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];
  glm::vec3 moveX(0.005, 0., 0.);
  glm::vec3 moveZ(0., 0., 0.005);
  int state = 0;
  switch (key) {
    case GLUT_KEY_LEFT:
      cout << "GLUT_KEY_LEFT" << endl;
      for (unsigned int iObj = 0; iObj < scene->listObject.size(); iObj++){
        if (scene->listObject[iObj]->state == CglicCube::TO_SEL){
          glPushMatrix();
          scene->listObject[iObj]->transform.setTranslation(-moveX);
          glPopMatrix();
          state = 1;
        };
      }
      if (state == 0)
        scene->transform.setTranslation(-moveX);
      break;
    case GLUT_KEY_RIGHT:
      cout << "GLUT_KEY_RIGHT TRANSFORM SCENE" << endl;
      for (unsigned int iObj = 0; iObj < scene->listObject.size(); iObj++){
        if (scene->listObject[iObj]->state == CglicCube::TO_SEL){
          glPushMatrix();
          scene->listObject[iObj]->transform.setTranslation(moveX);
          glPopMatrix();
          state = 1;
        };
      }
      if (state == 0)
        scene->transform.setTranslation(moveX);
      break;
    case GLUT_KEY_DOWN:
      cout << "GLUT_KEY_DOWN" << endl;
      for (unsigned int iObj = 0; iObj < scene->listObject.size(); iObj++){
        if (scene->listObject[iObj]->state == CglicCube::TO_SEL){
          glPushMatrix();
          scene->listObject[iObj]->transform.setTranslation(-moveZ);
          glPopMatrix();
          state = 1;
        }
      }
      if (state == 0)
        scene->transform.setTranslation(-moveZ);
      break;
    case GLUT_KEY_UP:
      cout << "GLUT_KEY_UP" << endl;
      for (unsigned int iObj = 0; iObj < scene->listObject.size(); iObj++){
        if (scene->listObject[iObj]->state == CglicCube::TO_SEL){
          glPushMatrix();
          scene->listObject[iObj]->transform.setTranslation(moveZ);
          glPopMatrix();
          state = 1;
        }
      }
      if (state == 0)
        scene->transform.setTranslation(moveZ);
      break;
    default:
      break;
  }
}

void CglicKeyboard::keyboard(unsigned char key, int x, int y)
{
  pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];
  // QUIT
  if ( key == 'q' || key == 27 )
    exit(0);

  // SELECT
  if ( key =='s')
  {
    selection+=1;
    if (selection >= scene->listObject.size())
      selection = -1;

    for (unsigned int i = 0; i < scene->listObject.size(); i++)
      scene->listObject[i]->state = CglicObject::TO_ON;
    scene->state = CglicScene::TO_SEL;
    if (selection >= 0){
      scene->listObject[selection]->state = CglicObject::TO_SEL;
      scene->state = CglicScene::TO_ON;
    };
  };

  // ZOOM
  if((key == 'z') || (key == 'Z')){
    double zoomFactor = 0.1;
    glm::vec3 zoom = (scene->center - pcv->window[pcv->winid()].view.m_cam);
    zoom *= zoomFactor;
    if (key == 'z' ){
      cout << "ZOOM IN \n";
      scene->transform.setTranslation(zoom);
    }
    else if (key == 'Z' ){
      cout << "ZOOM OUT \n";
      scene->transform.setTranslation(-zoom);
    };
  }

  // BB and WIREFRAME
  if (key == 'b' ){
    for (unsigned int i = 0; i < scene->listObject.size(); i++)
      scene->listObject[i]->activeBB();
  };
  if (key == 'm' ){
    for (unsigned int i = 0; i < scene->listObject.size(); i++)
      scene->listObject[i]->activeMesh();
  };
}

#include <glic/canvas.h>
#include <glic/keyboard.h>
#include <glic/cube.h>

extern CglicCanvas *pcv;

void CglicKeyboard::keyColor(unsigned char key,int x,int y) {
  pcv->winid();
}

void setTranslation(glm::vec3 tr, int &state){
  pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];
  for (unsigned int iObj = 0; iObj < scene->listObject.size(); iObj++){
    pCglicObject obj = scene->listObject[iObj];
    if (obj->state == CglicCube::TO_SEL){
      obj->transform.setTranslation(tr);
      state = 1;
    }
  }
  if (state == 0)
    scene->transform.setTranslation(tr);
}

void CglicKeyboard::special(unsigned char key, int x, int y)
{
  glm::vec3 moveX(0.005, 0., 0.);
  glm::vec3 moveZ(0., 0., 0.005);
  int state = 0;
  switch (key) {
    case GLUT_KEY_LEFT:
      cout << "GLUT_KEY_LEFT" << endl;
      setTranslation(-moveX, state);
      break;
    case GLUT_KEY_RIGHT:
      cout << "GLUT_KEY_RIGHT TRANSFORM SCENE" << endl;
      setTranslation(moveX, state);
      break;
    case GLUT_KEY_DOWN:
      cout << "GLUT_KEY_DOWN" << endl;
      setTranslation(-moveZ, state);
      break;
    case GLUT_KEY_UP:
      cout << "GLUT_KEY_UP" << endl;
      setTranslation(moveZ, state);
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
    glm::vec3 zoom = (scene->m_cam);
    zoom *= zoomFactor;
    if (key == 'z' ){
      cout << "ZOOM IN \n";
      scene->m_cam -= zoom;
    }
    else if (key == 'Z' ){
      cout << "ZOOM OUT \n";
      scene->m_cam += zoom;
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

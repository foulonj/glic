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
  pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];

  if(key!=lastKey){
    if (scene->state == CglicObject::TO_SEL){
      scene->transform.lastMatrices.push_back(scene->MODEL);
    }
    for (unsigned int i = 0; i < scene->listObject.size(); i++){
      CglicObject *obj = scene->listObject[i];
      if (obj->state == CglicCube::TO_SEL){
        obj->transform.lastMatrices.push_back(obj->MODEL);
      }
    }
  }

  //glm::vec3 moveX(0.005, 0., 0.);
  //glm::vec3 moveZ(0., 0., 0.005);
  glm::vec3 moveX = 0.01f * scene->m_right;
  glm::vec3 moveZ = 0.01f * scene->m_up;
  int state = 0;
  switch (key) {
    case GLUT_KEY_LEFT:
      cout << "GLUT_KEY_LEFT" << endl;
      setTranslation(-moveX, state);
      break;
    case GLUT_KEY_RIGHT:
      cout << "GLUT_KEY_RIGHT" << endl;
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
  lastKey = key;
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
    double *fov = &scene->view->m_fovy;
    double zoomFactor = 0.02;
    //glm::vec3 zoom = (-scene->m_look + scene->center) * zoomFactor;
    float zoom = 0;
    if (key == 'z' )
      *fov -= zoomFactor;
    else if (key == 'Z' )
      *fov += zoomFactor;
    if(*fov<69.2){*fov=69.2;}
    if(*fov>70.5){*fov=70.5;}
  }

  // BB
  if (key == 'b' ){
    for (unsigned int i = 0; i < scene->listObject.size(); i++)
      scene->listObject[i]->activeBB();
  }

  // Wireframe
  if (key == 'm' ){
    for (unsigned int i = 0; i < scene->listObject.size(); i++)
      scene->listObject[i]->activeMesh();
  }

  //Smooth to flat shading
  if (key == 'f'){
    for (unsigned int i = 0; i < scene->listObject.size(); i++)
      if( scene->listObject[i]->state == CglicObject::TO_SEL)
        scene->listObject[i]->useSmoothShading = !scene->listObject[i]->useSmoothShading;
  }

  //Look at center of selected object
  if (key == 'c'){
    bool noneSelected = true;
    glm::vec3 newCenter;
    for (unsigned int i = 0; i < scene->listObject.size(); i++){
      if( scene->listObject[i]->state == CglicObject::TO_SEL){
        noneSelected = false;
        newCenter = scene->listObject[i]->center;
      }
    }
    if(noneSelected)
      newCenter = glm::vec3(0,0,0);
    scene->center = newCenter;
    scene->axis->center = newCenter;
  }

  //Reset rotations of objects
  if (key == 'r'){
    //Si la scène est sélectionnée
    if(scene->state == CglicObject::TO_SEL){
      if(scene->transform.lastMatrices.size()>0){
        scene->MODEL = scene->transform.lastMatrices.back();
        scene->center = glm::vec3(glm::vec4(scene->MODEL[3]));
        scene->transform.lastMatrices.pop_back();
      }
    }
    for(int i = 0 ; i < scene->listObject.size() ; i++){
      pCglicObject obj = scene->listObject[i];
      if(obj->state == CglicObject::TO_SEL){
        if(obj->transform.lastMatrices.size()>0){
          obj->MODEL = obj->transform.lastMatrices.back();
          obj->center = glm::vec3(glm::vec4(obj->MODEL[3]));
          obj->transform.lastMatrices.pop_back();
        }
      }
    }
  }

  if(lastKey=='t'){
    if(key=='x'){
      cout << "constrainRotation to x" << endl;
    }
  }

  lastKey = key;

}

void CglicKeyboard::keyboardUp(unsigned char key, int x, int y){}


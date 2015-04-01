#include <glic/canvas.h>
#include <glic/keyboard.h>
#include <glic/cube.h>

extern CglicCanvas *pcv;

void CglicKeyboard::keyColor(unsigned char key,int x,int y) {
  pcv->winid();
}

void CglicKeyboard::special(unsigned char key, int x, int y)
{
  int state = 0;
  switch (key) {
    case GLUT_KEY_LEFT:
      cout << "GLUT_KEY_LEFT" << endl;
      for (unsigned int iObj = 0; iObj < pcv->scene[pcv->window[pcv->winid()].ids]->listObject.size(); iObj++){
        if (pcv->scene[pcv->window[pcv->winid()].ids]->listObject[iObj]->state == CglicCube::TO_SEL){
          glPushMatrix();
          pcv->scene[pcv->window[pcv->winid()].ids]->listObject[iObj]->transform.setTranslation(-1.0,0.,0.);
          glPopMatrix();
          state = 1;
        };
      }
      if (state == 0)
        pcv->scene[pcv->window[pcv->winid()].ids]->transform.setTranslation(-0.5,0.,0.);
      break;
    case GLUT_KEY_RIGHT:
      cout << "GLUT_KEY_RIGHT TRANSFORM SCENE" << endl;
      for (unsigned int iObj = 0; iObj < pcv->scene[pcv->window[pcv->winid()].ids]->listObject.size(); iObj++){
        if (pcv->scene[pcv->window[pcv->winid()].ids]->listObject[iObj]->state == CglicCube::TO_SEL){
          glPushMatrix();
          pcv->scene[pcv->window[pcv->winid()].ids]->listObject[iObj]->transform.setTranslation(1.0,0.,0.);
          glPopMatrix();
          state = 1;
        };
      }
      if (state == 0)
        pcv->scene[pcv->window[pcv->winid()].ids]->transform.setTranslation(0.5,0.,0.);
      break;
    case GLUT_KEY_DOWN:
      cout << "GLUT_KEY_DOWN" << endl;
      for (unsigned int iObj = 0; iObj < pcv->scene[pcv->window[pcv->winid()].ids]->listObject.size(); iObj++){
        if (pcv->scene[pcv->window[pcv->winid()].ids]->listObject[iObj]->state == CglicCube::TO_SEL){
          glPushMatrix();
          pcv->scene[pcv->window[pcv->winid()].ids]->listObject[iObj]->transform.setTranslation(.0,-1.,0.);
          glPopMatrix();
          state = 1;
        }
      }
      if (state == 0)
        pcv->scene[pcv->window[pcv->winid()].ids]->transform.setTranslation(0.,-0.5,0.);
      break;
    case GLUT_KEY_UP:
      cout << "GLUT_KEY_UP" << endl;
      for (unsigned int iObj = 0; iObj < pcv->scene[pcv->window[pcv->winid()].ids]->listObject.size(); iObj++){
        if (pcv->scene[pcv->window[pcv->winid()].ids]->listObject[iObj]->state == CglicCube::TO_SEL){
          glPushMatrix();
          pcv->scene[pcv->window[pcv->winid()].ids]->listObject[iObj]->transform.setTranslation(.0,1.,0.);
          glPopMatrix();
          state = 1;
        }
      }
      if (state == 0)
        pcv->scene[pcv->window[pcv->winid()].ids]->transform.setTranslation(0.,0.5,0.);
      break;
    default:
      break;
  }
}

void CglicKeyboard::keyboard(unsigned char key, int x, int y)
{
  //  ESC = end
  if ( key == 'q' || key == 27 )
    exit(0);
  if ( key =='s')
  {
    selection+=1;
    if (selection >= pcv->scene[pcv->window[pcv->winid()].ids]->listObject.size())
      selection = -1;

    for (unsigned int i = 0; i < pcv->scene[pcv->window[pcv->winid()].ids]->listObject.size(); i++)
      pcv->scene[pcv->window[pcv->winid()].ids]->listObject[i]->state = CglicObject::TO_ON;
    pcv->scene[pcv->window[pcv->winid()].ids]->state = CglicScene::TO_SEL;
    if (selection >= 0){
      pcv->scene[pcv->window[pcv->winid()].ids]->listObject[selection]->state = CglicObject::TO_SEL;
      pcv->scene[pcv->window[pcv->winid()].ids]->state = CglicScene::TO_ON;
    };
  };
  if (key == 'z' ){
    cout << "ZOOM IN \n";
    pcv->scene[pcv->window[pcv->winid()].ids]->transform.setTranslation(0.,0.,0.1);
  }
  else if (key == 'Z' ){
    cout << "ZOOM OUT \n";
    pcv->scene[pcv->window[pcv->winid()].ids]->transform.setTranslation(0.,0.,-0.1);
  }
}
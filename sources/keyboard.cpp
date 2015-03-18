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
      for (unsigned int iObj = 0; iObj < pcv->object.size(); iObj++){
        if (pcv->object[iObj]->state == CglicCube::TO_SEL){
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
      for (unsigned int iObj = 0; iObj < pcv->object.size(); iObj++){
        if (pcv->object[iObj]->state == CglicCube::TO_SEL){
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
      for (unsigned int iObj = 0; iObj < pcv->object.size(); iObj++){
        if (pcv->object[iObj]->state == CglicCube::TO_SEL){
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
      for (unsigned int iObj = 0; iObj < pcv->object.size(); iObj++){
        if (pcv->object[iObj]->state == CglicCube::TO_SEL){
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
  if ( key =='s')  /* backcolor */
  {
    selection+=1;
    if (selection >= pcv->object.size())
      selection = -1;
    for (unsigned int i = 0; i < pcv->object.size(); i++)
      pcv->object[i]->state = CglicObject::TO_ON;
    if (selection >= 0)
      pcv->object[selection]->state = CglicObject::TO_SEL;
    
    
    cout << "\n\n Selection " << selection << endl;
  };
  if ( key =='b')  /* backcolor */
    keyColor('b',0,0);
  /*else if ( key == 'c' ) {
   int ido = pcv->glicObject(new CglicCube(0., 0.2, 0.7, 0.1));
   
   cout << "pcv->winid(): " << pcv->winid() << endl;
   cout << "pcv->scene[pcv->winid()]->id():  " << pcv->window[pcv->winid()].ids << endl;
   
   cout << "pcv->scene[pcv->winid()]->id(): END " << endl;
   //pcv->glicSetObject(ido, pcv->scene[pcv->winid()]->id());
   glutPostRedisplay();
   }*/
  else if ( key == 's' ) {
    glutPostRedisplay();
  }
  
}
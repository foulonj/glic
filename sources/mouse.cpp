#include <glic/canvas.h>
#include <glic/mouse.h>
#include <glic/cube.h>
extern CglicCanvas *pcv;


CglicMouse::CglicMouse()
{
  memset((void*)this, 0, sizeof(*this));
  m_button[0] = m_button[1] = m_button[2] = false;
  //m_key = TM_NONE;
  isPressed = isReleased = false;
  arcball = false;
  currPos = glm::vec2(0);
  lastPos = glm::vec2(0);
  lastPassivePos = glm::vec2(0);
  m_pos   = glm::vec3(0);
}

glm::vec3 get_arcball_vector(glm::vec2 cursor) {
  int W = pcv->window[pcv->winid()].view.width;
  int H = pcv->window[pcv->winid()].view.height;
  glm::vec3 P = glm::vec3(1.0*cursor.x/W*2 - 1.0,
                          1.0*cursor.y/H*2 - 1.0,
                          0);
  P.y = -P.y;
  float OP_squared = P.x*P.x + P.y*P.y;
  if (OP_squared <= 1*1)
    P.z = sqrt(1*1 - OP_squared);  // Pythagore
  else
    P = glm::normalize(P);         // nearest point
  return P;
}

void CglicMouse::motion(int x, int y)
{
  pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];

  //GLuint   tm;
  //glm::vec3    v;
  //tm = glutGet(GLUT_ELAPSED_TIME);
  //if ( tm < m_tm + 40 )  return;
  //m_tm = tm;

  if(arcball)
    currPos = glm::vec2(x,y);

  if (currPos != lastPos) {
    glm::vec3 va = get_arcball_vector(lastPos);
    glm::vec3 vb = get_arcball_vector(currPos);
    glm::vec3 d  = vb-va;
    //float angle = acos(min(1.0f, glm::dot(va, vb)));
    //glm::vec3 axis = glm::cross(va, vb);
    glm::mat4 ID = glm::mat4(1.0f);
    glm::mat4 ROT = glm::rotate(ID, 5.0f * d.x, scene->m_up) * glm::rotate(ID, 5.0f * -d.y, scene->m_right);

    //On applique la rotation
    if (scene->isSelected())
      scene->transform.setRotation(ROT);
    for (unsigned int i = 0; i < scene->listObject.size(); i++)
      if (scene->listObject[i]->isSelected())
        scene->listObject[i]->transform.setRotation(ROT);

    lastPos = currPos;
  }
  if ( m_button[0] ){}
}

void CglicMouse::passiveMotion(int x, int y){
  pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];
  glm::vec2 currPassivePos(x,y);
  if (currPassivePos != lastPassivePos) {
    glm::vec3 va = get_arcball_vector(lastPassivePos);
    glm::vec3 vb = get_arcball_vector(currPassivePos);
    glm::vec3 d  = vb-va;
    //Si un objet est sélectionné
    for (unsigned int i = 0; i < scene->listObject.size(); i++){
      CglicObject *obj = scene->listObject[i];
      if (obj->isSelected()){
        if(obj->isConstrainedInRotation())
          obj->setConstrainedRotation(5.0f * d.y);
        else if(obj->isConstrainedInTranslation())
          obj->setConstrainedTranslation(1.0f * (d.y));
      }
    }
    lastPassivePos = currPassivePos;
  }
}


void CglicMouse::mouse(int b, int s, int x, int y)
{
  pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];

  //GLint  key;
  //m_tm = glutGet(GLUT_ELAPSED_TIME);
  //lastPos = glm::vec2(x,y);

  //Sauvegarde des opérations
  isPressed  = (s == GLUT_DOWN);
  isReleased = (s == GLUT_UP  );

  if(isReleased){
    for (unsigned int i = 0; i < scene->listObject.size(); i++){
      CglicObject *obj = scene->listObject[i];
      if ( (obj->isConstrainedInRotation()) || ((obj->isConstrainedInTranslation())) )
        obj->unConstrain();
    }
  }

  switch(b)
  {
    case GLUT_LEFT_BUTTON:
      m_button[0] = ((GLUT_DOWN==s)?1:0);

      //A l'appui, on enregistre le MODEL
      if(isPressed){
        if (scene->isSelected())
          scene->saveTransformations();
        for (unsigned int i = 0; i < scene->listObject.size(); i++){
          CglicObject *obj = scene->listObject[i];
          if (obj->isSelected()){
            if((!obj->isConstrainedInRotation()) && (!obj->isConstrainedInTranslation()))
              obj->saveTransformations();
          }
        }
      }

      //currPos = glm::vec2( glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) );
      //m_pos = projsph(glm::vec2(0.));


      //key = glutGetModifiers();
      //m_key = TM_NONE;
      //if ( glutGetModifiers() & GLUT_ACTIVE_SHIFT){
        //cout << "\n\n\t Active shift \n\n"; m_key = TM_SHIFT;
      //}
      //if (glutGetModifiers() & GLUT_ACTIVE_CTRL){
        //m_key = TM_CTRL;
        //pcv->glicPickObject(x, y);
      //}
      break;

    case GLUT_MIDDLE_BUTTON:
      m_button[1] = ((GLUT_DOWN==s)?1:0);
      break;

    case GLUT_RIGHT_BUTTON:
      //Remplacer
      m_button[2] = ((GLUT_DOWN==s)?1:0);
      if(s==GLUT_UP){
        pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];
        unsigned char pixel[3];
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT,viewport);

        for(int i = 0 ; i < scene->listObject.size() ; i++)
          if(!scene->listObject[i]->isSelected())
            scene->listObject[i]->pickingDisplay();

        glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);
        int pickedID = pixel[0];
        glFlush();

        cout << "Picked: " << pickedID << endl;
        bool match = false;

        for(int i = 0 ; i < scene->listObject.size() ; i++){
          if(scene->listObject[i]->isPicked(pickedID)){
            scene->listObject[i]->select();
            scene->unSelect();
            match = true;
          }
        }

        if(match){
          for(int i = 0 ; i < scene->listObject.size() ; i++)
            if(!scene->listObject[i]->isPicked(pickedID))
              scene->listObject[i]->unSelect();
        }

        else{
          for(int i = 0 ; i < scene->listObject.size() ; i++)
            scene->listObject[i]->unSelect();
          scene->select();
        }

        if(match)
          scene->reOrderObjects();
      }

      break;
  }

  //ARCBALL
  if((b == GLUT_LEFT_BUTTON) && (s == GLUT_DOWN)){
    arcball = true;
    lastPos = currPos = glm::vec2(x,y);
  }
  else
    arcball = false;

}


void CglicMouse::transform()
{}

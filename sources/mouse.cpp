#include <glic/canvas.h>
#include <glic/mouse.h>
#include <glic/cube.h>
extern CglicCanvas *pcv;


CglicMouse::CglicMouse()
{
  memset((void*)this, 0, sizeof(*this));
  m_ang = 0.0;
  m_trx  = m_try  = 0.0;
  m_otrx = m_otry = 0.0;
  m_button[0] = m_button[1] = m_button[2] = 0;
  m_zoom  = 0.0;
  m_pos[0] = m_pos[1] = m_pos[2] = 0.0;
  m_axe[0] = m_axe[1] = m_axe[2] = 0.0;
  m_key = TM_NONE;
}

/* project point onto hemi-sphere */
glm::vec3 CglicMouse::projsph(glm::vec2 diff) {
  double   d1,d2;
  glm::vec3 v;
  v.x =  2.0*(double)diff.x / (float)currPos.x;
  v.y = -2.0*(double)diff.y / (float)currPos.y;
  d1 = v.x*v.x + v.y*v.y;
  if ( d1 > 0.0 ) {
    d2 = sqrt(d1);
    if ( d2 > 1.0 )
      d2 = 1.0;
    v.z = cos(M_PI_2 * d2);
    v /= glm::length(v);
  }
  return v;
}


void CglicMouse::motion(int x, int y)
{
  pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];

  GLuint   tm;
  glm::vec3    v;

  tm = glutGet(GLUT_ELAPSED_TIME);
  if ( tm < m_tm + 40 )  return;
  m_tm = tm;

  glm::vec2 diffPos = glm::vec2(x,y) - lastPos;

  if ( m_button[0] ){
    v = projsph(diffPos);
    glm::vec3 d = v - m_pos;
    m_pos = v;
    //Si la scène est sélectionnée
    if (scene->state == CglicScene::TO_SEL){
      //Calcul des matrices de rotation
      glm::quat hQuat  = glm::angleAxis(- 2.0f * d.x, scene->m_up);
      glm::mat4 hRot   = glm::toMat4(hQuat);
      glm::quat vQuat  = glm::angleAxis(2.0f * d.y, scene->m_right);
      glm::mat4 vRot   = glm::toMat4(vQuat);
      scene->transform.setRotation(hRot, vRot);
    }
    //Si un objet est sélectionné
    else{
      for (unsigned int i = 0; i < scene->listObject.size(); i++){
        if (scene->listObject[i]->state == CglicCube::TO_SEL){
          glm::quat hQuat  = glm::angleAxis(2.0f * d.x,  scene->m_up);
          glm::mat4 hRot   = glm::toMat4(hQuat);
          glm::quat vQuat  = glm::angleAxis(-2.0f * d.y, scene->m_right);
          glm::mat4 vRot   = glm::toMat4(vQuat);
          scene->listObject[i]->transform.setRotation(hRot, vRot);
        }
      }
    }
  }
}


void CglicMouse::mouse(int b, int s, int x, int y)
{
  GLint  key;
  m_tm = glutGet(GLUT_ELAPSED_TIME);
  lastPos = glm::vec2(x,y);

  switch(b)
  {
    case GLUT_LEFT_BUTTON:
      m_button[0] = ((GLUT_DOWN==s)?1:0);

      currPos = glm::vec2( glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) );

      m_pos = projsph(glm::vec2(0.));
      key = glutGetModifiers();
      //cout << "\n\n\tno active shift \n\n";
      m_key = TM_NONE;
      if ( glutGetModifiers() & GLUT_ACTIVE_SHIFT){cout << "\n\n\t Active shift \n\n"; m_key = TM_SHIFT;};
      if (glutGetModifiers() & GLUT_ACTIVE_CTRL){
        //cout << "\n GLUT Actve CTRL\n" << endl;
        m_key = TM_CTRL;
        pcv->glicPickObject(x, y);
      };

      break;


    case GLUT_MIDDLE_BUTTON:
      m_button[1] = ((GLUT_DOWN==s)?1:0);
      break;

    case GLUT_RIGHT_BUTTON:
      m_button[2] = ((GLUT_DOWN==s)?1:0);
      if(s==GLUT_UP){
        pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];
        for(int i = 0 ; i < scene->listObject.size() ; i++)
          scene->listObject[i]->pickingDisplay();
        unsigned char pixel[3];
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT,viewport);
        glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);
        int pickedID = pixel[0];
        glFlush();

        cout << "Picked: " << pickedID << endl;
        bool match = false;

        for(int i = 0 ; i < scene->listObject.size() ; i++){
          if(pickedID == scene->listObject[i]->pickingID){
            scene->listObject[i]->state = CglicCube::TO_SEL;
            match = true;
            scene->state = CglicScene::TO_ON;
          }
        }

        if(match){
          for(int i = 0 ; i < scene->listObject.size() ; i++)
            if(pickedID!=scene->listObject[i]->pickingID)
              scene->listObject[i]->state = CglicObject::TO_OFF;
        }

        else{
          for(int i = 0 ; i < scene->listObject.size() ; i++)
            scene->listObject[i]->state = CglicObject::TO_OFF;
          scene->state = CglicScene::TO_SEL;
        }

        if(match)
          scene->reOrderObjects();
      }

      break;
  }
}


void CglicMouse::transform()
{}

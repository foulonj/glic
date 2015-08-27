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

  //if(arcball)
  currPos = glm::vec2(x,y);

  if (currPos != lastPos) {

    glm::vec3 va = get_arcball_vector(lastPos);
    glm::vec3 vb = get_arcball_vector(currPos);
    glm::vec3 d  = vb-va;
    //float angle = acos(min(1.0f, glm::dot(va, vb)));
    //glm::vec3 axis = glm::cross(va, vb);

    float dX = d.x;
    float dY = d.y;
    glm::mat4 ID = glm::mat4(1.0f);



    //On applique la rotation
    if(m_button[0]){
      //On tourne par rapport à un axe vertical
        glm::mat4 ROT = glm::mat4( glm::angleAxis(-5.0f * dY, scene->m_right) * glm::angleAxis(5.0f * dX, glm::vec3(0,1,0))  );
        glm::mat4 ROTOBJECT = glm::mat4( glm::angleAxis(5.0f * dX, glm::vec3(0,1,0))  );
      //On tourne par rapport à ce qu'on voit
        //glm::mat4 ROT = glm::mat4( glm::angleAxis(-5.0f * dY, scene->m_right) * glm::angleAxis(5.0f * dX, scene->m_up)       );

      if (scene->isSelected())
        scene->transform.setRotation(ROT);
      for (unsigned int i = 0; i < scene->listObject.size(); i++)
        if (scene->listObject[i]->isSelected())
          scene->listObject[i]->transform.setRotation(ROTOBJECT);
    }

    //cout << m_button[0] << m_button[1] << m_button[2] << endl;
    if(m_button[1]){
      glm::vec3 tr = 0.5f * (dX * glm::vec3(scene->m_right.x,0,scene->m_right.z) + dY * glm::vec3(scene->m_up.x,0,scene->m_up.z));
      //glm::vec3 tr = 0.5f * (dX * glm::vec3(1,0,0) - dY * glm::vec3(0,0,1));
      //glm::vec3 tr = dX * scene->m_right + dY * scene->m_up;
      if (scene->isSelected())
        scene->transform.setTranslation(tr);
      for (unsigned int i = 0; i < scene->listObject.size(); i++)
        if (scene->listObject[i]->isSelected())
          scene->listObject[i]->transform.setTranslation(tr);
    }

    lastPos = currPos;
  }
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

  m_button[0] = m_button[1] = m_button[2] = false;

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
      m_button[2] = ((GLUT_DOWN==s)?1:0);

      bool  ctrl = ((glutGetModifiers() && GLUT_ACTIVE_CTRL) ? 1:0);

      if(s==GLUT_UP){
        pCglicScene scene = pcv->scene[pcv->window[pcv->winid()].ids];

        int pickedID = scene->getPickedObjectID(x, y);
        bool match = false;
        int  IndPicked = -1;

        //On récupère l'indice de l'objet pické
        for(int i = 0 ; i < scene->listObject.size() ; i++){
          if (scene->listObject[i]->isPicked(pickedID)){
            match = true;
            IndPicked = i;
          }
        }
        //Si on ne picke pas, on déselectionne tout et on sélectionne la scène
        if(!match){
          scene->select();
          for(int i = 0 ; i < scene->listObject.size() ; i++)
            scene->listObject[i]->unSelect();
        }

        if(match){
           //On change l'état de sélection de l'objet pické
          scene->listObject[IndPicked]->toogleSelected();

          if(!ctrl){
            //On déselectionne tous les autres objets
            for(int i = 0 ; i < scene->listObject.size() ; i++)
              if(i!=IndPicked)
                scene->listObject[i]->unSelect();
          }

          //Si un selectionné, deselectionne la scène
          bool someSelected = false;
          for(int i = 0 ; i < scene->listObject.size() ; i++)
            if(scene->listObject[i]->isSelected())
              someSelected = true;
          if(someSelected)
            scene->unSelect();
          else
            scene->select();

          //On met le dernier objet pické au dessus de tous les autres si il est sélectionné
          if(scene->listObject[IndPicked]->isSelected())
            scene->reOrderObjects(IndPicked);
        }//End match
      }//End GLUT_UP
      break;

  }//End switch

  arcball = ((m_button[0])?1:0);
  lastPos = currPos = glm::vec2(x,y);
}


void CglicMouse::transform()
{}

#include <glic/scene.h>


// object constructor
CglicScene::CglicScene():transform(){
  state = TO_SEL;
  m_up = glm::vec3(0., 1., 0.);
}
CglicScene::~CglicScene(){}


void CglicScene::addObject(pCglicObject object)
{
  //cout << "  -- [add Object to scene n." << ids << "]" << endl;
  listObject.push_back(object);
}

void CglicScene::update_matrices()
{
  m_look = -m_cam;
  m_right = glm::cross(m_look, m_up);
  VIEW = glm::lookAt(m_cam, m_look, m_up);
  PROJ = glm::perspective(view->m_fovy, view->ratio, view->m_znear, view->m_zfar);
}

void CglicScene::applyTransformation()
{
  glm::vec3 tr = transform.translation;
  glm::vec3 ax = transform.axe;

  /*
  for (int iObj = 0; iObj < listObject.size(); iObj++){
    listObject[iObj]->MODEL = glm::translate(listObject[iObj]->MODEL, tr);
    if(ax != glm::vec3(0.0f))
      listObject[iObj]->MODEL = glm::rotate(listObject[iObj]->MODEL, (float)transform.angle, ax);
  }*/

  glTranslatef(tr.x, tr.y, tr.z);
  glRotatef(transform.angle, ax.x, ax.y, ax.z);

  transform.reset();
  center += tr;
}



void CglicScene::display()
{

  for (int iObj = 0; iObj < listObject.size(); iObj++){
    glPushMatrix();
    glLoadIdentity();

    listObject[iObj]->applyTransformation();

    glMultMatrixd(listObject[iObj]->m_tr);
    glGetDoublev(GL_MODELVIEW_MATRIX,listObject[iObj]->m_tr);
    glPopMatrix();
    glPushMatrix();
    glMultMatrixd(listObject[iObj]->m_tr);

    listObject[iObj]->display();

    glPopMatrix();
  }
}


void CglicScene::glicInit()
{
  //  glEnable(GL_DEPTH_TEST);	// Active le test de profondeur
  // 	glEnable(GL_LIGHTING);	// Active l'éclairage
  // 	glEnable(GL_LIGHT0);
}

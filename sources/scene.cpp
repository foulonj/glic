#include <glic/scene.h>

// object constructor
CglicScene::CglicScene():transform(){
  state = TO_SEL;
  m_up = glm::vec3(0., 1., 0.);
  m_cam = glm::vec3(0,0,2);
}
CglicScene::~CglicScene(){}


void CglicScene::addObject(pCglicObject object)
{
  //cout << "  -- [add Object to scene n." << ids << "]" << endl;
  listObject.push_back(object);
}

void CglicScene::update_matrices()
{
  //Update vectors
  bool lookAtZero = true;
  if(lookAtZero)
    m_look = -m_cam;
  else
    m_look = center - m_cam;
  m_right = glm::cross(m_look, m_up);

  //Update Matrices
  VIEW = glm::lookAt(m_cam, m_look, m_up);
  PROJ = glm::perspective(view->m_fovy, view->ratio, view->m_znear, view->m_zfar);

  //Send matrices to objects
  for(int i = 0 ; i < listObject.size() ; i++){
    listObject[i]->pPROJ = &PROJ;
    listObject[i]->pVIEW = &VIEW;
  }

  //DEBUG
  //Vectors
  cout << "cam   = " << m_cam.x   << " " << m_cam.y   << " " << m_cam.z   << endl;
  cout << "look  = " << m_look.x  << " " << m_look.y  << " " << m_look.z  << endl;
  cout << "up    = " << m_up.x    << " " << m_up.y    << " " << m_up.z    << endl;
  cout << "right = " << m_right.x << " " << m_right.y << " " << m_right.z << endl;
  //Matrices
  cout << endl;
  cout << " MODEL " << endl;
  int iObj = 0;
  for(int i = 0 ; i < 4 ; i++)
    cout << listObject[iObj]->MODEL[i][0] << " " << listObject[iObj]->MODEL[i][1] << " " << listObject[iObj]->MODEL[i][2] << " " << listObject[iObj]->MODEL[i][3] << endl;
  cout << endl;
  cout << " VIEW " << endl;
  for(int i = 0 ; i < 4 ; i++)
    cout << VIEW [i][0] << " " << VIEW [i][1] << " " << VIEW [i][2] << " " << VIEW [i][3] << endl;
  cout << endl;
  cout << " PROJ " << endl;
  for(int i = 0 ; i < 4 ; i++)
    cout << PROJ[i][0] << " " << PROJ[i][1] << " " << PROJ[i][2] << " " << PROJ[i][3] << endl;
  cout << endl;

}

void CglicScene::applyTransformation()
{
  bool VBOs = false;
  glm::vec3 tr = transform.translation;
  glm::vec3 ax = transform.axe;

  if(VBOs){
    for (int iObj = 0; iObj < listObject.size(); iObj++){
      listObject[iObj]->MODEL = glm::translate(listObject[iObj]->MODEL, tr);
      if(ax != glm::vec3(0.0f))
        listObject[iObj]->MODEL = glm::rotate(listObject[iObj]->MODEL, (float)transform.angle, ax);
    }
  }
  else{
    glTranslatef(tr.x, tr.y, tr.z);
    glRotatef(transform.angle, ax.x, ax.y, ax.z);
  }

  transform.reset();
  center += tr;
}



void CglicScene::display()
{
  bool VBOs = false;
  for (int iObj = 0; iObj < listObject.size(); iObj++){
    if(!VBOs){
      glPushMatrix();
      glLoadIdentity();
    }

    listObject[iObj]->applyTransformation();

    if(!VBOs){
      glMultMatrixd(listObject[iObj]->m_tr);
      glGetDoublev(GL_MODELVIEW_MATRIX,listObject[iObj]->m_tr);
      glPopMatrix();
      glPushMatrix();
      glMultMatrixd(listObject[iObj]->m_tr);
    }

    listObject[iObj]->display();

    if(!VBOs)
      glPopMatrix();
  }
}


void CglicScene::glicInit()
{
  //  glEnable(GL_DEPTH_TEST);	// Active le test de profondeur
  // 	glEnable(GL_LIGHTING);	// Active l'éclairage
  // 	glEnable(GL_LIGHT0);
}

#include <glic/scene.h>

// object constructor
CglicScene::CglicScene():transform(){
  state = TO_SEL;
  m_up = glm::vec3(0., 1., 0.);
  m_cam = glm::vec3(0,0,2);
  center = glm::vec3(0,0,0);
}
CglicScene::~CglicScene(){}


void CglicScene::addObject(pCglicObject object)
{
  listObject.push_back(object);
  object->pPROJ = &PROJ;
  object->pVIEW = &VIEW;
}



void CglicScene::display()
{
  applyTransformation();
  update_matrices();

  for (int iObj = 0; iObj < listObject.size(); iObj++){
    listObject[iObj]->applyTransformation();
    listObject[iObj]->display();
  }

  //debug();
}



void CglicScene::applyTransformation()
{
  glm::mat4 ID = glm::mat4(1.0f);
  center += transform.tr;
  m_cam =  glm::vec3(  glm::translate(ID, center) * transform.hRot * transform.vRot * glm::translate(ID, -center) * glm::vec4(m_cam,1)  );
  transform.reset();
  /*
  glm::mat4 ID = glm::mat4(1.0f);
  m_cam = glm::vec3( transform.hRot * transform.vRot * glm::vec4(m_cam,1));
  m_cam  += transform.tr;
  center += transform.tr;
  transform.reset();
  */
}

void CglicScene::update_matrices()
{
  m_look = -m_cam + 2.0f * center;
  m_right = glm::cross(m_look, m_up);
  VIEW = glm::lookAt(m_cam, m_look, m_up);
  PROJ = glm::perspective(view->m_fovy, view->ratio, view->m_znear, view->m_zfar);
}

void CglicScene::debug(){
  //Vectors
  cout << "cam   = " << m_cam.x   << " " << m_cam.y   << " " << m_cam.z   << endl;
  cout << "look  = " << m_look.x  << " " << m_look.y  << " " << m_look.z  << endl;
  cout << "up    = " << m_up.x    << " " << m_up.y    << " " << m_up.z    << endl;
  cout << "right = " << m_right.x << " " << m_right.y << " " << m_right.z << endl;
  //Matrices
  cout << endl;
  cout << " MODEL " << endl;
  CglicObject obj = *listObject[0];
  for(int i = 0 ; i < 4 ; i++)
    cout << obj.MODEL[i][0] << " " << obj.MODEL[i][1] << " " << obj.MODEL[i][2] << " " << obj.MODEL[i][3] << endl;
  cout << endl;
  cout << " VIEW " << endl;
  for(int i = 0 ; i < 4 ; i++)
    cout << VIEW[i][0] << " " << VIEW [i][1] << " " << VIEW [i][2] << " " << VIEW [i][3] << endl;
  cout << endl;
  cout << " PROJ " << endl;
  for(int i = 0 ; i < 4 ; i++)
    cout << PROJ[i][0] << " " << PROJ[i][1] << " " << PROJ[i][2] << " " << PROJ[i][3] << endl;
  cout << endl;

  glm::mat4 X = *obj.pPROJ;
  cout << endl;
  cout << " OBJ PROJ " << endl;
  for(int i = 0 ; i < 4 ; i++)
    cout << X[i][0] << " " << X[i][1] << " " << X[i][2] << " " << X[i][3] << endl;
  cout << endl;
}


void CglicScene::glicInit()
{
  //  glEnable(GL_DEPTH_TEST);	// Active le test de profondeur
  // 	glEnable(GL_LIGHTING);	// Active l'éclairage
  // 	glEnable(GL_LIGHT0);
}

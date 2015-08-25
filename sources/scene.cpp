#include <glic/scene.h>

// object constructor
CglicScene::CglicScene():transform(){
  state = TO_SEL;
  m_cam = glm::vec3(0,0.3,1.2);
  m_look = -m_cam;
  m_up = glm::vec3(0., 1., 0.);
  m_right = glm::cross(m_look, m_up);
  center = glm::vec3(0,0,0);
  VIEW = glm::lookAt(m_cam, m_look, m_up);
}
CglicScene::~CglicScene(){}


void CglicScene::addObject(pCglicObject object)
{
  listObject.push_back(object);

  object->pPROJ = &PROJ;
  object->pVIEW = &VIEW;
  object->pMODEL= &MODEL;
  object->sceneCenter = &center;
  object->sceneUp     = &m_up;
  object->pickingID = listObject.size();
  object->pickingColor = glm::vec3(object->pickingID/255.0f, 0, 0);
  object->pickingShader.load("shaders/shader.vert", "shaders/shader.frag");
  if(listObject.size()==1){
    axis = new CglicAxis();
    axis->pPROJ = &PROJ;
    axis->pVIEW = &VIEW;
    axis->pMODEL= &MODEL;
    axis->sceneCenter = &center;
    axis->sceneUp     = &m_up;
    axis->view  = view;
  }
}


void CglicScene::display()
{
  update_matrices();
  applyTransformation();

  for (int iObj = 0; iObj < listObject.size(); iObj++){
    listObject[iObj]->applyTransformation();
    listObject[iObj]->display();
  }

  axis->applyTransformation();
  axis->display();

  //debug();
}


void CglicScene::reOrderObjects(){
  //Init
  std::vector<pCglicObject> temp;
  temp.resize(1);
  int selInd = NULL;
  //Get element to become first
  for(int i = 0 ; i < listObject.size() ; i++){
    if(listObject[i]->state != CglicObject::TO_OFF){
      temp[0] = listObject[i];
      selInd = i;
    }
  }
  //Get other elements
  for(int i = 0 ; i < listObject.size() ; i++)
    if(i != selInd)
      temp.push_back(listObject[i]);

  if(temp.size() == listObject.size())
    for(int i = 0 ; i < listObject.size() ; i++)
      listObject[i] = temp[i];
}


void CglicScene::applyTransformation()
{
  glm::mat4 ID = glm::mat4(1.0f);
  //center += transform.tr;
  glm::mat4 TRANS;
  TRANS = glm::translate(ID, -center) * transform.rot * glm::translate(ID, center);

  //MODEL = MODEL * TRANS;
  for(int i = 0 ; i < listObject.size() ; i++){
    listObject[i]->transform.tr += transform.tr;
  }

  m_cam = glm::vec3(glm::inverse(TRANS) * glm::vec4(m_cam,1));
  //m_up = glm::normalize(glm::vec3(glm::inverse(TRANS) * glm::vec4(m_up,1)));
  m_look = glm::normalize(-m_cam);
  m_right = glm::normalize(glm::cross(m_look, m_up));

  transform.reset();
}

void CglicScene::update_matrices()
{
  VIEW = glm::lookAt(m_cam, m_look, m_up);
  PROJ = glm::perspective(view->m_fovy, view->ratio, view->m_znear, view->m_zfar);
}

void CglicScene::debug(){
  //Vectors
  cout << "cam   = " << m_cam.x   << " " << m_cam.y   << " " << m_cam.z   << endl;
  cout << "look  = " << m_look.x  << " " << m_look.y  << " " << m_look.z  << endl;
  cout << "up    = " << m_up.x    << " " << m_up.y    << " " << m_up.z    << endl;
  cout << "right = " << m_right.x << " " << m_right.y << " " << m_right.z << endl;
  cout << "center = " << center.x << " " << center.y << " " << center.z << endl;

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

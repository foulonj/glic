#include <glic/scene.h>
#include <glic/canvas.h>
extern CglicCanvas *pcv;

// object constructor
CglicScene::CglicScene():transform(){
  selected = true;
  m_cam = glm::normalize(glm::vec3(1,1,1));
  m_look = -m_cam;
  m_up = glm::normalize(glm::vec3(-1, 1., -1));
  m_right = glm::cross(m_look, m_up);
  center = glm::vec3(0,0,0);
  VIEW = glm::lookAt(m_cam, m_look, m_up);
  globalScale = 100000.0f;//For use of minimums later
}
CglicScene::~CglicScene(){}


void CglicScene::addObject(pCglicObject object)
{
  //Ajout de l'objet à la scène
  listObject.push_back(object);
  object->linkSceneParameters(&MODEL, &VIEW, &PROJ, &center, &m_up, listObject.size());

  //Création des axes
  if(listObject.size()==1){
    axis = new CglicAxis();
    axis->linkSceneParameters(&MODEL, &VIEW, &PROJ, &center, &m_up, 0);
    axis->view = view;
  }

  globalScale = min(globalScale, object->getLocalScale());
}


void CglicScene::display()
{
  if(pcv->profile.globalScale){
    for(int i = 0 ; i < listObject.size() ; i++){
      listObject[i]->setScaleFactor(globalScale);
    }
  }

  update_matrices();
  applyTransformation();

  for (int i = 0; i < listGroup.size(); i++)
    listGroup[i]->compute();

  for (int iObj = 0; iObj < listObject.size(); iObj++)
    listObject[iObj]->applyTransformation();

  for (int iObj = 0; iObj < listObject.size(); iObj++)
    listObject[iObj]->shadowsDisplay();

  for (int iObj = 0; iObj < listObject.size(); iObj++)
    listObject[iObj]->artifactsDisplay();

  for (int iObj = 0; iObj < listObject.size(); iObj++)
    listObject[iObj]->display();

  axis->applyTransformation();
  axis->display();

  debug();
}


int CglicScene::getPickedObjectID(int x, int y){
  unsigned char pixel[3];
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT,viewport);
  for(int i = 0 ; i < listObject.size() ; i++)
      listObject[i]->pickingDisplay();
  glFlush();
  glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);
  return pixel[0];
}


void CglicScene::reOrderObjects(int picked){
  listObject.insert(listObject.begin(), listObject[picked]);
  listObject.erase(listObject.begin() + picked + 1);
}


void CglicScene::applyTransformation()
{
  glm::mat4 ID = glm::mat4(1.0f);
  //center += transform.tr;
  glm::mat4 TRANS;
  TRANS = glm::translate(ID, -center) * transform.rot * glm::translate(ID, center);

  //MODEL = MODEL * TRANS;
  for(int i = 0 ; i < listObject.size() ; i++){
    listObject[i]->transform.setTranslation(transform.tr);
  }

  m_cam   = glm::normalize(glm::vec3(glm::inverse(TRANS) * glm::vec4(m_cam,1)));
  m_up    = glm::normalize(glm::vec3(glm::inverse(TRANS) * glm::vec4(m_up,1)));
  m_look  = glm::normalize(-m_cam);
  m_right = glm::normalize(glm::cross(m_look, m_up));

  transform.reset();
}

void CglicScene::update_matrices()
{
  VIEW = glm::lookAt(m_cam, m_look, m_up);
  PROJ = glm::perspective(view->m_fovy, view->ratio, view->m_znear, view->m_zfar);
}

void CglicScene::saveTransformations(){
  transform.lastMatrices.push_back(MODEL);
  transform.lastUps.push_back(m_up);
  transform.lastCams.push_back(m_cam);
}

void CglicScene::undoLast(){
  if(transform.lastMatrices.size()>0){
    MODEL = transform.lastMatrices.back();
    center = glm::vec3(glm::vec4(MODEL[3]));
    m_up = transform.lastUps.back();
    m_cam = transform.lastCams.back();
    transform.lastMatrices.pop_back();
    transform.lastUps.pop_back();
    transform.lastCams.pop_back();
  }
}

void CglicScene::resetAll(){
  while(transform.lastMatrices.size()>0)
    undoLast();
  for(int i = 0 ; i < listObject.size() ; i++)
    listObject[i]->resetAll();
}


void CglicScene::debug(){
  //Vectors
  cout << "cam   = " << m_cam.x   << " " << m_cam.y   << " " << m_cam.z   << endl;
  cout << "look  = " << m_look.x  << " " << m_look.y  << " " << m_look.z  << endl;
  cout << "up    = " << m_up.x    << " " << m_up.y    << " " << m_up.z    << endl;
  cout << "right = " << m_right.x << " " << m_right.y << " " << m_right.z << endl;
  cout << "center = " << center.x << " " << center.y << " " << center.z << endl;

  /*
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
  */
}


void CglicScene::glicInit()
{
  //  glEnable(GL_DEPTH_TEST);	// Active le test de profondeur
  // 	glEnable(GL_LIGHTING);	// Active l'éclairage
  // 	glEnable(GL_LIGHT0);
}

bool CglicScene::isSelected(){return selected;}
void CglicScene::select(){  selected = true;}
void CglicScene::unSelect(){selected = false;}

#include <glic/scene.h>


// object constructor
CglicScene::CglicScene():transform()
{
  //cout << "  -- [create CglicScene]" << endl;
  state = TO_SEL;
}

CglicScene::~CglicScene()
{
  //cout << "  -- [destroy CglicScene]" << endl;
}

void CglicScene::addObject(pCglicObject object)
{
  //cout << "  -- [add Object to scene n." << ids << "]" << endl;
  listObject.push_back(object);
}

void CglicScene::applyTransformation()
{
  //glLoadIdentity();
  glTranslatef(transform.translation.x,
               transform.translation.y,
               transform.translation.z);
  glRotatef(transform.angle,
            transform.axe.x,
            transform.axe.y,
            transform.axe.z);

  glm::vec3 null_vec3;
  transform.setTranslation(null_vec3);
  transform.setRotation(0., null_vec3);

}


void CglicScene::display()
{
  //cout << "  -- [display CglicScene n." << ids << "]" << endl;

  // grid
  glLineWidth(1.0);
  glBegin(GL_LINES);
  glColor3f(0.5, 0.5, 0.5);
  float dash_size = 0.05;
  for(float x = -1. ; x <= 1. ; x+=0.05){
    for(float z = -1. ; z <= 1. ; z+=0.05){
      glVertex3f(x-dash_size/2, 0., z);
      glVertex3f(x+dash_size/2, 0., z);
      glVertex3f(x, 0., z-dash_size/2);
      glVertex3f(x, 0., z+dash_size/2);
    }
  }
  glEnd();

  // axes
  glLineWidth(2.0);
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-10,0,0);
  glVertex3f(10,0,0);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0,10,0);
  glVertex3f(0,-10,0);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0,0,10);
  glVertex3f(0,0,-10);
  glEnd();
  glLineWidth(1.0);


  //cout << "    -> Display list of object \n ";

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

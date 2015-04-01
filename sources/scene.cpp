#include <glic/scene.h>


// object constructor
CglicScene::CglicScene():transform()
{
  cout << "  -- [create CglicScene]" << endl;
  state = TO_SEL;

}

CglicScene::~CglicScene()
{
  cout << "  -- [destroy CglicScene]" << endl;
}

void CglicScene::addObject(pCglicObject object)
{
  cout << "  -- [add Object to scene n." << ids << "]" << endl;
  listObject.push_back(object);
}

void CglicScene::applyTransformation()
{
  //glLoadIdentity();
  glTranslatef(transform.translation[0],
               transform.translation[1],
               transform.translation[2]);
  glRotatef(transform.angle,
            transform.axe[0],
            transform.axe[1],
            transform.axe[2]);
  
  transform.setTranslation(0., 0., 0.);
  vec3d axis;
  axis[0]=0.;axis[1]=0.;axis[2]=0.;
  transform.setRotation(0.,axis);
  
}


void CglicScene::display()
{
  cout << "  -- [display CglicScene n." << ids << "]" << endl;
  //draw grid
  glBegin(GL_LINES);
  glLineWidth(1.0);
  glColor3f(1.0, 0.5, 0.1);
  for(int i=-10;i<=10;++i) {
    glVertex3f(i,0,-10);
    glVertex3f(i,0,10);
    glVertex3f(10,0,i);
    glVertex3f(-10,0,i);
  }
  glEnd();
  
  
  cout << "    -> Display list of object \n ";
  for (int iObj = 0; iObj < listObject.size(); iObj++){
    cout << " id object : " << iObj << endl;
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

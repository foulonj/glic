#include <glic/scene.h>


// object constructor
CglicScene::CglicScene():transform()
{
  cout << "  -- [create CglicScene]" << endl;
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
    
    glMultMatrixd(listObject[iObj]->transform.mat.array());
    
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 4; j++)
        cout << listObject[iObj]->transform.mat(i,j) << "  ";
      cout << endl;
    }
    
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

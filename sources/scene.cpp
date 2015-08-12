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
  //cout << "    -> Display list of object \n ";

  for (int iObj = 0; iObj < listObject.size(); iObj++){
    /*
    Ici, on applique les changements de MVP,
    à faire avec :
      MODEL         dans object
      VIEW et PROJ  dans scene
    */
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

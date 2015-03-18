#include <glic/canvas.h>

CglicCanvas *pcv;


CglicCanvas::CglicCanvas(int argc, char **argv)
{
  cout << "[create CglicCanvas]\n";
  pcv = this;
  
  // here come the OpenGL calls
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  
  // initializing lighting
  glicLight();
}


int CglicCanvas::glicWindow(int x, int y, int w, int h)
{
  cout << " [create CglicWindow]\n";
  
  window.push_back(CglicWindow(x,y,w,h));
  return window.size()-1;
}


int CglicCanvas::glicScene()
{
  cout << " [create CglicScene]\n";
  scene.push_back(new CglicScene());
  scene[scene.size()-1]->ids = scene.size()-1;
  cout << "scene.size()-1: " << scene.size()-1 << endl;
  return scene.size()-1;
}


void CglicCanvas::glicSetScene(int ids, int idw)
{
  cout << " [add scene n." << ids << " to window n." << idw << " ]"<< endl;
  window[idw].ids = ids;
}


void CglicCanvas::glicLight()
{
  cout << " [create all CglicLight]\n";
  
  
  /*cout << "   Sun " << endl;
   light.push_back(CglicLight(0));
   light[0].setPos(0., 0., 1., 1.);
   light[0].setCol(CglicMaterial::TC_DIF, 1., 0., 0., 0.5);
   cout << "   Sun  end" << endl;*/
  
  cout << "   Light 1 " << endl;
  light.push_back(CglicLight(0));
  light[0].setPos(-1.0, 0., 0.5, 1.);
  light[0].setCol(CglicMaterial::TC_DIF, 1., 0., 0., 0.5);
  cout << "   Light 1  end" << endl;
  
  cout << "   Light 2 " << endl;
  light.push_back(CglicLight(1));
  cout << "   Light 2 bis" << endl;
  light[1].setPos(1.0, 0., 0.5, 1.);
  light[1].setCol(CglicMaterial::TC_DIF,0., 1., 0., 0.5);
  
  cout << "   Light 3 " << endl;
  light.push_back(CglicLight(2));
  cout << "   Light 3 bis" << endl;
  light[2].setPos(0., 1., 0.5, 1.);
  light[2].setCol(CglicMaterial::TC_DIF, 0., 0., 1., 1.);
}

int CglicCanvas::glicObject(pCglicObject obj)
{
  cout << " [define CglicObject]" << endl;
  object.push_back(obj);
  return object.size() - 1;
}

void CglicCanvas::glicSetObject(int ido, int ids)
{
  cout << " [add Object n." << ido << " to scene n." << ids << "]" << endl;
  scene[ids]->addObject(object[ido]);
}

int CglicCanvas::glicPickObject(int x, int y)
{
  cout << " [pick Object ] " << endl;
  
  return 0;
}


int CglicCanvas::winid()
{
  int idw = glutGetWindow();
  cout << " [get win id n." << idw << " ]" << endl;
  for (int i=0; i<window.size(); i++) {
    if ( window[i].m_id == idw )  return(i);
  }
  return(0);
}


void CglicCanvas::reshape(int w, int h)
{
  cout << " [reshapeGL]" << endl;
  int  idw = winid();
  window[idw].view.reshape(w, h);
}

void CglicCanvas::reshapeWrap(int w, int h) {
  cout << " [reshapeWrap]" << endl;
  pcv->reshape(w, h);
}


void CglicCanvas::display()
{
  cout << " [display CglicCanvas]" << endl;
  int  idw = winid();
  window[idw].display();
}

void CglicCanvas::displayWrap()
{
  cout << " [displayWrap]" << endl;
  pcv->display();
}


void CglicCanvas::motionWrap(int x, int y)
{
  cout << " [motionWrap]" << endl;
  pcv->mice.motion(x,y);
  glutPostRedisplay();
}


void CglicCanvas::mouseWrap(int b, int s, int x, int y)
{
  cout << " [mouseWrap]" << endl;
  pcv->mice.mouse(b, s, x, y);
  glutPostRedisplay();
}


void CglicCanvas::keyWrap(unsigned char key, int x, int y)
{
  cout << " [keyboardWrap]" << endl;
  pcv->keyboard.keyboard(key, x, y);
  glutPostRedisplay();
}


void CglicCanvas::specialWrap(int key, int x, int y)
{
  cout << " [specialWrap]" << endl;
  pcv->keyboard.special(key, x, y);
  glutPostRedisplay();
}


void CglicCanvas::glicMainLoop()
{
  glutMainLoop();
}


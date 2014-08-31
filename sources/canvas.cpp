#include <igl/canvas.h>

CiglCanvas *pcv;


CiglCanvas::CiglCanvas(int argc, char **argv)
{
	if ( argc != 2 ) exit(1);
	cout << "[create CiglCanvas]\n";

	// here come the OpenGL calls
	pcv = this;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
}


CiglCanvas::~CiglCanvas()
{

}


int CiglCanvas::iglWindow(int x, int y, int w, int h)
{
	cout << "new window " << x << ", " << y << ", " << w << ", " << h << endl;
	window.push_back(CiglWindow(x,y,w,h));

  return window.size()-1;
}


int CiglCanvas::iglScene()
{
	cout << "   -- new scene\n";
	scene.push_back(CiglScene());

  return scene.size()-1;
}


void CiglCanvas::iglSetScene(int ids, int idw)
{
  cout << "   -- add scene " << ids << " to window " << idw << endl;	
	window[idw].scene = &scene[ids];
	cout << "window idw " << window[idw].scene << endl;
}

void CiglCanvas::iglMainLoop()
{
  glutMainLoop();
}


int CiglCanvas::winid()
{
	int idw = glutGetWindow();
  cout << "   -- [win id " << idw << " ]" << endl;
  for (int i=0; i<window.size(); i++) {
    if ( window[i].m_id == idw )  return(i);
  }
  return(0);
}


void CiglCanvas::reshapeWrap(int w, int h) {
  cout << "   -- [reshapeWrap]\n";
	pcv->reshape(w, h); 
}
	
	
void CiglCanvas::reshape(int w, int h)
{
  cout << "   -- [reshapeGL]\n";
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
}


void CiglCanvas::displayWrap() {
  cout << "   -- [displayWrap]\n";
	pcv->display(); 
}


void CiglCanvas::display()
{
  cout << "   -- [displayGL]\n";
	int  idw = winid();
	window[idw].scene->display();
}



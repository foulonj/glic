#include <igl/canvas.h>
#include <igl/window.h>

extern CiglCanvas *pcv;


CiglWindow::CiglWindow(): m_id(-1), scene(NULL) 
{
}


CiglWindow::CiglWindow(int x, int y, int w, int h)
{
	cout << "- [create window]\n";
	this->m_x = x;
	this->m_y = y;
	this->m_w = w;
	this->m_h = h;
}


CiglWindow::~CiglWindow()
{

}


void CiglWindow::show()
{
	cout << " -- open window \n";

  // Function callbacks with wrapper functions
	glutInitWindowPosition(m_x, m_y);
	glutInitWindowSize(m_w, m_h);
	m_id = glutCreateWindow("essai");

	glutReshapeFunc(pcv->reshapeWrap);
	glutDisplayFunc(pcv->displayWrap);
}


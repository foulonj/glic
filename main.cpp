#include <iostream>
#include <igl.h>

using namespace std;


int main(int argc, char **argv)
{
	int   idw,ids;

  CiglCanvas cv(argc,argv);
  CiglScene  sc;

  idw = cv.iglWindow(0,0,500,500);
  ids = cv.iglScene();
  cv.iglSetScene(ids, idw);
  cv.window[idw].show();
	
  idw = cv.iglWindow(300,500,400,200);
  cv.iglSetScene(ids, idw);
	cv.window[idw].show();
	
	cout << "essai ok : idw  " << idw << endl;
  cv.iglMainLoop();
	//glutMainLoop();
	
  return(EXIT_SUCCESS);
}

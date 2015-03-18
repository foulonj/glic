#include <iostream>
#include <glic.h>

using namespace std;


int main(int argc, char **argv)
{
  int   idw,ids,ido;
  
  CglicCanvas cv(argc,argv);
  
  idw = cv.glicWindow(0,0,500,500);
  //cout << "\t Id window: " << idw << endl;
  ids = cv.glicScene();
  //cout << "\t Id scene: " << ids << endl;
  cv.glicSetScene(ids, idw);
  
  
  cv.window[idw].show();
  
  //cv.window[idw].glicAddLight(&cv.light[0]);
  //cv.window[idw].glicAddLight(&cv.light[1]);
  //cv.window[idw].glicAddLight(&cv.light[2]);
  
  ido = cv.glicObject(new CglicCube(0., 0.2, 0.7, 1.));
  cv.glicSetObject(ido, ids);
  
  ido = cv.glicObject(new CglicSphere(0., 0.2, 0., 1.5));
  //ido = cv.glicObject(new CglicCube(0.7, 0.2, 0., 1.));
  cv.glicSetObject(ido, ids);
  
  /*ido = cv.glicObject(new CglicAxis());
  cv.glicSetObject(ido, ids);*/
  
  //ido = cv.glicObject(new CglicSphere(0.1));
  //cv.glicSetObject(ido, ids);
  
  
  //idw = cv.glicWindow(600,600,400,400);
  //cout << "Id window: " << idw << endl;
  //ids = cv.glicScene();
  
  //cout << "Id scene: " << ids << endl;
  //cv.glicSetScene(ids, idw);
  //cv.window[idw].show();
  
  //ido = cv.glicObject(new CglicCube(0.7, 0.2, 0., 1.));
  
  //cv.glicSetObject(ido, ids);
  //cv.window[idw].glicAddLight(&cv.light[1]);
  
  //ido = cv.glicObject(new CglicCube());
  //cv.glicSetObject(ido, ids);
  
  
  /*
   if (argc>1){
   idw = cv.glicWindow(600,0,400,400);
   ids = cv.glicScene();
   cv.glicSetScene(ids, idw);
   cv.window[idw].show();
   cout << "\t\t Read mesh \n\n";
   CglicMesh* mesh=new CglicMesh(argv[1]);
   cout << "\t\t Read mesh end\n\n";
   cout << "\t\t Mesh Info\n\n";
   mesh->meshInfo(1);
   cout << "\t\t Mesh Info End\n\n";
   cout << "\t\t Add mesh\n\n";
   ido = cv.glicObject(mesh);
   cout << "\t\t Add mesh End\n\n";
   cout << "\t\t Set Mesh in window\n\n";
   cv.glicSetObject(ido, ids);
   cout << "\t\t Set Mesh in window end\n\n";
   };*/
  
  
  
  
  cv.glicMainLoop();
  return(EXIT_SUCCESS);
}

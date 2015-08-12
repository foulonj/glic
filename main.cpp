#include <iostream>
#include <glic.h>
#include <cstdlib>

using namespace std;


double frand_a_b(double a, double b){
  return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

void InitGlew(){
  GLenum err = glewInit();
  if (err != GLEW_OK){
    cout << "glewinit impossible" << endl;
    exit(1);
  }
  if (!GLEW_VERSION_2_1){
    cout << "Version 2.1 pas supportée" << endl;
    exit(1);
  }
}

int main(int argc, char **argv){

  int   idw,ids,ido;



  CglicCanvas cv(argc,argv);

  if (argc <=1){

    idw = cv.glicWindow(0,0,1000,1000);
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

    //for (int io = 0; io < 5; io++){
    // ido = cv.glicObject(new CglicCube(frand_a_b(0,1), frand_a_b(0,1), 1.0, frand_a_b(0.,1.)));
    //  cv.glicSetObject(ido, ids);
    //}



    ido = cv.glicObject(new CglicAxis());
    cv.glicSetObject(ido, ids);

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

    InitGlew();

  }

  else
  {
    idw = cv.glicWindow(0,0,1000,1000);
    ids = cv.glicScene();
    cv.glicSetScene(ids, idw);
    cv.window[idw].show();
    //cout << "\t\t Read mesh \n\n";



    vector<CglicMesh*> mesh;
    for (int i=0; i < argc - 1; i++){
      cout << "i: " << i << endl;
      mesh.push_back(new CglicMesh(argv[i+1]));
      mesh[i]->meshInfo(0);
      ido = cv.glicObject(mesh[i]);
      cv.glicSetObject(ido, ids);
    }

    //Ajout d'un axe
    ido = cv.glicObject(new CglicAxis());
    cv.glicSetObject(ido, ids);

    InitGlew();
    SHADER shader;
    shader.load("/home/loic/dev/glic/shaders/shader.vert", "/home/loic/dev/glic/shaders/shader.vert");
  };




  cv.glicMainLoop();
  return(EXIT_SUCCESS);
}

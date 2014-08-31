#include "light.hpp"


Light::Light(){
  cout << "Build light \n";
}

Light::Light(float a, float b, float c, float d){
  cout << "Build light with constructor position\n";
  pos[0]=a;
  pos[1]=b;
  pos[2]=c;
  pos[3]=d;
}

void Light::display(){
  cout << "\t \t Display function of light" << endl;
}

void Light::setPosition(float a, float b, float c, float d){
  pos[0]=a;
  pos[1]=b;
  pos[2]=c;
  pos[3]=d;
}
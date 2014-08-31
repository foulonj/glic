#include "properties.hpp"

void Properties::display(){
  cout << "\t Display Properties Class" << endl;
}

//! Fix ambient parameter
void Properties::setAmbient(float a, float b, float c, float d){
  amb[0]=a;
  amb[1]=b;
  amb[2]=c;
  amb[3]=d;
}
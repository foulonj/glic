#include "glic/profile.h"

CglicProfile::CglicProfile()
{

  displayShadows    = true;
  displayBottomGrid = true;
  displayAxes       = true;


  //Colors
  back_color    = glm::vec3(1, 1, 0.97);            //Background
  grid_color    = glm::vec3(0.5, 0.5, 0.5);         //Grid
  sele_color    = glm::vec3(1,   0.6, 0);           //Orange
  idle_color    = glm::vec3(0.3, 0.3, 0.3);         //Unselected boxes
}

CglicProfile::~CglicProfile()
{
  //dtor
}

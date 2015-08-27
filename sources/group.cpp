#include "glic/defs.h"

#include "glic/group.h"
#include "glic/canvas.h"

extern CglicCanvas *pcv;

CglicGroup::CglicGroup(std::vector<pCglicObject> groupOfObjects)
{
  listObject = groupOfObjects;
  //double a = (rand()/(double)(RAND_MAX + 1)) + 1;
  //double b = (rand()/(double)(RAND_MAX + 1)) + 1;
  //double c = (rand()/(double)(RAND_MAX + 1)) + 1;
  //glm::vec3 rand = glm::vec3(a,b,c);
  group_color = glm::vec3(0,0.7,0);//glm::vec3(0.5f) + 0.3f * rand;

  //Centres du groupe
  for(int i = 0 ; i < listObject.size() ; i++){
    pCenters.push_back(listObject[i]->getCenterPtr());
  }
}

CglicGroup::~CglicGroup()
{
  //dtor
}

void CglicGroup::compute(){

  //On vérifie si un membre du groupe est sélectionné
  bool match = false;
  for(int i = 0 ; i < listObject.size() ; i++){
    if(listObject[i]->isSelected()){
      match = true;
      selected = true;
    }
  }
  if(!match)
    selected = false;

  //On sélectionne les membres du groupe
  if(selected)
    for(int i = 0 ; i < listObject.size() ; i++)
      listObject[i]->select();

  //On update éventuellement le centre de rotation des objets
  if(pcv->profile.groupRotation){

    //On calcule le centre du groupe
    glm::vec3 tmpCenter;
    for(int i = 0 ; i < pCenters.size() ; i++){
      tmpCenter += *pCenters[i];
    }
    group_center = float( 1.0f/pCenters.size() ) * tmpCenter;

    //On envoie le centre aux objets
    for(int i = 0 ; i < listObject.size() ; i++){
      listObject[i]->setRotationCenter(group_center);
    }
  }
}

bool CglicGroup::isSelected(){return selected;}

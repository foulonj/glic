#ifndef PROFILE_H
#define PROFILE_H

#include "defs.h"

class CglicProfile
{
  public:
    //Constructor from config file
    CglicProfile();
    ~CglicProfile();


  public:
    bool displayShadows;
    bool displayBottomGrid;
    bool displayAxes;
    glm::vec3 back_color, grid_color, sele_color, idle_color;

  protected:
  private:
};

#endif // PROFILE_H

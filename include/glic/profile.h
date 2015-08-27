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
    bool displayAxesLabels;

    bool groupRotation;

    glm::vec3 back_color, grid_color, idle_color;
    glm::vec3 sele_color; //group_color;

  protected:
  private:
};

#endif // PROFILE_H

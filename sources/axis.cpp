#include <glic/axis.h>

CglicAxis::CglicAxis(){
  float dash_size = 0.05;
  std::vector<glm::vec3> tGrid;
  for(float x = -1. ; x <= 1. ; x+=0.05){
    for(float z = -1. ; z <= 1. ; z+=0.05){
      tGrid.push_back(glm::vec3(x-dash_size/2, 0., z));
      tGrid.push_back(glm::vec3(x+dash_size/2, 0., z));
      tGrid.push_back(glm::vec3(x, 0., z-dash_size/2));
      tGrid.push_back(glm::vec3(x, 0., z+dash_size/2));
    }
  }
  for(int i = 0 ; i < tGrid.size() ; i++)
    for(int j = 0 ; j < 3 ; j++)
      grid.push_back(tGrid[i][j]);
  glGenBuffers( 1,               &gridBuffer);
  glBindBuffer( GL_ARRAY_BUFFER, gridBuffer);
  glBufferData( GL_ARRAY_BUFFER, sizeof(float) * grid.size(), &grid[0], GL_STATIC_DRAW);

  std::vector<glm::vec3> tAxes = {glm::vec3(-1,0,0),
                                  glm::vec3(1,0,0),
                                  glm::vec3(0,1,0),
                                  glm::vec3(0,-1,0),
                                  glm::vec3(0,0,1),
                                  glm::vec3(0,0,-1)};
  for(int i = 0 ; i < tAxes.size() ; i++)
    for(int j = 0 ; j < 3 ; j++)
      axes.push_back(0.4*tAxes[i][j]);
  glGenBuffers( 1,               &axesBuffer);
  glBindBuffer( GL_ARRAY_BUFFER, axesBuffer);
  glBufferData( GL_ARRAY_BUFFER, sizeof(float) * axes.size(), &axes[0], GL_STATIC_DRAW);

  simpleShader.load("shaders/shader.vert", "shaders/shader.frag");
}

void CglicAxis::display()
{
  //Initialization
  glUseProgram(simpleShader.mProgramID);
  glEnableVertexAttribArray( 0);
  GLuint MatrixID = glGetUniformLocation(simpleShader.mProgramID, "MVP");
  GLuint colorID  = glGetUniformLocation(simpleShader.mProgramID, "COL");


  //Fixed GRID
  glm::mat4 MVP = glm::translate( *pPROJ * *pVIEW  * MODEL, center);
  glUniformMatrix4fv( MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glLineWidth(1.0);
  glBindBuffer(              GL_ARRAY_BUFFER, gridBuffer);
  glVertexAttribPointer(     0, 3, GL_FLOAT, GL_FALSE, 0, ( void*)0);
  glBindAttribLocation(      simpleShader.mProgramID, 0, "vertex_position");
  uniformVec3(colorID, grid_color);
  glPolygonMode(GL_FRONT, GL_LINE);
  glDrawArrays(GL_LINES, 0, grid.size()/3);


  //Axes
  glDisable(GL_DEPTH_TEST);
  glViewport(0,0,150,150);
  //Allows for axes to stay centered
  MVP = glm::translate(*pPROJ * *pVIEW * *pMODEL * MODEL, -*sceneCenter);
  glUniformMatrix4fv( MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glLineWidth(2.0);
  glBindBuffer(              GL_ARRAY_BUFFER, axesBuffer);
  glVertexAttribPointer(     0, 3, GL_FLOAT, GL_FALSE, 0, ( void*)0);
  glBindAttribLocation(      simpleShader.mProgramID, 0, "vertex_position");
  glPolygonMode(GL_FRONT, GL_LINE);
  //X
  uniformVec3(colorID, R);
  glDrawArrays(GL_LINES, 0, 2);
  //Y
  uniformVec3(colorID, G);
  glDrawArrays(GL_LINES, 2, 4);
  //Z
  uniformVec3(colorID, B);
  glDrawArrays(GL_LINES, 4, 6);
  //Labels des axes
  float offset = 20.0f;
  glTranslatef(-center.x, -center.y, -center.z);
  //X
  glm::vec3 newPos = glm::vec3( MVP * glm::vec4(offset*R, 0) );
  glColor3f(R.x, R.y, R.z);
  glRasterPos3f(newPos.x, newPos.y, newPos.z);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');
  //Y
  newPos = glm::vec3( MVP * glm::vec4(offset*G, 0) );
  glColor3f(G.x, G.y, G.z);
  glRasterPos3f(newPos.x, newPos.y, newPos.z);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
  //Z
  newPos = glm::vec3( MVP * glm::vec4(offset*B, 0) );
  glColor3f(B.x, B.y, B.z);
  glRasterPos3f(newPos.x, newPos.y, newPos.z);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Z');
  glTranslatef(center.x, center.y, center.z);


  //Ressources freeing
  glEnable(GL_DEPTH_TEST);
  view->reshape(view->width,view->height);
  glDisableVertexAttribArray(0);
  glLineWidth(1.0);
  glUseProgram(0);
  glPolygonMode(GL_FRONT, GL_FILL);
}

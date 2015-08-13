#include <glic/axis.h>


CglicAxis::CglicAxis(){
  shader.load("/home/loic/dev/glic/shaders/shader.vert", "/home/loic/dev/glic/shaders/shader.frag");
  vertices = new float[9];
  vertices[0] = -1;
  vertices[1] = 0;
  vertices[2] = 0;
  vertices[3] = 1;
  vertices[4] = 0;
  vertices[5] = 0;
  vertices[6] = 0;
  vertices[7] = 0;
  vertices[8] = -1;
  int mem = 3 * sizeof(float) * 3;
  glGenBuffers( 1,               &buffer);
  glBindBuffer( GL_ARRAY_BUFFER, buffer);
  glBufferData( GL_ARRAY_BUFFER, mem, vertices, GL_STATIC_DRAW);

  float dash_size = 0.05;
  for(float x = -1. ; x <= 1. ; x+=0.05){
    for(float z = -1. ; z <= 1. ; z+=0.05){
      grid.push_back(glm::vec3(x-dash_size/2, 0., z));
      grid.push_back(glm::vec3(x+dash_size/2, 0., z));
      grid.push_back(glm::vec3(x, 0., z-dash_size/2));
      grid.push_back(glm::vec3(x, 0., z+dash_size/2));
    }
  }

  axes.push_back(glm::vec3(-10,0,0));
  axes.push_back(glm::vec3(10,0,0));
  axes.push_back(glm::vec3(0,10,0));
  axes.push_back(glm::vec3(0,-10,0));
  axes.push_back(glm::vec3(0,0,10));
  axes.push_back(glm::vec3(0,0,-10));

  colo.push_back(glm::vec3(1.0, 0.0, 0.0));
  colo.push_back(glm::vec3(0.0, 1.0, 0.0));
  colo.push_back(glm::vec3(0.0, 0.0, 1.0));
}

CglicAxis::~CglicAxis(){
  delete[] vertices;
}

void CglicAxis::display()
{
  /*
  //Triangle
  glLineWidth(5.0);
  glUseProgram(shader.mProgramID);
  glEnableVertexAttribArray( 0);
  glBindBuffer(              GL_ARRAY_BUFFER, buffer);
  glVertexAttribPointer(     0, 3, GL_FLOAT, GL_FALSE, 0, ( void*)0);
  glBindAttribLocation(      shader.mProgramID, 0, "vertex_position");

  glm::mat4 MVP = MODEL;

  GLuint MatrixID = glGetUniformLocation(shader.mProgramID, "MVP");
  glUniformMatrix4fv( MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
  glLineWidth(1.0);
  glUseProgram(0);
  */

  // Grid
  glLineWidth(1.0);
  glBegin(GL_LINES);
  glColor3f(0.5, 0.5, 0.5);
  for(int i = 0 ; i < grid.size(); i+=2){
    glVertex3f(grid[i  ].x, grid[i  ].y, grid[i  ].z);
    glVertex3f(grid[i+1].x, grid[i+1].y, grid[i+1].z);
  }
  glEnd();
  // Axes
  glLineWidth(2.0);
  glBegin(GL_LINES);
  for(int i = 0 ; i <3 ; i++){
    glColor3f(colo[i].x, colo[i].y, colo[i].z);
    glVertex3f(axes[2*i  ].x, axes[2*i  ].y, axes[2*i  ].z);
    glVertex3f(axes[2*i+1].x, axes[2*i+1].y, axes[2*i+1].z);
  }
  glEnd();
  glLineWidth(1.0);
  // Labels
  float pos = 0.22f;
  char labs[] = {'x', 'y', 'z'};
  for(int i = 0 ; i <3 ; i++){
    glColor3f(colo[i].x, colo[i].y, colo[i].z);
    glRasterPos3f(pos*colo[i].x, pos*colo[i].y, pos*colo[i].z);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, labs[i]);
  }

}

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
  vertices[7] = 1;
  vertices[8] = 0;
  int mem = 3 * sizeof(float) * 3;
  glGenBuffers( 1,               &buffer);
  glBindBuffer( GL_ARRAY_BUFFER, buffer);
  glBufferData( GL_ARRAY_BUFFER, mem, vertices, GL_STATIC_DRAW);
}

CglicAxis::~CglicAxis(){
  delete[] vertices;
}

void CglicAxis::display()
{
  //Triangle
  glUseProgram(shader.mProgramID);
  glEnableVertexAttribArray( 0);
  glBindBuffer(              GL_ARRAY_BUFFER, buffer);
  glVertexAttribPointer(     0, 3, GL_FLOAT, GL_FALSE, 0, ( void*)0);
  glBindAttribLocation(      shader.mProgramID, 0, "vertex_position");

  //glm::mat4 MVP = projection * view * MODEL;
  glm::mat4 MVP(1.0f);
  GLuint MatrixID = glGetUniformLocation(shader.mProgramID, "MVP");
  glUniformMatrix4fv( MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glUseProgram(0);


  // grid
  glLineWidth(1.0);
  glBegin(GL_LINES);
  glColor3f(0.5, 0.5, 0.5);
  float dash_size = 0.05;
  for(float x = -1. ; x <= 1. ; x+=0.05){
    for(float z = -1. ; z <= 1. ; z+=0.05){
      glVertex3f(x-dash_size/2, 0., z);
      glVertex3f(x+dash_size/2, 0., z);
      glVertex3f(x, 0., z-dash_size/2);
      glVertex3f(x, 0., z+dash_size/2);
    }
  }
  glEnd();

  // axes
  glLineWidth(2.0);
  glBegin(GL_LINES);
  //X
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-10,0,0);
  glVertex3f(10,0,0);
  //Y
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0,10,0);
  glVertex3f(0,-10,0);
  //Z
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0,0,10);
  glVertex3f(0,0,-10);
  glEnd();
  glLineWidth(1.0);

  glColor3f(1.0, 0.0, 0.0);
  glRasterPos3f(0.22, 0.0, 0.0);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'x');
  glColor3f(0.0, 1.0, 0.0);
  glRasterPos3f(0.0, 0.22, 0.0);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'y');
  glColor3f(0.0, 0.0, 1.0);
  glRasterPos3f(0.0, 0.0, 0.22);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'z');


  //Tentative d'utilisation de VBO


}

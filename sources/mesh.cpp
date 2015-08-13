#include <glic/mesh.h>
extern "C" {
#include <libmesh5.h>
}


CglicMesh::CglicMesh(char *name)
{
  Point    *ppt;
  Tria     *pt;
  double   *n,dd;
  float     fp1,fp2,fp3;
  int       k,inm;

  //cout << "\n NAME:" << name << endl;

  inm = GmfOpenMesh(name,GmfRead,&ver,&dim);
  if ( !inm ){
    //cout << "  ** FILE NOT FOUND.\n";
    exit(0);
  }

  np = GmfStatKwd(inm,GmfVertices);
  nt = GmfStatKwd(inm,GmfTriangles);
  nn = GmfStatKwd(inm,GmfNormals);

  if ( !np ){
    cout << "  ** MISSING DATA\n";
    exit(0);
  }

  point.resize(np+1);
  GmfGotoKwd(inm,GmfVertices);
  for (k=0; k<np; k++){
    ppt = &point[k];
    if ( ver == GmfFloat ){
      GmfGetLin(inm,GmfVertices,&fp1,&fp2,&fp3,&ppt->ref);
      ppt->c[0] = fp1;
      ppt->c[1] = fp2;
      ppt->c[2] = 0.;
    }
    else
      GmfGetLin(inm,GmfVertices,&ppt->c[0],&ppt->c[1],&ppt->c[2],&ppt->ref);
  }

  //read triangles
  tria.resize(nt+1);
  GmfGotoKwd(inm,GmfTriangles);
  for (k=0; k<nt; k++) {
    pt = &tria[k];
    GmfGetLin(inm,GmfTriangles,&pt->v[0],&pt->v[1],&pt->v[2],&pt->ref);
  }

  normal.resize(np+1);

  if ( nn ) {
    GmfGotoKwd(inm,GmfNormals);
    for (k=0; k<nn; k++) {
      if ( ver == GmfFloat ) {
        GmfGetLin(inm,GmfNormals,&fp1,&fp2,&fp3);
        normal[k].n[0] = fp1;
        normal[k].n[1] = fp2;
        normal[k].n[2] = fp3;
      }
      else
        GmfGetLin(inm,GmfNormals,&normal[k].n[0],&normal[k].n[1],&normal[k].n[2]);
      n  = normal[k].n;
      dd = 1.0 / sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
      n[0] *= dd;
      n[1] *= dd;
      n[2] *= dd;
    }
  }
  meshBox();

  face_color = glm::vec3(0.8, 0.8, 1);
  edge_color = glm::vec3(0,0,1);

  //Chargement du shader
  shader.load("/home/loic/dev/glic/shaders/shader.vert", "/home/loic/dev/glic/shaders/shader.frag");

  //Buffer des vertices
  for (int i = 0 ; i < point.size() ; i++)
    for(int j = 0 ; j < 3 ; j++)
      vertices.push_back(point[i].c[j]);
  glGenBuffers( 1,               &meshBuffer);
  glBindBuffer( GL_ARRAY_BUFFER, meshBuffer);
  glBufferData( GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

  //Buffer des indices
  for (int i = 0 ; i < tria.size() ; i++)
    for(int j = 0 ; j < 3 ; j++)
      indices.push_back(tria[i].v[j]-1);
  glGenBuffers(1, &indicesBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void CglicMesh::meshInfo(const int& verbose, ostream& outstr)
{
  //cout << " \t\t MeshInfo \n" << endl;
  cout << "np: " << np << ", nt: " << nt << ", nn:" << nn << ", dim: " << dim << ", ver: " << ver << endl;

  if (verbose){
    cout << "Points" << endl;
    for (int i = 0; i < np; i++)
      cout << point[i].c[0] << ", " << point[i].c[1] << ", " << point[i].c[2] << ", " << point[i].ref << endl;
    cout << "Triangles" << endl;
    for (int i = 0; i < nt; i++)
      cout << tria[i].v[0] << ", " << tria[i].v[1] << ", " << tria[i].v[2] << ", " << tria[i].ref << endl;
    cout << "Normals" << endl;
    for (int i = 0; i < nn; i++)
      cout << normal[i].n[0] << ", " << normal[i].n[1] << ", " << normal[i].n[2] << endl;
  }
}

void CglicMesh::display()
{
  //cout << "   ---> display mesh\n";

  glm::mat4 MVP = *pPROJ * *pVIEW * MODEL;

  /*

  //Initialization
  glUseProgram(shader.mProgramID);
  GLuint MatrixID = glGetUniformLocation(shader.mProgramID, "MVP");
  GLuint colorID  = glGetUniformLocation(shader.mProgramID, "COL");
  glEnableVertexAttribArray( 0);
  glUniformMatrix4fv( MatrixID, 1, GL_FALSE, &MVP[0][0]);

  //Display
  glBindBuffer(              GL_ARRAY_BUFFER, meshBuffer);
  glVertexAttribPointer(     0, 3, GL_FLOAT, GL_FALSE, 0, ( void*)0);
  glBindAttribLocation(      shader.mProgramID, 0, "vertex_position");
  //Faces
  uniformVec3(colorID, face_color);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawArrays(GL_TRIANGLES, 0, np);
  //Edges
  glLineWidth(2.0);
  uniformVec3(colorID, edge_color);
  glPolygonMode(GL_FRONT, GL_LINE);
  glDrawArrays(GL_TRIANGLES, 0, np);

  */

  //Initialization
  glUseProgram(shader.mProgramID);
  GLuint MatrixID = glGetUniformLocation(shader.mProgramID, "MVP");
  GLuint colorID  = glGetUniformLocation(shader.mProgramID, "COL");
  glEnableVertexAttribArray( 0);
  glUniformMatrix4fv( MatrixID, 1, GL_FALSE, &MVP[0][0]);

  //Display
  glBindBuffer(              GL_ARRAY_BUFFER, meshBuffer);
  glVertexAttribPointer(     0, 3, GL_FLOAT, GL_FALSE, 0, ( void*)0);
  glBindAttribLocation(      shader.mProgramID, 0, "vertex_position");

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
  //Faces
  uniformVec3(colorID, face_color);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
  //Edges
  glLineWidth(1.0);
  uniformVec3(colorID, edge_color);
  glPolygonMode(GL_FRONT, GL_LINE);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);









/*

  else{
    //Bounding box
    if (box == TO_ON){
      glPushMatrix();
      glScalef(1.01 * fabs(xmax-xmin),
               1.01 * fabs(ymax-ymin),
               1.01 * fabs(zmax-zmin));
      glColor3f(1.0,1.0,1.0);
      glutWireCube(1.0);
      glPopMatrix();
    };
    //Contour
    if(state != TO_ON){
      glDisable(GL_DEPTH_TEST);
      glColor3f(1.0, 0.6, 0.0);
      glCullFace(GL_FRONT);
      float s = 1.05;
      glScalef(s, s, s);
      glCallList(listTria);
      glScalef(1./s, 1./s, 1./s);
      glFlush();
      glEnable(GL_DEPTH_TEST);
    }
    //Display effectif
    glColor3f(0.51,0.52,0.8);
    glCallList(listTria);
    if ( line == TO_ON){
      glColor3f(0., 0., 1.);
      glCallList(listEdge);
    }
    glFlush();
  }
  */
}


void CglicMesh::meshBox()
{

  Point     *p0;
  /* default */
  xmin = ymin = zmin =  FLOAT_MAX;
  xmax = ymax = zmax = -FLOAT_MAX;

  for (int k=0; k<np; k++) {
    p0 = &point[k];
    if ( p0->c[0] < xmin ) xmin = p0->c[0];
    if ( p0->c[0] > xmax ) xmax = p0->c[0];
    if ( p0->c[1] < ymin ) ymin = p0->c[1];
    if ( p0->c[1] > ymax ) ymax = p0->c[1];
    if ( p0->c[2] < zmin ) zmin = p0->c[2];
    if ( p0->c[2] > zmax ) zmax = p0->c[2];
  }

  //fprintf(stdout,"    Bounding box:  x:[%g  %g]  y:[%g  %g]  z:[%g  %g]\n", xmin,xmax,ymin,ymax,zmin,zmax);

  /* translate mesh at center */
  xtra = 0.5 * (xmin+xmax);
  ytra = 0.5 * (ymin+ymax);
  ztra = 0.5 * (zmin+zmax);
  for (int k=0; k<np; k++) {
    p0 = &point[k];
    p0->c[0] -= xtra;
    p0->c[1] -= ytra;
    p0->c[2] -= ztra;
  }
}

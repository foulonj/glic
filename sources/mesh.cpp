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

  //Calcul de la bounding box
  getBBOX();

  //Chargement du shader
  shader.load("shaders/shader.vert", "shaders/shader.frag");

  //Préparation des buffers
  std::vector<float> vertices;
  std::vector<float> normals;
  std::vector<int>   indices;

  //Buffer des vertices
  for (int i = 0 ; i < point.size() ; i++)
    for(int j = 0 ; j < 3 ; j++)
      vertices.push_back(point[i].c[j]);
  glGenBuffers( 1,               &meshBuffer);
  glBindBuffer( GL_ARRAY_BUFFER, meshBuffer);
  glBufferData( GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

  //Buffer des normales
  for (int i = 0 ; i < normal.size() ; i++)
    for(int j = 0 ; j < 3 ; j++)
      normals.push_back(normal[i].n[j]);
  glGenBuffers( 1,               &normalBuffer);
  glBindBuffer( GL_ARRAY_BUFFER, normalBuffer);
  glBufferData( GL_ARRAY_BUFFER, sizeof(float) * normals.size(), &normals[0], GL_STATIC_DRAW);

  //Buffer des indices
  for (int i = 0 ; i < tria.size() ; i++)
    for(int j = 0 ; j < 3 ; j++)
      indices.push_back(tria[i].v[j]-1);
  glGenBuffers(1, &indicesBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  //face_color = glm::vec3(0.8, 0.8, 1);
  //edge_color = glm::vec3(0,0,1);

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

void CglicMesh::getBBOX()
{
  Point     *p0;
  /* default */
  bbmin = glm::vec3(FLOAT_MAX);
  bbmax = glm::vec3(-FLOAT_MAX);

  for (int k=0; k<np; k++) {
    p0 = &point[k];
    if ( p0->c[0] < bbmin.x ) bbmin.x = p0->c[0];
    if ( p0->c[0] > bbmax.x ) bbmax.x = p0->c[0];
    if ( p0->c[1] < bbmin.y ) bbmin.y = p0->c[1];
    if ( p0->c[1] > bbmax.y ) bbmax.y = p0->c[1];
    if ( p0->c[2] < bbmin.z ) bbmin.z = p0->c[2];
    if ( p0->c[2] > bbmax.z ) bbmax.z = p0->c[2];
  }

  /* translate mesh at center */
  tra = 0.5f * (bbmin + bbmax);
  for (int k=0; k<np; k++) {
    p0 = &point[k];
    p0->c[0] -= tra.x;
    p0->c[1] -= tra.y;
    p0->c[2] -= tra.z;
  }

  float cube[] = {
    -0.5, -0.5, -0.5,
     0.5, -0.5, -0.5,
     0.5,  0.5, -0.5,
    -0.5,  0.5, -0.5,
    -0.5, -0.5,  0.5,
     0.5, -0.5,  0.5,
     0.5,  0.5,  0.5,
    -0.5,  0.5,  0.5,
  };
  glGenBuffers(1, &bboxBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, bboxBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

  GLushort elements[] = {
    0, 1, 2, 3,
    4, 5, 6, 7,
    0, 4, 1, 5, 2, 6, 3, 7
  };
  glGenBuffers(1, &bboxIndBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bboxIndBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}





void CglicMesh::display()
{

  glShadeModel(GL_FLAT);
  glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
  glShadeModel(GL_SMOOTH);

  //cout << "   ---> display mesh\n";

  glm::mat4 MVP = *pPROJ * *pVIEW * MODEL;

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
  //Contour
  if(state == TO_SEL){
    glLineWidth(10.0);
    uniformVec3(colorID, sele_color);
    glDisable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT, GL_LINE);
    glDrawElements(GL_TRIANGLES, 3 * tria.size(), GL_UNSIGNED_INT, (void*)0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(1.0);
  }
  //Faces
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1,0);
  uniformVec3(colorID, face_color);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawElements(GL_TRIANGLES, 3 * tria.size(), GL_UNSIGNED_INT, (void*)0);
  //Edges
  uniformVec3(colorID, edge_color);
  glPolygonMode(GL_FRONT, GL_LINE);
  glDrawElements(GL_TRIANGLES, 3 * tria.size(), GL_UNSIGNED_INT, (void*)0);
  //Bounding box
  if(box == TO_ON){
    if(state==TO_SEL){
      glLineWidth(2.0);
      uniformVec3(colorID, sele_color);
    }
    else{
      glLineWidth(1.0);
      uniformVec3(colorID, idle_color);
    }
    glPolygonMode(GL_FRONT, GL_LINE);
    glBindBuffer(GL_ARRAY_BUFFER, bboxBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, ( void*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bboxIndBuffer);

    glm::mat4 SCALE = glm::scale(MVP, 1.02f * (bbmax - bbmin));

    glUniformMatrix4fv( MatrixID, 1, GL_FALSE, &SCALE[0][0]);

    glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
    glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4*sizeof(GLushort)));
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8*sizeof(GLushort)));
    glLineWidth(1.0);
  }

  //Closing
  glDisableVertexAttribArray( 0);
  glUseProgram(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

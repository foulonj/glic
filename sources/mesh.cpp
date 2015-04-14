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
  
  cout << "\n NAME:" << name << endl;
  
  inm = GmfOpenMesh(name,GmfRead,&ver,&dim);
  if ( !inm ){
    cout << "  ** FILE NOT FOUND.\n";
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
  listTria=buildTria();
  listEdge=buildEdge();
}

void CglicMesh::meshInfo(const int& verbose, ostream& outstr)
{
  cout << " \t\t MeshInfo \n" << endl;
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


GLuint CglicMesh::buildTria()
{
  int i;
  Tria  *pt;
  Point     *p0,*p1,*p2;
  float      pp0[3],pp1[3],pp2[3];
  
  listTria = glGenLists(1);
  
  glNewList(listTria,GL_COMPILE);
  
  //glColor3f(0., 1., 0.);
  
  GLfloat mat_amb[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat mat_dif[] = { 0., 0., 0., 1.0 };
   GLfloat mat_specular[] = { 0.07, 0.0, 0.0, 1.0 };
   GLfloat mat_emi[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat mat_shininess[] = { 20.0 };
   
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_EMISSION, mat_emi);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  
  //glColor3f(0.51,0.52,0.8);
  
  
  //GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
  //GLfloat mat_shininess[] = { 80.0 };


  //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  
  glColor3f(0.51,0.52,0.8);
  //glColor3f(1.,0.99,0.94);
  
  
  glBegin (GL_TRIANGLES);
  for (int k=0; k<nt; k++) {
    pt = &tria[k];
    p0 = &point[pt->v[0]-1];
    p1 = &point[pt->v[1]-1];
    p2 = &point[pt->v[2]-1];
    for (i=0; i<3 ; i++) {
      pp0[i] = p0->c[i];
      pp1[i] = p1->c[i];
      pp2[i] = p2->c[i];
    }
    
    glVertex3fv(pp0);
    glVertex3fv(pp1);
    glVertex3fv(pp2);
  }
  glEnd();
  glEndList();
  return(listTria);
}

GLuint CglicMesh::buildEdge()
{
  int i;
  Tria  *pt;
  Point     *p0,*p1,*p2;
  float      pp0[3],pp1[3],pp2[3];
  
  listEdge = glGenLists(1);
  
  glNewList(listEdge,GL_COMPILE);
  
  glColor3f(0., 0., 1.);
  for (int k=0; k<nt; k++) {
    pt = &tria[k];
    p0 = &point[pt->v[0]-1];
    p1 = &point[pt->v[1]-1];
    p2 = &point[pt->v[2]-1];
    for (i=0; i<3 ; i++) {
      pp0[i] = p0->c[i];
      pp1[i] = p1->c[i];
      pp2[i] = p2->c[i];
    }
    
    glBegin(GL_LINES);
    glVertex3fv(pp0);
    glVertex3fv(pp1);
    glEnd();
    glBegin(GL_LINES);
    glVertex3fv(pp1);
    glVertex3fv(pp2);
    glEnd();
    glBegin(GL_LINES);
    glVertex3fv(pp2);
    glVertex3fv(pp0);
    glEnd();
  }
  
  glEndList();
  return(listEdge);
}


void CglicMesh::display()
{
  cout << "   ---> display mesh\n";

  if (box == TO_ON){
    glPushMatrix();
    glScalef(1.01 * fabs(xmax-xmin),
             1.01 * fabs(ymax-ymin),
             1.01 * fabs(zmax-zmin));
    glColor3f(1.0,1.0,1.0);
    glutWireCube(1.0);
    glPopMatrix();
  };
  
  glCallList(listTria);
  if ( line == TO_ON)
    glCallList(listEdge);
  glFlush();
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

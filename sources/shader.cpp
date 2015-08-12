#include "glic/shader.h"
#include <fstream>

using namespace std;

SHADER::SHADER(){
  mVertex_file_path   = "";
  mFragment_file_path = "";
  mProgramID          = 0;
}

void SHADER::load(string vert_path, string frag_path){

  cout << " OK " << endl;

  mVertex_file_path   = vert_path;
  mFragment_file_path = frag_path;

  // Crée les shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  cout << " OK " << endl;


  // Lit le code du vertex shader à partir du fichier
  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(mVertex_file_path.c_str(), std::ios::in);
  if(VertexShaderStream.is_open()){
    std::string Line = "";
    while(getline(VertexShaderStream, Line))
      VertexShaderCode += "\n" + Line;
    VertexShaderStream.close();
  }

  cout << " OK " << endl;


  // Lit le code du fragment shader à partir du fichier
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(mFragment_file_path.c_str(), std::ios::in);
  if(FragmentShaderStream.is_open()){
    std::string Line = "";
    while(getline(FragmentShaderStream, Line))
      FragmentShaderCode += "\n" + Line;
    FragmentShaderStream.close();
  }

  cout << " OK " << endl;


  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Compile le vertex shader
  printf("Compiling shader : %s\n", mVertex_file_path.c_str());
  char const * VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
  glCompileShader(VertexShaderID);

  cout << " OK " << endl;


  // Vérifie le vertex shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  std::vector<char> VertexShaderErrorMessage(InfoLogLength);
  glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
  fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

  cout << " OK " << endl;


  // Compile le fragment shader
  printf("Compiling shader : %s\n", mFragment_file_path.c_str());
  char const * FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
  glCompileShader(FragmentShaderID);

  cout << " OK " << endl;


  // Vérifie le fragment shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
  glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
  fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

  cout << " OK " << endl;


  // Lit le programme
  fprintf(stdout, "Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  cout << " OK " << endl;


  // Vérifie le programme
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
  glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
  fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

  cout << " OK " << endl;


  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);
  mProgramID = ProgramID;
}

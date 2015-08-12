#ifndef SHADERHEADERDEF
#define SHADERHEADERDEF

#include "defs.h"

class SHADER
{
 public:
  std::string mVertex_file_path;
  std::string mFragment_file_path;
  GLuint      mProgramID;

  SHADER();
  void load(std::string vert_path, std::string frag_path);

};

#endif
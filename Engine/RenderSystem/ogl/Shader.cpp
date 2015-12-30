#include "Renderer.h"

#include "ogl.h"
#include "Shader.h"

#include <string.h>

namespace renderer
{
  CShader::CShader()
  {
  }

  CShader::~CShader()
  {
  }

  bool CShader::Create(EType aType, const char * aCode)
  {
    bool lOk(false);

    // Create the shader of the given typer
    mID = glCreateShader(aType);

    // Obtain the size of the shader code
    GLint lSizeCode = strlen(aCode);

    // Replace the code of the shader
    glShaderSource(mID, 1, &aCode, &lSizeCode);

    // Compile the shader
    glCompileShader(mID);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(mID, GL_COMPILE_STATUS, &success);

    if (!success)
    {
      glGetShaderInfoLog(mID, 512, NULL, infoLog);
    }
    else
    {
      lOk = true;
    }

    return lOk;
  }
}

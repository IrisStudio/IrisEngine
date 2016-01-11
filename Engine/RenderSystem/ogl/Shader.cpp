#include "Renderer.h"

#include "ogl.h"
#include "Shader.h"
#include "Logger/Logger.h"
#include "ExtensionManager.h"
#include <string.h>

CShader::CShader()
  : mID(0)
  , mType( VERTEX_SHADER )
{
}

CShader::~CShader()
{
}

bool CShader::Create(EType aType, const char * aCode)
{
  /*
  bool lOk(true);

  mType = aType;

  GLint success;
  char infoLog[512];

  IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "OGL_ERROR_BEFORE_SHADER_COMPILATION");

  // Create the shader of the given typer
  GLint lShader = glCreateShader(GL_VERTEX_SHADER);

  IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "SHADER_ERRORS_1");

  // Obtain the size of the shader code
  GLint lSizeCode = strlen(aCode);

  // Replace the code of the shader
  glShaderSource(lShader, 1, &aCode, &lSizeCode);

  IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "SHADER_ERRORS_2");

  // Compile the shader
  glCompileShader(lShader);

  IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "SHADER_ERRORS¨_3");

  // Any error?
  glGetShaderiv(lShader, GL_COMPILE_STATUS, &success);

  IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "SHADER_ERRORS_4");

  if (!success)
  {
    glGetShaderInfoLog(lShader, 512, NULL, infoLog);
    IRIS_LOG_ERROR("Error compiling the shader");
    IRIS_LOG_ERROR(infoLog);
    lOk = false;
  }
    
  mID = glCreateProgram();
  IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "SHADER_ERRORS_5");

  if (!mID)
  {
    IRIS_LOG_ERROR("Error creating the program");
    IRIS_LOG_ERROR("Dumping shader:");
    IRIS_LOG_ERROR(aCode);
    lOk = false;
  }
  else
  {
    if (CExtensionManager::Instance().IsSupported("GL_ARB_separate_shader_objects"))
    {
      glProgramParameteri(mID, GL_PROGRAM_SEPARABLE, GL_TRUE);
      glAttachShader(mID, lShader);
      glLinkProgram(mID);

      glGetProgramiv(mID, GL_LINK_STATUS, &success);
      if(!success)
      {
        IRIS_LOG_ERROR("Error linking the program");
        glGetShaderInfoLog(lShader, 512, NULL, infoLog);
        IRIS_LOG_ERROR("Error compiling the shader");
        IRIS_LOG_ERROR(infoLog);
        lOk = false;
        glDeleteProgram(mID);
        mID = 0;
      }
      glDetachShader(mID, lShader);
    }
  }

  IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "SHADER_ERRORS");

  return lOk;

  */
  return false;
}

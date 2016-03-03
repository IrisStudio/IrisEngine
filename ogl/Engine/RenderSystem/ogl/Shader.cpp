#include "Renderer.h"

#include "ogl.h"
#include "Shader.h"
#include "Logger/Logger.h"
#include "ExtensionManager.h"
#include <string.h>

using namespace ogl;

CShader::CShader()
  : mProgramID(0)
  , mShaderID(0)
  , mType( VERTEX_SHADER )
  , mOk(false)
{
}

CShader::~CShader()
{
  glDeleteShader(mShaderID);
  glDeleteProgram(mProgramID);
}

bool CShader::Create(EType aType, const char * aCode)
{
  mType = aType;
  mCode = aCode;
  mOk = (Compile() && Link());
  return mOk;
}

bool CShader::Compile()
{
  GLint lSuccess = 0;
  mShaderID = glCreateShader(mType);

  if (mShaderID)
  {
    GLint lSizeCode = mCode.length();
    const GLchar* lShaderSrc = mCode.c_str();
    glShaderSource(mShaderID, 1, &lShaderSrc, &lSizeCode);
    glCompileShader(mShaderID);

    glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &lSuccess);

#ifdef _DEBUG
    if (!lSuccess)
    {
      char lInfoLog[512];
      glGetShaderInfoLog(mShaderID, 512, NULL, lInfoLog);
      IRIS_LOG_ERROR("Error compiling the shader");
      IRIS_LOG_ERROR(lInfoLog);
    }
#endif

  }

  return lSuccess != GL_FALSE;
}

bool CShader::Link()
{
  GLint lSuccess = GL_FALSE;

  mProgramID = glCreateProgram();
  if (mProgramID)
  {
    glProgramParameteri(mProgramID, GL_PROGRAM_SEPARABLE, GL_TRUE);
    glAttachShader(mProgramID, mShaderID );
    glLinkProgram(mProgramID);

    glGetProgramiv(mProgramID, GL_LINK_STATUS, &lSuccess);

#ifdef _DEBUG
    if (!lSuccess)
    {
      char lInfoLog[512];
      glGetProgramInfoLog(mProgramID, 512, NULL, lInfoLog);
      IRIS_LOG_ERROR("Error linking the program");
      IRIS_LOG_ERROR(lInfoLog);
    }
#endif

    glDetachShader(mProgramID, mShaderID);
  }

  return lSuccess != GL_FALSE;
}

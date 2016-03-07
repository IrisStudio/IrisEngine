#include "Renderer.h"

#include "StringUtils.h"

#include "Context.h"
#include "Logger/Logger.h"

#include "ExtensionManager.h"

namespace
{
}

CContext::CContext()
  : mOGLVersion("")
  , mGLSLVersion("")
{
}

CContext::~CContext()
{
}

bool CContext::Init()
{
  bool lOk(true);
  
  CExtensionManager::Instance().GetExtensions();

  mOGLVendor   = (const char*)glGetString(GL_VENDOR);
  mOGLRenderer = (const char*)glGetString(GL_RENDERER);
  mOGLVersion  = (const char*)glGetString(GL_VERSION);
  //mGLSLVersion = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

  return lOk;
}

const std::string& CContext::GetOGLVendor() const
{
  return mOGLVendor;
}

const std::string& CContext::GetOGLRenderer() const
{
  return mOGLRenderer;
}

const std::string& CContext::GetOGLVersion() const
{
  return mOGLVersion;
}

const std::string& CContext::GetGLSLVersion() const
{
  return mGLSLVersion;
}

bool CContext::IsCapable(ogl::Extension ar_extension) const
{
  return true;
}

void CContext::SetGLSLVersion(const std::string& ar_version)
{
  mGLSLVersion = ar_version;
  mShaderVersion = "#version " + ar_version + " core\n";
}

const std::string& CContext::GetShaderVersion() const
{
  return mShaderVersion;
}
#include "Renderer.h"

#include "ogl.h"
#include "ExtensionManager.h"
#include "Logger/Logger.h"

#include <string.h>

CExtensionManagerImpl::CExtensionManagerImpl()
{
}

CExtensionManagerImpl::~CExtensionManagerImpl()
{
}

using namespace ogl;
void CExtensionManagerImpl::GetExtensions()
{
  IRIS_LOG_APPLICATION("Supported extensions:");
  int NumberOfExtensions = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);
  for ( int i = 0; i< NumberOfExtensions; ++i)
  {
    mExtensions.insert(std::string((const char*)glGetStringi(GL_EXTENSIONS, i)));
    IRIS_LOG_APPLICATION((const char*)(glGetStringi(GL_EXTENSIONS, i)));
  }
}

bool CExtensionManagerImpl::IsSupported(const char* aExtension)
{
  return mExtensions.count( std::string( aExtension ) ) != 0;
}

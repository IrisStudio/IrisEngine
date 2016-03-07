#ifndef __OGL_EXTENSION_MANAGER__
#define __OGL_EXTENSION_MANAGER__

#include "Singleton.h"
#include <set>
#include <string>

class CExtensionManager: public Singleton< CExtensionManager >
{
public:
  CExtensionManager();
  virtual ~CExtensionManager();
  void GetExtensions();
  bool IsSupported( const char* aExtension );
private:
  std::set< std::string > mExtensions;
};

#endif

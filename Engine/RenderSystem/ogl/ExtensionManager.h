#ifndef __OGL_EXTENSION_MANAGER__
#define __OGL_EXTENSION_MANAGER__

#include <loki/Singleton.h>
#include <set>
#include <string>

class CExtensionManagerImpl
{
public:
  CExtensionManagerImpl();
  virtual ~CExtensionManagerImpl();
  void GetExtensions();
  bool IsSupported( const char* aExtension );
private:
  std::set< std::string > mExtensions;
};

typedef Loki::SingletonHolder< CExtensionManagerImpl > CExtensionManager;

#endif

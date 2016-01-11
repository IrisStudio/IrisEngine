#ifndef __OGL_EXTENSION_MANAGER__
#define __OGL_EXTENSION_MANAGER__

#include "Utils/Singleton.h"
#include <set>

class CExtensionManager : public Singleton<CExtensionManager>
{
  friend class Singleton<CExtensionManager>;
public:
  virtual ~CExtensionManager();
  void GetExtensions();
  bool IsSupported( const char* aExtension );
private:
  CExtensionManager();
  std::set< std::string > mExtensions;
};

#endif

#ifndef __CHAI_SCRIPT_MANAGER__
#define __CHAI_SCRIPT_MANAGER__

#include "Types.h"

#include <loki/Singleton.h>

class CScriptManagerImpl
{
public:
  CScriptManagerImpl();
  virtual ~CScriptManagerImpl();

  void Init();

  int32 ExecuteInstruction( std::string aInstruction );
};

typedef Loki::SingletonHolder< CScriptManagerImpl > CScriptManager;

#endif //__CHAI_SCRIPT_MANAGER__
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

  void ExecuteInstruction(std::string aInstruction);
  int32 ExecuteInstructionAndGet( std::string aInstruction );
  void ExecuteFile(std::string aFilePath);
};

typedef Loki::SingletonHolder< CScriptManagerImpl > CScriptManager;

#endif //__CHAI_SCRIPT_MANAGER__
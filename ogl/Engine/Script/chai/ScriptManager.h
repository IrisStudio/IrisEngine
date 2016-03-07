#ifndef __CHAI_SCRIPT_MANAGER__
#define __CHAI_SCRIPT_MANAGER__

#include "Types.h"

#include "Singleton.h"

class CScriptManager : public Singleton< CScriptManager >
{
public:
  CScriptManager();
  virtual ~CScriptManager();

  void Init();

  void ExecuteInstruction(std::string aInstruction);
  int32 ExecuteInstructionAndGet( std::string aInstruction );
  void ExecuteFile(std::string aFilePath);
};

#endif //__CHAI_SCRIPT_MANAGER__
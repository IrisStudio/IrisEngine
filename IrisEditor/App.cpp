#include <stdio.h>
#include "Effect.h"
#include "EffectLibrary.h"
#include "ogl\ogl.h"

#include "ScriptManager.h"
#include "Types.h"

#include "Application.h"

int main()
{
  CScriptManager::Instance().Init();

  int32 lResult = CScriptManager::Instance().ExecuteInstructionAndGet("TestFunc(20)");

  std::string file_str("../data/scripts/test.chai");

  CScriptManager::Instance().ExecuteFile(file_str);
  int32 lResult2 = CScriptManager::Instance().ExecuteInstructionAndGet("c");

  IApplication *app = new IApplication();;
  app->Run();
  CHECKED_DELETE(app);

  return 0;
}
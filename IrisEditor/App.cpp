#include <stdio.h>
#include "Effect.h"
#include "EffectLibrary.h"
#include "ogl\ogl.h"
#include "Window.h"

#include "ScriptManager.h"
#include "Types.h"

int main()
{
  CWindowImpl lMainWindow = CWindow::Instance();

  CScriptManager::Instance().Init();

  int32 lResult = CScriptManager::Instance().ExecuteInstruction("TestFunc(20)");
  
  if( lMainWindow.Create() )
  {
    if( lMainWindow.Show() )
    {
      while (true)
      {
        lMainWindow.BeginRender();
        lMainWindow.Clear(true, false, false);
        lMainWindow.EndRender();
      }
    }
  }

  return 0;
}
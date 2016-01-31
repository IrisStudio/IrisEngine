#include <stdio.h>
#include "Effect.h"
#include "EffectLibrary.h"
#include "ogl\ogl.h"
#include "Window.h"

int main()
{
  CWindowImpl lMainWindow = CWindow::Instance();

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
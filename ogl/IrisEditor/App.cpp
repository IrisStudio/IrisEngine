#include <stdio.h>
#include "Effect.h"
#include "EffectLibrary.h"
#include "ogl\ogl.h"

#include "ScriptManager.h"
#include "Types.h"

#include "Application.h"

#include "Time\Timer.h"

#include "GameObjectManager.h"
#include "Camera\CameraManager.h"

#include "StringUtils.h"


int main(int argc, char **argv )
{
  IApplication *app = new IApplication();;
  app->Run();
  CHECKED_DELETE(app);

  return 1;//qapp.exec();
}
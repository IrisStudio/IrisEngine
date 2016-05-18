#if defined(DEBUG) || defined(_DEBUG)
    #include <crtdbg.h>
#endif

#include <Windows.h>

#include "Application.h"
#include "Window.h"
#include "Time\Timer.h"

#include "GameObjectManager.h"
#include "Camera\CameraManager.h"

#include "StringUtils.h"
#include "Input\InputManager.h"


// Define your user buttons


static const float sMaximumFrameRate = 60.0f;
static const float sMinimumFrameRate = 15.0f;
static const float sUpdateInterval = 1.0f / sMaximumFrameRate;
static const float sMaxCyclesPerFrame = sMaximumFrameRate / sMinimumFrameRate;
static const int   sMaxSamples = 50;

IApplication::IApplication()
{
}

IApplication::~IApplication()
{
}

void IApplication::Run()
{
    #if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(3837);
    #endif

    float lUpdateIterations = 0.0f;

    CWindow& lMainWindow = CWindow::Instance();

    if (lMainWindow.Create(eST_Windowed))
    {
        if (lMainWindow.Show())
        {
            //Testing the EntityX construction
            CGameObjectManager& game_object_manager = CGameObjectManager::Instance();
            CTimer&  lTimer                         = CTimer::Instance(10);
            CInputManager& lInputManager            = CInputManager::Instance();
            lInputManager.Init(&lMainWindow);

            while (lMainWindow.Update())
            {
                lTimer.Update();
                lInputManager.ProcessInputs();
                lMainWindow.SetWindowTitle(iris::str_utils::Format("FPS: %f", lTimer.GetFPS()));
                game_object_manager.update(lTimer.GetElapsedTime());
            }
        }
    }
}
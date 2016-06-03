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

#include "EditorGui\EditorGui.h"

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
    //_CrtSetBreakAlloc(1664);
    #endif

    float lUpdateIterations = 0.0f;

    CWindow& lMainWindow = CWindow::Instance();

    if (lMainWindow.Create(eST_Windowed))
    {
        if (lMainWindow.Show())
        {
			ImGui_ImplGlfwGL3_Init(lMainWindow.GetHandle(), true);

            //Testing the EntityX construction
            CGameObjectManager& game_object_manager = CGameObjectManager::Instance();
            CTimer&  lTimer                         = CTimer::Instance(10);
            CInputManager& lInputManager            = CInputManager::Instance();
            lInputManager.Init(&lMainWindow);

            while (!lInputManager.DoAction(Exit))
            {
                lMainWindow.Update();
                lTimer.Update();
                lInputManager.ProcessInputs();
                lMainWindow.SetWindowTitle(iris::str_utils::Format("FPS: %f", lTimer.GetFPS()));
                game_object_manager.update(lTimer.GetElapsedTime());
            }
        }
    }
}
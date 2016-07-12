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

#include "EditorGui.h"
#include <imgui.h>

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))


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

            bool show_test_window = true;
            bool show_another_window = false;
            ImVec4 clear_color = ImColor(114, 144, 154);

            while (!lInputManager.DoAction(Exit))
            {
                CWindow& lMainWindow = CWindow::Instance();

                lMainWindow.Update();
                lTimer.Update();
                lInputManager.ProcessInputs();
                lMainWindow.SetWindowTitle(iris::str_utils::Format("FPS: %f", lTimer.GetFPS()));
                lMainWindow.BeginRender();
                lMainWindow.Clear(true, true, true);
                game_object_manager.update(lTimer.GetElapsedTime());

                /*
                ImGuiIO& io = ImGui::GetIO();
                ImGui_ImplGlfwGL3_NewFrame(lTimer.GetElapsedTime());

                // 1. Show a simple window
                // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
                {
                    static float f = 0.0f;
                    static float values[90] = { 0 };
                    static int values_offset = 0;
                    static int i = 0;

                    static float refresh_time = ImGui::GetTime(); // Create dummy data at fixed 60 hz rate for the demo

                    if (++i > 90)
                    {
                        i = 0;

                        for (int x = 0; x < 89; ++x)
                        {
                            values[x] = values[x + 1];
                        }

                        values[89] = lTimer.GetFPS();
                    }
                    else
                    {
                        values[i] = lTimer.GetFPS();
                    }



                    ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, "FPS avg", -1.0f, 1.0f, ImVec2(0, 80));
                    ImGui::Text("Hello, world!");
                    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
                    ImGui::ColorEdit3("clear color", (float*)&clear_color);

                    if (ImGui::Button("Test Window"))
                    {
                        show_test_window ^= 1;
                    }

                    if (ImGui::Button("Another Window"))
                    {
                        show_another_window ^= 1;
                    }

                    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                }

                // 2. Show another simple window, this time using an explicit Begin/End pair
                if (show_another_window)
                {
                    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
                    ImGui::Begin("Another Window", &show_another_window);
                    ImGui::Text("Hello");
                    ImGui::End();
                }

                // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
                if (show_test_window)
                {
                    ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
                    ImGui::ShowTestWindow(&show_test_window);
                }

                ImGui::Render();
                */
                lMainWindow.EndRender();
            }
        }
    }
}
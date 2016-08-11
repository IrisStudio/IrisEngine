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
#include "GBuffer.h"
#include "State.h"
#include "FrameBuffer.h"

#include "Commands/Deferred/DeferredLightPassCmd.h"

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

            CGBuffer& lGBuffer = CGBuffer::Instance();
            CFrameBuffer& lFrameBuffer = CFrameBuffer::Instance();
            lGBuffer.Create(lMainWindow.GetSize().x, lMainWindow.GetSize().y);

            gph::CDeferredLightPassCmd* lDeferredLightPass = new gph::CDeferredLightPassCmd();
            lDeferredLightPass->Init();

            while (!lInputManager.DoAction(Exit))
            {
                CWindow& lMainWindow = CWindow::Instance();

                lMainWindow.Update();
                lTimer.Update();
                lInputManager.ProcessInputs();
                lMainWindow.SetWindowTitle(iris::str_utils::Format("FPS: %f", lTimer.GetFPS()));
                lMainWindow.BeginRender();

                // Set the GBuffer and render the objects
                lGBuffer.GeometryPass();
                CState::SetViewport(0, 0, lMainWindow.GetSize().x, lMainWindow.GetSize().y);
                CState::ClearBuffers(float4(0.1f, 0.1f, 0.1f, 1.0f), eBB_COLOR_BUFFER_BIT | eBB_DEPTH_BUFFER_BIT | eBB_STENCIL_BUFFER_BIT );
				CState::EnableDepthTest();
                game_object_manager.update(lTimer.GetElapsedTime());

                // Paint the frame buffer
                lFrameBuffer.Bind();
                CState::SetViewport(0, 0, lMainWindow.GetSize().x, lMainWindow.GetSize().y);
                CState::ClearBuffers(float4(0.5f, 0.5f, 0.5f, 1.0f), eBB_COLOR_BUFFER_BIT | eBB_DEPTH_BUFFER_BIT | eBB_STENCIL_BUFFER_BIT );
                lFrameBuffer.Blit(lGBuffer, lMainWindow.GetSize().x, lMainWindow.GetSize().y );

                //lDeferredLightPass->Execute();

                /*
                ImGuiIO& io = ImGui::GetIO();
                ImGui_ImplGlfwGL3_NewFrame(lTimer.GetElapsedTime());

                // 1. Show a simple window
                // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
                {
                    bool show_g_buffer = true;
                    ImGui::Begin("GBUFFER", &show_g_buffer);
                    ImGui::SetWindowSize(ImVec2(500, 600));
                    ImVec2 tex_screen_pos = ImGui::GetCursorScreenPos();
                    ImGui::SetWindowPos(ImVec2(0, 0));
                    float tex_w = (float)400;
                    float tex_h = (float)200;

                    const uint32* lRenderTargets = lGBuffer.GetRenderTargets();

                    for (uint32 i = 0; i < CGBuffer::eGBT_Count; ++i )
                    {
                        ImGui::Image((ImTextureID)lRenderTargets[i], ImVec2(tex_w, tex_h), ImVec2(1, 1), ImVec2(0, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
                    }

                    ImGui::End();
                }

                // 2. Show another simple window, this time using an explicit Begin/End pair
                if (false)
                {
                    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
                    ImGui::Begin("Another Window", &show_another_window);
                    ImGui::Text("Hello");
                    ImGui::End();
                }

                // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
                if (false)
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
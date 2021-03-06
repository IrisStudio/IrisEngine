﻿#include "StringUtils.h"

#include "ogl.h"
#include "Window.h"
#include "Logger/Logger.h"

#include <Windows.h>
#include <string.h>

#include "Context.h"
#include "Shader.h"

#include "EffectLibrary.h"
#include <imgui.h>


static HWND   mHandle;
static HDC    mhDC;
static HGLRC  mhRC;
static MSG    msg;

void* CWindow::GetHandle()
{
    return mHandle;
}

using namespace iris;

namespace
{
    bool CreateContext(int32 aMayorVersion, int32 aMinVersion)
    {
        int OGLContextInfo[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, aMayorVersion,
            WGL_CONTEXT_MINOR_VERSION_ARB, aMinVersion,
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        if (!(mhRC = ogl::wglCreateContextAttribsARB(mhDC, 0, OGLContextInfo)))
        {
            return false;
        }

        return true;
    }
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    ImGuiIO& io = ImGui::GetIO();

    switch (msg)
    {
        case WM_SIZE:
            {
                printf("Resized\n");
                return 0;
            }
            break;

        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            }
            break;

        case WM_KEYDOWN:
            {
                if (wParam < 256)
                {
                    io.KeysDown[wParam] = 1;
                }

                switch (wParam)
                {
                    case VK_ESCAPE:
                        //Cleanup();
                        PostQuitMessage(0);
                        return 0;
                        break;
                }
            }
            break;

        case WM_LBUTTONDOWN:
            if (io.WantCaptureMouse)
            {
                io.MouseDown[0] = true;
            }

            return true;

        case WM_LBUTTONUP:
            if (io.WantCaptureMouse)
            {
                io.MouseDown[0] = false;
            }

            return true;

        case WM_RBUTTONDOWN:
            if (io.WantCaptureMouse)
            {
                io.MouseDown[1] = true;
            }

            return true;

        case WM_RBUTTONUP:
            if (io.WantCaptureMouse)
            {
                io.MouseDown[1] = false;
            }

            return true;

        case WM_MBUTTONDOWN:
            if (io.WantCaptureMouse)
            {
                io.MouseDown[2] = true;
            }

            return true;

        case WM_MBUTTONUP:
            if (io.WantCaptureMouse)
            {
                io.MouseDown[2] = false;
            }

            return true;

        case WM_MOUSEWHEEL:
            io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
            return true;

        case WM_MOUSEMOVE:
            LOG_APPLICATION("mouse move");
            io.MousePos.x = (signed short)(lParam);
            io.MousePos.y = (signed short)(lParam >> 16);
            return true;


        case WM_KEYUP:
            if (wParam < 256)
            {
                io.KeysDown[wParam] = 0;
            }

            return true;

        case WM_CHAR:

            // You can also use ToAscii()+GetKeyboardState() to retrieve characters.
            if (wParam > 0 && wParam < 0x10000)
            {
                io.AddInputCharacter((unsigned short)wParam);
            }

            return true;
    }//end switch( msg )

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

CWindow::CWindow()
    : mName("OGL_RENDERER")
    , mSize(uint2(800, 600))
    , mClearColor(float4(0.25f, 0.25f, 0.25f,1.0f))
{
    memset(&msg, 0, sizeof(msg));
}

CWindow::~CWindow()
{
}

bool CWindow::Create( WindowSize aSizeType )
{
    bool lOk(true);

    // Set up window class
    WNDCLASS wnd;
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hCursor = LoadCursor(0, IDC_ARROW);
    wnd.hIcon = LoadIcon(0, IDI_WINLOGO);
    wnd.lpszMenuName = 0;
    wnd.style = 0;
    wnd.hbrBackground = 0;
    wnd.lpfnWndProc = MsgProc;
    wnd.hInstance = GetModuleHandle(0);
    wnd.lpszClassName = (LPCSTR)mName;

    //Register window class
    RegisterClass(&wnd);

    switch (aSizeType)
    {
        case eST_Windowed:
            break;

        case eST_FitDesktop:
            {
                mSize = uint2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
                RECT rect;
                HWND taskBar = FindWindow("Shell_traywnd", NULL);

                if (taskBar && GetWindowRect(taskBar, &rect))
                {
                    mSize.y -= rect.bottom - rect.top;
                }

                break;
            }

        case eST_FullScreen:
            mSize = uint2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
            break;

        default:
            break;
    }

    mHandle = CreateWindowEx(
                  0,
                  mName,
                  mName,
                  WS_OVERLAPPEDWINDOW,
                  0,
                  0,
                  mSize.x,
                  mSize.y,
                  NULL,
                  NULL,
                  wnd.hInstance,
                  NULL
              );

    lOk = lOk && (mHandle != NULL);

    if (aSizeType == eST_FullScreen)
    {
        SetWindowLong(mHandle, GWL_EXSTYLE, 0);
        SetWindowLong(mHandle, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
        SetWindowPos(mHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
        SetWindowPos(mHandle, HWND_TOPMOST, 0, 0, mSize.x, mSize.y, SWP_SHOWWINDOW);
    }

    return lOk;
}

bool CWindow::Show()
{
    ShowWindow(mHandle, SW_SHOWDEFAULT);

    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0,0,0,0,0,0,0,0,0,0,0,0,0, // useles parameters
        16,
        0,0,0,0,0,0,0
    };

    mhDC = GetDC(mHandle);

    int pf = ChoosePixelFormat(mhDC, &pfd);

    if (!SetPixelFormat(mhDC, pf, &pfd))
    {
        return false;
    }

    if (!(mhRC = wglCreateContext(mhDC)))
    {
        return false;
    }

    if (!wglMakeCurrent(mhDC, mhRC))
    {
        wglDeleteContext(mhRC);
        return false;
    }

    // Set the window name with the rendering version
    CContext& lContext = CContext::Instance();
    lContext.Init();

    char* lVersion = "450";

    if (!CreateContext(4, 5))
    {
        lVersion = "410";

        if (!CreateContext(4, 1))
        {
            lVersion = "330";

            if (!CreateContext(3, 3))
            {
                lVersion = "320";

                if (!CreateContext(3, 2))
                {
                    lVersion = "310";

                    if (!CreateContext(3, 1))
                    {
                        return false;
                    }
                }
            }
        }
    }

    CShader::SetGLSLVersion(lVersion);

    // Init the effects
    CEffectLibrary::Instance();

    //const std::string& lWindowName = "Vendor:" + lContext.GetOGLVendor() + "-Renderer:" + lContext.GetOGLRenderer() + "-Version:" + lContext.GetOGLVersion() + "-Shaders:" + lContext.GetGLSLVersion();
    //SetWindowText(mHandle, lWindowName.c_str());

    if (!wglMakeCurrent(mhDC, mhRC))
    {
        wglDeleteContext(mhRC);
        return false;
    }

    return glGetError() == GL_NO_ERROR;
}

void CWindow::SetSize(const uint2& aSize)
{
    mSize = aSize;
}

const uint2& CWindow::GetSize() const
{
    return mSize;
}

bool CWindow::Update()
{
    bool lUpdated = false;

    if (msg.message != WM_QUIT)
    {
        UpdateWindow(mHandle);

        lUpdated = true;
    }

    return lUpdated;
}

void CWindow::BeginRender()
{
    RECT lRect;
    GetClientRect(mHandle, &lRect);
    mSize = uint2( uint32(lRect.right- lRect.left), uint32( lRect.bottom - lRect.top ) );
}

void CWindow::EndRender()
{
    SwapBuffers(mhDC);
}

void CWindow::SetWindowTitle(const std::string& aWindowTitle)
{
    SetWindowText(mHandle, aWindowTitle.c_str());
}
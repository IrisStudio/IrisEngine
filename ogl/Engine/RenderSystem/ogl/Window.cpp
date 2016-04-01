#include "StringUtils.h"

#include "ogl.h"
#include "Window.h"
#include "Logger/Logger.h"

#include <Windows.h>
#include <string.h>

#include "Context.h"
#include "Shader.h"
#include "Camera/CameraManager.h"

static HWND   mHandle;
static HDC    mhDC;
static HGLRC  mhRC;
static MSG    msg;

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
                CCameraSPtr lCurrentCamera = CCameraManager::Instance().GetCurrentCamera();

                switch (wParam)
                {
                    case VK_ESCAPE:
                        //Cleanup();
                        PostQuitMessage(0);
                        return 0;

                    case VK_DOWN:
                        lCurrentCamera->ProcessKeyboard(BACKWARD, 1.0f / 30.0f);
                        return 0;

                    case VK_RIGHT:
                        //Cleanup();
                        lCurrentCamera->ProcessKeyboard(RIGHT, 1.0f / 30.0f);
                        return 0;

                    case VK_UP:
                        //Cleanup();
                        lCurrentCamera->ProcessKeyboard(FORWARD, 1.0f / 30.0f);
                        return 0;

                    case VK_LEFT:
                        //Cleanup();
                        lCurrentCamera->ProcessKeyboard(LEFT, 1.0f / 30.0f);
                        return 0;
                        break;
                }
            }
            break;
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

bool CWindow::Update()
{
    bool lUpdated = false;

    if (msg.message != WM_QUIT)
    {
        UpdateWindow(mHandle);

        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        lUpdated = true;
    }

    return lUpdated;
}

void CWindow::BeginRender()
{
  RECT lRect;
  GetWindowRect(mHandle, &lRect);
  mSize = uint2( uint32(lRect.right- lRect.left), uint32( lRect.bottom - lRect.top ) );
  ogl::CheckOGLError("before viewport");
  glViewport(0, 0, mSize.x, mSize.y);
  ogl::CheckOGLError("after viewport %d, %d", mSize.x, mSize.x );
}

void CWindow::Clear(bool aColorBuffer, bool aDepthBuffer, bool aStencilBuffer)
{
    GLbitfield clear_mask = 0;

    if( aColorBuffer )
    {
        glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
        clear_mask |= GL_COLOR_BUFFER_BIT;
    }

    if(aDepthBuffer)
    {
        clear_mask |= GL_DEPTH_BUFFER_BIT;
    }

    if( aStencilBuffer )
    {
        clear_mask |= GL_STENCIL_BUFFER_BIT;
    }

    glClear(clear_mask);
}

void CWindow::EndRender()
{
    SwapBuffers(mhDC);
}

void CWindow::SetWindowTitle(const std::string& aWindowTitle)
{
  SetWindowText(mHandle, aWindowTitle.c_str());
}
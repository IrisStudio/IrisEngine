#include "Renderer.h"

#include "StringUtils.h"

#include "ogl.h"
#include "Window.h"
#include "Logger/Logger.h"

#include <Windows.h>
#include <string.h>

#include "ExtensionManager.h"

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
  case WM_DESTROY:
  {
    PostQuitMessage(0);
    return 0;
  }
  break;

  case WM_KEYDOWN:
  {
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
  }//end switch( msg )

  return DefWindowProc(hWnd, msg, wParam, lParam);
}

CWindowImpl::CWindowImpl()
  : mName("OGL_RENDERER")
  , mSize(uint2(800, 600))
  , mClearColor(float4(0.25f, 0.25f, 0.25f,1.0f))
{
  memset(&msg, 0, sizeof(msg));
}

CWindowImpl::~CWindowImpl()
{
}

bool CWindowImpl::Create( ESizeType aSizeType )
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

  mSize = uint2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

  if (eST_FitDesktop == aSizeType)
  {
    RECT rect;
    HWND taskBar = FindWindow("Shell_traywnd", NULL);
    if (taskBar && GetWindowRect(taskBar, &rect))
    {
      mSize.y -= rect.bottom - rect.top;
    }
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

bool CWindowImpl::Show()
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
    return false;

  if (!(mhRC = wglCreateContext(mhDC)))
    return false;

  if (!wglMakeCurrent(mhDC, mhRC))
  {
    wglDeleteContext(mhRC);
    return false;
  }

  // Set the window name with the rendering version

  const std::string& lWindowName = str_utils::Format("Vendor: %s - Renderer: %s - OGL Version: %s - GLSL Version %s", (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER), (const char*)glGetString(GL_VERSION), (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
  SetWindowText(mHandle, lWindowName.c_str() );

  CExtensionManager::Instance().GetExtensions();

  if (!CreateContext(4, 5))
  {
    if (!CreateContext(4, 1))
    {
      if (!CreateContext(3, 3))
      {
        if (!CreateContext(3, 2))
        {
          if (!CreateContext(3, 1))
          {
            return false;
          }
        }
      }
    }
  }

  if (!wglMakeCurrent(mhDC, mhRC))
  {
    wglDeleteContext(mhRC);
    return false;
  }

  return glGetError() == GL_NO_ERROR;
}

void CWindowImpl::SetSize(const uint2& aSize)
{
  mSize = aSize;
}

bool CWindowImpl::Update()
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

void CWindowImpl::BeginRender()
{
  glViewport(0, 0, mSize.x, mSize.y );
}

void CWindowImpl::Clear(bool aColorBuffer, bool aDepthBuffer, bool aStencilBuffer)
{
  GLbitfield clear_mask = 0;
  if( aColorBuffer )
  {
    glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
    clear_mask |= GL_COLOR_BUFFER_BIT;
  }
  if(aDepthBuffer)
    clear_mask |= GL_COLOR_BUFFER_BIT;

  if( aStencilBuffer )
    clear_mask |= GL_STENCIL_BUFFER_BIT;

  glClear(clear_mask);
}

void CWindowImpl::EndRender()
{
  SwapBuffers(mhDC);
}
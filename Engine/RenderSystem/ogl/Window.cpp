#include "Renderer.h"

#include "ogl.h"
#include "Window.h"
#include "Logger/Logger.h"

#include <Windows.h>

#include <string.h>

static HWND mHandle;
static HDC  mhDC;
static HGLRC mhRC;

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
  , mClearColor(float4(0.5f, 1.0f, 1.0f,1.0f))
{
}

CWindowImpl::~CWindowImpl()
{
}

bool CWindowImpl::Create()
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

  mHandle = CreateWindowEx(
    0,
    mName,
    mName,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL,
    NULL,
    wnd.hInstance,
    NULL
    );

  lOk = lOk && (mHandle != NULL);

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
    return false;

  return true;
}

void CWindowImpl::SetSize(const uint2& aSize)
{
  mSize = aSize;
}

void CWindowImpl::BeginRender()
{
  UpdateWindow(mHandle);
  glViewport(0, 0, mSize.x, mSize.y );
}

void CWindowImpl::Clear(bool aColorBuffer, bool aDepthBuffer, bool aStencilBuffer)
{
  glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void CWindowImpl::EndRender()
{
  SwapBuffers(mhDC);
}
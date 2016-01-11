#include <Windows.h>
#include <stdio.h>
#include "RenderSystem.h"
#include "Effect.h"
#include "EffectLibrary.h"
#include "ogl\ogl.h"

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

WNDCLASSEX g_wcl;
HWND g_hWnd;
HDC g_hDC;
HGLRC g_hRC;

int main()
{
  //Window class name
  const char* windowName = "OGL Window";

  //Set up window class
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
  wnd.lpszClassName = (LPCSTR)windowName;

  //Register window class
  RegisterClass(&wnd);

  //Create window
  //! This returns NULL
  HWND hWnd = CreateWindowEx(
    0,
    wnd.lpszClassName,
    wnd.lpszClassName,
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

  //Simple check to see if window creation failed
  if (hWnd == NULL)
  {
    //Pause
    system("PAUSE");
    return -1;
  }

  //Show the window
  ShowWindow(hWnd, SW_SHOWDEFAULT);

  /*
  PIXELFORMATDESCRIPTOR pfd = { 0 };

  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;
  */

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

  g_hDC = GetDC(hWnd);

  int pf = ChoosePixelFormat(g_hDC, &pfd);

  if (!SetPixelFormat(g_hDC, pf, &pfd))
    return -1;

  if (!(g_hRC = wglCreateContext(g_hDC)))
    return -1;

  if (!wglMakeCurrent(g_hDC, g_hRC))
    return -1;

  printf("Hello World\n");

  while (true)
  {
    //UpdateWindow(hWnd);
    glViewport(0, 0, 1600, 800);
    glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SwapBuffers(g_hDC);
  }

  CRenderer mRenderer;

  if (mRenderer.Create( 1600, 800 ))
  {
    while (mRenderer.Execute() )
    {
    }
  }
  mRenderer.Terminate();
  return 0;
}
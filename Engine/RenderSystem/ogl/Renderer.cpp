#include "Renderer.h"

#include "ogl.h"

namespace renderer
{
  static GLFWwindow* sWindow;
  CRenderer::CRenderer()
  {
  }

  CRenderer::~CRenderer()
  {
  }

  bool CRenderer::Create( uint32 aWidth, uint32 aHeight )
  {
    bool lOk = false;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create the window
    sWindow = glfwCreateWindow(aWidth, aHeight, "Window", nullptr, nullptr);

    if( sWindow != nullptr )
    {
      glfwMakeContextCurrent(sWindow);
      glewExperimental = GL_TRUE;
      lOk = (glewInit() == GLEW_OK);
      glViewport(0, 0, aWidth, aHeight);
    }
    
    return lOk;
  }

  bool CRenderer::Execute()
  {
    if( !glfwWindowShouldClose(sWindow) )
    {
      glfwPollEvents();

      glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glfwSwapBuffers(sWindow);
      return true;
    }
    return false;
  }

  void CRenderer::Terminate()
  {
    glfwTerminate();
  }
}

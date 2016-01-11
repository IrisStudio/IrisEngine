#include "Renderer.h"
#include "ExtensionManager.h"
#include "ogl.h"
#include "Effect.h"
#include "RenderSystem.h"
#include "EffectLibrary.h"
#include "Logger/Logger.h"

#include <windows.h>

namespace
{
  uint32 m_vertexArrayObject;
  uint32 m_vertexBufferObject;
  CEffectSPtr mEffect;

  WNDCLASSEX  m_wcl;

  inline const GLubyte *BUFFER_OFFSET(size_t bytes)
  {
    return reinterpret_cast<const GLubyte *>(0) + bytes;
  }

  void initFullScreenQuad()
  {
    // Setup the full screen quad geometry as a triangle strip.
    // The vertex positions are in normalized device coordinates (NDC).
    //
    // In NDC:
    //  (-1,  1) is always the top-left corner of the viewport.
    //  (-1, -1) is always the bottom-left corner of the viewport.
    //  ( 1,  1) is always the top-right corner of the viewport.
    //  ( 1, -1) is always the bottom-right corner of the viewport.
    //
    //	v0---v2
    //	|   / |
    //	| /   |
    //	v1---v3

    float quad[] =
    {
      -1.0f,  1.0f,	// v0 - top left corner
      -1.0f, -1.0f,	// v1 - bottom left corner
      1.0f,  1.0f,	// v2 - top right corner
      1.0f, -1.0f	// v3 - bottom right corner
    };

    // Create the vertex array object for the full screen quad.
    /*
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);
    IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "OGL_ERRORS");

    // Create the Vertex Buffer Object for the full screen quad.

    glGenBuffers(1, &m_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "OGL_ERRORS");

    // Map the generic vertex attributes used by the full screen quad's shader
    // program to the full screen quad's vertex data stored in the vertex
    // buffer object.

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "OGL_ERRORS");*/
  }
}

CRenderer::CRenderer()
{
}

CRenderer::~CRenderer()
{
}

bool CRenderer::Create( uint32 aWidth, uint32 aHeight )
{
  /*
  GLenum lError = GL_NO_ERROR;
  bool lOk = false;

  glfwInit();
  lError = glGetError();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  lError = glGetError();
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  lError = glGetError();
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create the window
  sWindow = glfwCreateWindow(aWidth, aHeight, "Window", nullptr, nullptr);

  IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "OGL_ERRORS_3");

  if( sWindow != nullptr )
  {
    IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "OGL_ERRORS_4");
    glfwMakeContextCurrent(sWindow);
    IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "OGL_ERRORS_5");
    glewExperimental = GL_TRUE;
    IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "OGL_ERRORS_6");
    lOk = (glewInit() == GLEW_OK);
    IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "OGL_ERRORS_7");
    glViewport(0, 0, aWidth, aHeight);
    IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "OGL_ERRORS_8");
    CExtensionManager::Instance().GetExtensions();
    IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "OGL_ERRORS_9_GET_EXTENSIONS");
    CEffectLibrary library;
    mEffect = library.CreateEffect("../data/effects/effect01.xml");
    initFullScreenQuad();
  }
    
  return lOk;
  */


  return false;
}

bool CRenderer::Execute()
{
  return false;
}

void CRenderer::Terminate()
{
}

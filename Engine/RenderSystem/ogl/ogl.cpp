#include "ogl.h"
#include <assert.h>

#define GET_PROC_ADDR(name, var, type) \
if (!var) \
{ \
  var = reinterpret_cast<type>(GetAnyGLFuncAddress(name)); \
  assert(var != 0); \
}

namespace ogl
{
  namespace
  {
    void *GetAnyGLFuncAddress(const char *name)
    {
      void *p = (void *)wglGetProcAddress(name);
      if(p == 0 ||
        (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
        (p == (void*)-1) )
      {
        HMODULE module = LoadLibraryA("opengl32.dll");
        p = (void *)GetProcAddress(module, name);
      }

      return p;
    }
  }

#define BIND_OGL_ADDR( return_type, func_name, ... )           \
  typedef return_type (APIENTRY * PFN##func_name##PROC )( __VA_ARGS__ ); \
  static PFN##func_name##PROC pfn##func_name = 0;                    \
  if(!pfn##func_name)                                                \
  {                                                                  \
  pfn##func_name = reinterpret_cast<PFN##func_name##PROC>(GetAnyGLFuncAddress(#func_name));           \
  assert(pfn##func_name != 0);                                       \
  }                                                                  \

#define CALL_PROC_ADDR(func_name, ... ) pfn##func_name( __VA_ARGS__ );

  void glGetIntegerv( GLenum pname, GLint params)
  {
    BIND_OGL_ADDR(void, glGetIntegerv, GLenum pname, GLint params )
    CALL_PROC_ADDR(glGetIntegerv, pname, params )
  }

  const GLubyte *glGetStringi(GLenum name, GLuint index)
  {
    BIND_OGL_ADDR(const GLubyte *, glGetStringi, GLenum name, GLuint index )
    return CALL_PROC_ADDR(glGetStringi, name, index )
  }

  const GLubyte *glGetString(GLenum name)
  {
    BIND_OGL_ADDR(const GLubyte *, glGetString, GLenum name )
    return CALL_PROC_ADDR(glGetString, name )
  }
}
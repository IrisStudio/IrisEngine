#include "ogl.h"
#include "StringUtils.h"
#include "Logger/Logger.h"
#include <assert.h>
#include <string>
#include <Windows.h>

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

    HGLRC wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int *attribList)
    {
      BIND_OGL_ADDR(HGLRC, wglCreateContextAttribsARB, HDC hDC, HGLRC hShareContext, const int *attribList)
      return CALL_PROC_ADDR(wglCreateContextAttribsARB, hDC, hShareContext, attribList)
    }

    void InitOGLFunctions()
    {
      /* GL_VERSION_1_2 */
      oglCopyTexSubImage3D = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glCopyTexSubImage3D"));
      oglDrawRangeElements = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *)>(GetAnyGLFuncAddress("glDrawRangeElements"));
      oglTexImage3D = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glTexImage3D"));
      oglTexSubImage3D = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glTexSubImage3D"));

      /* GL_VERSION_1_3 */
      oglActiveTexture = reinterpret_cast<void(APIENTRY*)(GLenum)>(GetAnyGLFuncAddress("glActiveTexture"));
      oglCompressedTexImage1D = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *)>(GetAnyGLFuncAddress("glCompressedTexImage1D"));
      oglCompressedTexImage2D = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *)>(GetAnyGLFuncAddress("glCompressedTexImage2D"));
      oglCompressedTexImage3D = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *)>(GetAnyGLFuncAddress("glCompressedTexImage3D"));
      oglCompressedTexSubImage1D = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *)>(GetAnyGLFuncAddress("glCompressedTexSubImage1D"));
      oglCompressedTexSubImage2D = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *)>(GetAnyGLFuncAddress("glCompressedTexSubImage2D"));
      oglCompressedTexSubImage3D = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *)>(GetAnyGLFuncAddress("glCompressedTexSubImage3D"));
      oglGetCompressedTexImage = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, void *)>(GetAnyGLFuncAddress("glGetCompressedTexImage"));
      oglSampleCoverage = reinterpret_cast<void(APIENTRY*)(GLfloat, GLboolean)>(GetAnyGLFuncAddress("glSampleCoverage"));

      /* GL_VERSION_1_4 */
      oglBlendColor = reinterpret_cast<void(APIENTRY*)(GLfloat, GLfloat, GLfloat, GLfloat)>(GetAnyGLFuncAddress("glBlendColor"));
      oglBlendEquation = reinterpret_cast<void(APIENTRY*)(GLenum)>(GetAnyGLFuncAddress("glBlendEquation"));
      oglBlendFuncSeparate = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLenum, GLenum)>(GetAnyGLFuncAddress("glBlendFuncSeparate"));
      oglMultiDrawArrays = reinterpret_cast<void(APIENTRY*)(GLenum, const GLint *, const GLsizei *, GLsizei)>(GetAnyGLFuncAddress("glMultiDrawArrays"));
      oglMultiDrawElements = reinterpret_cast<void(APIENTRY*)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei)>(GetAnyGLFuncAddress("glMultiDrawElements"));
      oglPointParameterf = reinterpret_cast<void(APIENTRY*)(GLenum, GLfloat)>(GetAnyGLFuncAddress("glPointParameterf"));
      oglPointParameterfv = reinterpret_cast<void(APIENTRY*)(GLenum, const GLfloat *)>(GetAnyGLFuncAddress("glPointParameterfv"));
      oglPointParameteri = reinterpret_cast<void(APIENTRY*)(GLenum, GLint)>(GetAnyGLFuncAddress("glPointParameteri"));
      oglPointParameteriv = reinterpret_cast<void(APIENTRY*)(GLenum, const GLint *)>(GetAnyGLFuncAddress("glPointParameteriv"));

      /* GL_VERSION_1_5 */
      oglBeginQuery = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glBeginQuery"));
      oglBindBuffer = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glBindBuffer"));
      oglBufferData = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizeiptr, const void *, GLenum)>(GetAnyGLFuncAddress("glBufferData"));
      oglBufferSubData = reinterpret_cast<void(APIENTRY*)(GLenum, GLintptr, GLsizeiptr, const void *)>(GetAnyGLFuncAddress("glBufferSubData"));
      oglDeleteBuffers = reinterpret_cast<void(APIENTRY*)(GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glDeleteBuffers"));
      oglDeleteQueries = reinterpret_cast<void(APIENTRY*)(GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glDeleteQueries"));
      oglEndQuery = reinterpret_cast<void(APIENTRY*)(GLenum)>(GetAnyGLFuncAddress("glEndQuery"));
      oglGenBuffers = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glGenBuffers"));
      oglGenQueries = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glGenQueries"));
      oglGetBufferParameteriv = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetBufferParameteriv"));
      oglGetBufferPointerv = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, void **)>(GetAnyGLFuncAddress("glGetBufferPointerv"));
      oglGetBufferSubData = reinterpret_cast<void(APIENTRY*)(GLenum, GLintptr, GLsizeiptr, void *)>(GetAnyGLFuncAddress("glGetBufferSubData"));
      oglGetQueryObjectiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetQueryObjectiv"));
      oglGetQueryObjectuiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint *)>(GetAnyGLFuncAddress("glGetQueryObjectuiv"));
      oglGetQueryiv = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetQueryiv"));
      oglIsBuffer = reinterpret_cast<GLboolean(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glIsBuffer"));
      oglIsQuery = reinterpret_cast<GLboolean(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glIsQuery"));
      oglMapBuffer = reinterpret_cast<void *(APIENTRY*)(GLenum, GLenum)>(GetAnyGLFuncAddress("glMapBuffer"));
      oglUnmapBuffer = reinterpret_cast<GLboolean(APIENTRY*)(GLenum)>(GetAnyGLFuncAddress("glUnmapBuffer"));

      /* GL_VERSION_2_0 */
      oglAttachShader = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glAttachShader"));
      oglBindAttribLocation = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, const GLchar *)>(GetAnyGLFuncAddress("glBindAttribLocation"));
      oglBlendEquationSeparate = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum)>(GetAnyGLFuncAddress("glBlendEquationSeparate"));
      oglCompileShader = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glCompileShader"));
      oglCreateProgram = reinterpret_cast<GLuint(APIENTRY*)(void)>(GetAnyGLFuncAddress("glCreateProgram"));
      oglCreateShader = reinterpret_cast<GLuint(APIENTRY*)(GLenum)>(GetAnyGLFuncAddress("glCreateShader"));
      oglDeleteProgram = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glDeleteProgram"));
      oglDeleteShader = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glDeleteShader"));
      oglDetachShader = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glDetachShader"));
      oglDisableVertexAttribArray = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glDisableVertexAttribArray"));
      oglDrawBuffers = reinterpret_cast<void(APIENTRY*)(GLsizei, const GLenum *)>(GetAnyGLFuncAddress("glDrawBuffers"));
      oglEnableVertexAttribArray = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glEnableVertexAttribArray"));
      oglGetActiveAttrib = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *)>(GetAnyGLFuncAddress("glGetActiveAttrib"));
      oglGetActiveUniform = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *)>(GetAnyGLFuncAddress("glGetActiveUniform"));
      oglGetAttachedShaders = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLsizei *, GLuint *)>(GetAnyGLFuncAddress("glGetAttachedShaders"));
      oglGetAttribLocation = reinterpret_cast<GLint(APIENTRY*)(GLuint, const GLchar *)>(GetAnyGLFuncAddress("glGetAttribLocation"));
      oglGetProgramInfoLog = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetProgramInfoLog"));
      oglGetProgramiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetProgramiv"));
      oglGetShaderInfoLog = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetShaderInfoLog"));
      oglGetShaderSource = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetShaderSource"));
      oglGetShaderiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetShaderiv"));
      oglGetUniformLocation = reinterpret_cast<GLint(APIENTRY*)(GLuint, const GLchar *)>(GetAnyGLFuncAddress("glGetUniformLocation"));
      oglGetUniformfv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLfloat *)>(GetAnyGLFuncAddress("glGetUniformfv"));
      oglGetUniformiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint *)>(GetAnyGLFuncAddress("glGetUniformiv"));
      oglGetVertexAttribPointerv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, void **)>(GetAnyGLFuncAddress("glGetVertexAttribPointerv"));
      oglGetVertexAttribdv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLdouble *)>(GetAnyGLFuncAddress("glGetVertexAttribdv"));
      oglGetVertexAttribfv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLfloat *)>(GetAnyGLFuncAddress("glGetVertexAttribfv"));
      oglGetVertexAttribiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetVertexAttribiv"));
      oglIsProgram = reinterpret_cast<GLboolean(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glIsProgram"));
      oglIsShader = reinterpret_cast<GLboolean(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glIsShader"));
      oglLinkProgram = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glLinkProgram"));
      oglShaderSource = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLchar *const*, const GLint *)>(GetAnyGLFuncAddress("glShaderSource"));
      oglStencilFuncSeparate = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLint, GLuint)>(GetAnyGLFuncAddress("glStencilFuncSeparate"));
      oglStencilMaskSeparate = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glStencilMaskSeparate"));
      oglStencilOpSeparate = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLenum, GLenum)>(GetAnyGLFuncAddress("glStencilOpSeparate"));
      oglUniform1f = reinterpret_cast<void(APIENTRY*)(GLint, GLfloat)>(GetAnyGLFuncAddress("glUniform1f"));
      oglUniform1fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLfloat *)>(GetAnyGLFuncAddress("glUniform1fv"));
      oglUniform1i = reinterpret_cast<void(APIENTRY*)(GLint, GLint)>(GetAnyGLFuncAddress("glUniform1i"));
      oglUniform1iv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLint *)>(GetAnyGLFuncAddress("glUniform1iv"));
      oglUniform2f = reinterpret_cast<void(APIENTRY*)(GLint, GLfloat, GLfloat)>(GetAnyGLFuncAddress("glUniform2f"));
      oglUniform2fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLfloat *)>(GetAnyGLFuncAddress("glUniform2fv"));
      oglUniform2i = reinterpret_cast<void(APIENTRY*)(GLint, GLint, GLint)>(GetAnyGLFuncAddress("glUniform2i"));
      oglUniform2iv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLint *)>(GetAnyGLFuncAddress("glUniform2iv"));
      oglUniform3f = reinterpret_cast<void(APIENTRY*)(GLint, GLfloat, GLfloat, GLfloat)>(GetAnyGLFuncAddress("glUniform3f"));
      oglUniform3fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLfloat *)>(GetAnyGLFuncAddress("glUniform3fv"));
      oglUniform3i = reinterpret_cast<void(APIENTRY*)(GLint, GLint, GLint, GLint)>(GetAnyGLFuncAddress("glUniform3i"));
      oglUniform3iv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLint *)>(GetAnyGLFuncAddress("glUniform3iv"));
      oglUniform4f = reinterpret_cast<void(APIENTRY*)(GLint, GLfloat, GLfloat, GLfloat, GLfloat)>(GetAnyGLFuncAddress("glUniform4f"));
      oglUniform4fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLfloat *)>(GetAnyGLFuncAddress("glUniform4fv"));
      oglUniform4i = reinterpret_cast<void(APIENTRY*)(GLint, GLint, GLint, GLint, GLint)>(GetAnyGLFuncAddress("glUniform4i"));
      oglUniform4iv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLint *)>(GetAnyGLFuncAddress("glUniform4iv"));
      oglUniformMatrix2fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glUniformMatrix2fv"));
      oglUniformMatrix3fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glUniformMatrix3fv"));
      oglUniformMatrix4fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glUniformMatrix4fv"));
      oglUseProgram = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glUseProgram"));
      oglValidateProgram = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glValidateProgram"));
      oglVertexAttrib1d = reinterpret_cast<void(APIENTRY*)(GLuint, GLdouble)>(GetAnyGLFuncAddress("glVertexAttrib1d"));
      oglVertexAttrib1dv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLdouble *)>(GetAnyGLFuncAddress("glVertexAttrib1dv"));
      oglVertexAttrib1f = reinterpret_cast<void(APIENTRY*)(GLuint, GLfloat)>(GetAnyGLFuncAddress("glVertexAttrib1f"));
      oglVertexAttrib1fv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLfloat *)>(GetAnyGLFuncAddress("glVertexAttrib1fv"));
      oglVertexAttrib1s = reinterpret_cast<void(APIENTRY*)(GLuint, GLshort)>(GetAnyGLFuncAddress("glVertexAttrib1s"));
      oglVertexAttrib1sv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLshort *)>(GetAnyGLFuncAddress("glVertexAttrib1sv"));
      oglVertexAttrib2d = reinterpret_cast<void(APIENTRY*)(GLuint, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glVertexAttrib2d"));
      oglVertexAttrib2dv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLdouble *)>(GetAnyGLFuncAddress("glVertexAttrib2dv"));
      oglVertexAttrib2f = reinterpret_cast<void(APIENTRY*)(GLuint, GLfloat, GLfloat)>(GetAnyGLFuncAddress("glVertexAttrib2f"));
      oglVertexAttrib2fv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLfloat *)>(GetAnyGLFuncAddress("glVertexAttrib2fv"));
      oglVertexAttrib2s = reinterpret_cast<void(APIENTRY*)(GLuint, GLshort, GLshort)>(GetAnyGLFuncAddress("glVertexAttrib2s"));
      oglVertexAttrib2sv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLshort *)>(GetAnyGLFuncAddress("glVertexAttrib2sv"));
      oglVertexAttrib3d = reinterpret_cast<void(APIENTRY*)(GLuint, GLdouble, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glVertexAttrib3d"));
      oglVertexAttrib3dv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLdouble *)>(GetAnyGLFuncAddress("glVertexAttrib3dv"));
      oglVertexAttrib3f = reinterpret_cast<void(APIENTRY*)(GLuint, GLfloat, GLfloat, GLfloat)>(GetAnyGLFuncAddress("glVertexAttrib3f"));
      oglVertexAttrib3fv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLfloat *)>(GetAnyGLFuncAddress("glVertexAttrib3fv"));
      oglVertexAttrib3s = reinterpret_cast<void(APIENTRY*)(GLuint, GLshort, GLshort, GLshort)>(GetAnyGLFuncAddress("glVertexAttrib3s"));
      oglVertexAttrib3sv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLshort *)>(GetAnyGLFuncAddress("glVertexAttrib3sv"));
      oglVertexAttrib4Nbv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLbyte *)>(GetAnyGLFuncAddress("glVertexAttrib4Nbv"));
      oglVertexAttrib4Niv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLint *)>(GetAnyGLFuncAddress("glVertexAttrib4Niv"));
      oglVertexAttrib4Nsv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLshort *)>(GetAnyGLFuncAddress("glVertexAttrib4Nsv"));
      oglVertexAttrib4Nub = reinterpret_cast<void(APIENTRY*)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte)>(GetAnyGLFuncAddress("glVertexAttrib4Nub"));
      oglVertexAttrib4Nubv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLubyte *)>(GetAnyGLFuncAddress("glVertexAttrib4Nubv"));
      oglVertexAttrib4Nuiv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLuint *)>(GetAnyGLFuncAddress("glVertexAttrib4Nuiv"));
      oglVertexAttrib4Nusv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLushort *)>(GetAnyGLFuncAddress("glVertexAttrib4Nusv"));
      oglVertexAttrib4bv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLbyte *)>(GetAnyGLFuncAddress("glVertexAttrib4bv"));
      oglVertexAttrib4d = reinterpret_cast<void(APIENTRY*)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glVertexAttrib4d"));
      oglVertexAttrib4dv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLdouble *)>(GetAnyGLFuncAddress("glVertexAttrib4dv"));
      oglVertexAttrib4f = reinterpret_cast<void(APIENTRY*)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat)>(GetAnyGLFuncAddress("glVertexAttrib4f"));
      oglVertexAttrib4fv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLfloat *)>(GetAnyGLFuncAddress("glVertexAttrib4fv"));
      oglVertexAttrib4iv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLint *)>(GetAnyGLFuncAddress("glVertexAttrib4iv"));
      oglVertexAttrib4s = reinterpret_cast<void(APIENTRY*)(GLuint, GLshort, GLshort, GLshort, GLshort)>(GetAnyGLFuncAddress("glVertexAttrib4s"));
      oglVertexAttrib4sv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLshort *)>(GetAnyGLFuncAddress("glVertexAttrib4sv"));
      oglVertexAttrib4ubv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLubyte *)>(GetAnyGLFuncAddress("glVertexAttrib4ubv"));
      oglVertexAttrib4uiv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLuint *)>(GetAnyGLFuncAddress("glVertexAttrib4uiv"));
      oglVertexAttrib4usv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLushort *)>(GetAnyGLFuncAddress("glVertexAttrib4usv"));
      oglVertexAttribPointer = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *)>(GetAnyGLFuncAddress("glVertexAttribPointer"));

      /* GL_VERSION_2_1 */
      oglUniformMatrix2x3fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glUniformMatrix2x3fv"));
      oglUniformMatrix2x4fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glUniformMatrix2x4fv"));
      oglUniformMatrix3x2fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glUniformMatrix3x2fv"));
      oglUniformMatrix3x4fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glUniformMatrix3x4fv"));
      oglUniformMatrix4x2fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glUniformMatrix4x2fv"));
      oglUniformMatrix4x3fv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glUniformMatrix4x3fv"));

      /* GL_VERSION_3_0 */
      oglBeginConditionalRender = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum)>(GetAnyGLFuncAddress("glBeginConditionalRender"));
      oglBeginTransformFeedback = reinterpret_cast<void(APIENTRY*)(GLenum)>(GetAnyGLFuncAddress("glBeginTransformFeedback"));
      oglBindBufferBase = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLuint)>(GetAnyGLFuncAddress("glBindBufferBase"));
      oglBindBufferRange = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr)>(GetAnyGLFuncAddress("glBindBufferRange"));
      oglBindFragDataLocation = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, const GLchar *)>(GetAnyGLFuncAddress("glBindFragDataLocation"));
      oglBindFramebuffer = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glBindFramebuffer"));
      oglBindRenderbuffer = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glBindRenderbuffer"));
      oglBindVertexArray = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glBindVertexArray"));
      oglBlitFramebuffer = reinterpret_cast<void(APIENTRY*)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum)>(GetAnyGLFuncAddress("glBlitFramebuffer"));
      oglCheckFramebufferStatus = reinterpret_cast<GLenum(APIENTRY*)(GLenum)>(GetAnyGLFuncAddress("glCheckFramebufferStatus"));
      oglClampColor = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum)>(GetAnyGLFuncAddress("glClampColor"));
      oglClearBufferfi = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLfloat, GLint)>(GetAnyGLFuncAddress("glClearBufferfi"));
      oglClearBufferfv = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, const GLfloat *)>(GetAnyGLFuncAddress("glClearBufferfv"));
      oglClearBufferiv = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, const GLint *)>(GetAnyGLFuncAddress("glClearBufferiv"));
      oglClearBufferuiv = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, const GLuint *)>(GetAnyGLFuncAddress("glClearBufferuiv"));
      oglColorMaski = reinterpret_cast<void(APIENTRY*)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean)>(GetAnyGLFuncAddress("glColorMaski"));
      oglDeleteFramebuffers = reinterpret_cast<void(APIENTRY*)(GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glDeleteFramebuffers"));
      oglDeleteRenderbuffers = reinterpret_cast<void(APIENTRY*)(GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glDeleteRenderbuffers"));
      oglDeleteVertexArrays = reinterpret_cast<void(APIENTRY*)(GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glDeleteVertexArrays"));
      oglDisablei = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glDisablei"));
      oglEnablei = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glEnablei"));
      oglEndConditionalRender = reinterpret_cast<void(APIENTRY*)(void)>(GetAnyGLFuncAddress("glEndConditionalRender"));
      oglEndTransformFeedback = reinterpret_cast<void(APIENTRY*)(void)>(GetAnyGLFuncAddress("glEndTransformFeedback"));
      oglFlushMappedBufferRange = reinterpret_cast<void(APIENTRY*)(GLenum, GLintptr, GLsizeiptr)>(GetAnyGLFuncAddress("glFlushMappedBufferRange"));
      oglFramebufferRenderbuffer = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLenum, GLuint)>(GetAnyGLFuncAddress("glFramebufferRenderbuffer"));
      oglFramebufferTexture1D = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLenum, GLuint, GLint)>(GetAnyGLFuncAddress("glFramebufferTexture1D"));
      oglFramebufferTexture2D = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLenum, GLuint, GLint)>(GetAnyGLFuncAddress("glFramebufferTexture2D"));
      oglFramebufferTexture3D = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLenum, GLuint, GLint, GLint)>(GetAnyGLFuncAddress("glFramebufferTexture3D"));
      oglFramebufferTextureLayer = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLuint, GLint, GLint)>(GetAnyGLFuncAddress("glFramebufferTextureLayer"));
      oglGenFramebuffers = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glGenFramebuffers"));
      oglGenRenderbuffers = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glGenRenderbuffers"));
      oglGenVertexArrays = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glGenVertexArrays"));
      oglGenerateMipmap = reinterpret_cast<void(APIENTRY*)(GLenum)>(GetAnyGLFuncAddress("glGenerateMipmap"));
      oglGetBooleani_v = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLboolean *)>(GetAnyGLFuncAddress("glGetBooleani_v"));
      oglGetFragDataLocation = reinterpret_cast<GLint(APIENTRY*)(GLuint, const GLchar *)>(GetAnyGLFuncAddress("glGetFragDataLocation"));
      oglGetFramebufferAttachmentParameteriv = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetFramebufferAttachmentParameteriv"));
      oglGetIntegeri_v = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLint *)>(GetAnyGLFuncAddress("glGetIntegeri_v"));
      oglGetRenderbufferParameteriv = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetRenderbufferParameteriv"));
      oglGetStringi = reinterpret_cast<const GLubyte *(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glGetStringi"));
      oglGetTexParameterIiv = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetTexParameterIiv"));
      oglGetTexParameterIuiv = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLuint *)>(GetAnyGLFuncAddress("glGetTexParameterIuiv"));
      oglGetTransformFeedbackVarying = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *)>(GetAnyGLFuncAddress("glGetTransformFeedbackVarying"));
      oglGetUniformuiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLuint *)>(GetAnyGLFuncAddress("glGetUniformuiv"));
      oglGetVertexAttribIiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetVertexAttribIiv"));
      oglGetVertexAttribIuiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint *)>(GetAnyGLFuncAddress("glGetVertexAttribIuiv"));
      oglIsEnabledi = reinterpret_cast<GLboolean(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glIsEnabledi"));
      oglIsFramebuffer = reinterpret_cast<GLboolean(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glIsFramebuffer"));
      oglIsRenderbuffer = reinterpret_cast<GLboolean(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glIsRenderbuffer"));
      oglIsVertexArray = reinterpret_cast<GLboolean(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glIsVertexArray"));
      oglMapBufferRange = reinterpret_cast<void *(APIENTRY*)(GLenum, GLintptr, GLsizeiptr, GLbitfield)>(GetAnyGLFuncAddress("glMapBufferRange"));
      oglRenderbufferStorage = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glRenderbufferStorage"));
      oglRenderbufferStorageMultisample = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glRenderbufferStorageMultisample"));
      oglTexParameterIiv = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, const GLint *)>(GetAnyGLFuncAddress("glTexParameterIiv"));
      oglTexParameterIuiv = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, const GLuint *)>(GetAnyGLFuncAddress("glTexParameterIuiv"));
      oglTransformFeedbackVaryings = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLchar *const*, GLenum)>(GetAnyGLFuncAddress("glTransformFeedbackVaryings"));
      oglUniform1ui = reinterpret_cast<void(APIENTRY*)(GLint, GLuint)>(GetAnyGLFuncAddress("glUniform1ui"));
      oglUniform1uiv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glUniform1uiv"));
      oglUniform2ui = reinterpret_cast<void(APIENTRY*)(GLint, GLuint, GLuint)>(GetAnyGLFuncAddress("glUniform2ui"));
      oglUniform2uiv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glUniform2uiv"));
      oglUniform3ui = reinterpret_cast<void(APIENTRY*)(GLint, GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glUniform3ui"));
      oglUniform3uiv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glUniform3uiv"));
      oglUniform4ui = reinterpret_cast<void(APIENTRY*)(GLint, GLuint, GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glUniform4ui"));
      oglUniform4uiv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glUniform4uiv"));
      oglVertexAttribI1i = reinterpret_cast<void(APIENTRY*)(GLuint, GLint)>(GetAnyGLFuncAddress("glVertexAttribI1i"));
      oglVertexAttribI1iv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLint *)>(GetAnyGLFuncAddress("glVertexAttribI1iv"));
      oglVertexAttribI1ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glVertexAttribI1ui"));
      oglVertexAttribI1uiv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLuint *)>(GetAnyGLFuncAddress("glVertexAttribI1uiv"));
      oglVertexAttribI2i = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint)>(GetAnyGLFuncAddress("glVertexAttribI2i"));
      oglVertexAttribI2iv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLint *)>(GetAnyGLFuncAddress("glVertexAttribI2iv"));
      oglVertexAttribI2ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glVertexAttribI2ui"));
      oglVertexAttribI2uiv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLuint *)>(GetAnyGLFuncAddress("glVertexAttribI2uiv"));
      oglVertexAttribI3i = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint)>(GetAnyGLFuncAddress("glVertexAttribI3i"));
      oglVertexAttribI3iv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLint *)>(GetAnyGLFuncAddress("glVertexAttribI3iv"));
      oglVertexAttribI3ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glVertexAttribI3ui"));
      oglVertexAttribI3uiv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLuint *)>(GetAnyGLFuncAddress("glVertexAttribI3uiv"));
      oglVertexAttribI4bv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLbyte *)>(GetAnyGLFuncAddress("glVertexAttribI4bv"));
      oglVertexAttribI4i = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint)>(GetAnyGLFuncAddress("glVertexAttribI4i"));
      oglVertexAttribI4iv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLint *)>(GetAnyGLFuncAddress("glVertexAttribI4iv"));
      oglVertexAttribI4sv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLshort *)>(GetAnyGLFuncAddress("glVertexAttribI4sv"));
      oglVertexAttribI4ubv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLubyte *)>(GetAnyGLFuncAddress("glVertexAttribI4ubv"));
      oglVertexAttribI4ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glVertexAttribI4ui"));
      oglVertexAttribI4uiv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLuint *)>(GetAnyGLFuncAddress("glVertexAttribI4uiv"));
      oglVertexAttribI4usv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLushort *)>(GetAnyGLFuncAddress("glVertexAttribI4usv"));
      oglVertexAttribIPointer = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLenum, GLsizei, const void *)>(GetAnyGLFuncAddress("glVertexAttribIPointer"));

      /* GL_VERSION_3_1 */
      oglCopyBufferSubData = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr)>(GetAnyGLFuncAddress("glCopyBufferSubData"));
      oglDrawArraysInstanced = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glDrawArraysInstanced"));
      oglDrawElementsInstanced = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, const void *, GLsizei)>(GetAnyGLFuncAddress("glDrawElementsInstanced"));
      oglGetActiveUniformBlockName = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetActiveUniformBlockName"));
      oglGetActiveUniformBlockiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetActiveUniformBlockiv"));
      oglGetActiveUniformName = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetActiveUniformName"));
      oglGetActiveUniformsiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLuint *, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetActiveUniformsiv"));
      oglGetUniformBlockIndex = reinterpret_cast<GLuint(APIENTRY*)(GLuint, const GLchar *)>(GetAnyGLFuncAddress("glGetUniformBlockIndex"));
      oglGetUniformIndices = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLchar *const*, GLuint *)>(GetAnyGLFuncAddress("glGetUniformIndices"));
      oglPrimitiveRestartIndex = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glPrimitiveRestartIndex"));
      oglTexBuffer = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLuint)>(GetAnyGLFuncAddress("glTexBuffer"));
      oglUniformBlockBinding = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glUniformBlockBinding"));

      /* GL_VERSION_3_2 */
      oglClientWaitSync = reinterpret_cast<GLenum(APIENTRY*)(GLsync, GLbitfield, GLuint64)>(GetAnyGLFuncAddress("glClientWaitSync"));
      oglDeleteSync = reinterpret_cast<void(APIENTRY*)(GLsync)>(GetAnyGLFuncAddress("glDeleteSync"));
      oglDrawElementsBaseVertex = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, const void *, GLint)>(GetAnyGLFuncAddress("glDrawElementsBaseVertex"));
      oglDrawElementsInstancedBaseVertex = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint)>(GetAnyGLFuncAddress("glDrawElementsInstancedBaseVertex"));
      oglDrawRangeElementsBaseVertex = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint)>(GetAnyGLFuncAddress("glDrawRangeElementsBaseVertex"));
      oglFenceSync = reinterpret_cast<GLsync(APIENTRY*)(GLenum, GLbitfield)>(GetAnyGLFuncAddress("glFenceSync"));
      oglFramebufferTexture = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLuint, GLint)>(GetAnyGLFuncAddress("glFramebufferTexture"));
      oglGetBufferParameteri64v = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLint64 *)>(GetAnyGLFuncAddress("glGetBufferParameteri64v"));
      oglGetInteger64i_v = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLint64 *)>(GetAnyGLFuncAddress("glGetInteger64i_v"));
      oglGetInteger64v = reinterpret_cast<void(APIENTRY*)(GLenum, GLint64 *)>(GetAnyGLFuncAddress("glGetInteger64v"));
      oglGetMultisamplefv = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLfloat *)>(GetAnyGLFuncAddress("glGetMultisamplefv"));
      oglGetSynciv = reinterpret_cast<void(APIENTRY*)(GLsync, GLenum, GLsizei, GLsizei *, GLint *)>(GetAnyGLFuncAddress("glGetSynciv"));
      oglIsSync = reinterpret_cast<GLboolean(APIENTRY*)(GLsync)>(GetAnyGLFuncAddress("glIsSync"));
      oglMultiDrawElementsBaseVertex = reinterpret_cast<void(APIENTRY*)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *)>(GetAnyGLFuncAddress("glMultiDrawElementsBaseVertex"));
      oglProvokingVertex = reinterpret_cast<void(APIENTRY*)(GLenum)>(GetAnyGLFuncAddress("glProvokingVertex"));
      oglSampleMaski = reinterpret_cast<void(APIENTRY*)(GLuint, GLbitfield)>(GetAnyGLFuncAddress("glSampleMaski"));
      oglTexImage2DMultisample = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean)>(GetAnyGLFuncAddress("glTexImage2DMultisample"));
      oglTexImage3DMultisample = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean)>(GetAnyGLFuncAddress("glTexImage3DMultisample"));
      oglWaitSync = reinterpret_cast<void(APIENTRY*)(GLsync, GLbitfield, GLuint64)>(GetAnyGLFuncAddress("glWaitSync"));

      /* GL_VERSION_3_3 */
      oglBindFragDataLocationIndexed = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint, const GLchar *)>(GetAnyGLFuncAddress("glBindFragDataLocationIndexed"));
      oglBindSampler = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glBindSampler"));
      oglDeleteSamplers = reinterpret_cast<void(APIENTRY*)(GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glDeleteSamplers"));
      oglGenSamplers = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glGenSamplers"));
      oglGetFragDataIndex = reinterpret_cast<GLint(APIENTRY*)(GLuint, const GLchar *)>(GetAnyGLFuncAddress("glGetFragDataIndex"));
      oglGetQueryObjecti64v = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint64 *)>(GetAnyGLFuncAddress("glGetQueryObjecti64v"));
      oglGetQueryObjectui64v = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint64 *)>(GetAnyGLFuncAddress("glGetQueryObjectui64v"));
      oglGetSamplerParameterIiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetSamplerParameterIiv"));
      oglGetSamplerParameterIuiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint *)>(GetAnyGLFuncAddress("glGetSamplerParameterIuiv"));
      oglGetSamplerParameterfv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLfloat *)>(GetAnyGLFuncAddress("glGetSamplerParameterfv"));
      oglGetSamplerParameteriv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetSamplerParameteriv"));
      oglIsSampler = reinterpret_cast<GLboolean(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glIsSampler"));
      oglQueryCounter = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum)>(GetAnyGLFuncAddress("glQueryCounter"));
      oglSamplerParameterIiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, const GLint *)>(GetAnyGLFuncAddress("glSamplerParameterIiv"));
      oglSamplerParameterIuiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, const GLuint *)>(GetAnyGLFuncAddress("glSamplerParameterIuiv"));
      oglSamplerParameterf = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLfloat)>(GetAnyGLFuncAddress("glSamplerParameterf"));
      oglSamplerParameterfv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, const GLfloat *)>(GetAnyGLFuncAddress("glSamplerParameterfv"));
      oglSamplerParameteri = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint)>(GetAnyGLFuncAddress("glSamplerParameteri"));
      oglSamplerParameteriv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, const GLint *)>(GetAnyGLFuncAddress("glSamplerParameteriv"));
      oglVertexAttribDivisor = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glVertexAttribDivisor"));
      oglVertexAttribP1ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLboolean, GLuint)>(GetAnyGLFuncAddress("glVertexAttribP1ui"));
      oglVertexAttribP1uiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLboolean, const GLuint *)>(GetAnyGLFuncAddress("glVertexAttribP1uiv"));
      oglVertexAttribP2ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLboolean, GLuint)>(GetAnyGLFuncAddress("glVertexAttribP2ui"));
      oglVertexAttribP2uiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLboolean, const GLuint *)>(GetAnyGLFuncAddress("glVertexAttribP2uiv"));
      oglVertexAttribP3ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLboolean, GLuint)>(GetAnyGLFuncAddress("glVertexAttribP3ui"));
      oglVertexAttribP3uiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLboolean, const GLuint *)>(GetAnyGLFuncAddress("glVertexAttribP3uiv"));
      oglVertexAttribP4ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLboolean, GLuint)>(GetAnyGLFuncAddress("glVertexAttribP4ui"));
      oglVertexAttribP4uiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLboolean, const GLuint *)>(GetAnyGLFuncAddress("glVertexAttribP4uiv"));

      /* GL_VERSION_4_0 */
      oglBeginQueryIndexed = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLuint)>(GetAnyGLFuncAddress("glBeginQueryIndexed"));
      oglBindTransformFeedback = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glBindTransformFeedback"));
      oglBlendEquationSeparatei = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLenum)>(GetAnyGLFuncAddress("glBlendEquationSeparatei"));
      oglBlendEquationi = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum)>(GetAnyGLFuncAddress("glBlendEquationi"));
      oglBlendFuncSeparatei = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLenum, GLenum, GLenum)>(GetAnyGLFuncAddress("glBlendFuncSeparatei"));
      oglBlendFunci = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLenum)>(GetAnyGLFuncAddress("glBlendFunci"));
      oglDeleteTransformFeedbacks = reinterpret_cast<void(APIENTRY*)(GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glDeleteTransformFeedbacks"));
      oglDrawArraysIndirect = reinterpret_cast<void(APIENTRY*)(GLenum, const void *)>(GetAnyGLFuncAddress("glDrawArraysIndirect"));
      oglDrawElementsIndirect = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glDrawElementsIndirect"));
      oglDrawTransformFeedback = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glDrawTransformFeedback"));
      oglDrawTransformFeedbackStream = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLuint)>(GetAnyGLFuncAddress("glDrawTransformFeedbackStream"));
      oglEndQueryIndexed = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint)>(GetAnyGLFuncAddress("glEndQueryIndexed"));
      oglGenTransformFeedbacks = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glGenTransformFeedbacks"));
      oglGetActiveSubroutineName = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetActiveSubroutineName"));
      oglGetActiveSubroutineUniformName = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetActiveSubroutineUniformName"));
      oglGetActiveSubroutineUniformiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetActiveSubroutineUniformiv"));
      oglGetProgramStageiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetProgramStageiv"));
      oglGetQueryIndexediv = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetQueryIndexediv"));
      oglGetSubroutineIndex = reinterpret_cast<GLuint(APIENTRY*)(GLuint, GLenum, const GLchar *)>(GetAnyGLFuncAddress("glGetSubroutineIndex"));
      oglGetSubroutineUniformLocation = reinterpret_cast<GLint(APIENTRY*)(GLuint, GLenum, const GLchar *)>(GetAnyGLFuncAddress("glGetSubroutineUniformLocation"));
      oglGetUniformSubroutineuiv = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLuint *)>(GetAnyGLFuncAddress("glGetUniformSubroutineuiv"));
      oglGetUniformdv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLdouble *)>(GetAnyGLFuncAddress("glGetUniformdv"));
      oglIsTransformFeedback = reinterpret_cast<GLboolean(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glIsTransformFeedback"));
      oglMinSampleShading = reinterpret_cast<void(APIENTRY*)(GLfloat)>(GetAnyGLFuncAddress("glMinSampleShading"));
      oglPatchParameterfv = reinterpret_cast<void(APIENTRY*)(GLenum, const GLfloat *)>(GetAnyGLFuncAddress("glPatchParameterfv"));
      oglPatchParameteri = reinterpret_cast<void(APIENTRY*)(GLenum, GLint)>(GetAnyGLFuncAddress("glPatchParameteri"));
      oglPauseTransformFeedback = reinterpret_cast<void(APIENTRY*)(void)>(GetAnyGLFuncAddress("glPauseTransformFeedback"));
      oglResumeTransformFeedback = reinterpret_cast<void(APIENTRY*)(void)>(GetAnyGLFuncAddress("glResumeTransformFeedback"));
      oglUniform1d = reinterpret_cast<void(APIENTRY*)(GLint, GLdouble)>(GetAnyGLFuncAddress("glUniform1d"));
      oglUniform1dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLdouble *)>(GetAnyGLFuncAddress("glUniform1dv"));
      oglUniform2d = reinterpret_cast<void(APIENTRY*)(GLint, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glUniform2d"));
      oglUniform2dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLdouble *)>(GetAnyGLFuncAddress("glUniform2dv"));
      oglUniform3d = reinterpret_cast<void(APIENTRY*)(GLint, GLdouble, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glUniform3d"));
      oglUniform3dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLdouble *)>(GetAnyGLFuncAddress("glUniform3dv"));
      oglUniform4d = reinterpret_cast<void(APIENTRY*)(GLint, GLdouble, GLdouble, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glUniform4d"));
      oglUniform4dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, const GLdouble *)>(GetAnyGLFuncAddress("glUniform4dv"));
      oglUniformMatrix2dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glUniformMatrix2dv"));
      oglUniformMatrix2x3dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glUniformMatrix2x3dv"));
      oglUniformMatrix2x4dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glUniformMatrix2x4dv"));
      oglUniformMatrix3dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glUniformMatrix3dv"));
      oglUniformMatrix3x2dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glUniformMatrix3x2dv"));
      oglUniformMatrix3x4dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glUniformMatrix3x4dv"));
      oglUniformMatrix4dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glUniformMatrix4dv"));
      oglUniformMatrix4x2dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glUniformMatrix4x2dv"));
      oglUniformMatrix4x3dv = reinterpret_cast<void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glUniformMatrix4x3dv"));
      oglUniformSubroutinesuiv = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glUniformSubroutinesuiv"));

      /* GL_VERSION_4_1 */
      oglActiveShaderProgram = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glActiveShaderProgram"));
      oglBindProgramPipeline = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glBindProgramPipeline"));
      oglClearDepthf = reinterpret_cast<void(APIENTRY*)(GLfloat)>(GetAnyGLFuncAddress("glClearDepthf"));
      oglCreateShaderProgramv = reinterpret_cast<GLuint(APIENTRY*)(GLenum, GLsizei, const GLchar *const*)>(GetAnyGLFuncAddress("glCreateShaderProgramv"));
      oglDeleteProgramPipelines = reinterpret_cast<void(APIENTRY*)(GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glDeleteProgramPipelines"));
      oglDepthRangeArrayv = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLdouble *)>(GetAnyGLFuncAddress("glDepthRangeArrayv"));
      oglDepthRangeIndexed = reinterpret_cast<void(APIENTRY*)(GLuint, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glDepthRangeIndexed"));
      oglDepthRangef = reinterpret_cast<void(APIENTRY*)(GLfloat, GLfloat)>(GetAnyGLFuncAddress("glDepthRangef"));
      oglGenProgramPipelines = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glGenProgramPipelines"));
      oglGetDoublei_v = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLdouble *)>(GetAnyGLFuncAddress("glGetDoublei_v"));
      oglGetFloati_v = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLfloat *)>(GetAnyGLFuncAddress("glGetFloati_v"));
      oglGetProgramBinary = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLsizei *, GLenum *, void *)>(GetAnyGLFuncAddress("glGetProgramBinary"));
      oglGetProgramPipelineInfoLog = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetProgramPipelineInfoLog"));
      oglGetProgramPipelineiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetProgramPipelineiv"));
      oglGetShaderPrecisionFormat = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLint *, GLint *)>(GetAnyGLFuncAddress("glGetShaderPrecisionFormat"));
      oglGetVertexAttribLdv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLdouble *)>(GetAnyGLFuncAddress("glGetVertexAttribLdv"));
      oglIsProgramPipeline = reinterpret_cast<GLboolean(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glIsProgramPipeline"));
      oglProgramBinary = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, const void *, GLsizei)>(GetAnyGLFuncAddress("glProgramBinary"));
      oglProgramParameteri = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint)>(GetAnyGLFuncAddress("glProgramParameteri"));
      oglProgramUniform1d = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLdouble)>(GetAnyGLFuncAddress("glProgramUniform1d"));
      oglProgramUniform1dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniform1dv"));
      oglProgramUniform1f = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLfloat)>(GetAnyGLFuncAddress("glProgramUniform1f"));
      oglProgramUniform1fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniform1fv"));
      oglProgramUniform1i = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint)>(GetAnyGLFuncAddress("glProgramUniform1i"));
      oglProgramUniform1iv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLint *)>(GetAnyGLFuncAddress("glProgramUniform1iv"));
      oglProgramUniform1ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLuint)>(GetAnyGLFuncAddress("glProgramUniform1ui"));
      oglProgramUniform1uiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glProgramUniform1uiv"));
      oglProgramUniform2d = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glProgramUniform2d"));
      oglProgramUniform2dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniform2dv"));
      oglProgramUniform2f = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLfloat, GLfloat)>(GetAnyGLFuncAddress("glProgramUniform2f"));
      oglProgramUniform2fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniform2fv"));
      oglProgramUniform2i = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint)>(GetAnyGLFuncAddress("glProgramUniform2i"));
      oglProgramUniform2iv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLint *)>(GetAnyGLFuncAddress("glProgramUniform2iv"));
      oglProgramUniform2ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLuint, GLuint)>(GetAnyGLFuncAddress("glProgramUniform2ui"));
      oglProgramUniform2uiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glProgramUniform2uiv"));
      oglProgramUniform3d = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLdouble, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glProgramUniform3d"));
      oglProgramUniform3dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniform3dv"));
      oglProgramUniform3f = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLfloat, GLfloat, GLfloat)>(GetAnyGLFuncAddress("glProgramUniform3f"));
      oglProgramUniform3fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniform3fv"));
      oglProgramUniform3i = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint)>(GetAnyGLFuncAddress("glProgramUniform3i"));
      oglProgramUniform3iv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLint *)>(GetAnyGLFuncAddress("glProgramUniform3iv"));
      oglProgramUniform3ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glProgramUniform3ui"));
      oglProgramUniform3uiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glProgramUniform3uiv"));
      oglProgramUniform4d = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glProgramUniform4d"));
      oglProgramUniform4dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniform4dv"));
      oglProgramUniform4f = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat)>(GetAnyGLFuncAddress("glProgramUniform4f"));
      oglProgramUniform4fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniform4fv"));
      oglProgramUniform4i = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint, GLint)>(GetAnyGLFuncAddress("glProgramUniform4i"));
      oglProgramUniform4iv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLint *)>(GetAnyGLFuncAddress("glProgramUniform4iv"));
      oglProgramUniform4ui = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glProgramUniform4ui"));
      oglProgramUniform4uiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glProgramUniform4uiv"));
      oglProgramUniformMatrix2dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniformMatrix2dv"));
      oglProgramUniformMatrix2fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniformMatrix2fv"));
      oglProgramUniformMatrix2x3dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniformMatrix2x3dv"));
      oglProgramUniformMatrix2x3fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniformMatrix2x3fv"));
      oglProgramUniformMatrix2x4dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniformMatrix2x4dv"));
      oglProgramUniformMatrix2x4fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniformMatrix2x4fv"));
      oglProgramUniformMatrix3dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniformMatrix3dv"));
      oglProgramUniformMatrix3fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniformMatrix3fv"));
      oglProgramUniformMatrix3x2dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniformMatrix3x2dv"));
      oglProgramUniformMatrix3x2fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniformMatrix3x2fv"));
      oglProgramUniformMatrix3x4dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniformMatrix3x4dv"));
      oglProgramUniformMatrix3x4fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniformMatrix3x4fv"));
      oglProgramUniformMatrix4dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniformMatrix4dv"));
      oglProgramUniformMatrix4fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniformMatrix4fv"));
      oglProgramUniformMatrix4x2dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniformMatrix4x2dv"));
      oglProgramUniformMatrix4x2fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniformMatrix4x2fv"));
      oglProgramUniformMatrix4x3dv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *)>(GetAnyGLFuncAddress("glProgramUniformMatrix4x3dv"));
      oglProgramUniformMatrix4x3fv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *)>(GetAnyGLFuncAddress("glProgramUniformMatrix4x3fv"));
      oglReleaseShaderCompiler = reinterpret_cast<void(APIENTRY*)(void)>(GetAnyGLFuncAddress("glReleaseShaderCompiler"));
      oglScissorArrayv = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLint *)>(GetAnyGLFuncAddress("glScissorArrayv"));
      oglScissorIndexed = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glScissorIndexed"));
      oglScissorIndexedv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLint *)>(GetAnyGLFuncAddress("glScissorIndexedv"));
      oglShaderBinary = reinterpret_cast<void(APIENTRY*)(GLsizei, const GLuint *, GLenum, const void *, GLsizei)>(GetAnyGLFuncAddress("glShaderBinary"));
      oglUseProgramStages = reinterpret_cast<void(APIENTRY*)(GLuint, GLbitfield, GLuint)>(GetAnyGLFuncAddress("glUseProgramStages"));
      oglValidateProgramPipeline = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glValidateProgramPipeline"));
      oglVertexAttribL1d = reinterpret_cast<void(APIENTRY*)(GLuint, GLdouble)>(GetAnyGLFuncAddress("glVertexAttribL1d"));
      oglVertexAttribL1dv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLdouble *)>(GetAnyGLFuncAddress("glVertexAttribL1dv"));
      oglVertexAttribL2d = reinterpret_cast<void(APIENTRY*)(GLuint, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glVertexAttribL2d"));
      oglVertexAttribL2dv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLdouble *)>(GetAnyGLFuncAddress("glVertexAttribL2dv"));
      oglVertexAttribL3d = reinterpret_cast<void(APIENTRY*)(GLuint, GLdouble, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glVertexAttribL3d"));
      oglVertexAttribL3dv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLdouble *)>(GetAnyGLFuncAddress("glVertexAttribL3dv"));
      oglVertexAttribL4d = reinterpret_cast<void(APIENTRY*)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble)>(GetAnyGLFuncAddress("glVertexAttribL4d"));
      oglVertexAttribL4dv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLdouble *)>(GetAnyGLFuncAddress("glVertexAttribL4dv"));
      oglVertexAttribLPointer = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLenum, GLsizei, const void *)>(GetAnyGLFuncAddress("glVertexAttribLPointer"));
      oglViewportArrayv = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLfloat *)>(GetAnyGLFuncAddress("glViewportArrayv"));
      oglViewportIndexedf = reinterpret_cast<void(APIENTRY*)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat)>(GetAnyGLFuncAddress("glViewportIndexedf"));
      oglViewportIndexedfv = reinterpret_cast<void(APIENTRY*)(GLuint, const GLfloat *)>(GetAnyGLFuncAddress("glViewportIndexedfv"));

      /* GL_VERSION_4_2 */
      oglBindImageTexture = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum)>(GetAnyGLFuncAddress("glBindImageTexture"));
      oglDrawArraysInstancedBaseInstance = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLsizei, GLsizei, GLuint)>(GetAnyGLFuncAddress("glDrawArraysInstancedBaseInstance"));
      oglDrawElementsInstancedBaseInstance = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint)>(GetAnyGLFuncAddress("glDrawElementsInstancedBaseInstance"));
      oglDrawElementsInstancedBaseVertexBaseInstance = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint)>(GetAnyGLFuncAddress("glDrawElementsInstancedBaseVertexBaseInstance"));
      oglDrawTransformFeedbackInstanced = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLsizei)>(GetAnyGLFuncAddress("glDrawTransformFeedbackInstanced"));
      oglDrawTransformFeedbackStreamInstanced = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLuint, GLsizei)>(GetAnyGLFuncAddress("glDrawTransformFeedbackStreamInstanced"));
      oglGetActiveAtomicCounterBufferiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetActiveAtomicCounterBufferiv"));
      oglGetInternalformativ = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLenum, GLsizei, GLint *)>(GetAnyGLFuncAddress("glGetInternalformativ"));
      oglMemoryBarrier = reinterpret_cast<void(APIENTRY*)(GLbitfield)>(GetAnyGLFuncAddress("glMemoryBarrier"));
      oglTexStorage1D = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, GLsizei)>(GetAnyGLFuncAddress("glTexStorage1D"));
      oglTexStorage2D = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glTexStorage2D"));
      oglTexStorage3D = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glTexStorage3D"));

      /* GL_VERSION_4_3 */
      oglBindVertexBuffer = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLintptr, GLsizei)>(GetAnyGLFuncAddress("glBindVertexBuffer"));
      oglClearBufferData = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glClearBufferData"));
      oglClearBufferSubData = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glClearBufferSubData"));
      oglCopyImageSubData = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glCopyImageSubData"));
      oglDebugMessageCallback = reinterpret_cast<void(APIENTRY*)(GLDEBUGPROC, const void *)>(GetAnyGLFuncAddress("glDebugMessageCallback"));
      oglDebugMessageControl = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean)>(GetAnyGLFuncAddress("glDebugMessageControl"));
      oglDebugMessageInsert = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *)>(GetAnyGLFuncAddress("glDebugMessageInsert"));
      oglDispatchCompute = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glDispatchCompute"));
      oglDispatchComputeIndirect = reinterpret_cast<void(APIENTRY*)(GLintptr)>(GetAnyGLFuncAddress("glDispatchComputeIndirect"));
      oglFramebufferParameteri = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLint)>(GetAnyGLFuncAddress("glFramebufferParameteri"));
      oglGetDebugMessageLog = reinterpret_cast<GLuint(APIENTRY*)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetDebugMessageLog"));
      oglGetFramebufferParameteriv = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetFramebufferParameteriv"));
      oglGetInternalformati64v = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLenum, GLsizei, GLint64 *)>(GetAnyGLFuncAddress("glGetInternalformati64v"));
      oglGetObjectLabel = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetObjectLabel"));
      oglGetObjectPtrLabel = reinterpret_cast<void(APIENTRY*)(const void *, GLsizei, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetObjectPtrLabel"));
      oglGetPointerv = reinterpret_cast<void(APIENTRY*)(GLenum, void **)>(GetAnyGLFuncAddress("glGetPointerv"));
      oglGetProgramInterfaceiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetProgramInterfaceiv"));
      oglGetProgramResourceIndex = reinterpret_cast<GLuint(APIENTRY*)(GLuint, GLenum, const GLchar *)>(GetAnyGLFuncAddress("glGetProgramResourceIndex"));
      oglGetProgramResourceLocation = reinterpret_cast<GLint(APIENTRY*)(GLuint, GLenum, const GLchar *)>(GetAnyGLFuncAddress("glGetProgramResourceLocation"));
      oglGetProgramResourceLocationIndex = reinterpret_cast<GLint(APIENTRY*)(GLuint, GLenum, const GLchar *)>(GetAnyGLFuncAddress("glGetProgramResourceLocationIndex"));
      oglGetProgramResourceName = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *)>(GetAnyGLFuncAddress("glGetProgramResourceName"));
      oglGetProgramResourceiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *)>(GetAnyGLFuncAddress("glGetProgramResourceiv"));
      oglInvalidateBufferData = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glInvalidateBufferData"));
      oglInvalidateBufferSubData = reinterpret_cast<void(APIENTRY*)(GLuint, GLintptr, GLsizeiptr)>(GetAnyGLFuncAddress("glInvalidateBufferSubData"));
      oglInvalidateFramebuffer = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, const GLenum *)>(GetAnyGLFuncAddress("glInvalidateFramebuffer"));
      oglInvalidateSubFramebuffer = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glInvalidateSubFramebuffer"));
      oglInvalidateTexImage = reinterpret_cast<void(APIENTRY*)(GLuint, GLint)>(GetAnyGLFuncAddress("glInvalidateTexImage"));
      oglInvalidateTexSubImage = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glInvalidateTexSubImage"));
      oglMultiDrawArraysIndirect = reinterpret_cast<void(APIENTRY*)(GLenum, const void *, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glMultiDrawArraysIndirect"));
      oglMultiDrawElementsIndirect = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, const void *, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glMultiDrawElementsIndirect"));
      oglObjectLabel = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLsizei, const GLchar *)>(GetAnyGLFuncAddress("glObjectLabel"));
      oglObjectPtrLabel = reinterpret_cast<void(APIENTRY*)(const void *, GLsizei, const GLchar *)>(GetAnyGLFuncAddress("glObjectPtrLabel"));
      oglPopDebugGroup = reinterpret_cast<void(APIENTRY*)(void)>(GetAnyGLFuncAddress("glPopDebugGroup"));
      oglPushDebugGroup = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLsizei, const GLchar *)>(GetAnyGLFuncAddress("glPushDebugGroup"));
      oglShaderStorageBlockBinding = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glShaderStorageBlockBinding"));
      oglTexBufferRange = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr)>(GetAnyGLFuncAddress("glTexBufferRange"));
      oglTexStorage2DMultisample = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean)>(GetAnyGLFuncAddress("glTexStorage2DMultisample"));
      oglTexStorage3DMultisample = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean)>(GetAnyGLFuncAddress("glTexStorage3DMultisample"));
      oglTextureView = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glTextureView"));
      oglVertexAttribBinding = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glVertexAttribBinding"));
      oglVertexAttribFormat = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLenum, GLboolean, GLuint)>(GetAnyGLFuncAddress("glVertexAttribFormat"));
      oglVertexAttribIFormat = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLenum, GLuint)>(GetAnyGLFuncAddress("glVertexAttribIFormat"));
      oglVertexAttribLFormat = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLenum, GLuint)>(GetAnyGLFuncAddress("glVertexAttribLFormat"));
      oglVertexBindingDivisor = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glVertexBindingDivisor"));

      /* GL_VERSION_4_4 */
      oglBindBuffersBase = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glBindBuffersBase"));
      oglBindBuffersRange = reinterpret_cast<void(APIENTRY*)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *)>(GetAnyGLFuncAddress("glBindBuffersRange"));
      oglBindImageTextures = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glBindImageTextures"));
      oglBindSamplers = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glBindSamplers"));
      oglBindTextures = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLuint *)>(GetAnyGLFuncAddress("glBindTextures"));
      oglBindVertexBuffers = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *)>(GetAnyGLFuncAddress("glBindVertexBuffers"));
      oglBufferStorage = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizeiptr, const void *, GLbitfield)>(GetAnyGLFuncAddress("glBufferStorage"));
      oglClearTexImage = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glClearTexImage"));
      oglClearTexSubImage = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glClearTexSubImage"));

      /* GL_VERSION_4_5 */
      oglBindTextureUnit = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glBindTextureUnit"));
      oglBlitNamedFramebuffer = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum)>(GetAnyGLFuncAddress("glBlitNamedFramebuffer"));
      oglCheckNamedFramebufferStatus = reinterpret_cast<GLenum(APIENTRY*)(GLuint, GLenum)>(GetAnyGLFuncAddress("glCheckNamedFramebufferStatus"));
      oglClearNamedBufferData = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glClearNamedBufferData"));
      oglClearNamedBufferSubData = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glClearNamedBufferSubData"));
      oglClearNamedFramebufferfi = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, const GLfloat, GLint)>(GetAnyGLFuncAddress("glClearNamedFramebufferfi"));
      oglClearNamedFramebufferfv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint, const GLfloat *)>(GetAnyGLFuncAddress("glClearNamedFramebufferfv"));
      oglClearNamedFramebufferiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint, const GLint *)>(GetAnyGLFuncAddress("glClearNamedFramebufferiv"));
      oglClearNamedFramebufferuiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint, const GLuint *)>(GetAnyGLFuncAddress("glClearNamedFramebufferuiv"));
      oglClipControl = reinterpret_cast<void(APIENTRY*)(GLenum, GLenum)>(GetAnyGLFuncAddress("glClipControl"));
      oglCompressedTextureSubImage1D = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *)>(GetAnyGLFuncAddress("glCompressedTextureSubImage1D"));
      oglCompressedTextureSubImage2D = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *)>(GetAnyGLFuncAddress("glCompressedTextureSubImage2D"));
      oglCompressedTextureSubImage3D = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *)>(GetAnyGLFuncAddress("glCompressedTextureSubImage3D"));
      oglCopyNamedBufferSubData = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr)>(GetAnyGLFuncAddress("glCopyNamedBufferSubData"));
      oglCopyTextureSubImage1D = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint, GLsizei)>(GetAnyGLFuncAddress("glCopyTextureSubImage1D"));
      oglCopyTextureSubImage2D = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glCopyTextureSubImage2D"));
      oglCopyTextureSubImage3D = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glCopyTextureSubImage3D"));
      oglCreateBuffers = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glCreateBuffers"));
      oglCreateFramebuffers = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glCreateFramebuffers"));
      oglCreateProgramPipelines = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glCreateProgramPipelines"));
      oglCreateQueries = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLuint *)>(GetAnyGLFuncAddress("glCreateQueries"));
      oglCreateRenderbuffers = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glCreateRenderbuffers"));
      oglCreateSamplers = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glCreateSamplers"));
      oglCreateTextures = reinterpret_cast<void(APIENTRY*)(GLenum, GLsizei, GLuint *)>(GetAnyGLFuncAddress("glCreateTextures"));
      oglCreateTransformFeedbacks = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glCreateTransformFeedbacks"));
      oglCreateVertexArrays = reinterpret_cast<void(APIENTRY*)(GLsizei, GLuint *)>(GetAnyGLFuncAddress("glCreateVertexArrays"));
      oglDisableVertexArrayAttrib = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glDisableVertexArrayAttrib"));
      oglEnableVertexArrayAttrib = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glEnableVertexArrayAttrib"));
      oglFlushMappedNamedBufferRange = reinterpret_cast<void(APIENTRY*)(GLuint, GLintptr, GLsizeiptr)>(GetAnyGLFuncAddress("glFlushMappedNamedBufferRange"));
      oglGenerateTextureMipmap = reinterpret_cast<void(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glGenerateTextureMipmap"));
      oglGetCompressedTextureImage = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, void *)>(GetAnyGLFuncAddress("glGetCompressedTextureImage"));
      oglGetCompressedTextureSubImage = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *)>(GetAnyGLFuncAddress("glGetCompressedTextureSubImage"));
      oglGetGraphicsResetStatus = reinterpret_cast<GLenum(APIENTRY*)(void)>(GetAnyGLFuncAddress("glGetGraphicsResetStatus"));
      oglGetNamedBufferParameteri64v = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint64 *)>(GetAnyGLFuncAddress("glGetNamedBufferParameteri64v"));
      oglGetNamedBufferParameteriv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetNamedBufferParameteriv"));
      oglGetNamedBufferPointerv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, void **)>(GetAnyGLFuncAddress("glGetNamedBufferPointerv"));
      oglGetNamedBufferSubData = reinterpret_cast<void(APIENTRY*)(GLuint, GLintptr, GLsizeiptr, void *)>(GetAnyGLFuncAddress("glGetNamedBufferSubData"));
      oglGetNamedFramebufferAttachmentParameteriv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetNamedFramebufferAttachmentParameteriv"));
      oglGetNamedFramebufferParameteriv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetNamedFramebufferParameteriv"));
      oglGetNamedRenderbufferParameteriv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetNamedRenderbufferParameteriv"));
      oglGetQueryBufferObjecti64v = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLenum, GLintptr)>(GetAnyGLFuncAddress("glGetQueryBufferObjecti64v"));
      oglGetQueryBufferObjectiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLenum, GLintptr)>(GetAnyGLFuncAddress("glGetQueryBufferObjectiv"));
      oglGetQueryBufferObjectui64v = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLenum, GLintptr)>(GetAnyGLFuncAddress("glGetQueryBufferObjectui64v"));
      oglGetQueryBufferObjectuiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLenum, GLintptr)>(GetAnyGLFuncAddress("glGetQueryBufferObjectuiv"));
      oglGetTextureImage = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLenum, GLenum, GLsizei, void *)>(GetAnyGLFuncAddress("glGetTextureImage"));
      oglGetTextureLevelParameterfv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLenum, GLfloat *)>(GetAnyGLFuncAddress("glGetTextureLevelParameterfv"));
      oglGetTextureLevelParameteriv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetTextureLevelParameteriv"));
      oglGetTextureParameterIiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetTextureParameterIiv"));
      oglGetTextureParameterIuiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint *)>(GetAnyGLFuncAddress("glGetTextureParameterIuiv"));
      oglGetTextureParameterfv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLfloat *)>(GetAnyGLFuncAddress("glGetTextureParameterfv"));
      oglGetTextureParameteriv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetTextureParameteriv"));
      oglGetTextureSubImage = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *)>(GetAnyGLFuncAddress("glGetTextureSubImage"));
      oglGetTransformFeedbacki64_v = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint, GLint64 *)>(GetAnyGLFuncAddress("glGetTransformFeedbacki64_v"));
      oglGetTransformFeedbacki_v = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint, GLint *)>(GetAnyGLFuncAddress("glGetTransformFeedbacki_v"));
      oglGetTransformFeedbackiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetTransformFeedbackiv"));
      oglGetVertexArrayIndexed64iv = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLenum, GLint64 *)>(GetAnyGLFuncAddress("glGetVertexArrayIndexed64iv"));
      oglGetVertexArrayIndexediv = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetVertexArrayIndexediv"));
      oglGetVertexArrayiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint *)>(GetAnyGLFuncAddress("glGetVertexArrayiv"));
      oglGetnCompressedTexImage = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLsizei, void *)>(GetAnyGLFuncAddress("glGetnCompressedTexImage"));
      oglGetnTexImage = reinterpret_cast<void(APIENTRY*)(GLenum, GLint, GLenum, GLenum, GLsizei, void *)>(GetAnyGLFuncAddress("glGetnTexImage"));
      oglGetnUniformdv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLdouble *)>(GetAnyGLFuncAddress("glGetnUniformdv"));
      oglGetnUniformfv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLfloat *)>(GetAnyGLFuncAddress("glGetnUniformfv"));
      oglGetnUniformiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLint *)>(GetAnyGLFuncAddress("glGetnUniformiv"));
      oglGetnUniformuiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLsizei, GLuint *)>(GetAnyGLFuncAddress("glGetnUniformuiv"));
      oglInvalidateNamedFramebufferData = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLenum *)>(GetAnyGLFuncAddress("glInvalidateNamedFramebufferData"));
      oglInvalidateNamedFramebufferSubData = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glInvalidateNamedFramebufferSubData"));
      oglMapNamedBuffer = reinterpret_cast<void *(APIENTRY*)(GLuint, GLenum)>(GetAnyGLFuncAddress("glMapNamedBuffer"));
      oglMapNamedBufferRange = reinterpret_cast<void *(APIENTRY*)(GLuint, GLintptr, GLsizeiptr, GLbitfield)>(GetAnyGLFuncAddress("glMapNamedBufferRange"));
      oglMemoryBarrierByRegion = reinterpret_cast<void(APIENTRY*)(GLbitfield)>(GetAnyGLFuncAddress("glMemoryBarrierByRegion"));
      oglNamedBufferData = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizeiptr, const void *, GLenum)>(GetAnyGLFuncAddress("glNamedBufferData"));
      oglNamedBufferStorage = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizeiptr, const void *, GLbitfield)>(GetAnyGLFuncAddress("glNamedBufferStorage"));
      oglNamedBufferSubData = reinterpret_cast<void(APIENTRY*)(GLuint, GLintptr, GLsizeiptr, const void *)>(GetAnyGLFuncAddress("glNamedBufferSubData"));
      oglNamedFramebufferDrawBuffer = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum)>(GetAnyGLFuncAddress("glNamedFramebufferDrawBuffer"));
      oglNamedFramebufferDrawBuffers = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, const GLenum *)>(GetAnyGLFuncAddress("glNamedFramebufferDrawBuffers"));
      oglNamedFramebufferParameteri = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint)>(GetAnyGLFuncAddress("glNamedFramebufferParameteri"));
      oglNamedFramebufferReadBuffer = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum)>(GetAnyGLFuncAddress("glNamedFramebufferReadBuffer"));
      oglNamedFramebufferRenderbuffer = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLenum, GLuint)>(GetAnyGLFuncAddress("glNamedFramebufferRenderbuffer"));
      oglNamedFramebufferTexture = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint, GLint)>(GetAnyGLFuncAddress("glNamedFramebufferTexture"));
      oglNamedFramebufferTextureLayer = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint, GLint, GLint)>(GetAnyGLFuncAddress("glNamedFramebufferTextureLayer"));
      oglNamedRenderbufferStorage = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glNamedRenderbufferStorage"));
      oglNamedRenderbufferStorageMultisample = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glNamedRenderbufferStorageMultisample"));
      oglReadnPixels = reinterpret_cast<void(APIENTRY*)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *)>(GetAnyGLFuncAddress("glReadnPixels"));
      oglTextureBarrier = reinterpret_cast<void(APIENTRY*)(void)>(GetAnyGLFuncAddress("glTextureBarrier"));
      oglTextureBuffer = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint)>(GetAnyGLFuncAddress("glTextureBuffer"));
      oglTextureBufferRange = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLuint, GLintptr, GLsizeiptr)>(GetAnyGLFuncAddress("glTextureBufferRange"));
      oglTextureParameterIiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, const GLint *)>(GetAnyGLFuncAddress("glTextureParameterIiv"));
      oglTextureParameterIuiv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, const GLuint *)>(GetAnyGLFuncAddress("glTextureParameterIuiv"));
      oglTextureParameterf = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLfloat)>(GetAnyGLFuncAddress("glTextureParameterf"));
      oglTextureParameterfv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, const GLfloat *)>(GetAnyGLFuncAddress("glTextureParameterfv"));
      oglTextureParameteri = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, GLint)>(GetAnyGLFuncAddress("glTextureParameteri"));
      oglTextureParameteriv = reinterpret_cast<void(APIENTRY*)(GLuint, GLenum, const GLint *)>(GetAnyGLFuncAddress("glTextureParameteriv"));
      oglTextureStorage1D = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLenum, GLsizei)>(GetAnyGLFuncAddress("glTextureStorage1D"));
      oglTextureStorage2D = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glTextureStorage2D"));
      oglTextureStorage2DMultisample = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean)>(GetAnyGLFuncAddress("glTextureStorage2DMultisample"));
      oglTextureStorage3D = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei)>(GetAnyGLFuncAddress("glTextureStorage3D"));
      oglTextureStorage3DMultisample = reinterpret_cast<void(APIENTRY*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean)>(GetAnyGLFuncAddress("glTextureStorage3DMultisample"));
      oglTextureSubImage1D = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glTextureSubImage1D"));
      oglTextureSubImage2D = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glTextureSubImage2D"));
      oglTextureSubImage3D = reinterpret_cast<void(APIENTRY*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *)>(GetAnyGLFuncAddress("glTextureSubImage3D"));
      oglTransformFeedbackBufferBase = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glTransformFeedbackBufferBase"));
      oglTransformFeedbackBufferRange = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint, GLintptr, GLsizeiptr)>(GetAnyGLFuncAddress("glTransformFeedbackBufferRange"));
      oglUnmapNamedBuffer = reinterpret_cast<GLboolean(APIENTRY*)(GLuint)>(GetAnyGLFuncAddress("glUnmapNamedBuffer"));
      oglVertexArrayAttribBinding = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glVertexArrayAttribBinding"));
      oglVertexArrayAttribFormat = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint)>(GetAnyGLFuncAddress("glVertexArrayAttribFormat"));
      oglVertexArrayAttribIFormat = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLint, GLenum, GLuint)>(GetAnyGLFuncAddress("glVertexArrayAttribIFormat"));
      oglVertexArrayAttribLFormat = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLint, GLenum, GLuint)>(GetAnyGLFuncAddress("glVertexArrayAttribLFormat"));
      oglVertexArrayBindingDivisor = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint)>(GetAnyGLFuncAddress("glVertexArrayBindingDivisor"));
      oglVertexArrayElementBuffer = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint)>(GetAnyGLFuncAddress("glVertexArrayElementBuffer"));
      oglVertexArrayVertexBuffer = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLuint, GLintptr, GLsizei)>(GetAnyGLFuncAddress("glVertexArrayVertexBuffer"));
      oglVertexArrayVertexBuffers = reinterpret_cast<void(APIENTRY*)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *)>(GetAnyGLFuncAddress("glVertexArrayVertexBuffers"));
    }

    void CheckOGLError(const char* aErrorMsg, ...)
    {
#define CASE_OGL_ERROR( enum ) case enum: lErrorStr = #enum; break;
        GLenum lError = glGetError();

        std::string lErrorStr = "GL_UNKNOWN_ERROR";

        if(lError != GL_NO_ERROR)
        {
            switch (lError)
            {
                    CASE_OGL_ERROR(GL_INVALID_ENUM)
                    CASE_OGL_ERROR(GL_INVALID_VALUE)
                    CASE_OGL_ERROR(GL_INVALID_OPERATION)
                    CASE_OGL_ERROR(GL_STACK_OVERFLOW)
                    CASE_OGL_ERROR(GL_STACK_UNDERFLOW)
                    CASE_OGL_ERROR(GL_OUT_OF_MEMORY)
                    CASE_OGL_ERROR(GL_INVALID_FRAMEBUFFER_OPERATION)
                    CASE_OGL_ERROR(GL_CONTEXT_LOST)

                default:
                    break;
            }

            va_list args;
            va_start(args, aErrorMsg);
            int len = _vscprintf(aErrorMsg, args) + 1;
            char* buffer = (char*)malloc(len * sizeof(char));
            vsprintf_s(buffer, len, aErrorMsg, args);
            IRIS_LOG_ERROR( (lErrorStr + ": " + buffer).c_str() )
            free(buffer);
            va_end(args);
        }

#undef CASE_OGL_ERROR
    }


    /* GL_VERSION_1_2 */
     void(APIENTRY *oglCopyTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglDrawRangeElements)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *) = nullptr;
     void(APIENTRY *oglTexImage3D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) = nullptr;
     void(APIENTRY *oglTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) = nullptr;

    /* GL_VERSION_1_3 */
     void(APIENTRY *oglActiveTexture)(GLenum) = nullptr;
     void(APIENTRY *oglCompressedTexImage1D)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *) = nullptr;
     void(APIENTRY *oglCompressedTexImage2D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *) = nullptr;
     void(APIENTRY *oglCompressedTexImage3D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *) = nullptr;
     void(APIENTRY *oglCompressedTexSubImage1D)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) = nullptr;
     void(APIENTRY *oglCompressedTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) = nullptr;
     void(APIENTRY *oglCompressedTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) = nullptr;
     void(APIENTRY *oglGetCompressedTexImage)(GLenum, GLint, void *) = nullptr;
     void(APIENTRY *oglSampleCoverage)(GLfloat, GLboolean) = nullptr;

    /* GL_VERSION_1_4 */
     void(APIENTRY *oglBlendColor)(GLfloat, GLfloat, GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglBlendEquation)(GLenum) = nullptr;
     void(APIENTRY *oglBlendFuncSeparate)(GLenum, GLenum, GLenum, GLenum) = nullptr;
     void(APIENTRY *oglMultiDrawArrays)(GLenum, const GLint *, const GLsizei *, GLsizei) = nullptr;
     void(APIENTRY *oglMultiDrawElements)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei) = nullptr;
     void(APIENTRY *oglPointParameterf)(GLenum, GLfloat) = nullptr;
     void(APIENTRY *oglPointParameterfv)(GLenum, const GLfloat *) = nullptr;
     void(APIENTRY *oglPointParameteri)(GLenum, GLint) = nullptr;
     void(APIENTRY *oglPointParameteriv)(GLenum, const GLint *) = nullptr;

    /* GL_VERSION_1_5 */
     void(APIENTRY *oglBeginQuery)(GLenum, GLuint) = nullptr;
     void(APIENTRY *oglBindBuffer)(GLenum, GLuint) = nullptr;
     void(APIENTRY *oglBufferData)(GLenum, GLsizeiptr, const void *, GLenum) = nullptr;
     void(APIENTRY *oglBufferSubData)(GLenum, GLintptr, GLsizeiptr, const void *) = nullptr;
     void(APIENTRY *oglDeleteBuffers)(GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglDeleteQueries)(GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglEndQuery)(GLenum) = nullptr;
     void(APIENTRY *oglGenBuffers)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglGenQueries)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglGetBufferParameteriv)(GLenum, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetBufferPointerv)(GLenum, GLenum, void **) = nullptr;
     void(APIENTRY *oglGetBufferSubData)(GLenum, GLintptr, GLsizeiptr, void *) = nullptr;
     void(APIENTRY *oglGetQueryObjectiv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetQueryObjectuiv)(GLuint, GLenum, GLuint *) = nullptr;
     void(APIENTRY *oglGetQueryiv)(GLenum, GLenum, GLint *) = nullptr;
     GLboolean(APIENTRY *oglIsBuffer)(GLuint) = nullptr;
     GLboolean(APIENTRY *oglIsQuery)(GLuint) = nullptr;
     void *(APIENTRY *oglMapBuffer)(GLenum, GLenum) = nullptr;
     GLboolean(APIENTRY *oglUnmapBuffer)(GLenum) = nullptr;

    /* GL_VERSION_2_0 */
     void(APIENTRY *oglAttachShader)(GLuint, GLuint) = nullptr;
     void(APIENTRY *oglBindAttribLocation)(GLuint, GLuint, const GLchar *) = nullptr;
     void(APIENTRY *oglBlendEquationSeparate)(GLenum, GLenum) = nullptr;
     void(APIENTRY *oglCompileShader)(GLuint) = nullptr;
     GLuint(APIENTRY *oglCreateProgram)(void) = nullptr;
     GLuint(APIENTRY *oglCreateShader)(GLenum) = nullptr;
     void(APIENTRY *oglDeleteProgram)(GLuint) = nullptr;
     void(APIENTRY *oglDeleteShader)(GLuint) = nullptr;
     void(APIENTRY *oglDetachShader)(GLuint, GLuint) = nullptr;
     void(APIENTRY *oglDisableVertexAttribArray)(GLuint) = nullptr;
     void(APIENTRY *oglDrawBuffers)(GLsizei, const GLenum *) = nullptr;
     void(APIENTRY *oglEnableVertexAttribArray)(GLuint) = nullptr;
     void(APIENTRY *oglGetActiveAttrib)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *) = nullptr;
     void(APIENTRY *oglGetActiveUniform)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *) = nullptr;
     void(APIENTRY *oglGetAttachedShaders)(GLuint, GLsizei, GLsizei *, GLuint *) = nullptr;
     GLint(APIENTRY *oglGetAttribLocation)(GLuint, const GLchar *) = nullptr;
     void(APIENTRY *oglGetProgramInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetProgramiv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetShaderInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetShaderSource)(GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetShaderiv)(GLuint, GLenum, GLint *) = nullptr;
     GLint(APIENTRY *oglGetUniformLocation)(GLuint, const GLchar *) = nullptr;
     void(APIENTRY *oglGetUniformfv)(GLuint, GLint, GLfloat *) = nullptr;
     void(APIENTRY *oglGetUniformiv)(GLuint, GLint, GLint *) = nullptr;
     void(APIENTRY *oglGetVertexAttribPointerv)(GLuint, GLenum, void **) = nullptr;
     void(APIENTRY *oglGetVertexAttribdv)(GLuint, GLenum, GLdouble *) = nullptr;
     void(APIENTRY *oglGetVertexAttribfv)(GLuint, GLenum, GLfloat *) = nullptr;
     void(APIENTRY *oglGetVertexAttribiv)(GLuint, GLenum, GLint *) = nullptr;
     GLboolean(APIENTRY *oglIsProgram)(GLuint) = nullptr;
     GLboolean(APIENTRY *oglIsShader)(GLuint) = nullptr;
     void(APIENTRY *oglLinkProgram)(GLuint) = nullptr;
     void(APIENTRY *oglShaderSource)(GLuint, GLsizei, const GLchar *const*, const GLint *) = nullptr;
     void(APIENTRY *oglStencilFuncSeparate)(GLenum, GLenum, GLint, GLuint) = nullptr;
     void(APIENTRY *oglStencilMaskSeparate)(GLenum, GLuint) = nullptr;
     void(APIENTRY *oglStencilOpSeparate)(GLenum, GLenum, GLenum, GLenum) = nullptr;
     void(APIENTRY *oglUniform1f)(GLint, GLfloat) = nullptr;
     void(APIENTRY *oglUniform1fv)(GLint, GLsizei, const GLfloat *) = nullptr;
     void(APIENTRY *oglUniform1i)(GLint, GLint) = nullptr;
     void(APIENTRY *oglUniform1iv)(GLint, GLsizei, const GLint *) = nullptr;
     void(APIENTRY *oglUniform2f)(GLint, GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglUniform2fv)(GLint, GLsizei, const GLfloat *) = nullptr;
     void(APIENTRY *oglUniform2i)(GLint, GLint, GLint) = nullptr;
     void(APIENTRY *oglUniform2iv)(GLint, GLsizei, const GLint *) = nullptr;
     void(APIENTRY *oglUniform3f)(GLint, GLfloat, GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglUniform3fv)(GLint, GLsizei, const GLfloat *) = nullptr;
     void(APIENTRY *oglUniform3i)(GLint, GLint, GLint, GLint) = nullptr;
     void(APIENTRY *oglUniform3iv)(GLint, GLsizei, const GLint *) = nullptr;
     void(APIENTRY *oglUniform4f)(GLint, GLfloat, GLfloat, GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglUniform4fv)(GLint, GLsizei, const GLfloat *) = nullptr;
     void(APIENTRY *oglUniform4i)(GLint, GLint, GLint, GLint, GLint) = nullptr;
     void(APIENTRY *oglUniform4iv)(GLint, GLsizei, const GLint *) = nullptr;
     void(APIENTRY *oglUniformMatrix2fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglUniformMatrix3fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglUniformMatrix4fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglUseProgram)(GLuint) = nullptr;
     void(APIENTRY *oglValidateProgram)(GLuint) = nullptr;
     void(APIENTRY *oglVertexAttrib1d)(GLuint, GLdouble) = nullptr;
     void(APIENTRY *oglVertexAttrib1dv)(GLuint, const GLdouble *) = nullptr;
     void(APIENTRY *oglVertexAttrib1f)(GLuint, GLfloat) = nullptr;
     void(APIENTRY *oglVertexAttrib1fv)(GLuint, const GLfloat *) = nullptr;
     void(APIENTRY *oglVertexAttrib1s)(GLuint, GLshort) = nullptr;
     void(APIENTRY *oglVertexAttrib1sv)(GLuint, const GLshort *) = nullptr;
     void(APIENTRY *oglVertexAttrib2d)(GLuint, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglVertexAttrib2dv)(GLuint, const GLdouble *) = nullptr;
     void(APIENTRY *oglVertexAttrib2f)(GLuint, GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglVertexAttrib2fv)(GLuint, const GLfloat *) = nullptr;
     void(APIENTRY *oglVertexAttrib2s)(GLuint, GLshort, GLshort) = nullptr;
     void(APIENTRY *oglVertexAttrib2sv)(GLuint, const GLshort *) = nullptr;
     void(APIENTRY *oglVertexAttrib3d)(GLuint, GLdouble, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglVertexAttrib3dv)(GLuint, const GLdouble *) = nullptr;
     void(APIENTRY *oglVertexAttrib3f)(GLuint, GLfloat, GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglVertexAttrib3fv)(GLuint, const GLfloat *) = nullptr;
     void(APIENTRY *oglVertexAttrib3s)(GLuint, GLshort, GLshort, GLshort) = nullptr;
     void(APIENTRY *oglVertexAttrib3sv)(GLuint, const GLshort *) = nullptr;
     void(APIENTRY *oglVertexAttrib4Nbv)(GLuint, const GLbyte *) = nullptr;
     void(APIENTRY *oglVertexAttrib4Niv)(GLuint, const GLint *) = nullptr;
     void(APIENTRY *oglVertexAttrib4Nsv)(GLuint, const GLshort *) = nullptr;
     void(APIENTRY *oglVertexAttrib4Nub)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte) = nullptr;
     void(APIENTRY *oglVertexAttrib4Nubv)(GLuint, const GLubyte *) = nullptr;
     void(APIENTRY *oglVertexAttrib4Nuiv)(GLuint, const GLuint *) = nullptr;
     void(APIENTRY *oglVertexAttrib4Nusv)(GLuint, const GLushort *) = nullptr;
     void(APIENTRY *oglVertexAttrib4bv)(GLuint, const GLbyte *) = nullptr;
     void(APIENTRY *oglVertexAttrib4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglVertexAttrib4dv)(GLuint, const GLdouble *) = nullptr;
     void(APIENTRY *oglVertexAttrib4f)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglVertexAttrib4fv)(GLuint, const GLfloat *) = nullptr;
     void(APIENTRY *oglVertexAttrib4iv)(GLuint, const GLint *) = nullptr;
     void(APIENTRY *oglVertexAttrib4s)(GLuint, GLshort, GLshort, GLshort, GLshort) = nullptr;
     void(APIENTRY *oglVertexAttrib4sv)(GLuint, const GLshort *) = nullptr;
     void(APIENTRY *oglVertexAttrib4ubv)(GLuint, const GLubyte *) = nullptr;
     void(APIENTRY *oglVertexAttrib4uiv)(GLuint, const GLuint *) = nullptr;
     void(APIENTRY *oglVertexAttrib4usv)(GLuint, const GLushort *) = nullptr;
     void(APIENTRY *oglVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *) = nullptr;

    /* GL_VERSION_2_1 */
     void(APIENTRY *oglUniformMatrix2x3fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglUniformMatrix2x4fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglUniformMatrix3x2fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglUniformMatrix3x4fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglUniformMatrix4x2fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglUniformMatrix4x3fv)(GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;

    /* GL_VERSION_3_0 */
     void(APIENTRY *oglBeginConditionalRender)(GLuint, GLenum) = nullptr;
     void(APIENTRY *oglBeginTransformFeedback)(GLenum) = nullptr;
     void(APIENTRY *oglBindBufferBase)(GLenum, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglBindBufferRange)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr) = nullptr;
     void(APIENTRY *oglBindFragDataLocation)(GLuint, GLuint, const GLchar *) = nullptr;
     void(APIENTRY *oglBindFramebuffer)(GLenum, GLuint) = nullptr;
     void(APIENTRY *oglBindRenderbuffer)(GLenum, GLuint) = nullptr;
     void(APIENTRY *oglBindVertexArray)(GLuint) = nullptr;
     void(APIENTRY *oglBlitFramebuffer)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) = nullptr;
     GLenum(APIENTRY *oglCheckFramebufferStatus)(GLenum) = nullptr;
     void(APIENTRY *oglClampColor)(GLenum, GLenum) = nullptr;
     void(APIENTRY *oglClearBufferfi)(GLenum, GLint, GLfloat, GLint) = nullptr;
     void(APIENTRY *oglClearBufferfv)(GLenum, GLint, const GLfloat *) = nullptr;
     void(APIENTRY *oglClearBufferiv)(GLenum, GLint, const GLint *) = nullptr;
     void(APIENTRY *oglClearBufferuiv)(GLenum, GLint, const GLuint *) = nullptr;
     void(APIENTRY *oglColorMaski)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean) = nullptr;
     void(APIENTRY *oglDeleteFramebuffers)(GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglDeleteRenderbuffers)(GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglDeleteVertexArrays)(GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglDisablei)(GLenum, GLuint) = nullptr;
     void(APIENTRY *oglEnablei)(GLenum, GLuint) = nullptr;
     void(APIENTRY *oglEndConditionalRender)(void) = nullptr;
     void(APIENTRY *oglEndTransformFeedback)(void) = nullptr;
     void(APIENTRY *oglFlushMappedBufferRange)(GLenum, GLintptr, GLsizeiptr) = nullptr;
     void(APIENTRY *oglFramebufferRenderbuffer)(GLenum, GLenum, GLenum, GLuint) = nullptr;
     void(APIENTRY *oglFramebufferTexture1D)(GLenum, GLenum, GLenum, GLuint, GLint) = nullptr;
     void(APIENTRY *oglFramebufferTexture2D)(GLenum, GLenum, GLenum, GLuint, GLint) = nullptr;
     void(APIENTRY *oglFramebufferTexture3D)(GLenum, GLenum, GLenum, GLuint, GLint, GLint) = nullptr;
     void(APIENTRY *oglFramebufferTextureLayer)(GLenum, GLenum, GLuint, GLint, GLint) = nullptr;
     void(APIENTRY *oglGenFramebuffers)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglGenRenderbuffers)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglGenVertexArrays)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglGenerateMipmap)(GLenum) = nullptr;
     void(APIENTRY *oglGetBooleani_v)(GLenum, GLuint, GLboolean *) = nullptr;
     GLint(APIENTRY *oglGetFragDataLocation)(GLuint, const GLchar *) = nullptr;
     void(APIENTRY *oglGetFramebufferAttachmentParameteriv)(GLenum, GLenum, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetIntegeri_v)(GLenum, GLuint, GLint *) = nullptr;
     void(APIENTRY *oglGetRenderbufferParameteriv)(GLenum, GLenum, GLint *) = nullptr;
     const GLubyte *(APIENTRY *oglGetStringi)(GLenum, GLuint) = nullptr;
     void(APIENTRY *oglGetTexParameterIiv)(GLenum, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetTexParameterIuiv)(GLenum, GLenum, GLuint *) = nullptr;
     void(APIENTRY *oglGetTransformFeedbackVarying)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *) = nullptr;
     void(APIENTRY *oglGetUniformuiv)(GLuint, GLint, GLuint *) = nullptr;
     void(APIENTRY *oglGetVertexAttribIiv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetVertexAttribIuiv)(GLuint, GLenum, GLuint *) = nullptr;
     GLboolean(APIENTRY *oglIsEnabledi)(GLenum, GLuint) = nullptr;
     GLboolean(APIENTRY *oglIsFramebuffer)(GLuint) = nullptr;
     GLboolean(APIENTRY *oglIsRenderbuffer)(GLuint) = nullptr;
     GLboolean(APIENTRY *oglIsVertexArray)(GLuint) = nullptr;
     void *(APIENTRY *oglMapBufferRange)(GLenum, GLintptr, GLsizeiptr, GLbitfield) = nullptr;
     void(APIENTRY *oglRenderbufferStorage)(GLenum, GLenum, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglRenderbufferStorageMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglTexParameterIiv)(GLenum, GLenum, const GLint *) = nullptr;
     void(APIENTRY *oglTexParameterIuiv)(GLenum, GLenum, const GLuint *) = nullptr;
     void(APIENTRY *oglTransformFeedbackVaryings)(GLuint, GLsizei, const GLchar *const*, GLenum) = nullptr;
     void(APIENTRY *oglUniform1ui)(GLint, GLuint) = nullptr;
     void(APIENTRY *oglUniform1uiv)(GLint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglUniform2ui)(GLint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglUniform2uiv)(GLint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglUniform3ui)(GLint, GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglUniform3uiv)(GLint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglUniform4ui)(GLint, GLuint, GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglUniform4uiv)(GLint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglVertexAttribI1i)(GLuint, GLint) = nullptr;
     void(APIENTRY *oglVertexAttribI1iv)(GLuint, const GLint *) = nullptr;
     void(APIENTRY *oglVertexAttribI1ui)(GLuint, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribI1uiv)(GLuint, const GLuint *) = nullptr;
     void(APIENTRY *oglVertexAttribI2i)(GLuint, GLint, GLint) = nullptr;
     void(APIENTRY *oglVertexAttribI2iv)(GLuint, const GLint *) = nullptr;
     void(APIENTRY *oglVertexAttribI2ui)(GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribI2uiv)(GLuint, const GLuint *) = nullptr;
     void(APIENTRY *oglVertexAttribI3i)(GLuint, GLint, GLint, GLint) = nullptr;
     void(APIENTRY *oglVertexAttribI3iv)(GLuint, const GLint *) = nullptr;
     void(APIENTRY *oglVertexAttribI3ui)(GLuint, GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribI3uiv)(GLuint, const GLuint *) = nullptr;
     void(APIENTRY *oglVertexAttribI4bv)(GLuint, const GLbyte *) = nullptr;
     void(APIENTRY *oglVertexAttribI4i)(GLuint, GLint, GLint, GLint, GLint) = nullptr;
     void(APIENTRY *oglVertexAttribI4iv)(GLuint, const GLint *) = nullptr;
     void(APIENTRY *oglVertexAttribI4sv)(GLuint, const GLshort *) = nullptr;
     void(APIENTRY *oglVertexAttribI4ubv)(GLuint, const GLubyte *) = nullptr;
     void(APIENTRY *oglVertexAttribI4ui)(GLuint, GLuint, GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribI4uiv)(GLuint, const GLuint *) = nullptr;
     void(APIENTRY *oglVertexAttribI4usv)(GLuint, const GLushort *) = nullptr;
     void(APIENTRY *oglVertexAttribIPointer)(GLuint, GLint, GLenum, GLsizei, const void *) = nullptr;

    /* GL_VERSION_3_1 */
     void(APIENTRY *oglCopyBufferSubData)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr) = nullptr;
     void(APIENTRY *oglDrawArraysInstanced)(GLenum, GLint, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglDrawElementsInstanced)(GLenum, GLsizei, GLenum, const void *, GLsizei) = nullptr;
     void(APIENTRY *oglGetActiveUniformBlockName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetActiveUniformBlockiv)(GLuint, GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetActiveUniformName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetActiveUniformsiv)(GLuint, GLsizei, const GLuint *, GLenum, GLint *) = nullptr;
     GLuint(APIENTRY *oglGetUniformBlockIndex)(GLuint, const GLchar *) = nullptr;
     void(APIENTRY *oglGetUniformIndices)(GLuint, GLsizei, const GLchar *const*, GLuint *) = nullptr;
     void(APIENTRY *oglPrimitiveRestartIndex)(GLuint) = nullptr;
     void(APIENTRY *oglTexBuffer)(GLenum, GLenum, GLuint) = nullptr;
     void(APIENTRY *oglUniformBlockBinding)(GLuint, GLuint, GLuint) = nullptr;

    /* GL_VERSION_3_2 */
     GLenum(APIENTRY *oglClientWaitSync)(GLsync, GLbitfield, GLuint64) = nullptr;
     void(APIENTRY *oglDeleteSync)(GLsync) = nullptr;
     void(APIENTRY *oglDrawElementsBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLint) = nullptr;
     void(APIENTRY *oglDrawElementsInstancedBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint) = nullptr;
     void(APIENTRY *oglDrawRangeElementsBaseVertex)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint) = nullptr;
     GLsync(APIENTRY *oglFenceSync)(GLenum, GLbitfield) = nullptr;
     void(APIENTRY *oglFramebufferTexture)(GLenum, GLenum, GLuint, GLint) = nullptr;
     void(APIENTRY *oglGetBufferParameteri64v)(GLenum, GLenum, GLint64 *) = nullptr;
     void(APIENTRY *oglGetInteger64i_v)(GLenum, GLuint, GLint64 *) = nullptr;
     void(APIENTRY *oglGetInteger64v)(GLenum, GLint64 *) = nullptr;
     void(APIENTRY *oglGetMultisamplefv)(GLenum, GLuint, GLfloat *) = nullptr;
     void(APIENTRY *oglGetSynciv)(GLsync, GLenum, GLsizei, GLsizei *, GLint *) = nullptr;
     GLboolean(APIENTRY *oglIsSync)(GLsync) = nullptr;
     void(APIENTRY *oglMultiDrawElementsBaseVertex)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *) = nullptr;
     void(APIENTRY *oglProvokingVertex)(GLenum) = nullptr;
     void(APIENTRY *oglSampleMaski)(GLuint, GLbitfield) = nullptr;
     void(APIENTRY *oglTexImage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) = nullptr;
     void(APIENTRY *oglTexImage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) = nullptr;
     void(APIENTRY *oglWaitSync)(GLsync, GLbitfield, GLuint64) = nullptr;

    /* GL_VERSION_3_3 */
     void(APIENTRY *oglBindFragDataLocationIndexed)(GLuint, GLuint, GLuint, const GLchar *) = nullptr;
     void(APIENTRY *oglBindSampler)(GLuint, GLuint) = nullptr;
     void(APIENTRY *oglDeleteSamplers)(GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglGenSamplers)(GLsizei, GLuint *) = nullptr;
     GLint(APIENTRY *oglGetFragDataIndex)(GLuint, const GLchar *) = nullptr;
     void(APIENTRY *oglGetQueryObjecti64v)(GLuint, GLenum, GLint64 *) = nullptr;
     void(APIENTRY *oglGetQueryObjectui64v)(GLuint, GLenum, GLuint64 *) = nullptr;
     void(APIENTRY *oglGetSamplerParameterIiv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetSamplerParameterIuiv)(GLuint, GLenum, GLuint *) = nullptr;
     void(APIENTRY *oglGetSamplerParameterfv)(GLuint, GLenum, GLfloat *) = nullptr;
     void(APIENTRY *oglGetSamplerParameteriv)(GLuint, GLenum, GLint *) = nullptr;
     GLboolean(APIENTRY *oglIsSampler)(GLuint) = nullptr;
     void(APIENTRY *oglQueryCounter)(GLuint, GLenum) = nullptr;
     void(APIENTRY *oglSamplerParameterIiv)(GLuint, GLenum, const GLint *) = nullptr;
     void(APIENTRY *oglSamplerParameterIuiv)(GLuint, GLenum, const GLuint *) = nullptr;
     void(APIENTRY *oglSamplerParameterf)(GLuint, GLenum, GLfloat) = nullptr;
     void(APIENTRY *oglSamplerParameterfv)(GLuint, GLenum, const GLfloat *) = nullptr;
     void(APIENTRY *oglSamplerParameteri)(GLuint, GLenum, GLint) = nullptr;
     void(APIENTRY *oglSamplerParameteriv)(GLuint, GLenum, const GLint *) = nullptr;
     void(APIENTRY *oglVertexAttribDivisor)(GLuint, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribP1ui)(GLuint, GLenum, GLboolean, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribP1uiv)(GLuint, GLenum, GLboolean, const GLuint *) = nullptr;
     void(APIENTRY *oglVertexAttribP2ui)(GLuint, GLenum, GLboolean, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribP2uiv)(GLuint, GLenum, GLboolean, const GLuint *) = nullptr;
     void(APIENTRY *oglVertexAttribP3ui)(GLuint, GLenum, GLboolean, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribP3uiv)(GLuint, GLenum, GLboolean, const GLuint *) = nullptr;
     void(APIENTRY *oglVertexAttribP4ui)(GLuint, GLenum, GLboolean, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribP4uiv)(GLuint, GLenum, GLboolean, const GLuint *) = nullptr;

    /* GL_VERSION_4_0 */
     void(APIENTRY *oglBeginQueryIndexed)(GLenum, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglBindTransformFeedback)(GLenum, GLuint) = nullptr;
     void(APIENTRY *oglBlendEquationSeparatei)(GLuint, GLenum, GLenum) = nullptr;
     void(APIENTRY *oglBlendEquationi)(GLuint, GLenum) = nullptr;
     void(APIENTRY *oglBlendFuncSeparatei)(GLuint, GLenum, GLenum, GLenum, GLenum) = nullptr;
     void(APIENTRY *oglBlendFunci)(GLuint, GLenum, GLenum) = nullptr;
     void(APIENTRY *oglDeleteTransformFeedbacks)(GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglDrawArraysIndirect)(GLenum, const void *) = nullptr;
     void(APIENTRY *oglDrawElementsIndirect)(GLenum, GLenum, const void *) = nullptr;
     void(APIENTRY *oglDrawTransformFeedback)(GLenum, GLuint) = nullptr;
     void(APIENTRY *oglDrawTransformFeedbackStream)(GLenum, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglEndQueryIndexed)(GLenum, GLuint) = nullptr;
     void(APIENTRY *oglGenTransformFeedbacks)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglGetActiveSubroutineName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetActiveSubroutineUniformName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetActiveSubroutineUniformiv)(GLuint, GLenum, GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetProgramStageiv)(GLuint, GLenum, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetQueryIndexediv)(GLenum, GLuint, GLenum, GLint *) = nullptr;
     GLuint(APIENTRY *oglGetSubroutineIndex)(GLuint, GLenum, const GLchar *) = nullptr;
     GLint(APIENTRY *oglGetSubroutineUniformLocation)(GLuint, GLenum, const GLchar *) = nullptr;
     void(APIENTRY *oglGetUniformSubroutineuiv)(GLenum, GLint, GLuint *) = nullptr;
     void(APIENTRY *oglGetUniformdv)(GLuint, GLint, GLdouble *) = nullptr;
     GLboolean(APIENTRY *oglIsTransformFeedback)(GLuint) = nullptr;
     void(APIENTRY *oglMinSampleShading)(GLfloat) = nullptr;
     void(APIENTRY *oglPatchParameterfv)(GLenum, const GLfloat *) = nullptr;
     void(APIENTRY *oglPatchParameteri)(GLenum, GLint) = nullptr;
     void(APIENTRY *oglPauseTransformFeedback)(void) = nullptr;
     void(APIENTRY *oglResumeTransformFeedback)(void) = nullptr;
     void(APIENTRY *oglUniform1d)(GLint, GLdouble) = nullptr;
     void(APIENTRY *oglUniform1dv)(GLint, GLsizei, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniform2d)(GLint, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglUniform2dv)(GLint, GLsizei, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniform3d)(GLint, GLdouble, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglUniform3dv)(GLint, GLsizei, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniform4d)(GLint, GLdouble, GLdouble, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglUniform4dv)(GLint, GLsizei, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniformMatrix2dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniformMatrix2x3dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniformMatrix2x4dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniformMatrix3dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniformMatrix3x2dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniformMatrix3x4dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniformMatrix4dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniformMatrix4x2dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniformMatrix4x3dv)(GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglUniformSubroutinesuiv)(GLenum, GLsizei, const GLuint *) = nullptr;

    /* GL_VERSION_4_1 */
     void(APIENTRY *oglActiveShaderProgram)(GLuint, GLuint) = nullptr;
     void(APIENTRY *oglBindProgramPipeline)(GLuint) = nullptr;
     void(APIENTRY *oglClearDepthf)(GLfloat) = nullptr;
     GLuint(APIENTRY *oglCreateShaderProgramv)(GLenum, GLsizei, const GLchar *const*) = nullptr;
     void(APIENTRY *oglDeleteProgramPipelines)(GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglDepthRangeArrayv)(GLuint, GLsizei, const GLdouble *) = nullptr;
     void(APIENTRY *oglDepthRangeIndexed)(GLuint, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglDepthRangef)(GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglGenProgramPipelines)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglGetDoublei_v)(GLenum, GLuint, GLdouble *) = nullptr;
     void(APIENTRY *oglGetFloati_v)(GLenum, GLuint, GLfloat *) = nullptr;
     void(APIENTRY *oglGetProgramBinary)(GLuint, GLsizei, GLsizei *, GLenum *, void *) = nullptr;
     void(APIENTRY *oglGetProgramPipelineInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetProgramPipelineiv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetShaderPrecisionFormat)(GLenum, GLenum, GLint *, GLint *) = nullptr;
     void(APIENTRY *oglGetVertexAttribLdv)(GLuint, GLenum, GLdouble *) = nullptr;
     GLboolean(APIENTRY *oglIsProgramPipeline)(GLuint) = nullptr;
     void(APIENTRY *oglProgramBinary)(GLuint, GLenum, const void *, GLsizei) = nullptr;
     void(APIENTRY *oglProgramParameteri)(GLuint, GLenum, GLint) = nullptr;
     void(APIENTRY *oglProgramUniform1d)(GLuint, GLint, GLdouble) = nullptr;
     void(APIENTRY *oglProgramUniform1dv)(GLuint, GLint, GLsizei, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniform1f)(GLuint, GLint, GLfloat) = nullptr;
     void(APIENTRY *oglProgramUniform1fv)(GLuint, GLint, GLsizei, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniform1i)(GLuint, GLint, GLint) = nullptr;
     void(APIENTRY *oglProgramUniform1iv)(GLuint, GLint, GLsizei, const GLint *) = nullptr;
     void(APIENTRY *oglProgramUniform1ui)(GLuint, GLint, GLuint) = nullptr;
     void(APIENTRY *oglProgramUniform1uiv)(GLuint, GLint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglProgramUniform2d)(GLuint, GLint, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglProgramUniform2dv)(GLuint, GLint, GLsizei, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniform2f)(GLuint, GLint, GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglProgramUniform2fv)(GLuint, GLint, GLsizei, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniform2i)(GLuint, GLint, GLint, GLint) = nullptr;
     void(APIENTRY *oglProgramUniform2iv)(GLuint, GLint, GLsizei, const GLint *) = nullptr;
     void(APIENTRY *oglProgramUniform2ui)(GLuint, GLint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglProgramUniform2uiv)(GLuint, GLint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglProgramUniform3d)(GLuint, GLint, GLdouble, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglProgramUniform3dv)(GLuint, GLint, GLsizei, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniform3f)(GLuint, GLint, GLfloat, GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglProgramUniform3fv)(GLuint, GLint, GLsizei, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniform3i)(GLuint, GLint, GLint, GLint, GLint) = nullptr;
     void(APIENTRY *oglProgramUniform3iv)(GLuint, GLint, GLsizei, const GLint *) = nullptr;
     void(APIENTRY *oglProgramUniform3ui)(GLuint, GLint, GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglProgramUniform3uiv)(GLuint, GLint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglProgramUniform4d)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglProgramUniform4dv)(GLuint, GLint, GLsizei, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniform4f)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglProgramUniform4fv)(GLuint, GLint, GLsizei, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniform4i)(GLuint, GLint, GLint, GLint, GLint, GLint) = nullptr;
     void(APIENTRY *oglProgramUniform4iv)(GLuint, GLint, GLsizei, const GLint *) = nullptr;
     void(APIENTRY *oglProgramUniform4ui)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglProgramUniform4uiv)(GLuint, GLint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix2x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix2x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix2x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix2x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix3x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix3x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix3x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix3x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix4x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix4x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix4x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = nullptr;
     void(APIENTRY *oglProgramUniformMatrix4x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = nullptr;
     void(APIENTRY *oglReleaseShaderCompiler)(void) = nullptr;
     void(APIENTRY *oglScissorArrayv)(GLuint, GLsizei, const GLint *) = nullptr;
     void(APIENTRY *oglScissorIndexed)(GLuint, GLint, GLint, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglScissorIndexedv)(GLuint, const GLint *) = nullptr;
     void(APIENTRY *oglShaderBinary)(GLsizei, const GLuint *, GLenum, const void *, GLsizei) = nullptr;
     void(APIENTRY *oglUseProgramStages)(GLuint, GLbitfield, GLuint) = nullptr;
     void(APIENTRY *oglValidateProgramPipeline)(GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribL1d)(GLuint, GLdouble) = nullptr;
     void(APIENTRY *oglVertexAttribL1dv)(GLuint, const GLdouble *) = nullptr;
     void(APIENTRY *oglVertexAttribL2d)(GLuint, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglVertexAttribL2dv)(GLuint, const GLdouble *) = nullptr;
     void(APIENTRY *oglVertexAttribL3d)(GLuint, GLdouble, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglVertexAttribL3dv)(GLuint, const GLdouble *) = nullptr;
     void(APIENTRY *oglVertexAttribL4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble) = nullptr;
     void(APIENTRY *oglVertexAttribL4dv)(GLuint, const GLdouble *) = nullptr;
     void(APIENTRY *oglVertexAttribLPointer)(GLuint, GLint, GLenum, GLsizei, const void *) = nullptr;
     void(APIENTRY *oglViewportArrayv)(GLuint, GLsizei, const GLfloat *) = nullptr;
     void(APIENTRY *oglViewportIndexedf)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat) = nullptr;
     void(APIENTRY *oglViewportIndexedfv)(GLuint, const GLfloat *) = nullptr;

    /* GL_VERSION_4_2 */
     void(APIENTRY *oglBindImageTexture)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum) = nullptr;
     void(APIENTRY *oglDrawArraysInstancedBaseInstance)(GLenum, GLint, GLsizei, GLsizei, GLuint) = nullptr;
     void(APIENTRY *oglDrawElementsInstancedBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint) = nullptr;
     void(APIENTRY *oglDrawElementsInstancedBaseVertexBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint) = nullptr;
     void(APIENTRY *oglDrawTransformFeedbackInstanced)(GLenum, GLuint, GLsizei) = nullptr;
     void(APIENTRY *oglDrawTransformFeedbackStreamInstanced)(GLenum, GLuint, GLuint, GLsizei) = nullptr;
     void(APIENTRY *oglGetActiveAtomicCounterBufferiv)(GLuint, GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetInternalformativ)(GLenum, GLenum, GLenum, GLsizei, GLint *) = nullptr;
     void(APIENTRY *oglMemoryBarrier)(GLbitfield) = nullptr;
     void(APIENTRY *oglTexStorage1D)(GLenum, GLsizei, GLenum, GLsizei) = nullptr;
     void(APIENTRY *oglTexStorage2D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglTexStorage3D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei) = nullptr;

    /* GL_VERSION_4_3 */
     void(APIENTRY *oglBindVertexBuffer)(GLuint, GLuint, GLintptr, GLsizei) = nullptr;
     void(APIENTRY *oglClearBufferData)(GLenum, GLenum, GLenum, GLenum, const void *) = nullptr;
     void(APIENTRY *oglClearBufferSubData)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *) = nullptr;
     void(APIENTRY *oglCopyImageSubData)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglDebugMessageCallback)(GLDEBUGPROC, const void *) = nullptr;
     void(APIENTRY *oglDebugMessageControl)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean) = nullptr;
     void(APIENTRY *oglDebugMessageInsert)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *) = nullptr;
     void(APIENTRY *oglDispatchCompute)(GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglDispatchComputeIndirect)(GLintptr) = nullptr;
     void(APIENTRY *oglFramebufferParameteri)(GLenum, GLenum, GLint) = nullptr;
     GLuint(APIENTRY *oglGetDebugMessageLog)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetFramebufferParameteriv)(GLenum, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetInternalformati64v)(GLenum, GLenum, GLenum, GLsizei, GLint64 *) = nullptr;
     void(APIENTRY *oglGetObjectLabel)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetObjectPtrLabel)(const void *, GLsizei, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetPointerv)(GLenum, void **) = nullptr;
     void(APIENTRY *oglGetProgramInterfaceiv)(GLuint, GLenum, GLenum, GLint *) = nullptr;
     GLuint(APIENTRY *oglGetProgramResourceIndex)(GLuint, GLenum, const GLchar *) = nullptr;
     GLint(APIENTRY *oglGetProgramResourceLocation)(GLuint, GLenum, const GLchar *) = nullptr;
     GLint(APIENTRY *oglGetProgramResourceLocationIndex)(GLuint, GLenum, const GLchar *) = nullptr;
     void(APIENTRY *oglGetProgramResourceName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = nullptr;
     void(APIENTRY *oglGetProgramResourceiv)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *) = nullptr;
     void(APIENTRY *oglInvalidateBufferData)(GLuint) = nullptr;
     void(APIENTRY *oglInvalidateBufferSubData)(GLuint, GLintptr, GLsizeiptr) = nullptr;
     void(APIENTRY *oglInvalidateFramebuffer)(GLenum, GLsizei, const GLenum *) = nullptr;
     void(APIENTRY *oglInvalidateSubFramebuffer)(GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglInvalidateTexImage)(GLuint, GLint) = nullptr;
     void(APIENTRY *oglInvalidateTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglMultiDrawArraysIndirect)(GLenum, const void *, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglMultiDrawElementsIndirect)(GLenum, GLenum, const void *, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglObjectLabel)(GLenum, GLuint, GLsizei, const GLchar *) = nullptr;
     void(APIENTRY *oglObjectPtrLabel)(const void *, GLsizei, const GLchar *) = nullptr;
     void(APIENTRY *oglPopDebugGroup)(void) = nullptr;
     void(APIENTRY *oglPushDebugGroup)(GLenum, GLuint, GLsizei, const GLchar *) = nullptr;
     void(APIENTRY *oglShaderStorageBlockBinding)(GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglTexBufferRange)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr) = nullptr;
     void(APIENTRY *oglTexStorage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) = nullptr;
     void(APIENTRY *oglTexStorage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) = nullptr;
     void(APIENTRY *oglTextureView)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribBinding)(GLuint, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribFormat)(GLuint, GLint, GLenum, GLboolean, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribIFormat)(GLuint, GLint, GLenum, GLuint) = nullptr;
     void(APIENTRY *oglVertexAttribLFormat)(GLuint, GLint, GLenum, GLuint) = nullptr;
     void(APIENTRY *oglVertexBindingDivisor)(GLuint, GLuint) = nullptr;

    /* GL_VERSION_4_4 */
     void(APIENTRY *oglBindBuffersBase)(GLenum, GLuint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglBindBuffersRange)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *) = nullptr;
     void(APIENTRY *oglBindImageTextures)(GLuint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglBindSamplers)(GLuint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglBindTextures)(GLuint, GLsizei, const GLuint *) = nullptr;
     void(APIENTRY *oglBindVertexBuffers)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *) = nullptr;
     void(APIENTRY *oglBufferStorage)(GLenum, GLsizeiptr, const void *, GLbitfield) = nullptr;
     void(APIENTRY *oglClearTexImage)(GLuint, GLint, GLenum, GLenum, const void *) = nullptr;
     void(APIENTRY *oglClearTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) = nullptr;

    /* GL_VERSION_4_5 */
     void(APIENTRY *oglBindTextureUnit)(GLuint, GLuint) = nullptr;
     void(APIENTRY *oglBlitNamedFramebuffer)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) = nullptr;
     GLenum(APIENTRY *oglCheckNamedFramebufferStatus)(GLuint, GLenum) = nullptr;
     void(APIENTRY *oglClearNamedBufferData)(GLuint, GLenum, GLenum, GLenum, const void *) = nullptr;
     void(APIENTRY *oglClearNamedBufferSubData)(GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *) = nullptr;
     void(APIENTRY *oglClearNamedFramebufferfi)(GLuint, GLenum, const GLfloat, GLint) = nullptr;
     void(APIENTRY *oglClearNamedFramebufferfv)(GLuint, GLenum, GLint, const GLfloat *) = nullptr;
     void(APIENTRY *oglClearNamedFramebufferiv)(GLuint, GLenum, GLint, const GLint *) = nullptr;
     void(APIENTRY *oglClearNamedFramebufferuiv)(GLuint, GLenum, GLint, const GLuint *) = nullptr;
     void(APIENTRY *oglClipControl)(GLenum, GLenum) = nullptr;
     void(APIENTRY *oglCompressedTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) = nullptr;
     void(APIENTRY *oglCompressedTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) = nullptr;
     void(APIENTRY *oglCompressedTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) = nullptr;
     void(APIENTRY *oglCopyNamedBufferSubData)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr) = nullptr;
     void(APIENTRY *oglCopyTextureSubImage1D)(GLuint, GLint, GLint, GLint, GLint, GLsizei) = nullptr;
     void(APIENTRY *oglCopyTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglCopyTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglCreateBuffers)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglCreateFramebuffers)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglCreateProgramPipelines)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglCreateQueries)(GLenum, GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglCreateRenderbuffers)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglCreateSamplers)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglCreateTextures)(GLenum, GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglCreateTransformFeedbacks)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglCreateVertexArrays)(GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglDisableVertexArrayAttrib)(GLuint, GLuint) = nullptr;
     void(APIENTRY *oglEnableVertexArrayAttrib)(GLuint, GLuint) = nullptr;
     void(APIENTRY *oglFlushMappedNamedBufferRange)(GLuint, GLintptr, GLsizeiptr) = nullptr;
     void(APIENTRY *oglGenerateTextureMipmap)(GLuint) = nullptr;
     void(APIENTRY *oglGetCompressedTextureImage)(GLuint, GLint, GLsizei, void *) = nullptr;
     void(APIENTRY *oglGetCompressedTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *) = nullptr;
     GLenum(APIENTRY *oglGetGraphicsResetStatus)(void) = nullptr;
     void(APIENTRY *oglGetNamedBufferParameteri64v)(GLuint, GLenum, GLint64 *) = nullptr;
     void(APIENTRY *oglGetNamedBufferParameteriv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetNamedBufferPointerv)(GLuint, GLenum, void **) = nullptr;
     void(APIENTRY *oglGetNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, void *) = nullptr;
     void(APIENTRY *oglGetNamedFramebufferAttachmentParameteriv)(GLuint, GLenum, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetNamedFramebufferParameteriv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetNamedRenderbufferParameteriv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetQueryBufferObjecti64v)(GLuint, GLuint, GLenum, GLintptr) = nullptr;
     void(APIENTRY *oglGetQueryBufferObjectiv)(GLuint, GLuint, GLenum, GLintptr) = nullptr;
     void(APIENTRY *oglGetQueryBufferObjectui64v)(GLuint, GLuint, GLenum, GLintptr) = nullptr;
     void(APIENTRY *oglGetQueryBufferObjectuiv)(GLuint, GLuint, GLenum, GLintptr) = nullptr;
     void(APIENTRY *oglGetTextureImage)(GLuint, GLint, GLenum, GLenum, GLsizei, void *) = nullptr;
     void(APIENTRY *oglGetTextureLevelParameterfv)(GLuint, GLint, GLenum, GLfloat *) = nullptr;
     void(APIENTRY *oglGetTextureLevelParameteriv)(GLuint, GLint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetTextureParameterIiv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetTextureParameterIuiv)(GLuint, GLenum, GLuint *) = nullptr;
     void(APIENTRY *oglGetTextureParameterfv)(GLuint, GLenum, GLfloat *) = nullptr;
     void(APIENTRY *oglGetTextureParameteriv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) = nullptr;
     void(APIENTRY *oglGetTransformFeedbacki64_v)(GLuint, GLenum, GLuint, GLint64 *) = nullptr;
     void(APIENTRY *oglGetTransformFeedbacki_v)(GLuint, GLenum, GLuint, GLint *) = nullptr;
     void(APIENTRY *oglGetTransformFeedbackiv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetVertexArrayIndexed64iv)(GLuint, GLuint, GLenum, GLint64 *) = nullptr;
     void(APIENTRY *oglGetVertexArrayIndexediv)(GLuint, GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetVertexArrayiv)(GLuint, GLenum, GLint *) = nullptr;
     void(APIENTRY *oglGetnCompressedTexImage)(GLenum, GLint, GLsizei, void *) = nullptr;
     void(APIENTRY *oglGetnTexImage)(GLenum, GLint, GLenum, GLenum, GLsizei, void *) = nullptr;
     void(APIENTRY *oglGetnUniformdv)(GLuint, GLint, GLsizei, GLdouble *) = nullptr;
     void(APIENTRY *oglGetnUniformfv)(GLuint, GLint, GLsizei, GLfloat *) = nullptr;
     void(APIENTRY *oglGetnUniformiv)(GLuint, GLint, GLsizei, GLint *) = nullptr;
     void(APIENTRY *oglGetnUniformuiv)(GLuint, GLint, GLsizei, GLuint *) = nullptr;
     void(APIENTRY *oglInvalidateNamedFramebufferData)(GLuint, GLsizei, const GLenum *) = nullptr;
     void(APIENTRY *oglInvalidateNamedFramebufferSubData)(GLuint, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei) = nullptr;
     void *(APIENTRY *oglMapNamedBuffer)(GLuint, GLenum) = nullptr;
     void *(APIENTRY *oglMapNamedBufferRange)(GLuint, GLintptr, GLsizeiptr, GLbitfield) = nullptr;
     void(APIENTRY *oglMemoryBarrierByRegion)(GLbitfield) = nullptr;
     void(APIENTRY *oglNamedBufferData)(GLuint, GLsizeiptr, const void *, GLenum) = nullptr;
     void(APIENTRY *oglNamedBufferStorage)(GLuint, GLsizeiptr, const void *, GLbitfield) = nullptr;
     void(APIENTRY *oglNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, const void *) = nullptr;
     void(APIENTRY *oglNamedFramebufferDrawBuffer)(GLuint, GLenum) = nullptr;
     void(APIENTRY *oglNamedFramebufferDrawBuffers)(GLuint, GLsizei, const GLenum *) = nullptr;
     void(APIENTRY *oglNamedFramebufferParameteri)(GLuint, GLenum, GLint) = nullptr;
     void(APIENTRY *oglNamedFramebufferReadBuffer)(GLuint, GLenum) = nullptr;
     void(APIENTRY *oglNamedFramebufferRenderbuffer)(GLuint, GLenum, GLenum, GLuint) = nullptr;
     void(APIENTRY *oglNamedFramebufferTexture)(GLuint, GLenum, GLuint, GLint) = nullptr;
     void(APIENTRY *oglNamedFramebufferTextureLayer)(GLuint, GLenum, GLuint, GLint, GLint) = nullptr;
     void(APIENTRY *oglNamedRenderbufferStorage)(GLuint, GLenum, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglNamedRenderbufferStorageMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglReadnPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) = nullptr;
     void(APIENTRY *oglTextureBarrier)(void) = nullptr;
     void(APIENTRY *oglTextureBuffer)(GLuint, GLenum, GLuint) = nullptr;
     void(APIENTRY *oglTextureBufferRange)(GLuint, GLenum, GLuint, GLintptr, GLsizeiptr) = nullptr;
     void(APIENTRY *oglTextureParameterIiv)(GLuint, GLenum, const GLint *) = nullptr;
     void(APIENTRY *oglTextureParameterIuiv)(GLuint, GLenum, const GLuint *) = nullptr;
     void(APIENTRY *oglTextureParameterf)(GLuint, GLenum, GLfloat) = nullptr;
     void(APIENTRY *oglTextureParameterfv)(GLuint, GLenum, const GLfloat *) = nullptr;
     void(APIENTRY *oglTextureParameteri)(GLuint, GLenum, GLint) = nullptr;
     void(APIENTRY *oglTextureParameteriv)(GLuint, GLenum, const GLint *) = nullptr;
     void(APIENTRY *oglTextureStorage1D)(GLuint, GLsizei, GLenum, GLsizei) = nullptr;
     void(APIENTRY *oglTextureStorage2D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglTextureStorage2DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) = nullptr;
     void(APIENTRY *oglTextureStorage3D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei) = nullptr;
     void(APIENTRY *oglTextureStorage3DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) = nullptr;
     void(APIENTRY *oglTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *) = nullptr;
     void(APIENTRY *oglTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) = nullptr;
     void(APIENTRY *oglTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) = nullptr;
     void(APIENTRY *oglTransformFeedbackBufferBase)(GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglTransformFeedbackBufferRange)(GLuint, GLuint, GLuint, GLintptr, GLsizeiptr) = nullptr;
     GLboolean(APIENTRY *oglUnmapNamedBuffer)(GLuint) = nullptr;
     void(APIENTRY *oglVertexArrayAttribBinding)(GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglVertexArrayAttribFormat)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint) = nullptr;
     void(APIENTRY *oglVertexArrayAttribIFormat)(GLuint, GLuint, GLint, GLenum, GLuint) = nullptr;
     void(APIENTRY *oglVertexArrayAttribLFormat)(GLuint, GLuint, GLint, GLenum, GLuint) = nullptr;
     void(APIENTRY *oglVertexArrayBindingDivisor)(GLuint, GLuint, GLuint) = nullptr;
     void(APIENTRY *oglVertexArrayElementBuffer)(GLuint, GLuint) = nullptr;
     void(APIENTRY *oglVertexArrayVertexBuffer)(GLuint, GLuint, GLuint, GLintptr, GLsizei) = nullptr;
     void(APIENTRY *oglVertexArrayVertexBuffers)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *) = nullptr;
}
#pragma once
#ifndef _OGL_LIBRARY_
#define _OGL_LIBRARY_

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glext.h>
//#include <GL/glxext.h>
#include <GL/glcorearb.h>
#include <GL/wglext.h>
#include <cstddef>

namespace ogl
{
  extern const GLubyte *glGetString(GLenum name);
  extern const GLubyte *glGetStringi(GLenum name, GLuint index);
  extern void glGetIntegerv( GLenum pname, GLint params);
  extern HGLRC wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int *attribList);
}

#endif
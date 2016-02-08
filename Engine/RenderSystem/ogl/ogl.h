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

#define CHECK_OGL_ERROR( aMsg, ... ) CheckOGLError( aMsg, __VA_ARGS__ );

namespace ogl
{
  extern void CheckOGLError( const char* aErrorMsg, ... );
  extern const GLubyte *glGetString(GLenum name);
  extern const GLubyte *glGetStringi(GLenum name, GLuint index);
  extern void glGetIntegerv( GLenum pname, GLint params);
  extern HGLRC wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int *attribList);

  extern GLuint glCreateShader(GLenum type);
  extern void glAttachShader(GLuint program, GLuint shader);
  extern void glCompileShader(GLuint shader);
  extern void glShaderSource(GLuint shader, GLsizei count, const GLchar* *string, const GLint *length);
  extern void glGetProgramiv(GLuint program, GLenum pname, GLint *params);
  extern void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
  extern void glGetShaderiv(GLuint shader, GLenum pname, GLint *params);
  extern void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
  extern GLuint glCreateProgram();
  extern void glDeleteProgram(GLuint program);
  extern void glDeleteShader(GLuint shader);
  extern void glDetachShader(GLuint program, GLuint shader);
  extern void glProgramParameteri(GLuint program, GLenum pname, GLint value);
  extern void glLinkProgram(GLuint program);
  extern void glGenProgramPipelines(GLsizei n, GLuint *pipelines);
  extern void glBindProgramPipeline(GLuint pipeline);
  extern void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program);
  extern GLuint glCreateShaderProgramv(GLenum type, GLsizei count, const char **strings);

  extern void glGenVertexArrays(GLsizei n, GLuint *arrays);
  extern void glBindVertexArray(GLuint array);
}

#endif
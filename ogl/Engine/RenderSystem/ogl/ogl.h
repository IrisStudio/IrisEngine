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

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef GLAPI
#define GLAPI extern
#endif

namespace ogl
{
    GLAPI void CheckOGLError( const char* aErrorMsg, ... );
    GLAPI const GLubyte *glGetString(GLenum name);
    GLAPI const GLubyte *glGetStringi(GLenum name, GLuint index);
    GLAPI void glGetIntegerv( GLenum pname, GLint params);
    GLAPI HGLRC wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int *attribList);

    GLAPI GLuint glCreateShader(GLenum type);
    GLAPI void glAttachShader(GLuint program, GLuint shader);
    GLAPI void glCompileShader(GLuint shader);
    GLAPI void glShaderSource(GLuint shader, GLsizei count, const GLchar* *string, const GLint *length);
    GLAPI void glGetProgramiv(GLuint program, GLenum pname, GLint *params);
    GLAPI void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    GLAPI void glGetShaderiv(GLuint shader, GLenum pname, GLint *params);
    GLAPI void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    GLAPI GLuint glCreateProgram();
    GLAPI void glDeleteProgram(GLuint program);
    GLAPI void glDeleteShader(GLuint shader);
    GLAPI void glDetachShader(GLuint program, GLuint shader);
    GLAPI void glProgramParameteri(GLuint program, GLenum pname, GLint value);
    GLAPI void glLinkProgram(GLuint program);
    GLAPI void glGenProgramPipelines(GLsizei n, GLuint *pipelines);
    GLAPI void glBindProgramPipeline(GLuint pipeline);
    GLAPI void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program);
    GLAPI GLuint glCreateShaderProgramv(GLenum type, GLsizei count, const char **strings);

    GLAPI void glGenVertexArrays(GLsizei n, GLuint *arrays);
    GLAPI void glBindVertexArray(GLuint array);

    GLAPI void glGenBuffers(GLsizei n, GLuint * buffers);
    GLAPI void glBindBuffer(GLenum target, GLuint buffer);
    GLAPI void glBufferData(GLenum target,
                             GLsizeiptr size,
                             const GLvoid * data,
                             GLenum usage);
    GLAPI void glVertexAttribPointer(GLuint index,
                                      GLint size,
                                      GLenum type,
                                      GLboolean normalized,
                                      GLsizei stride,
                                      const GLvoid * pointer);
    void glEnableVertexAttribArray(GLuint index);

}

#endif
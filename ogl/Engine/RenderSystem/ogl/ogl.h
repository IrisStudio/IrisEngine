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
    GLAPI void InitOGLFunctions();
    GLAPI void CheckOGLError( const char* aErrorMsg, ... );

    /* GL_VERSION_1_2 */
    GLAPI void(APIENTRY *oglCopyTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
#define glCopyTexSubImage3D oglCopyTexSubImage3D
    GLAPI void(APIENTRY *oglDrawRangeElements)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *);
#define glDrawRangeElements oglDrawRangeElements
    GLAPI void(APIENTRY *oglTexImage3D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
#define glTexImage3D oglTexImage3D
    GLAPI void(APIENTRY *oglTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
#define glTexSubImage3D oglTexSubImage3D

    /* GL_VERSION_1_3 */

    GLAPI void(APIENTRY *oglActiveTexture)(GLenum);
#define glActiveTexture oglActiveTexture
    GLAPI void(APIENTRY *oglCompressedTexImage1D)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *);
#define glCompressedTexImage1D oglCompressedTexImage1D
    GLAPI void(APIENTRY *oglCompressedTexImage2D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *);
#define glCompressedTexImage2D oglCompressedTexImage2D
    GLAPI void(APIENTRY *oglCompressedTexImage3D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *);
#define glCompressedTexImage3D oglCompressedTexImage3D
    GLAPI void(APIENTRY *oglCompressedTexSubImage1D)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTexSubImage1D oglCompressedTexSubImage1D
    GLAPI void(APIENTRY *oglCompressedTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTexSubImage2D oglCompressedTexSubImage2D
    GLAPI void(APIENTRY *oglCompressedTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTexSubImage3D oglCompressedTexSubImage3D
    GLAPI void(APIENTRY *oglGetCompressedTexImage)(GLenum, GLint, void *);
#define glGetCompressedTexImage oglGetCompressedTexImage
    GLAPI void(APIENTRY *oglSampleCoverage)(GLfloat, GLboolean);
#define glSampleCoverage oglSampleCoverage

    /* GL_VERSION_1_4 */

    GLAPI void(APIENTRY *oglBlendColor)(GLfloat, GLfloat, GLfloat, GLfloat);
#define glBlendColor oglBlendColor
    GLAPI void(APIENTRY *oglBlendEquation)(GLenum);
#define glBlendEquation oglBlendEquation
    GLAPI void(APIENTRY *oglBlendFuncSeparate)(GLenum, GLenum, GLenum, GLenum);
#define glBlendFuncSeparate oglBlendFuncSeparate
    GLAPI void(APIENTRY *oglMultiDrawArrays)(GLenum, const GLint *, const GLsizei *, GLsizei);
#define glMultiDrawArrays oglMultiDrawArrays
    GLAPI void(APIENTRY *oglMultiDrawElements)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei);
#define glMultiDrawElements oglMultiDrawElements
    GLAPI void(APIENTRY *oglPointParameterf)(GLenum, GLfloat);
#define glPointParameterf oglPointParameterf
    GLAPI void(APIENTRY *oglPointParameterfv)(GLenum, const GLfloat *);
#define glPointParameterfv oglPointParameterfv
    GLAPI void(APIENTRY *oglPointParameteri)(GLenum, GLint);
#define glPointParameteri oglPointParameteri
    GLAPI void(APIENTRY *oglPointParameteriv)(GLenum, const GLint *);
#define glPointParameteriv oglPointParameteriv

    /* GL_VERSION_1_5 */

    GLAPI void(APIENTRY *oglBeginQuery)(GLenum, GLuint);
#define glBeginQuery oglBeginQuery
    GLAPI void(APIENTRY *oglBindBuffer)(GLenum, GLuint);
#define glBindBuffer oglBindBuffer
    GLAPI void(APIENTRY *oglBufferData)(GLenum, GLsizeiptr, const void *, GLenum);
#define glBufferData oglBufferData
    GLAPI void(APIENTRY *oglBufferSubData)(GLenum, GLintptr, GLsizeiptr, const void *);
#define glBufferSubData oglBufferSubData
    GLAPI void(APIENTRY *oglDeleteBuffers)(GLsizei, const GLuint *);
#define glDeleteBuffers oglDeleteBuffers
    GLAPI void(APIENTRY *oglDeleteQueries)(GLsizei, const GLuint *);
#define glDeleteQueries oglDeleteQueries
    GLAPI void(APIENTRY *oglEndQuery)(GLenum);
#define glEndQuery oglEndQuery
    GLAPI void(APIENTRY *oglGenBuffers)(GLsizei, GLuint *);
#define glGenBuffers oglGenBuffers
    GLAPI void(APIENTRY *oglGenQueries)(GLsizei, GLuint *);
#define glGenQueries oglGenQueries
    GLAPI void(APIENTRY *oglGetBufferParameteriv)(GLenum, GLenum, GLint *);
#define glGetBufferParameteriv oglGetBufferParameteriv
    GLAPI void(APIENTRY *oglGetBufferPointerv)(GLenum, GLenum, void **);
#define glGetBufferPointerv oglGetBufferPointerv
    GLAPI void(APIENTRY *oglGetBufferSubData)(GLenum, GLintptr, GLsizeiptr, void *);
#define glGetBufferSubData oglGetBufferSubData
    GLAPI void(APIENTRY *oglGetQueryObjectiv)(GLuint, GLenum, GLint *);
#define glGetQueryObjectiv oglGetQueryObjectiv
    GLAPI void(APIENTRY *oglGetQueryObjectuiv)(GLuint, GLenum, GLuint *);
#define glGetQueryObjectuiv oglGetQueryObjectuiv
    GLAPI void(APIENTRY *oglGetQueryiv)(GLenum, GLenum, GLint *);
#define glGetQueryiv oglGetQueryiv
    GLAPI GLboolean(APIENTRY *oglIsBuffer)(GLuint);
#define glIsBuffer oglIsBuffer
    GLAPI GLboolean(APIENTRY *oglIsQuery)(GLuint);
#define glIsQuery oglIsQuery
    GLAPI void *(APIENTRY *oglMapBuffer)(GLenum, GLenum);
#define glMapBuffer oglMapBuffer
    GLAPI GLboolean(APIENTRY *oglUnmapBuffer)(GLenum);
#define glUnmapBuffer oglUnmapBuffer

    /* GL_VERSION_2_0 */

    GLAPI void(APIENTRY *oglAttachShader)(GLuint, GLuint);
#define glAttachShader oglAttachShader
    GLAPI void(APIENTRY *oglBindAttribLocation)(GLuint, GLuint, const GLchar *);
#define glBindAttribLocation oglBindAttribLocation
    GLAPI void(APIENTRY *oglBlendEquationSeparate)(GLenum, GLenum);
#define glBlendEquationSeparate oglBlendEquationSeparate
    GLAPI void(APIENTRY *oglCompileShader)(GLuint);
#define glCompileShader oglCompileShader
    GLAPI GLuint(APIENTRY *oglCreateProgram)(void);
#define glCreateProgram oglCreateProgram
    GLAPI GLuint(APIENTRY *oglCreateShader)(GLenum);
#define glCreateShader oglCreateShader
    GLAPI void(APIENTRY *oglDeleteProgram)(GLuint);
#define glDeleteProgram oglDeleteProgram
    GLAPI void(APIENTRY *oglDeleteShader)(GLuint);
#define glDeleteShader oglDeleteShader
    GLAPI void(APIENTRY *oglDetachShader)(GLuint, GLuint);
#define glDetachShader oglDetachShader
    GLAPI void(APIENTRY *oglDisableVertexAttribArray)(GLuint);
#define glDisableVertexAttribArray oglDisableVertexAttribArray
    GLAPI void(APIENTRY *oglDrawBuffers)(GLsizei, const GLenum *);
#define glDrawBuffers oglDrawBuffers
    GLAPI void(APIENTRY *oglEnableVertexAttribArray)(GLuint);
#define glEnableVertexAttribArray oglEnableVertexAttribArray
    GLAPI void(APIENTRY *oglGetActiveAttrib)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
#define glGetActiveAttrib oglGetActiveAttrib
    GLAPI void(APIENTRY *oglGetActiveUniform)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
#define glGetActiveUniform oglGetActiveUniform
    GLAPI void(APIENTRY *oglGetAttachedShaders)(GLuint, GLsizei, GLsizei *, GLuint *);
#define glGetAttachedShaders oglGetAttachedShaders
    GLAPI GLint(APIENTRY *oglGetAttribLocation)(GLuint, const GLchar *);
#define glGetAttribLocation oglGetAttribLocation
    GLAPI void(APIENTRY *oglGetProgramInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetProgramInfoLog oglGetProgramInfoLog
    GLAPI void(APIENTRY *oglGetProgramiv)(GLuint, GLenum, GLint *);
#define glGetProgramiv oglGetProgramiv
    GLAPI void(APIENTRY *oglGetShaderInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetShaderInfoLog oglGetShaderInfoLog
    GLAPI void(APIENTRY *oglGetShaderSource)(GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetShaderSource oglGetShaderSource
    GLAPI void(APIENTRY *oglGetShaderiv)(GLuint, GLenum, GLint *);
#define glGetShaderiv oglGetShaderiv
    GLAPI GLint(APIENTRY *oglGetUniformLocation)(GLuint, const GLchar *);
#define glGetUniformLocation oglGetUniformLocation
    GLAPI void(APIENTRY *oglGetUniformfv)(GLuint, GLint, GLfloat *);
#define glGetUniformfv oglGetUniformfv
    GLAPI void(APIENTRY *oglGetUniformiv)(GLuint, GLint, GLint *);
#define glGetUniformiv oglGetUniformiv
    GLAPI void(APIENTRY *oglGetVertexAttribPointerv)(GLuint, GLenum, void **);
#define glGetVertexAttribPointerv oglGetVertexAttribPointerv
    GLAPI void(APIENTRY *oglGetVertexAttribdv)(GLuint, GLenum, GLdouble *);
#define glGetVertexAttribdv oglGetVertexAttribdv
    GLAPI void(APIENTRY *oglGetVertexAttribfv)(GLuint, GLenum, GLfloat *);
#define glGetVertexAttribfv oglGetVertexAttribfv
    GLAPI void(APIENTRY *oglGetVertexAttribiv)(GLuint, GLenum, GLint *);
#define glGetVertexAttribiv oglGetVertexAttribiv
    GLAPI GLboolean(APIENTRY *oglIsProgram)(GLuint);
#define glIsProgram oglIsProgram
    GLAPI GLboolean(APIENTRY *oglIsShader)(GLuint);
#define glIsShader oglIsShader
    GLAPI void(APIENTRY *oglLinkProgram)(GLuint);
#define glLinkProgram oglLinkProgram
    GLAPI void(APIENTRY *oglShaderSource)(GLuint, GLsizei, const GLchar *const*, const GLint *);
#define glShaderSource oglShaderSource
    GLAPI void(APIENTRY *oglStencilFuncSeparate)(GLenum, GLenum, GLint, GLuint);
#define glStencilFuncSeparate oglStencilFuncSeparate
    GLAPI void(APIENTRY *oglStencilMaskSeparate)(GLenum, GLuint);
#define glStencilMaskSeparate oglStencilMaskSeparate
    GLAPI void(APIENTRY *oglStencilOpSeparate)(GLenum, GLenum, GLenum, GLenum);
#define glStencilOpSeparate oglStencilOpSeparate
    GLAPI void(APIENTRY *oglUniform1f)(GLint, GLfloat);
#define glUniform1f oglUniform1f
    GLAPI void(APIENTRY *oglUniform1fv)(GLint, GLsizei, const GLfloat *);
#define glUniform1fv oglUniform1fv
    GLAPI void(APIENTRY *oglUniform1i)(GLint, GLint);
#define glUniform1i oglUniform1i
    GLAPI void(APIENTRY *oglUniform1iv)(GLint, GLsizei, const GLint *);
#define glUniform1iv oglUniform1iv
    GLAPI void(APIENTRY *oglUniform2f)(GLint, GLfloat, GLfloat);
#define glUniform2f oglUniform2f
    GLAPI void(APIENTRY *oglUniform2fv)(GLint, GLsizei, const GLfloat *);
#define glUniform2fv oglUniform2fv
    GLAPI void(APIENTRY *oglUniform2i)(GLint, GLint, GLint);
#define glUniform2i oglUniform2i
    GLAPI void(APIENTRY *oglUniform2iv)(GLint, GLsizei, const GLint *);
#define glUniform2iv oglUniform2iv
    GLAPI void(APIENTRY *oglUniform3f)(GLint, GLfloat, GLfloat, GLfloat);
#define glUniform3f oglUniform3f
    GLAPI void(APIENTRY *oglUniform3fv)(GLint, GLsizei, const GLfloat *);
#define glUniform3fv oglUniform3fv
    GLAPI void(APIENTRY *oglUniform3i)(GLint, GLint, GLint, GLint);
#define glUniform3i oglUniform3i
    GLAPI void(APIENTRY *oglUniform3iv)(GLint, GLsizei, const GLint *);
#define glUniform3iv oglUniform3iv
    GLAPI void(APIENTRY *oglUniform4f)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
#define glUniform4f oglUniform4f
    GLAPI void(APIENTRY *oglUniform4fv)(GLint, GLsizei, const GLfloat *);
#define glUniform4fv oglUniform4fv
    GLAPI void(APIENTRY *oglUniform4i)(GLint, GLint, GLint, GLint, GLint);
#define glUniform4i oglUniform4i
    GLAPI void(APIENTRY *oglUniform4iv)(GLint, GLsizei, const GLint *);
#define glUniform4iv oglUniform4iv
    GLAPI void(APIENTRY *oglUniformMatrix2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix2fv oglUniformMatrix2fv
    GLAPI void(APIENTRY *oglUniformMatrix3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix3fv oglUniformMatrix3fv
    GLAPI void(APIENTRY *oglUniformMatrix4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix4fv oglUniformMatrix4fv
    GLAPI void(APIENTRY *oglUseProgram)(GLuint);
#define glUseProgram oglUseProgram
    GLAPI void(APIENTRY *oglValidateProgram)(GLuint);
#define glValidateProgram oglValidateProgram
    GLAPI void(APIENTRY *oglVertexAttrib1d)(GLuint, GLdouble);
#define glVertexAttrib1d oglVertexAttrib1d
    GLAPI void(APIENTRY *oglVertexAttrib1dv)(GLuint, const GLdouble *);
#define glVertexAttrib1dv oglVertexAttrib1dv
    GLAPI void(APIENTRY *oglVertexAttrib1f)(GLuint, GLfloat);
#define glVertexAttrib1f oglVertexAttrib1f
    GLAPI void(APIENTRY *oglVertexAttrib1fv)(GLuint, const GLfloat *);
#define glVertexAttrib1fv oglVertexAttrib1fv
    GLAPI void(APIENTRY *oglVertexAttrib1s)(GLuint, GLshort);
#define glVertexAttrib1s oglVertexAttrib1s
    GLAPI void(APIENTRY *oglVertexAttrib1sv)(GLuint, const GLshort *);
#define glVertexAttrib1sv oglVertexAttrib1sv
    GLAPI void(APIENTRY *oglVertexAttrib2d)(GLuint, GLdouble, GLdouble);
#define glVertexAttrib2d oglVertexAttrib2d
    GLAPI void(APIENTRY *oglVertexAttrib2dv)(GLuint, const GLdouble *);
#define glVertexAttrib2dv oglVertexAttrib2dv
    GLAPI void(APIENTRY *oglVertexAttrib2f)(GLuint, GLfloat, GLfloat);
#define glVertexAttrib2f oglVertexAttrib2f
    GLAPI void(APIENTRY *oglVertexAttrib2fv)(GLuint, const GLfloat *);
#define glVertexAttrib2fv oglVertexAttrib2fv
    GLAPI void(APIENTRY *oglVertexAttrib2s)(GLuint, GLshort, GLshort);
#define glVertexAttrib2s oglVertexAttrib2s
    GLAPI void(APIENTRY *oglVertexAttrib2sv)(GLuint, const GLshort *);
#define glVertexAttrib2sv oglVertexAttrib2sv
    GLAPI void(APIENTRY *oglVertexAttrib3d)(GLuint, GLdouble, GLdouble, GLdouble);
#define glVertexAttrib3d oglVertexAttrib3d
    GLAPI void(APIENTRY *oglVertexAttrib3dv)(GLuint, const GLdouble *);
#define glVertexAttrib3dv oglVertexAttrib3dv
    GLAPI void(APIENTRY *oglVertexAttrib3f)(GLuint, GLfloat, GLfloat, GLfloat);
#define glVertexAttrib3f oglVertexAttrib3f
    GLAPI void(APIENTRY *oglVertexAttrib3fv)(GLuint, const GLfloat *);
#define glVertexAttrib3fv oglVertexAttrib3fv
    GLAPI void(APIENTRY *oglVertexAttrib3s)(GLuint, GLshort, GLshort, GLshort);
#define glVertexAttrib3s oglVertexAttrib3s
    GLAPI void(APIENTRY *oglVertexAttrib3sv)(GLuint, const GLshort *);
#define glVertexAttrib3sv oglVertexAttrib3sv
    GLAPI void(APIENTRY *oglVertexAttrib4Nbv)(GLuint, const GLbyte *);
#define glVertexAttrib4Nbv oglVertexAttrib4Nbv
    GLAPI void(APIENTRY *oglVertexAttrib4Niv)(GLuint, const GLint *);
#define glVertexAttrib4Niv oglVertexAttrib4Niv
    GLAPI void(APIENTRY *oglVertexAttrib4Nsv)(GLuint, const GLshort *);
#define glVertexAttrib4Nsv oglVertexAttrib4Nsv
    GLAPI void(APIENTRY *oglVertexAttrib4Nub)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
#define glVertexAttrib4Nub oglVertexAttrib4Nub
    GLAPI void(APIENTRY *oglVertexAttrib4Nubv)(GLuint, const GLubyte *);
#define glVertexAttrib4Nubv oglVertexAttrib4Nubv
    GLAPI void(APIENTRY *oglVertexAttrib4Nuiv)(GLuint, const GLuint *);
#define glVertexAttrib4Nuiv oglVertexAttrib4Nuiv
    GLAPI void(APIENTRY *oglVertexAttrib4Nusv)(GLuint, const GLushort *);
#define glVertexAttrib4Nusv oglVertexAttrib4Nusv
    GLAPI void(APIENTRY *oglVertexAttrib4bv)(GLuint, const GLbyte *);
#define glVertexAttrib4bv oglVertexAttrib4bv
    GLAPI void(APIENTRY *oglVertexAttrib4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
#define glVertexAttrib4d oglVertexAttrib4d
    GLAPI void(APIENTRY *oglVertexAttrib4dv)(GLuint, const GLdouble *);
#define glVertexAttrib4dv oglVertexAttrib4dv
    GLAPI void(APIENTRY *oglVertexAttrib4f)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
#define glVertexAttrib4f oglVertexAttrib4f
    GLAPI void(APIENTRY *oglVertexAttrib4fv)(GLuint, const GLfloat *);
#define glVertexAttrib4fv oglVertexAttrib4fv
    GLAPI void(APIENTRY *oglVertexAttrib4iv)(GLuint, const GLint *);
#define glVertexAttrib4iv oglVertexAttrib4iv
    GLAPI void(APIENTRY *oglVertexAttrib4s)(GLuint, GLshort, GLshort, GLshort, GLshort);
#define glVertexAttrib4s oglVertexAttrib4s
    GLAPI void(APIENTRY *oglVertexAttrib4sv)(GLuint, const GLshort *);
#define glVertexAttrib4sv oglVertexAttrib4sv
    GLAPI void(APIENTRY *oglVertexAttrib4ubv)(GLuint, const GLubyte *);
#define glVertexAttrib4ubv oglVertexAttrib4ubv
    GLAPI void(APIENTRY *oglVertexAttrib4uiv)(GLuint, const GLuint *);
#define glVertexAttrib4uiv oglVertexAttrib4uiv
    GLAPI void(APIENTRY *oglVertexAttrib4usv)(GLuint, const GLushort *);
#define glVertexAttrib4usv oglVertexAttrib4usv
    GLAPI void(APIENTRY *oglVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
#define glVertexAttribPointer oglVertexAttribPointer

    /* GL_VERSION_2_1 */

    GLAPI void(APIENTRY *oglUniformMatrix2x3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix2x3fv oglUniformMatrix2x3fv
    GLAPI void(APIENTRY *oglUniformMatrix2x4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix2x4fv oglUniformMatrix2x4fv
    GLAPI void(APIENTRY *oglUniformMatrix3x2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix3x2fv oglUniformMatrix3x2fv
    GLAPI void(APIENTRY *oglUniformMatrix3x4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix3x4fv oglUniformMatrix3x4fv
    GLAPI void(APIENTRY *oglUniformMatrix4x2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix4x2fv oglUniformMatrix4x2fv
    GLAPI void(APIENTRY *oglUniformMatrix4x3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix4x3fv oglUniformMatrix4x3fv

    /* GL_VERSION_3_0 */

    GLAPI void(APIENTRY *oglBeginConditionalRender)(GLuint, GLenum);
#define glBeginConditionalRender oglBeginConditionalRender
    GLAPI void(APIENTRY *oglBeginTransformFeedback)(GLenum);
#define glBeginTransformFeedback oglBeginTransformFeedback
    GLAPI void(APIENTRY *oglBindBufferBase)(GLenum, GLuint, GLuint);
#define glBindBufferBase oglBindBufferBase
    GLAPI void(APIENTRY *oglBindBufferRange)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
#define glBindBufferRange oglBindBufferRange
    GLAPI void(APIENTRY *oglBindFragDataLocation)(GLuint, GLuint, const GLchar *);
#define glBindFragDataLocation oglBindFragDataLocation
    GLAPI void(APIENTRY *oglBindFramebuffer)(GLenum, GLuint);
#define glBindFramebuffer oglBindFramebuffer
    GLAPI void(APIENTRY *oglBindRenderbuffer)(GLenum, GLuint);
#define glBindRenderbuffer oglBindRenderbuffer
    GLAPI void(APIENTRY *oglBindVertexArray)(GLuint);
#define glBindVertexArray oglBindVertexArray
    GLAPI void(APIENTRY *oglBlitFramebuffer)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
#define glBlitFramebuffer oglBlitFramebuffer
    GLAPI GLenum(APIENTRY *oglCheckFramebufferStatus)(GLenum);
#define glCheckFramebufferStatus oglCheckFramebufferStatus
    GLAPI void(APIENTRY *oglClampColor)(GLenum, GLenum);
#define glClampColor oglClampColor
    GLAPI void(APIENTRY *oglClearBufferfi)(GLenum, GLint, GLfloat, GLint);
#define glClearBufferfi oglClearBufferfi
    GLAPI void(APIENTRY *oglClearBufferfv)(GLenum, GLint, const GLfloat *);
#define glClearBufferfv oglClearBufferfv
    GLAPI void(APIENTRY *oglClearBufferiv)(GLenum, GLint, const GLint *);
#define glClearBufferiv oglClearBufferiv
    GLAPI void(APIENTRY *oglClearBufferuiv)(GLenum, GLint, const GLuint *);
#define glClearBufferuiv oglClearBufferuiv
    GLAPI void(APIENTRY *oglColorMaski)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
#define glColorMaski oglColorMaski
    GLAPI void(APIENTRY *oglDeleteFramebuffers)(GLsizei, const GLuint *);
#define glDeleteFramebuffers oglDeleteFramebuffers
    GLAPI void(APIENTRY *oglDeleteRenderbuffers)(GLsizei, const GLuint *);
#define glDeleteRenderbuffers oglDeleteRenderbuffers
    GLAPI void(APIENTRY *oglDeleteVertexArrays)(GLsizei, const GLuint *);
#define glDeleteVertexArrays oglDeleteVertexArrays
    GLAPI void(APIENTRY *oglDisablei)(GLenum, GLuint);
#define glDisablei oglDisablei
    GLAPI void(APIENTRY *oglEnablei)(GLenum, GLuint);
#define glEnablei oglEnablei
    GLAPI void(APIENTRY *oglEndConditionalRender)(void);
#define glEndConditionalRender oglEndConditionalRender
    GLAPI void(APIENTRY *oglEndTransformFeedback)(void);
#define glEndTransformFeedback oglEndTransformFeedback
    GLAPI void(APIENTRY *oglFlushMappedBufferRange)(GLenum, GLintptr, GLsizeiptr);
#define glFlushMappedBufferRange oglFlushMappedBufferRange
    GLAPI void(APIENTRY *oglFramebufferRenderbuffer)(GLenum, GLenum, GLenum, GLuint);
#define glFramebufferRenderbuffer oglFramebufferRenderbuffer
    GLAPI void(APIENTRY *oglFramebufferTexture1D)(GLenum, GLenum, GLenum, GLuint, GLint);
#define glFramebufferTexture1D oglFramebufferTexture1D
    GLAPI void(APIENTRY *oglFramebufferTexture2D)(GLenum, GLenum, GLenum, GLuint, GLint);
#define glFramebufferTexture2D oglFramebufferTexture2D
    GLAPI void(APIENTRY *oglFramebufferTexture3D)(GLenum, GLenum, GLenum, GLuint, GLint, GLint);
#define glFramebufferTexture3D oglFramebufferTexture3D
    GLAPI void(APIENTRY *oglFramebufferTextureLayer)(GLenum, GLenum, GLuint, GLint, GLint);
#define glFramebufferTextureLayer oglFramebufferTextureLayer
    GLAPI void(APIENTRY *oglGenFramebuffers)(GLsizei, GLuint *);
#define glGenFramebuffers oglGenFramebuffers
    GLAPI void(APIENTRY *oglGenRenderbuffers)(GLsizei, GLuint *);
#define glGenRenderbuffers oglGenRenderbuffers
    GLAPI void(APIENTRY *oglGenVertexArrays)(GLsizei, GLuint *);
#define glGenVertexArrays oglGenVertexArrays
    GLAPI void(APIENTRY *oglGenerateMipmap)(GLenum);
#define glGenerateMipmap oglGenerateMipmap
    GLAPI void(APIENTRY *oglGetBooleani_v)(GLenum, GLuint, GLboolean *);
#define glGetBooleani_v oglGetBooleani_v
    GLAPI GLint(APIENTRY *oglGetFragDataLocation)(GLuint, const GLchar *);
#define glGetFragDataLocation oglGetFragDataLocation
    GLAPI void(APIENTRY *oglGetFramebufferAttachmentParameteriv)(GLenum, GLenum, GLenum, GLint *);
#define glGetFramebufferAttachmentParameteriv oglGetFramebufferAttachmentParameteriv
    GLAPI void(APIENTRY *oglGetIntegeri_v)(GLenum, GLuint, GLint *);
#define glGetIntegeri_v oglGetIntegeri_v
    GLAPI void(APIENTRY *oglGetRenderbufferParameteriv)(GLenum, GLenum, GLint *);
#define glGetRenderbufferParameteriv oglGetRenderbufferParameteriv
    GLAPI const GLubyte *(APIENTRY *oglGetStringi)(GLenum, GLuint);
#define glGetStringi oglGetStringi
    GLAPI void(APIENTRY *oglGetTexParameterIiv)(GLenum, GLenum, GLint *);
#define glGetTexParameterIiv oglGetTexParameterIiv
    GLAPI void(APIENTRY *oglGetTexParameterIuiv)(GLenum, GLenum, GLuint *);
#define glGetTexParameterIuiv oglGetTexParameterIuiv
    GLAPI void(APIENTRY *oglGetTransformFeedbackVarying)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *);
#define glGetTransformFeedbackVarying oglGetTransformFeedbackVarying
    GLAPI void(APIENTRY *oglGetUniformuiv)(GLuint, GLint, GLuint *);
#define glGetUniformuiv oglGetUniformuiv
    GLAPI void(APIENTRY *oglGetVertexAttribIiv)(GLuint, GLenum, GLint *);
#define glGetVertexAttribIiv oglGetVertexAttribIiv
    GLAPI void(APIENTRY *oglGetVertexAttribIuiv)(GLuint, GLenum, GLuint *);
#define glGetVertexAttribIuiv oglGetVertexAttribIuiv
    GLAPI GLboolean(APIENTRY *oglIsEnabledi)(GLenum, GLuint);
#define glIsEnabledi oglIsEnabledi
    GLAPI GLboolean(APIENTRY *oglIsFramebuffer)(GLuint);
#define glIsFramebuffer oglIsFramebuffer
    GLAPI GLboolean(APIENTRY *oglIsRenderbuffer)(GLuint);
#define glIsRenderbuffer oglIsRenderbuffer
    GLAPI GLboolean(APIENTRY *oglIsVertexArray)(GLuint);
#define glIsVertexArray oglIsVertexArray
    GLAPI void *(APIENTRY *oglMapBufferRange)(GLenum, GLintptr, GLsizeiptr, GLbitfield);
#define glMapBufferRange oglMapBufferRange
    GLAPI void(APIENTRY *oglRenderbufferStorage)(GLenum, GLenum, GLsizei, GLsizei);
#define glRenderbufferStorage oglRenderbufferStorage
    GLAPI void(APIENTRY *oglRenderbufferStorageMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
#define glRenderbufferStorageMultisample oglRenderbufferStorageMultisample
    GLAPI void(APIENTRY *oglTexParameterIiv)(GLenum, GLenum, const GLint *);
#define glTexParameterIiv oglTexParameterIiv
    GLAPI void(APIENTRY *oglTexParameterIuiv)(GLenum, GLenum, const GLuint *);
#define glTexParameterIuiv oglTexParameterIuiv
    GLAPI void(APIENTRY *oglTransformFeedbackVaryings)(GLuint, GLsizei, const GLchar *const*, GLenum);
#define glTransformFeedbackVaryings oglTransformFeedbackVaryings
    GLAPI void(APIENTRY *oglUniform1ui)(GLint, GLuint);
#define glUniform1ui oglUniform1ui
    GLAPI void(APIENTRY *oglUniform1uiv)(GLint, GLsizei, const GLuint *);
#define glUniform1uiv oglUniform1uiv
    GLAPI void(APIENTRY *oglUniform2ui)(GLint, GLuint, GLuint);
#define glUniform2ui oglUniform2ui
    GLAPI void(APIENTRY *oglUniform2uiv)(GLint, GLsizei, const GLuint *);
#define glUniform2uiv oglUniform2uiv
    GLAPI void(APIENTRY *oglUniform3ui)(GLint, GLuint, GLuint, GLuint);
#define glUniform3ui oglUniform3ui
    GLAPI void(APIENTRY *oglUniform3uiv)(GLint, GLsizei, const GLuint *);
#define glUniform3uiv oglUniform3uiv
    GLAPI void(APIENTRY *oglUniform4ui)(GLint, GLuint, GLuint, GLuint, GLuint);
#define glUniform4ui oglUniform4ui
    GLAPI void(APIENTRY *oglUniform4uiv)(GLint, GLsizei, const GLuint *);
#define glUniform4uiv oglUniform4uiv
    GLAPI void(APIENTRY *oglVertexAttribI1i)(GLuint, GLint);
#define glVertexAttribI1i oglVertexAttribI1i
    GLAPI void(APIENTRY *oglVertexAttribI1iv)(GLuint, const GLint *);
#define glVertexAttribI1iv oglVertexAttribI1iv
    GLAPI void(APIENTRY *oglVertexAttribI1ui)(GLuint, GLuint);
#define glVertexAttribI1ui oglVertexAttribI1ui
    GLAPI void(APIENTRY *oglVertexAttribI1uiv)(GLuint, const GLuint *);
#define glVertexAttribI1uiv oglVertexAttribI1uiv
    GLAPI void(APIENTRY *oglVertexAttribI2i)(GLuint, GLint, GLint);
#define glVertexAttribI2i oglVertexAttribI2i
    GLAPI void(APIENTRY *oglVertexAttribI2iv)(GLuint, const GLint *);
#define glVertexAttribI2iv oglVertexAttribI2iv
    GLAPI void(APIENTRY *oglVertexAttribI2ui)(GLuint, GLuint, GLuint);
#define glVertexAttribI2ui oglVertexAttribI2ui
    GLAPI void(APIENTRY *oglVertexAttribI2uiv)(GLuint, const GLuint *);
#define glVertexAttribI2uiv oglVertexAttribI2uiv
    GLAPI void(APIENTRY *oglVertexAttribI3i)(GLuint, GLint, GLint, GLint);
#define glVertexAttribI3i oglVertexAttribI3i
    GLAPI void(APIENTRY *oglVertexAttribI3iv)(GLuint, const GLint *);
#define glVertexAttribI3iv oglVertexAttribI3iv
    GLAPI void(APIENTRY *oglVertexAttribI3ui)(GLuint, GLuint, GLuint, GLuint);
#define glVertexAttribI3ui oglVertexAttribI3ui
    GLAPI void(APIENTRY *oglVertexAttribI3uiv)(GLuint, const GLuint *);
#define glVertexAttribI3uiv oglVertexAttribI3uiv
    GLAPI void(APIENTRY *oglVertexAttribI4bv)(GLuint, const GLbyte *);
#define glVertexAttribI4bv oglVertexAttribI4bv
    GLAPI void(APIENTRY *oglVertexAttribI4i)(GLuint, GLint, GLint, GLint, GLint);
#define glVertexAttribI4i oglVertexAttribI4i
    GLAPI void(APIENTRY *oglVertexAttribI4iv)(GLuint, const GLint *);
#define glVertexAttribI4iv oglVertexAttribI4iv
    GLAPI void(APIENTRY *oglVertexAttribI4sv)(GLuint, const GLshort *);
#define glVertexAttribI4sv oglVertexAttribI4sv
    GLAPI void(APIENTRY *oglVertexAttribI4ubv)(GLuint, const GLubyte *);
#define glVertexAttribI4ubv oglVertexAttribI4ubv
    GLAPI void(APIENTRY *oglVertexAttribI4ui)(GLuint, GLuint, GLuint, GLuint, GLuint);
#define glVertexAttribI4ui oglVertexAttribI4ui
    GLAPI void(APIENTRY *oglVertexAttribI4uiv)(GLuint, const GLuint *);
#define glVertexAttribI4uiv oglVertexAttribI4uiv
    GLAPI void(APIENTRY *oglVertexAttribI4usv)(GLuint, const GLushort *);
#define glVertexAttribI4usv oglVertexAttribI4usv
    GLAPI void(APIENTRY *oglVertexAttribIPointer)(GLuint, GLint, GLenum, GLsizei, const void *);
#define glVertexAttribIPointer oglVertexAttribIPointer

    /* GL_VERSION_3_1 */

    GLAPI void(APIENTRY *oglCopyBufferSubData)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
#define glCopyBufferSubData oglCopyBufferSubData
    GLAPI void(APIENTRY *oglDrawArraysInstanced)(GLenum, GLint, GLsizei, GLsizei);
#define glDrawArraysInstanced oglDrawArraysInstanced
    GLAPI void(APIENTRY *oglDrawElementsInstanced)(GLenum, GLsizei, GLenum, const void *, GLsizei);
#define glDrawElementsInstanced oglDrawElementsInstanced
    GLAPI void(APIENTRY *oglGetActiveUniformBlockName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveUniformBlockName oglGetActiveUniformBlockName
    GLAPI void(APIENTRY *oglGetActiveUniformBlockiv)(GLuint, GLuint, GLenum, GLint *);
#define glGetActiveUniformBlockiv oglGetActiveUniformBlockiv
    GLAPI void(APIENTRY *oglGetActiveUniformName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveUniformName oglGetActiveUniformName
    GLAPI void(APIENTRY *oglGetActiveUniformsiv)(GLuint, GLsizei, const GLuint *, GLenum, GLint *);
#define glGetActiveUniformsiv oglGetActiveUniformsiv
    GLAPI GLuint(APIENTRY *oglGetUniformBlockIndex)(GLuint, const GLchar *);
#define glGetUniformBlockIndex oglGetUniformBlockIndex
    GLAPI void(APIENTRY *oglGetUniformIndices)(GLuint, GLsizei, const GLchar *const*, GLuint *);
#define glGetUniformIndices oglGetUniformIndices
    GLAPI void(APIENTRY *oglPrimitiveRestartIndex)(GLuint);
#define glPrimitiveRestartIndex oglPrimitiveRestartIndex
    GLAPI void(APIENTRY *oglTexBuffer)(GLenum, GLenum, GLuint);
#define glTexBuffer oglTexBuffer
    GLAPI void(APIENTRY *oglUniformBlockBinding)(GLuint, GLuint, GLuint);
#define glUniformBlockBinding oglUniformBlockBinding

    /* GL_VERSION_3_2 */

    GLAPI GLenum(APIENTRY *oglClientWaitSync)(GLsync, GLbitfield, GLuint64);
#define glClientWaitSync oglClientWaitSync
    GLAPI void(APIENTRY *oglDeleteSync)(GLsync);
#define glDeleteSync oglDeleteSync
    GLAPI void(APIENTRY *oglDrawElementsBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLint);
#define glDrawElementsBaseVertex oglDrawElementsBaseVertex
    GLAPI void(APIENTRY *oglDrawElementsInstancedBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint);
#define glDrawElementsInstancedBaseVertex oglDrawElementsInstancedBaseVertex
    GLAPI void(APIENTRY *oglDrawRangeElementsBaseVertex)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint);
#define glDrawRangeElementsBaseVertex oglDrawRangeElementsBaseVertex
    GLAPI GLsync(APIENTRY *oglFenceSync)(GLenum, GLbitfield);
#define glFenceSync oglFenceSync
    GLAPI void(APIENTRY *oglFramebufferTexture)(GLenum, GLenum, GLuint, GLint);
#define glFramebufferTexture oglFramebufferTexture
    GLAPI void(APIENTRY *oglGetBufferParameteri64v)(GLenum, GLenum, GLint64 *);
#define glGetBufferParameteri64v oglGetBufferParameteri64v
    GLAPI void(APIENTRY *oglGetInteger64i_v)(GLenum, GLuint, GLint64 *);
#define glGetInteger64i_v oglGetInteger64i_v
    GLAPI void(APIENTRY *oglGetInteger64v)(GLenum, GLint64 *);
#define glGetInteger64v oglGetInteger64v
    GLAPI void(APIENTRY *oglGetMultisamplefv)(GLenum, GLuint, GLfloat *);
#define glGetMultisamplefv oglGetMultisamplefv
    GLAPI void(APIENTRY *oglGetSynciv)(GLsync, GLenum, GLsizei, GLsizei *, GLint *);
#define glGetSynciv oglGetSynciv
    GLAPI GLboolean(APIENTRY *oglIsSync)(GLsync);
#define glIsSync oglIsSync
    GLAPI void(APIENTRY *oglMultiDrawElementsBaseVertex)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *);
#define glMultiDrawElementsBaseVertex oglMultiDrawElementsBaseVertex
    GLAPI void(APIENTRY *oglProvokingVertex)(GLenum);
#define glProvokingVertex oglProvokingVertex
    GLAPI void(APIENTRY *oglSampleMaski)(GLuint, GLbitfield);
#define glSampleMaski oglSampleMaski
    GLAPI void(APIENTRY *oglTexImage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
#define glTexImage2DMultisample oglTexImage2DMultisample
    GLAPI void(APIENTRY *oglTexImage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
#define glTexImage3DMultisample oglTexImage3DMultisample
    GLAPI void(APIENTRY *oglWaitSync)(GLsync, GLbitfield, GLuint64);
#define glWaitSync oglWaitSync

    /* GL_VERSION_3_3 */

    GLAPI void(APIENTRY *oglBindFragDataLocationIndexed)(GLuint, GLuint, GLuint, const GLchar *);
#define glBindFragDataLocationIndexed oglBindFragDataLocationIndexed
    GLAPI void(APIENTRY *oglBindSampler)(GLuint, GLuint);
#define glBindSampler oglBindSampler
    GLAPI void(APIENTRY *oglDeleteSamplers)(GLsizei, const GLuint *);
#define glDeleteSamplers oglDeleteSamplers
    GLAPI void(APIENTRY *oglGenSamplers)(GLsizei, GLuint *);
#define glGenSamplers oglGenSamplers
    GLAPI GLint(APIENTRY *oglGetFragDataIndex)(GLuint, const GLchar *);
#define glGetFragDataIndex oglGetFragDataIndex
    GLAPI void(APIENTRY *oglGetQueryObjecti64v)(GLuint, GLenum, GLint64 *);
#define glGetQueryObjecti64v oglGetQueryObjecti64v
    GLAPI void(APIENTRY *oglGetQueryObjectui64v)(GLuint, GLenum, GLuint64 *);
#define glGetQueryObjectui64v oglGetQueryObjectui64v
    GLAPI void(APIENTRY *oglGetSamplerParameterIiv)(GLuint, GLenum, GLint *);
#define glGetSamplerParameterIiv oglGetSamplerParameterIiv
    GLAPI void(APIENTRY *oglGetSamplerParameterIuiv)(GLuint, GLenum, GLuint *);
#define glGetSamplerParameterIuiv oglGetSamplerParameterIuiv
    GLAPI void(APIENTRY *oglGetSamplerParameterfv)(GLuint, GLenum, GLfloat *);
#define glGetSamplerParameterfv oglGetSamplerParameterfv
    GLAPI void(APIENTRY *oglGetSamplerParameteriv)(GLuint, GLenum, GLint *);
#define glGetSamplerParameteriv oglGetSamplerParameteriv
    GLAPI GLboolean(APIENTRY *oglIsSampler)(GLuint);
#define glIsSampler oglIsSampler
    GLAPI void(APIENTRY *oglQueryCounter)(GLuint, GLenum);
#define glQueryCounter oglQueryCounter
    GLAPI void(APIENTRY *oglSamplerParameterIiv)(GLuint, GLenum, const GLint *);
#define glSamplerParameterIiv oglSamplerParameterIiv
    GLAPI void(APIENTRY *oglSamplerParameterIuiv)(GLuint, GLenum, const GLuint *);
#define glSamplerParameterIuiv oglSamplerParameterIuiv
    GLAPI void(APIENTRY *oglSamplerParameterf)(GLuint, GLenum, GLfloat);
#define glSamplerParameterf oglSamplerParameterf
    GLAPI void(APIENTRY *oglSamplerParameterfv)(GLuint, GLenum, const GLfloat *);
#define glSamplerParameterfv oglSamplerParameterfv
    GLAPI void(APIENTRY *oglSamplerParameteri)(GLuint, GLenum, GLint);
#define glSamplerParameteri oglSamplerParameteri
    GLAPI void(APIENTRY *oglSamplerParameteriv)(GLuint, GLenum, const GLint *);
#define glSamplerParameteriv oglSamplerParameteriv
    GLAPI void(APIENTRY *oglVertexAttribDivisor)(GLuint, GLuint);
#define glVertexAttribDivisor oglVertexAttribDivisor
    GLAPI void(APIENTRY *oglVertexAttribP1ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP1ui oglVertexAttribP1ui
    GLAPI void(APIENTRY *oglVertexAttribP1uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#define glVertexAttribP1uiv oglVertexAttribP1uiv
    GLAPI void(APIENTRY *oglVertexAttribP2ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP2ui oglVertexAttribP2ui
    GLAPI void(APIENTRY *oglVertexAttribP2uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#define glVertexAttribP2uiv oglVertexAttribP2uiv
    GLAPI void(APIENTRY *oglVertexAttribP3ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP3ui oglVertexAttribP3ui
    GLAPI void(APIENTRY *oglVertexAttribP3uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#define glVertexAttribP3uiv oglVertexAttribP3uiv
    GLAPI void(APIENTRY *oglVertexAttribP4ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP4ui oglVertexAttribP4ui
    GLAPI void(APIENTRY *oglVertexAttribP4uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#define glVertexAttribP4uiv oglVertexAttribP4uiv

    /* GL_VERSION_4_0 */

    GLAPI void(APIENTRY *oglBeginQueryIndexed)(GLenum, GLuint, GLuint);
#define glBeginQueryIndexed oglBeginQueryIndexed
    GLAPI void(APIENTRY *oglBindTransformFeedback)(GLenum, GLuint);
#define glBindTransformFeedback oglBindTransformFeedback
    GLAPI void(APIENTRY *oglBlendEquationSeparatei)(GLuint, GLenum, GLenum);
#define glBlendEquationSeparatei oglBlendEquationSeparatei
    GLAPI void(APIENTRY *oglBlendEquationi)(GLuint, GLenum);
#define glBlendEquationi oglBlendEquationi
    GLAPI void(APIENTRY *oglBlendFuncSeparatei)(GLuint, GLenum, GLenum, GLenum, GLenum);
#define glBlendFuncSeparatei oglBlendFuncSeparatei
    GLAPI void(APIENTRY *oglBlendFunci)(GLuint, GLenum, GLenum);
#define glBlendFunci oglBlendFunci
    GLAPI void(APIENTRY *oglDeleteTransformFeedbacks)(GLsizei, const GLuint *);
#define glDeleteTransformFeedbacks oglDeleteTransformFeedbacks
    GLAPI void(APIENTRY *oglDrawArraysIndirect)(GLenum, const void *);
#define glDrawArraysIndirect oglDrawArraysIndirect
    GLAPI void(APIENTRY *oglDrawElementsIndirect)(GLenum, GLenum, const void *);
#define glDrawElementsIndirect oglDrawElementsIndirect
    GLAPI void(APIENTRY *oglDrawTransformFeedback)(GLenum, GLuint);
#define glDrawTransformFeedback oglDrawTransformFeedback
    GLAPI void(APIENTRY *oglDrawTransformFeedbackStream)(GLenum, GLuint, GLuint);
#define glDrawTransformFeedbackStream oglDrawTransformFeedbackStream
    GLAPI void(APIENTRY *oglEndQueryIndexed)(GLenum, GLuint);
#define glEndQueryIndexed oglEndQueryIndexed
    GLAPI void(APIENTRY *oglGenTransformFeedbacks)(GLsizei, GLuint *);
#define glGenTransformFeedbacks oglGenTransformFeedbacks
    GLAPI void(APIENTRY *oglGetActiveSubroutineName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveSubroutineName oglGetActiveSubroutineName
    GLAPI void(APIENTRY *oglGetActiveSubroutineUniformName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveSubroutineUniformName oglGetActiveSubroutineUniformName
    GLAPI void(APIENTRY *oglGetActiveSubroutineUniformiv)(GLuint, GLenum, GLuint, GLenum, GLint *);
#define glGetActiveSubroutineUniformiv oglGetActiveSubroutineUniformiv
    GLAPI void(APIENTRY *oglGetProgramStageiv)(GLuint, GLenum, GLenum, GLint *);
#define glGetProgramStageiv oglGetProgramStageiv
    GLAPI void(APIENTRY *oglGetQueryIndexediv)(GLenum, GLuint, GLenum, GLint *);
#define glGetQueryIndexediv oglGetQueryIndexediv
    GLAPI GLuint(APIENTRY *oglGetSubroutineIndex)(GLuint, GLenum, const GLchar *);
#define glGetSubroutineIndex oglGetSubroutineIndex
    GLAPI GLint(APIENTRY *oglGetSubroutineUniformLocation)(GLuint, GLenum, const GLchar *);
#define glGetSubroutineUniformLocation oglGetSubroutineUniformLocation
    GLAPI void(APIENTRY *oglGetUniformSubroutineuiv)(GLenum, GLint, GLuint *);
#define glGetUniformSubroutineuiv oglGetUniformSubroutineuiv
    GLAPI void(APIENTRY *oglGetUniformdv)(GLuint, GLint, GLdouble *);
#define glGetUniformdv oglGetUniformdv
    GLAPI GLboolean(APIENTRY *oglIsTransformFeedback)(GLuint);
#define glIsTransformFeedback oglIsTransformFeedback
    GLAPI void(APIENTRY *oglMinSampleShading)(GLfloat);
#define glMinSampleShading oglMinSampleShading
    GLAPI void(APIENTRY *oglPatchParameterfv)(GLenum, const GLfloat *);
#define glPatchParameterfv oglPatchParameterfv
    GLAPI void(APIENTRY *oglPatchParameteri)(GLenum, GLint);
#define glPatchParameteri oglPatchParameteri
    GLAPI void(APIENTRY *oglPauseTransformFeedback)(void);
#define glPauseTransformFeedback oglPauseTransformFeedback
    GLAPI void(APIENTRY *oglResumeTransformFeedback)(void);
#define glResumeTransformFeedback oglResumeTransformFeedback
    GLAPI void(APIENTRY *oglUniform1d)(GLint, GLdouble);
#define glUniform1d oglUniform1d
    GLAPI void(APIENTRY *oglUniform1dv)(GLint, GLsizei, const GLdouble *);
#define glUniform1dv oglUniform1dv
    GLAPI void(APIENTRY *oglUniform2d)(GLint, GLdouble, GLdouble);
#define glUniform2d oglUniform2d
    GLAPI void(APIENTRY *oglUniform2dv)(GLint, GLsizei, const GLdouble *);
#define glUniform2dv oglUniform2dv
    GLAPI void(APIENTRY *oglUniform3d)(GLint, GLdouble, GLdouble, GLdouble);
#define glUniform3d oglUniform3d
    GLAPI void(APIENTRY *oglUniform3dv)(GLint, GLsizei, const GLdouble *);
#define glUniform3dv oglUniform3dv
    GLAPI void(APIENTRY *oglUniform4d)(GLint, GLdouble, GLdouble, GLdouble, GLdouble);
#define glUniform4d oglUniform4d
    GLAPI void(APIENTRY *oglUniform4dv)(GLint, GLsizei, const GLdouble *);
#define glUniform4dv oglUniform4dv
    GLAPI void(APIENTRY *oglUniformMatrix2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix2dv oglUniformMatrix2dv
    GLAPI void(APIENTRY *oglUniformMatrix2x3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix2x3dv oglUniformMatrix2x3dv
    GLAPI void(APIENTRY *oglUniformMatrix2x4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix2x4dv oglUniformMatrix2x4dv
    GLAPI void(APIENTRY *oglUniformMatrix3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix3dv oglUniformMatrix3dv
    GLAPI void(APIENTRY *oglUniformMatrix3x2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix3x2dv oglUniformMatrix3x2dv
    GLAPI void(APIENTRY *oglUniformMatrix3x4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix3x4dv oglUniformMatrix3x4dv
    GLAPI void(APIENTRY *oglUniformMatrix4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix4dv oglUniformMatrix4dv
    GLAPI void(APIENTRY *oglUniformMatrix4x2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix4x2dv oglUniformMatrix4x2dv
    GLAPI void(APIENTRY *oglUniformMatrix4x3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix4x3dv oglUniformMatrix4x3dv
    GLAPI void(APIENTRY *oglUniformSubroutinesuiv)(GLenum, GLsizei, const GLuint *);
#define glUniformSubroutinesuiv oglUniformSubroutinesuiv

    /* GL_VERSION_4_1 */

    GLAPI void(APIENTRY *oglActiveShaderProgram)(GLuint, GLuint);
#define glActiveShaderProgram oglActiveShaderProgram
    GLAPI void(APIENTRY *oglBindProgramPipeline)(GLuint);
#define glBindProgramPipeline oglBindProgramPipeline
    GLAPI void(APIENTRY *oglClearDepthf)(GLfloat);
#define glClearDepthf oglClearDepthf
    GLAPI GLuint(APIENTRY *oglCreateShaderProgramv)(GLenum, GLsizei, const GLchar *const*);
#define glCreateShaderProgramv oglCreateShaderProgramv
    GLAPI void(APIENTRY *oglDeleteProgramPipelines)(GLsizei, const GLuint *);
#define glDeleteProgramPipelines oglDeleteProgramPipelines
    GLAPI void(APIENTRY *oglDepthRangeArrayv)(GLuint, GLsizei, const GLdouble *);
#define glDepthRangeArrayv oglDepthRangeArrayv
    GLAPI void(APIENTRY *oglDepthRangeIndexed)(GLuint, GLdouble, GLdouble);
#define glDepthRangeIndexed oglDepthRangeIndexed
    GLAPI void(APIENTRY *oglDepthRangef)(GLfloat, GLfloat);
#define glDepthRangef oglDepthRangef
    GLAPI void(APIENTRY *oglGenProgramPipelines)(GLsizei, GLuint *);
#define glGenProgramPipelines oglGenProgramPipelines
    GLAPI void(APIENTRY *oglGetDoublei_v)(GLenum, GLuint, GLdouble *);
#define glGetDoublei_v oglGetDoublei_v
    GLAPI void(APIENTRY *oglGetFloati_v)(GLenum, GLuint, GLfloat *);
#define glGetFloati_v oglGetFloati_v
    GLAPI void(APIENTRY *oglGetProgramBinary)(GLuint, GLsizei, GLsizei *, GLenum *, void *);
#define glGetProgramBinary oglGetProgramBinary
    GLAPI void(APIENTRY *oglGetProgramPipelineInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetProgramPipelineInfoLog oglGetProgramPipelineInfoLog
    GLAPI void(APIENTRY *oglGetProgramPipelineiv)(GLuint, GLenum, GLint *);
#define glGetProgramPipelineiv oglGetProgramPipelineiv
    GLAPI void(APIENTRY *oglGetShaderPrecisionFormat)(GLenum, GLenum, GLint *, GLint *);
#define glGetShaderPrecisionFormat oglGetShaderPrecisionFormat
    GLAPI void(APIENTRY *oglGetVertexAttribLdv)(GLuint, GLenum, GLdouble *);
#define glGetVertexAttribLdv oglGetVertexAttribLdv
    GLAPI GLboolean(APIENTRY *oglIsProgramPipeline)(GLuint);
#define glIsProgramPipeline oglIsProgramPipeline
    GLAPI void(APIENTRY *oglProgramBinary)(GLuint, GLenum, const void *, GLsizei);
#define glProgramBinary oglProgramBinary
    GLAPI void(APIENTRY *oglProgramParameteri)(GLuint, GLenum, GLint);
#define glProgramParameteri oglProgramParameteri
    GLAPI void(APIENTRY *oglProgramUniform1d)(GLuint, GLint, GLdouble);
#define glProgramUniform1d oglProgramUniform1d
    GLAPI void(APIENTRY *oglProgramUniform1dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform1dv oglProgramUniform1dv
    GLAPI void(APIENTRY *oglProgramUniform1f)(GLuint, GLint, GLfloat);
#define glProgramUniform1f oglProgramUniform1f
    GLAPI void(APIENTRY *oglProgramUniform1fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform1fv oglProgramUniform1fv
    GLAPI void(APIENTRY *oglProgramUniform1i)(GLuint, GLint, GLint);
#define glProgramUniform1i oglProgramUniform1i
    GLAPI void(APIENTRY *oglProgramUniform1iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform1iv oglProgramUniform1iv
    GLAPI void(APIENTRY *oglProgramUniform1ui)(GLuint, GLint, GLuint);
#define glProgramUniform1ui oglProgramUniform1ui
    GLAPI void(APIENTRY *oglProgramUniform1uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniform1uiv oglProgramUniform1uiv
    GLAPI void(APIENTRY *oglProgramUniform2d)(GLuint, GLint, GLdouble, GLdouble);
#define glProgramUniform2d oglProgramUniform2d
    GLAPI void(APIENTRY *oglProgramUniform2dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform2dv oglProgramUniform2dv
    GLAPI void(APIENTRY *oglProgramUniform2f)(GLuint, GLint, GLfloat, GLfloat);
#define glProgramUniform2f oglProgramUniform2f
    GLAPI void(APIENTRY *oglProgramUniform2fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform2fv oglProgramUniform2fv
    GLAPI void(APIENTRY *oglProgramUniform2i)(GLuint, GLint, GLint, GLint);
#define glProgramUniform2i oglProgramUniform2i
    GLAPI void(APIENTRY *oglProgramUniform2iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform2iv oglProgramUniform2iv
    GLAPI void(APIENTRY *oglProgramUniform2ui)(GLuint, GLint, GLuint, GLuint);
#define glProgramUniform2ui oglProgramUniform2ui
    GLAPI void(APIENTRY *oglProgramUniform2uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniform2uiv oglProgramUniform2uiv
    GLAPI void(APIENTRY *oglProgramUniform3d)(GLuint, GLint, GLdouble, GLdouble, GLdouble);
#define glProgramUniform3d oglProgramUniform3d
    GLAPI void(APIENTRY *oglProgramUniform3dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform3dv oglProgramUniform3dv
    GLAPI void(APIENTRY *oglProgramUniform3f)(GLuint, GLint, GLfloat, GLfloat, GLfloat);
#define glProgramUniform3f oglProgramUniform3f
    GLAPI void(APIENTRY *oglProgramUniform3fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform3fv oglProgramUniform3fv
    GLAPI void(APIENTRY *oglProgramUniform3i)(GLuint, GLint, GLint, GLint, GLint);
#define glProgramUniform3i oglProgramUniform3i
    GLAPI void(APIENTRY *oglProgramUniform3iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform3iv oglProgramUniform3iv
    GLAPI void(APIENTRY *oglProgramUniform3ui)(GLuint, GLint, GLuint, GLuint, GLuint);
#define glProgramUniform3ui oglProgramUniform3ui
    GLAPI void(APIENTRY *oglProgramUniform3uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniform3uiv oglProgramUniform3uiv
    GLAPI void(APIENTRY *oglProgramUniform4d)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble);
#define glProgramUniform4d oglProgramUniform4d
    GLAPI void(APIENTRY *oglProgramUniform4dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform4dv oglProgramUniform4dv
    GLAPI void(APIENTRY *oglProgramUniform4f)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
#define glProgramUniform4f oglProgramUniform4f
    GLAPI void(APIENTRY *oglProgramUniform4fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform4fv oglProgramUniform4fv
    GLAPI void(APIENTRY *oglProgramUniform4i)(GLuint, GLint, GLint, GLint, GLint, GLint);
#define glProgramUniform4i oglProgramUniform4i
    GLAPI void(APIENTRY *oglProgramUniform4iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform4iv oglProgramUniform4iv
    GLAPI void(APIENTRY *oglProgramUniform4ui)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
#define glProgramUniform4ui oglProgramUniform4ui
    GLAPI void(APIENTRY *oglProgramUniform4uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniform4uiv oglProgramUniform4uiv
    GLAPI void(APIENTRY *oglProgramUniformMatrix2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix2dv oglProgramUniformMatrix2dv
    GLAPI void(APIENTRY *oglProgramUniformMatrix2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix2fv oglProgramUniformMatrix2fv
    GLAPI void(APIENTRY *oglProgramUniformMatrix2x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix2x3dv oglProgramUniformMatrix2x3dv
    GLAPI void(APIENTRY *oglProgramUniformMatrix2x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix2x3fv oglProgramUniformMatrix2x3fv
    GLAPI void(APIENTRY *oglProgramUniformMatrix2x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix2x4dv oglProgramUniformMatrix2x4dv
    GLAPI void(APIENTRY *oglProgramUniformMatrix2x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix2x4fv oglProgramUniformMatrix2x4fv
    GLAPI void(APIENTRY *oglProgramUniformMatrix3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix3dv oglProgramUniformMatrix3dv
    GLAPI void(APIENTRY *oglProgramUniformMatrix3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix3fv oglProgramUniformMatrix3fv
    GLAPI void(APIENTRY *oglProgramUniformMatrix3x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix3x2dv oglProgramUniformMatrix3x2dv
    GLAPI void(APIENTRY *oglProgramUniformMatrix3x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix3x2fv oglProgramUniformMatrix3x2fv
    GLAPI void(APIENTRY *oglProgramUniformMatrix3x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix3x4dv oglProgramUniformMatrix3x4dv
    GLAPI void(APIENTRY *oglProgramUniformMatrix3x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix3x4fv oglProgramUniformMatrix3x4fv
    GLAPI void(APIENTRY *oglProgramUniformMatrix4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix4dv oglProgramUniformMatrix4dv
    GLAPI void(APIENTRY *oglProgramUniformMatrix4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix4fv oglProgramUniformMatrix4fv
    GLAPI void(APIENTRY *oglProgramUniformMatrix4x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix4x2dv oglProgramUniformMatrix4x2dv
    GLAPI void(APIENTRY *oglProgramUniformMatrix4x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix4x2fv oglProgramUniformMatrix4x2fv
    GLAPI void(APIENTRY *oglProgramUniformMatrix4x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix4x3dv oglProgramUniformMatrix4x3dv
    GLAPI void(APIENTRY *oglProgramUniformMatrix4x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix4x3fv oglProgramUniformMatrix4x3fv
    GLAPI void(APIENTRY *oglReleaseShaderCompiler)(void);
#define glReleaseShaderCompiler oglReleaseShaderCompiler
    GLAPI void(APIENTRY *oglScissorArrayv)(GLuint, GLsizei, const GLint *);
#define glScissorArrayv oglScissorArrayv
    GLAPI void(APIENTRY *oglScissorIndexed)(GLuint, GLint, GLint, GLsizei, GLsizei);
#define glScissorIndexed oglScissorIndexed
    GLAPI void(APIENTRY *oglScissorIndexedv)(GLuint, const GLint *);
#define glScissorIndexedv oglScissorIndexedv
    GLAPI void(APIENTRY *oglShaderBinary)(GLsizei, const GLuint *, GLenum, const void *, GLsizei);
#define glShaderBinary oglShaderBinary
    GLAPI void(APIENTRY *oglUseProgramStages)(GLuint, GLbitfield, GLuint);
#define glUseProgramStages oglUseProgramStages
    GLAPI void(APIENTRY *oglValidateProgramPipeline)(GLuint);
#define glValidateProgramPipeline oglValidateProgramPipeline
    GLAPI void(APIENTRY *oglVertexAttribL1d)(GLuint, GLdouble);
#define glVertexAttribL1d oglVertexAttribL1d
    GLAPI void(APIENTRY *oglVertexAttribL1dv)(GLuint, const GLdouble *);
#define glVertexAttribL1dv oglVertexAttribL1dv
    GLAPI void(APIENTRY *oglVertexAttribL2d)(GLuint, GLdouble, GLdouble);
#define glVertexAttribL2d oglVertexAttribL2d
    GLAPI void(APIENTRY *oglVertexAttribL2dv)(GLuint, const GLdouble *);
#define glVertexAttribL2dv oglVertexAttribL2dv
    GLAPI void(APIENTRY *oglVertexAttribL3d)(GLuint, GLdouble, GLdouble, GLdouble);
#define glVertexAttribL3d oglVertexAttribL3d
    GLAPI void(APIENTRY *oglVertexAttribL3dv)(GLuint, const GLdouble *);
#define glVertexAttribL3dv oglVertexAttribL3dv
    GLAPI void(APIENTRY *oglVertexAttribL4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
#define glVertexAttribL4d oglVertexAttribL4d
    GLAPI void(APIENTRY *oglVertexAttribL4dv)(GLuint, const GLdouble *);
#define glVertexAttribL4dv oglVertexAttribL4dv
    GLAPI void(APIENTRY *oglVertexAttribLPointer)(GLuint, GLint, GLenum, GLsizei, const void *);
#define glVertexAttribLPointer oglVertexAttribLPointer
    GLAPI void(APIENTRY *oglViewportArrayv)(GLuint, GLsizei, const GLfloat *);
#define glViewportArrayv oglViewportArrayv
    GLAPI void(APIENTRY *oglViewportIndexedf)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
#define glViewportIndexedf oglViewportIndexedf
    GLAPI void(APIENTRY *oglViewportIndexedfv)(GLuint, const GLfloat *);
#define glViewportIndexedfv oglViewportIndexedfv

    /* GL_VERSION_4_2 */

    GLAPI void(APIENTRY *oglBindImageTexture)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
#define glBindImageTexture oglBindImageTexture
    GLAPI void(APIENTRY *oglDrawArraysInstancedBaseInstance)(GLenum, GLint, GLsizei, GLsizei, GLuint);
#define glDrawArraysInstancedBaseInstance oglDrawArraysInstancedBaseInstance
    GLAPI void(APIENTRY *oglDrawElementsInstancedBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint);
#define glDrawElementsInstancedBaseInstance oglDrawElementsInstancedBaseInstance
    GLAPI void(APIENTRY *oglDrawElementsInstancedBaseVertexBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint);
#define glDrawElementsInstancedBaseVertexBaseInstance oglDrawElementsInstancedBaseVertexBaseInstance
    GLAPI void(APIENTRY *oglDrawTransformFeedbackInstanced)(GLenum, GLuint, GLsizei);
#define glDrawTransformFeedbackInstanced oglDrawTransformFeedbackInstanced
    GLAPI void(APIENTRY *oglDrawTransformFeedbackStreamInstanced)(GLenum, GLuint, GLuint, GLsizei);
#define glDrawTransformFeedbackStreamInstanced oglDrawTransformFeedbackStreamInstanced
    GLAPI void(APIENTRY *oglGetActiveAtomicCounterBufferiv)(GLuint, GLuint, GLenum, GLint *);
#define glGetActiveAtomicCounterBufferiv oglGetActiveAtomicCounterBufferiv
    GLAPI void(APIENTRY *oglGetInternalformativ)(GLenum, GLenum, GLenum, GLsizei, GLint *);
#define glGetInternalformativ oglGetInternalformativ
    GLAPI void(APIENTRY *oglMemoryBarrier)(GLbitfield);
#define glMemoryBarrier oglMemoryBarrier
    GLAPI void(APIENTRY *oglTexStorage1D)(GLenum, GLsizei, GLenum, GLsizei);
#define glTexStorage1D oglTexStorage1D
    GLAPI void(APIENTRY *oglTexStorage2D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
#define glTexStorage2D oglTexStorage2D
    GLAPI void(APIENTRY *oglTexStorage3D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
#define glTexStorage3D oglTexStorage3D

    /* GL_VERSION_4_3 */

    GLAPI void(APIENTRY *oglBindVertexBuffer)(GLuint, GLuint, GLintptr, GLsizei);
#define glBindVertexBuffer oglBindVertexBuffer
    GLAPI void(APIENTRY *oglClearBufferData)(GLenum, GLenum, GLenum, GLenum, const void *);
#define glClearBufferData oglClearBufferData
    GLAPI void(APIENTRY *oglClearBufferSubData)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
#define glClearBufferSubData oglClearBufferSubData
    GLAPI void(APIENTRY *oglCopyImageSubData)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
#define glCopyImageSubData oglCopyImageSubData
    GLAPI void(APIENTRY *oglDebugMessageCallback)(GLDEBUGPROC, const void *);
#define glDebugMessageCallback oglDebugMessageCallback
    GLAPI void(APIENTRY *oglDebugMessageControl)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
#define glDebugMessageControl oglDebugMessageControl
    GLAPI void(APIENTRY *oglDebugMessageInsert)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *);
#define glDebugMessageInsert oglDebugMessageInsert
    GLAPI void(APIENTRY *oglDispatchCompute)(GLuint, GLuint, GLuint);
#define glDispatchCompute oglDispatchCompute
    GLAPI void(APIENTRY *oglDispatchComputeIndirect)(GLintptr);
#define glDispatchComputeIndirect oglDispatchComputeIndirect
    GLAPI void(APIENTRY *oglFramebufferParameteri)(GLenum, GLenum, GLint);
#define glFramebufferParameteri oglFramebufferParameteri
    GLAPI GLuint(APIENTRY *oglGetDebugMessageLog)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *);
#define glGetDebugMessageLog oglGetDebugMessageLog
    GLAPI void(APIENTRY *oglGetFramebufferParameteriv)(GLenum, GLenum, GLint *);
#define glGetFramebufferParameteriv oglGetFramebufferParameteriv
    GLAPI void(APIENTRY *oglGetInternalformati64v)(GLenum, GLenum, GLenum, GLsizei, GLint64 *);
#define glGetInternalformati64v oglGetInternalformati64v
    GLAPI void(APIENTRY *oglGetObjectLabel)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetObjectLabel oglGetObjectLabel
    GLAPI void(APIENTRY *oglGetObjectPtrLabel)(const void *, GLsizei, GLsizei *, GLchar *);
#define glGetObjectPtrLabel oglGetObjectPtrLabel
    GLAPI void(APIENTRY *oglGetPointerv)(GLenum, void **);
#define glGetPointerv oglGetPointerv
    GLAPI void(APIENTRY *oglGetProgramInterfaceiv)(GLuint, GLenum, GLenum, GLint *);
#define glGetProgramInterfaceiv oglGetProgramInterfaceiv
    GLAPI GLuint(APIENTRY *oglGetProgramResourceIndex)(GLuint, GLenum, const GLchar *);
#define glGetProgramResourceIndex oglGetProgramResourceIndex
    GLAPI GLint(APIENTRY *oglGetProgramResourceLocation)(GLuint, GLenum, const GLchar *);
#define glGetProgramResourceLocation oglGetProgramResourceLocation
    GLAPI GLint(APIENTRY *oglGetProgramResourceLocationIndex)(GLuint, GLenum, const GLchar *);
#define glGetProgramResourceLocationIndex oglGetProgramResourceLocationIndex
    GLAPI void(APIENTRY *oglGetProgramResourceName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetProgramResourceName oglGetProgramResourceName
    GLAPI void(APIENTRY *oglGetProgramResourceiv)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *);
#define glGetProgramResourceiv oglGetProgramResourceiv
    GLAPI void(APIENTRY *oglInvalidateBufferData)(GLuint);
#define glInvalidateBufferData oglInvalidateBufferData
    GLAPI void(APIENTRY *oglInvalidateBufferSubData)(GLuint, GLintptr, GLsizeiptr);
#define glInvalidateBufferSubData oglInvalidateBufferSubData
    GLAPI void(APIENTRY *oglInvalidateFramebuffer)(GLenum, GLsizei, const GLenum *);
#define glInvalidateFramebuffer oglInvalidateFramebuffer
    GLAPI void(APIENTRY *oglInvalidateSubFramebuffer)(GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
#define glInvalidateSubFramebuffer oglInvalidateSubFramebuffer
    GLAPI void(APIENTRY *oglInvalidateTexImage)(GLuint, GLint);
#define glInvalidateTexImage oglInvalidateTexImage
    GLAPI void(APIENTRY *oglInvalidateTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
#define glInvalidateTexSubImage oglInvalidateTexSubImage
    GLAPI void(APIENTRY *oglMultiDrawArraysIndirect)(GLenum, const void *, GLsizei, GLsizei);
#define glMultiDrawArraysIndirect oglMultiDrawArraysIndirect
    GLAPI void(APIENTRY *oglMultiDrawElementsIndirect)(GLenum, GLenum, const void *, GLsizei, GLsizei);
#define glMultiDrawElementsIndirect oglMultiDrawElementsIndirect
    GLAPI void(APIENTRY *oglObjectLabel)(GLenum, GLuint, GLsizei, const GLchar *);
#define glObjectLabel oglObjectLabel
    GLAPI void(APIENTRY *oglObjectPtrLabel)(const void *, GLsizei, const GLchar *);
#define glObjectPtrLabel oglObjectPtrLabel
    GLAPI void(APIENTRY *oglPopDebugGroup)(void);
#define glPopDebugGroup oglPopDebugGroup
    GLAPI void(APIENTRY *oglPushDebugGroup)(GLenum, GLuint, GLsizei, const GLchar *);
#define glPushDebugGroup oglPushDebugGroup
    GLAPI void(APIENTRY *oglShaderStorageBlockBinding)(GLuint, GLuint, GLuint);
#define glShaderStorageBlockBinding oglShaderStorageBlockBinding
    GLAPI void(APIENTRY *oglTexBufferRange)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr);
#define glTexBufferRange oglTexBufferRange
    GLAPI void(APIENTRY *oglTexStorage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
#define glTexStorage2DMultisample oglTexStorage2DMultisample
    GLAPI void(APIENTRY *oglTexStorage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
#define glTexStorage3DMultisample oglTexStorage3DMultisample
    GLAPI void(APIENTRY *oglTextureView)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint);
#define glTextureView oglTextureView
    GLAPI void(APIENTRY *oglVertexAttribBinding)(GLuint, GLuint);
#define glVertexAttribBinding oglVertexAttribBinding
    GLAPI void(APIENTRY *oglVertexAttribFormat)(GLuint, GLint, GLenum, GLboolean, GLuint);
#define glVertexAttribFormat oglVertexAttribFormat
    GLAPI void(APIENTRY *oglVertexAttribIFormat)(GLuint, GLint, GLenum, GLuint);
#define glVertexAttribIFormat oglVertexAttribIFormat
    GLAPI void(APIENTRY *oglVertexAttribLFormat)(GLuint, GLint, GLenum, GLuint);
#define glVertexAttribLFormat oglVertexAttribLFormat
    GLAPI void(APIENTRY *oglVertexBindingDivisor)(GLuint, GLuint);
#define glVertexBindingDivisor oglVertexBindingDivisor

    /* GL_VERSION_4_4 */

    GLAPI void(APIENTRY *oglBindBuffersBase)(GLenum, GLuint, GLsizei, const GLuint *);
#define glBindBuffersBase oglBindBuffersBase
    GLAPI void(APIENTRY *oglBindBuffersRange)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *);
#define glBindBuffersRange oglBindBuffersRange
    GLAPI void(APIENTRY *oglBindImageTextures)(GLuint, GLsizei, const GLuint *);
#define glBindImageTextures oglBindImageTextures
    GLAPI void(APIENTRY *oglBindSamplers)(GLuint, GLsizei, const GLuint *);
#define glBindSamplers oglBindSamplers
    GLAPI void(APIENTRY *oglBindTextures)(GLuint, GLsizei, const GLuint *);
#define glBindTextures oglBindTextures
    GLAPI void(APIENTRY *oglBindVertexBuffers)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
#define glBindVertexBuffers oglBindVertexBuffers
    GLAPI void(APIENTRY *oglBufferStorage)(GLenum, GLsizeiptr, const void *, GLbitfield);
#define glBufferStorage oglBufferStorage
    GLAPI void(APIENTRY *oglClearTexImage)(GLuint, GLint, GLenum, GLenum, const void *);
#define glClearTexImage oglClearTexImage
    GLAPI void(APIENTRY *oglClearTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
#define glClearTexSubImage oglClearTexSubImage

    /* GL_VERSION_4_5 */

    GLAPI void(APIENTRY *oglBindTextureUnit)(GLuint, GLuint);
#define glBindTextureUnit oglBindTextureUnit
    GLAPI void(APIENTRY *oglBlitNamedFramebuffer)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
#define glBlitNamedFramebuffer oglBlitNamedFramebuffer
    GLAPI GLenum(APIENTRY *oglCheckNamedFramebufferStatus)(GLuint, GLenum);
#define glCheckNamedFramebufferStatus oglCheckNamedFramebufferStatus
    GLAPI void(APIENTRY *oglClearNamedBufferData)(GLuint, GLenum, GLenum, GLenum, const void *);
#define glClearNamedBufferData oglClearNamedBufferData
    GLAPI void(APIENTRY *oglClearNamedBufferSubData)(GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
#define glClearNamedBufferSubData oglClearNamedBufferSubData
    GLAPI void(APIENTRY *oglClearNamedFramebufferfi)(GLuint, GLenum, const GLfloat, GLint);
#define glClearNamedFramebufferfi oglClearNamedFramebufferfi
    GLAPI void(APIENTRY *oglClearNamedFramebufferfv)(GLuint, GLenum, GLint, const GLfloat *);
#define glClearNamedFramebufferfv oglClearNamedFramebufferfv
    GLAPI void(APIENTRY *oglClearNamedFramebufferiv)(GLuint, GLenum, GLint, const GLint *);
#define glClearNamedFramebufferiv oglClearNamedFramebufferiv
    GLAPI void(APIENTRY *oglClearNamedFramebufferuiv)(GLuint, GLenum, GLint, const GLuint *);
#define glClearNamedFramebufferuiv oglClearNamedFramebufferuiv
    GLAPI void(APIENTRY *oglClipControl)(GLenum, GLenum);
#define glClipControl oglClipControl
    GLAPI void(APIENTRY *oglCompressedTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTextureSubImage1D oglCompressedTextureSubImage1D
    GLAPI void(APIENTRY *oglCompressedTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTextureSubImage2D oglCompressedTextureSubImage2D
    GLAPI void(APIENTRY *oglCompressedTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTextureSubImage3D oglCompressedTextureSubImage3D
    GLAPI void(APIENTRY *oglCopyNamedBufferSubData)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr);
#define glCopyNamedBufferSubData oglCopyNamedBufferSubData
    GLAPI void(APIENTRY *oglCopyTextureSubImage1D)(GLuint, GLint, GLint, GLint, GLint, GLsizei);
#define glCopyTextureSubImage1D oglCopyTextureSubImage1D
    GLAPI void(APIENTRY *oglCopyTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
#define glCopyTextureSubImage2D oglCopyTextureSubImage2D
    GLAPI void(APIENTRY *oglCopyTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
#define glCopyTextureSubImage3D oglCopyTextureSubImage3D
    GLAPI void(APIENTRY *oglCreateBuffers)(GLsizei, GLuint *);
#define glCreateBuffers oglCreateBuffers
    GLAPI void(APIENTRY *oglCreateFramebuffers)(GLsizei, GLuint *);
#define glCreateFramebuffers oglCreateFramebuffers
    GLAPI void(APIENTRY *oglCreateProgramPipelines)(GLsizei, GLuint *);
#define glCreateProgramPipelines oglCreateProgramPipelines
    GLAPI void(APIENTRY *oglCreateQueries)(GLenum, GLsizei, GLuint *);
#define glCreateQueries oglCreateQueries
    GLAPI void(APIENTRY *oglCreateRenderbuffers)(GLsizei, GLuint *);
#define glCreateRenderbuffers oglCreateRenderbuffers
    GLAPI void(APIENTRY *oglCreateSamplers)(GLsizei, GLuint *);
#define glCreateSamplers oglCreateSamplers
    GLAPI void(APIENTRY *oglCreateTextures)(GLenum, GLsizei, GLuint *);
#define glCreateTextures oglCreateTextures
    GLAPI void(APIENTRY *oglCreateTransformFeedbacks)(GLsizei, GLuint *);
#define glCreateTransformFeedbacks oglCreateTransformFeedbacks
    GLAPI void(APIENTRY *oglCreateVertexArrays)(GLsizei, GLuint *);
#define glCreateVertexArrays oglCreateVertexArrays
    GLAPI void(APIENTRY *oglDisableVertexArrayAttrib)(GLuint, GLuint);
#define glDisableVertexArrayAttrib oglDisableVertexArrayAttrib
    GLAPI void(APIENTRY *oglEnableVertexArrayAttrib)(GLuint, GLuint);
#define glEnableVertexArrayAttrib oglEnableVertexArrayAttrib
    GLAPI void(APIENTRY *oglFlushMappedNamedBufferRange)(GLuint, GLintptr, GLsizeiptr);
#define glFlushMappedNamedBufferRange oglFlushMappedNamedBufferRange
    GLAPI void(APIENTRY *oglGenerateTextureMipmap)(GLuint);
#define glGenerateTextureMipmap oglGenerateTextureMipmap
    GLAPI void(APIENTRY *oglGetCompressedTextureImage)(GLuint, GLint, GLsizei, void *);
#define glGetCompressedTextureImage oglGetCompressedTextureImage
    GLAPI void(APIENTRY *oglGetCompressedTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *);
#define glGetCompressedTextureSubImage oglGetCompressedTextureSubImage
    GLAPI GLenum(APIENTRY *oglGetGraphicsResetStatus)(void);
#define glGetGraphicsResetStatus oglGetGraphicsResetStatus
    GLAPI void(APIENTRY *oglGetNamedBufferParameteri64v)(GLuint, GLenum, GLint64 *);
#define glGetNamedBufferParameteri64v oglGetNamedBufferParameteri64v
    GLAPI void(APIENTRY *oglGetNamedBufferParameteriv)(GLuint, GLenum, GLint *);
#define glGetNamedBufferParameteriv oglGetNamedBufferParameteriv
    GLAPI void(APIENTRY *oglGetNamedBufferPointerv)(GLuint, GLenum, void **);
#define glGetNamedBufferPointerv oglGetNamedBufferPointerv
    GLAPI void(APIENTRY *oglGetNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, void *);
#define glGetNamedBufferSubData oglGetNamedBufferSubData
    GLAPI void(APIENTRY *oglGetNamedFramebufferAttachmentParameteriv)(GLuint, GLenum, GLenum, GLint *);
#define glGetNamedFramebufferAttachmentParameteriv oglGetNamedFramebufferAttachmentParameteriv
    GLAPI void(APIENTRY *oglGetNamedFramebufferParameteriv)(GLuint, GLenum, GLint *);
#define glGetNamedFramebufferParameteriv oglGetNamedFramebufferParameteriv
    GLAPI void(APIENTRY *oglGetNamedRenderbufferParameteriv)(GLuint, GLenum, GLint *);
#define glGetNamedRenderbufferParameteriv oglGetNamedRenderbufferParameteriv
    GLAPI void(APIENTRY *oglGetQueryBufferObjecti64v)(GLuint, GLuint, GLenum, GLintptr);
#define glGetQueryBufferObjecti64v oglGetQueryBufferObjecti64v
    GLAPI void(APIENTRY *oglGetQueryBufferObjectiv)(GLuint, GLuint, GLenum, GLintptr);
#define glGetQueryBufferObjectiv oglGetQueryBufferObjectiv
    GLAPI void(APIENTRY *oglGetQueryBufferObjectui64v)(GLuint, GLuint, GLenum, GLintptr);
#define glGetQueryBufferObjectui64v oglGetQueryBufferObjectui64v
    GLAPI void(APIENTRY *oglGetQueryBufferObjectuiv)(GLuint, GLuint, GLenum, GLintptr);
#define glGetQueryBufferObjectuiv oglGetQueryBufferObjectuiv
    GLAPI void(APIENTRY *oglGetTextureImage)(GLuint, GLint, GLenum, GLenum, GLsizei, void *);
#define glGetTextureImage oglGetTextureImage
    GLAPI void(APIENTRY *oglGetTextureLevelParameterfv)(GLuint, GLint, GLenum, GLfloat *);
#define glGetTextureLevelParameterfv oglGetTextureLevelParameterfv
    GLAPI void(APIENTRY *oglGetTextureLevelParameteriv)(GLuint, GLint, GLenum, GLint *);
#define glGetTextureLevelParameteriv oglGetTextureLevelParameteriv
    GLAPI void(APIENTRY *oglGetTextureParameterIiv)(GLuint, GLenum, GLint *);
#define glGetTextureParameterIiv oglGetTextureParameterIiv
    GLAPI void(APIENTRY *oglGetTextureParameterIuiv)(GLuint, GLenum, GLuint *);
#define glGetTextureParameterIuiv oglGetTextureParameterIuiv
    GLAPI void(APIENTRY *oglGetTextureParameterfv)(GLuint, GLenum, GLfloat *);
#define glGetTextureParameterfv oglGetTextureParameterfv
    GLAPI void(APIENTRY *oglGetTextureParameteriv)(GLuint, GLenum, GLint *);
#define glGetTextureParameteriv oglGetTextureParameteriv
    GLAPI void(APIENTRY *oglGetTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
#define glGetTextureSubImage oglGetTextureSubImage
    GLAPI void(APIENTRY *oglGetTransformFeedbacki64_v)(GLuint, GLenum, GLuint, GLint64 *);
#define glGetTransformFeedbacki64_v oglGetTransformFeedbacki64_v
    GLAPI void(APIENTRY *oglGetTransformFeedbacki_v)(GLuint, GLenum, GLuint, GLint *);
#define glGetTransformFeedbacki_v oglGetTransformFeedbacki_v
    GLAPI void(APIENTRY *oglGetTransformFeedbackiv)(GLuint, GLenum, GLint *);
#define glGetTransformFeedbackiv oglGetTransformFeedbackiv
    GLAPI void(APIENTRY *oglGetVertexArrayIndexed64iv)(GLuint, GLuint, GLenum, GLint64 *);
#define glGetVertexArrayIndexed64iv oglGetVertexArrayIndexed64iv
    GLAPI void(APIENTRY *oglGetVertexArrayIndexediv)(GLuint, GLuint, GLenum, GLint *);
#define glGetVertexArrayIndexediv oglGetVertexArrayIndexediv
    GLAPI void(APIENTRY *oglGetVertexArrayiv)(GLuint, GLenum, GLint *);
#define glGetVertexArrayiv oglGetVertexArrayiv
    GLAPI void(APIENTRY *oglGetnCompressedTexImage)(GLenum, GLint, GLsizei, void *);
#define glGetnCompressedTexImage oglGetnCompressedTexImage
    GLAPI void(APIENTRY *oglGetnTexImage)(GLenum, GLint, GLenum, GLenum, GLsizei, void *);
#define glGetnTexImage oglGetnTexImage
    GLAPI void(APIENTRY *oglGetnUniformdv)(GLuint, GLint, GLsizei, GLdouble *);
#define glGetnUniformdv oglGetnUniformdv
    GLAPI void(APIENTRY *oglGetnUniformfv)(GLuint, GLint, GLsizei, GLfloat *);
#define glGetnUniformfv oglGetnUniformfv
    GLAPI void(APIENTRY *oglGetnUniformiv)(GLuint, GLint, GLsizei, GLint *);
#define glGetnUniformiv oglGetnUniformiv
    GLAPI void(APIENTRY *oglGetnUniformuiv)(GLuint, GLint, GLsizei, GLuint *);
#define glGetnUniformuiv oglGetnUniformuiv
    GLAPI void(APIENTRY *oglInvalidateNamedFramebufferData)(GLuint, GLsizei, const GLenum *);
#define glInvalidateNamedFramebufferData oglInvalidateNamedFramebufferData
    GLAPI void(APIENTRY *oglInvalidateNamedFramebufferSubData)(GLuint, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
#define glInvalidateNamedFramebufferSubData oglInvalidateNamedFramebufferSubData
    GLAPI void *(APIENTRY *oglMapNamedBuffer)(GLuint, GLenum);
#define glMapNamedBuffer oglMapNamedBuffer
    GLAPI void *(APIENTRY *oglMapNamedBufferRange)(GLuint, GLintptr, GLsizeiptr, GLbitfield);
#define glMapNamedBufferRange oglMapNamedBufferRange
    GLAPI void(APIENTRY *oglMemoryBarrierByRegion)(GLbitfield);
#define glMemoryBarrierByRegion oglMemoryBarrierByRegion
    GLAPI void(APIENTRY *oglNamedBufferData)(GLuint, GLsizeiptr, const void *, GLenum);
#define glNamedBufferData oglNamedBufferData
    GLAPI void(APIENTRY *oglNamedBufferStorage)(GLuint, GLsizeiptr, const void *, GLbitfield);
#define glNamedBufferStorage oglNamedBufferStorage
    GLAPI void(APIENTRY *oglNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, const void *);
#define glNamedBufferSubData oglNamedBufferSubData
    GLAPI void(APIENTRY *oglNamedFramebufferDrawBuffer)(GLuint, GLenum);
#define glNamedFramebufferDrawBuffer oglNamedFramebufferDrawBuffer
    GLAPI void(APIENTRY *oglNamedFramebufferDrawBuffers)(GLuint, GLsizei, const GLenum *);
#define glNamedFramebufferDrawBuffers oglNamedFramebufferDrawBuffers
    GLAPI void(APIENTRY *oglNamedFramebufferParameteri)(GLuint, GLenum, GLint);
#define glNamedFramebufferParameteri oglNamedFramebufferParameteri
    GLAPI void(APIENTRY *oglNamedFramebufferReadBuffer)(GLuint, GLenum);
#define glNamedFramebufferReadBuffer oglNamedFramebufferReadBuffer
    GLAPI void(APIENTRY *oglNamedFramebufferRenderbuffer)(GLuint, GLenum, GLenum, GLuint);
#define glNamedFramebufferRenderbuffer oglNamedFramebufferRenderbuffer
    GLAPI void(APIENTRY *oglNamedFramebufferTexture)(GLuint, GLenum, GLuint, GLint);
#define glNamedFramebufferTexture oglNamedFramebufferTexture
    GLAPI void(APIENTRY *oglNamedFramebufferTextureLayer)(GLuint, GLenum, GLuint, GLint, GLint);
#define glNamedFramebufferTextureLayer oglNamedFramebufferTextureLayer
    GLAPI void(APIENTRY *oglNamedRenderbufferStorage)(GLuint, GLenum, GLsizei, GLsizei);
#define glNamedRenderbufferStorage oglNamedRenderbufferStorage
    GLAPI void(APIENTRY *oglNamedRenderbufferStorageMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
#define glNamedRenderbufferStorageMultisample oglNamedRenderbufferStorageMultisample
    GLAPI void(APIENTRY *oglReadnPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
#define glReadnPixels oglReadnPixels
    GLAPI void(APIENTRY *oglTextureBarrier)(void);
#define glTextureBarrier oglTextureBarrier
    GLAPI void(APIENTRY *oglTextureBuffer)(GLuint, GLenum, GLuint);
#define glTextureBuffer oglTextureBuffer
    GLAPI void(APIENTRY *oglTextureBufferRange)(GLuint, GLenum, GLuint, GLintptr, GLsizeiptr);
#define glTextureBufferRange oglTextureBufferRange
    GLAPI void(APIENTRY *oglTextureParameterIiv)(GLuint, GLenum, const GLint *);
#define glTextureParameterIiv oglTextureParameterIiv
    GLAPI void(APIENTRY *oglTextureParameterIuiv)(GLuint, GLenum, const GLuint *);
#define glTextureParameterIuiv oglTextureParameterIuiv
    GLAPI void(APIENTRY *oglTextureParameterf)(GLuint, GLenum, GLfloat);
#define glTextureParameterf oglTextureParameterf
    GLAPI void(APIENTRY *oglTextureParameterfv)(GLuint, GLenum, const GLfloat *);
#define glTextureParameterfv oglTextureParameterfv
    GLAPI void(APIENTRY *oglTextureParameteri)(GLuint, GLenum, GLint);
#define glTextureParameteri oglTextureParameteri
    GLAPI void(APIENTRY *oglTextureParameteriv)(GLuint, GLenum, const GLint *);
#define glTextureParameteriv oglTextureParameteriv
    GLAPI void(APIENTRY *oglTextureStorage1D)(GLuint, GLsizei, GLenum, GLsizei);
#define glTextureStorage1D oglTextureStorage1D
    GLAPI void(APIENTRY *oglTextureStorage2D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
#define glTextureStorage2D oglTextureStorage2D
    GLAPI void(APIENTRY *oglTextureStorage2DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
#define glTextureStorage2DMultisample oglTextureStorage2DMultisample
    GLAPI void(APIENTRY *oglTextureStorage3D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
#define glTextureStorage3D oglTextureStorage3D
    GLAPI void(APIENTRY *oglTextureStorage3DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
#define glTextureStorage3DMultisample oglTextureStorage3DMultisample
    GLAPI void(APIENTRY *oglTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
#define glTextureSubImage1D oglTextureSubImage1D
    GLAPI void(APIENTRY *oglTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
#define glTextureSubImage2D oglTextureSubImage2D
    GLAPI void(APIENTRY *oglTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
#define glTextureSubImage3D oglTextureSubImage3D
    GLAPI void(APIENTRY *oglTransformFeedbackBufferBase)(GLuint, GLuint, GLuint);
#define glTransformFeedbackBufferBase oglTransformFeedbackBufferBase
    GLAPI void(APIENTRY *oglTransformFeedbackBufferRange)(GLuint, GLuint, GLuint, GLintptr, GLsizeiptr);
#define glTransformFeedbackBufferRange oglTransformFeedbackBufferRange
    GLAPI GLboolean(APIENTRY *oglUnmapNamedBuffer)(GLuint);
#define glUnmapNamedBuffer oglUnmapNamedBuffer
    GLAPI void(APIENTRY *oglVertexArrayAttribBinding)(GLuint, GLuint, GLuint);
#define glVertexArrayAttribBinding oglVertexArrayAttribBinding
    GLAPI void(APIENTRY *oglVertexArrayAttribFormat)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint);
#define glVertexArrayAttribFormat oglVertexArrayAttribFormat
    GLAPI void(APIENTRY *oglVertexArrayAttribIFormat)(GLuint, GLuint, GLint, GLenum, GLuint);
#define glVertexArrayAttribIFormat oglVertexArrayAttribIFormat
    GLAPI void(APIENTRY *oglVertexArrayAttribLFormat)(GLuint, GLuint, GLint, GLenum, GLuint);
#define glVertexArrayAttribLFormat oglVertexArrayAttribLFormat
    GLAPI void(APIENTRY *oglVertexArrayBindingDivisor)(GLuint, GLuint, GLuint);
#define glVertexArrayBindingDivisor oglVertexArrayBindingDivisor
    GLAPI void(APIENTRY *oglVertexArrayElementBuffer)(GLuint, GLuint);
#define glVertexArrayElementBuffer oglVertexArrayElementBuffer
    GLAPI void(APIENTRY *oglVertexArrayVertexBuffer)(GLuint, GLuint, GLuint, GLintptr, GLsizei);
#define glVertexArrayVertexBuffer oglVertexArrayVertexBuffer
    GLAPI void(APIENTRY *oglVertexArrayVertexBuffers)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
#define glVertexArrayVertexBuffers oglVertexArrayVertexBuffers

    GLAPI HGLRC wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int *attribList);
}

#endif
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

    HGLRC wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int *attribList)
    {
        BIND_OGL_ADDR( HGLRC, wglCreateContextAttribsARB, HDC hDC, HGLRC hShareContext, const int *attribList )
        return CALL_PROC_ADDR(wglCreateContextAttribsARB, hDC, hShareContext, attribList)
    }

    GLuint glCreateShader(GLenum type)
    {
        BIND_OGL_ADDR(GLuint, glCreateShader, GLenum type)
        return CALL_PROC_ADDR(glCreateShader, type)
    }

    void glAttachShader(GLuint program, GLuint shader)
    {
        BIND_OGL_ADDR(const GLubyte *, glAttachShader, GLuint program, GLuint shader )
        CALL_PROC_ADDR(glAttachShader, program, shader )
    }

    void glCompileShader(GLuint shader)
    {
        BIND_OGL_ADDR(void, glCompileShader, GLuint shader)
        CALL_PROC_ADDR(glCompileShader, shader)
    }

    void glShaderSource(GLuint shader, GLsizei count, const GLchar* *string, const GLint *length)
    {
        BIND_OGL_ADDR(void, glShaderSource, GLuint shader, GLsizei count, const GLchar* *string, const GLint *length)
        CALL_PROC_ADDR(glShaderSource, shader, count, string, length)
    }

    void glGetProgramiv(GLuint program, GLenum pname, GLint *params)
    {
        BIND_OGL_ADDR(void, glGetProgramiv, GLuint program, GLenum pname, GLint *params )
        CALL_PROC_ADDR(glGetProgramiv, program, pname, params)
    }

    void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
    {
        BIND_OGL_ADDR(void, glGetProgramInfoLog, GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog )
        CALL_PROC_ADDR(glGetProgramInfoLog, program, bufSize, length, infoLog)
    }

    void glGetShaderiv(GLuint shader, GLenum pname, GLint *params)
    {
        BIND_OGL_ADDR(void, glGetShaderiv, GLuint shader, GLenum pname, GLint *params )
        CALL_PROC_ADDR(glGetShaderiv, shader, pname, params )
    }

    void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
    {
        BIND_OGL_ADDR(void, glGetShaderInfoLog, GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog )
        CALL_PROC_ADDR(glGetShaderInfoLog, shader, bufSize, length, infoLog)
    }

    GLuint glCreateProgram()
    {
        BIND_OGL_ADDR(GLuint, glCreateProgram )
        return CALL_PROC_ADDR(glCreateProgram)
    }

    void glDeleteProgram(GLuint program)
    {
        BIND_OGL_ADDR(void, glDeleteProgram, GLuint program )
        CALL_PROC_ADDR(glDeleteProgram, program)
    }

    void glDeleteShader(GLuint shader)
    {
        BIND_OGL_ADDR(void, glDeleteShader, GLuint shader)
        CALL_PROC_ADDR(glDeleteShader, shader)
    }

    void glDetachShader(GLuint program, GLuint shader)
    {
        BIND_OGL_ADDR(void, glDetachShader, GLuint program, GLuint shader)
        CALL_PROC_ADDR(glDetachShader, program, shader )
    }

    void glProgramParameteri(GLuint program, GLenum pname, GLint value)
    {
        BIND_OGL_ADDR(void, glProgramParameteri, GLuint program, GLenum pname, GLint value)
        CALL_PROC_ADDR(glProgramParameteri, program, pname, value)
    }

    void glLinkProgram(GLuint program)
    {
        BIND_OGL_ADDR(void, glLinkProgram, GLuint program)
        CALL_PROC_ADDR(glLinkProgram, program)
    }

    void glGenProgramPipelines(GLsizei n, GLuint *pipelines)
    {
        BIND_OGL_ADDR(void, glGenProgramPipelines, GLsizei n, GLuint *pipelines)
        CALL_PROC_ADDR(glGenProgramPipelines, n, pipelines )
    }

    void glBindProgramPipeline(GLuint pipeline)
    {
        BIND_OGL_ADDR(void, glBindProgramPipeline, GLuint pipeline)
        CALL_PROC_ADDR(glBindProgramPipeline, pipeline)
    }

    void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
    {
        BIND_OGL_ADDR(void, glUseProgramStages, GLuint pipeline, GLbitfield stages, GLuint program )
        CALL_PROC_ADDR(glUseProgramStages, pipeline, stages, program )
    }

    GLuint glCreateShaderProgramv(GLenum type, GLsizei count, const char **strings)
    {
        BIND_OGL_ADDR(GLuint, glCreateShaderProgramv, GLenum type, GLsizei count, const char **strings)
        return CALL_PROC_ADDR(glCreateShaderProgramv, type, count, strings)
    }

    void glGenVertexArrays(GLsizei n, GLuint *arrays)
    {
        BIND_OGL_ADDR(void, glGenVertexArrays, GLsizei n, GLuint *arrays)
        CALL_PROC_ADDR(glGenVertexArrays, n, arrays)
    }

    void glBindVertexArray(GLuint array)
    {
        BIND_OGL_ADDR(void, glBindVertexArray, GLuint array)
        CALL_PROC_ADDR(glBindVertexArray, array)
    }

    void glGenBuffers(GLsizei n, GLuint * buffers)
    {
        BIND_OGL_ADDR(void, glGenBuffers, GLsizei n, GLuint * buffers)
        CALL_PROC_ADDR(glGenBuffers, n, buffers)
    }

    void glBindBuffer(GLenum target, GLuint buffer)
    {
        BIND_OGL_ADDR(void, glBindBuffer, GLenum target, GLuint buffer)
        CALL_PROC_ADDR(glBindBuffer, target, buffer)
    }

    void glBufferData(GLenum target,
                      GLsizeiptr size,
                      const GLvoid * data,
                      GLenum usage)
    {
        BIND_OGL_ADDR(void, glBufferData, GLenum target,
                      GLsizeiptr size,
                      const GLvoid * data,
                      GLenum usage)
        CALL_PROC_ADDR(glBufferData, target,
                       size,
                       data,
                       usage)
    }

    void glVertexAttribPointer(GLuint index,
                               GLint size,
                               GLenum type,
                               GLboolean normalized,
                               GLsizei stride,
                               const GLvoid * pointer)
    {
        BIND_OGL_ADDR(void, glVertexAttribPointer, GLuint index,
                      GLint size,
                      GLenum type,
                      GLboolean normalized,
                      GLsizei stride,
                      const GLvoid * pointer)
        CALL_PROC_ADDR(glVertexAttribPointer, index,
                       size,
                       type,
                       normalized,
                       stride,
                       pointer)
    }

    void glEnableVertexAttribArray(GLuint index)
    {
        BIND_OGL_ADDR(void, glEnableVertexAttribArray, GLuint index )
        CALL_PROC_ADDR(glEnableVertexAttribArray, index )
    }

}
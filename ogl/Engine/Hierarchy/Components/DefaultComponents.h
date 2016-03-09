#ifndef __DEFAULT_COMPONENTS__
#define __DEFAULT_COMPONENTS__

#include "Types.h"

#include "Effect.h"
#include "EffectLibrary.h"
#include "ogl.h"

#include "io/Resource.h"

struct Transform
{
    Transform(float3 position = float3(0.0f), float3 rotation = float3(0.0f), float3 scale = float3(0.0f))
        : position(position)
        , rotation(rotation)
        , scale(scale)
    {}

    float3 position, rotation, scale;
};

struct Velocity
{
    Velocity(float3 direction = float3(1.0f, 0.0f, 0.0f), float speed = 0.0f)
        : direction(direction)
        , speed(speed)
    {}

    float3 direction;
    float speed;
};

struct Renderer
{
    Renderer()
    {
        GLuint VBO;
        ogl::glGenBuffers(1, &VBO);

        float points[] =
        {
            0.0f,  0.5f,  0.0f,
            0.5f, -0.5f,  0.0f,
            -0.5f, -0.5f,  0.0f
        };

        ogl::CHECK_OGL_ERROR("Before all");
        GLuint vbo = 0;
        ogl::glGenBuffers(1, &vbo);
        ogl::glBindBuffer(GL_ARRAY_BUFFER, vbo);
        ogl::glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
        ogl::CHECK_OGL_ERROR("after vbo");

        vao = 0;
        ogl::CHECK_OGL_ERROR("before vao");
        ogl::glGenVertexArrays(1, &vao);
        ogl::glBindVertexArray(vao);
        ogl::glEnableVertexAttribArray(0);
        ogl::glBindBuffer(GL_ARRAY_BUFFER, vbo);
        ogl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        ogl::CHECK_OGL_ERROR("after vao");

        iris::io::CResource vert("shaders/first_triangle/ft.vert");
        const std::string lVtxShaderSrc(vert.GetFileContent());
        CShaderSPtr lVertexShader(new CShader());
        lVertexShader->Create(ShaderType::eST_Vertex, lVtxShaderSrc.c_str());

        iris::io::CResource frag("shaders/first_triangle/ft.frag");
        const std::string lFragShaderSrc(frag.GetFileContent());
        CShaderSPtr lFragmentShader(new CShader());
        lFragmentShader->Create(ShaderType::eST_Fragment, lFragShaderSrc.c_str());

        CEffectSPtr lEffect( new CEffect(lVertexShader, lFragmentShader) );
        mEffect = lEffect;
    }

    GLuint vao;
    CEffectSPtr mEffect;
};

#endif //__DEFAULT_COMPONENTS__
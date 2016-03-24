#ifndef __DEFAULT_COMPONENTS__
#define __DEFAULT_COMPONENTS__

#include "Types.h"

#include "Effect.h"
#include "EffectLibrary.h"
#include "ogl.h"
#include "Geometry.h"
#include "Mesh/Cube.h"

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

extern uint32 flags = 0;
struct Renderer
{
    Renderer()
    {
        mGeom = CGeometrySPtr(new CGeometry());
        float points[] =
        {
            0.0f,  0.5f,  0.0f,
            0.5f, -0.5f,  0.0f,
            -0.5f, -0.5f,  0.0f,
        };

       mCube.Init(5.0f, 5.0f, 5.0f);

        flags = eGD_ScreenPosition;

        mGeom->Create( flags, &points, nullptr, 12, uint32(0) );

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

    CCube mCube;
    CGeometrySPtr mGeom;
    CEffectSPtr mEffect;
};

#endif //__DEFAULT_COMPONENTS__
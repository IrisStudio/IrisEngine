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
        mCube.Init(5.0f, 5.0f, 5.0f);
        mCube.SetColor(float4(0.6f, 0.3f, 0.8f, 1.0f));
    }

    CCube mCube;
};

#endif //__DEFAULT_COMPONENTS__
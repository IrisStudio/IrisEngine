#ifndef __DEFAULT_COMPONENTS__
#define __DEFAULT_COMPONENTS__

#include "Types.h"

#include "Effect.h"
#include "EffectLibrary.h"
#include "ogl.h"
#include "Geometry.h"
#include "Mesh/Cube.h"
#include "Mesh/FullScreenQuad.h"

#include "io/Resource.h"

#include "io/ObjLoader.h"

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
		CObjLoader lLoaderObj;
		lLoaderObj.Load(CResource("models/cube/cube.obj"));
        CEffectLibrary::Instance().Init();
        mQuad.Init(5.0f, 5.0f, 5.0f);
        mQuad2.Init(5.0f, 5.0f, 5.0f);
    }

    CCube mCube;
    CFullScreenQuad mQuad;
    CFullScreenQuad mQuad2;
};

#endif //__DEFAULT_COMPONENTS__
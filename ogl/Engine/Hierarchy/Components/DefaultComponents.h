#ifndef __DEFAULT_COMPONENTS__
#define __DEFAULT_COMPONENTS__

#include "Types.h"

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

#endif //__DEFAULT_COMPONENTS__
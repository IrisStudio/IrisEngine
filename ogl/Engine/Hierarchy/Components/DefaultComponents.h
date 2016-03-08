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

#endif //__DEFAULT_COMPONENTS__
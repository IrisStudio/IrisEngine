#ifndef _TYPES_H_
#define _TYPES_H_

#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

typedef signed char         int8;
typedef short               int16;
typedef int                 int32;
typedef __int64             int64;

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned __int64    uint64;

typedef glm::vec2           float2;
typedef glm::vec3           float3;
typedef glm::vec4           float4;

typedef glm::highp_mat3x3   float3x3;
typedef glm::highp_mat4x4   float4x4;

#endif

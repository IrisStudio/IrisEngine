#ifndef _TYPES_H_
#define _TYPES_H_

#include <memory>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/compatibility.hpp>

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

typedef glm::ivec2           int2;
typedef glm::ivec3           int3;
typedef glm::ivec4           int4;

typedef glm::uvec2           uint2;
typedef glm::uvec3           uint3;
typedef glm::uvec4           uint4;

typedef glm::mat3            float3x3;
typedef glm::mat4            float4x4;

typedef glm::quat            quaternion;


#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);   \
    void operator=(const TypeName&)

#define CHECKED_DELETE(Ptr) \
    if( Ptr )                 \
    {                         \
        delete Ptr;             \
        Ptr = nullptr;          \
    }                         \

#endif

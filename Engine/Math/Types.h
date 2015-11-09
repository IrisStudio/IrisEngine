#ifndef _TYPES_H_
#define _TYPES_H_

namespace iris
{
typedef signed char         int8;
typedef short               int16;
typedef int                 int32;
typedef __int64             int64;

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned __int64    uint64;

typedef Vector2<float>      float2;
typedef Vector2<double>     double2;
typedef Vector2<int32>      int2;
typedef Vector2<uint32>     uint2;

typedef Vector4<float>      float4;
typedef Vector4<double>     double4;
typedef Vector4<int32>      int4;
typedef Vector4<uint32>     uint4;

}

#endif

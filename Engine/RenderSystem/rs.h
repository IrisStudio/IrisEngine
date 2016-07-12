#ifndef __IRIS_RS__
#define __IRIS_RS__

#include "Types.h"
#include "EnumString.h"

enum WindowSize
{
    eST_Windowed = 0,
    eST_FitDesktop,
    eST_FullScreen
};

enum Extension
{
};

enum GBufferTarget
{
    eGBT_AlbedoSpec = 0,
    eGBT_WorldSpacePosition,
    eGBT_WorldSpaceNormal,
    eGBT_Depth,
    eGBT_Count
};

Begin_Enum_String(Extension)
{
}
End_Enum_String;

enum TextureType
{
    eTT_1D = 0x0DE0,
    eTT_2D = 0x0DE1,
    eTT_3D = 0
};


enum ShaderType
{
    eST_Vertex    = 0x8B31,
    eST_Fragment  = 0x8B30,
    eST_Geometry  = 0x8DD9,
};

Begin_Enum_String(ShaderType)
{
    Enum_String_Id(eST_Vertex, "Vertex");
    Enum_String_Id(eST_Fragment, "Fragment");
    Enum_String_Id(eST_Geometry, "Geometry");
}
End_Enum_String;

enum BlendEquation
{
    eBE_Add = 0x8006,
    eBE_Subtract = 0x800A,
    eBE_ReverseSubtract = 0x800B
};

enum BlendFunc
{
    eBF_ZERO = 0,
    eBF_ONE = 1,
    eBF_SRC_COLOR = 0x0300,
    eBF_ONE_MINUS_SRC_COLOR = 0x0301,
    eBF_DST_COLOR = 0x0306,
    eBF_ONE_MINUS_DST_COLOR = 0x0307,
    eBF_SRC_ALPHA = 0x0302,
    eBF_ONE_MINUS_SRC_ALPHA = 0x0303,
    eBF_DST_ALPHA = 0x0304,
    eBF_ONE_MINUS_DST_ALPHA = 0x0305,
    eBF_CONSTANT_COLOR = 0x8001,
    eBF_ONE_MINUS_CONSTANT_COLOR = 0x8002,
    eBF_CONSTANT_ALPHA = 0x8003,
    eBF_ONE_MINUS_CONSTANT_ALPHA = 0x8004,
    eBF_SRC_ALPHA_SATURATE = 0x0308,
};

class CTexture;
typedef std::shared_ptr< CTexture > CTextureSPtr;
typedef std::vector< CTextureSPtr > TTextures;

class CEffect;
typedef std::shared_ptr< CEffect > CEffectSPtr;

#endif
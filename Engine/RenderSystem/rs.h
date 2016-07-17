#ifndef __IRIS_RS__
#define __IRIS_RS__

#include "Types.h"
#include "EnumString.h"

enum BufferBit
{
    eBB_CURRENT_BIT                    = 0x00000001,
    eBB_POINT_BIT                      = 0x00000002,
    eBB_LINE_BIT                       = 0x00000004,
    eBB_POLYGON_BIT                    = 0x00000008,
    eBB_POLYGON_STIPPLE_BIT            = 0x00000010,
    eBB_PIXEL_MODE_BIT                 = 0x00000020,
    eBB_LIGHTING_BIT                   = 0x00000040,
    eBB_FOG_BIT                        = 0x00000080,
    eBB_DEPTH_BUFFER_BIT               = 0x00000100,
    eBB_ACCUM_BUFFER_BIT               = 0x00000200,
    eBB_STENCIL_BUFFER_BIT             = 0x00000400,
    eBB_VIEWPORT_BIT                   = 0x00000800,
    eBB_TRANSFORM_BIT                  = 0x00001000,
    eBB_ENABLE_BIT                     = 0x00002000,
    eBB_COLOR_BUFFER_BIT               = 0x00004000,
    eBB_HINT_BIT                       = 0x00008000,
    eBB_EVAL_BIT                       = 0x00010000,
    eBB_LIST_BIT                       = 0x00020000,
    eBB_TEXTURE_BIT                    = 0x00040000,
    eBB_SCISSOR_BIT                    = 0x00080000,
    eBB_ALL_ATTRIB_BITS                = 0x000fffff
};

enum WindowSize
{
    eST_Windowed = 0,
    eST_FitDesktop,
    eST_FullScreen
};

enum Extension
{
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
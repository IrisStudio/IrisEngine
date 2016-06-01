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

class CTexture;
typedef std::shared_ptr< CTexture > CTextureSPtr;
typedef std::vector< CTextureSPtr > TTextures;

class CEffect;
typedef std::shared_ptr< CEffect > CEffectSPtr;

#endif
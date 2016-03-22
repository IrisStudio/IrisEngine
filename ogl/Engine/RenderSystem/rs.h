#ifndef __IRIS_RS__
#define __IRIS_RS__

#include "Types.h"
#include "EnumString.h"


enum ShaderType
{
    eST_Vertex    = 0x8B31,
    eST_Fragment  = 0x8B30,
    eST_Geometry  = 0x8DD9,
};

enum GeometryData
{
    eGD_Position        = 1 << 0,
    eGD_ScreenPosition  = 1 << 1,
    eGD_Normal          = 1 << 2,
    eGD_Tangent         = 1 << 3,
    eGD_Binormal        = 1 << 4
};

Begin_Enum_String(ShaderType)
{
    Enum_String_Id(eST_Vertex, "Vertex");
    Enum_String_Id(eST_Fragment, "Fragment");
    Enum_String_Id(eST_Geometry, "Geometry");
}
End_Enum_String;

#endif
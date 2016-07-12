#pragma once
#ifndef _IRIS_GPH_
#define _IRIS_GPH_

#include "Types.h"

#include "EnumString.h"

enum TextureChanel
{
    eTC_Diffuse = 0,
    eTC_Specular,
    eTC_SpecularHighlight,
    eTC_BakedLight,
    eTC_Alpha,
    eTC_Displacement,
    eTC_Bump,
    eTC_Count
};

enum MeshResource
{
    eMR_Binary = 0,
    eMR_Obj,
    eMR_FBX,
    eMR_Count
};

enum GeometryData
{
    eGD_Position        = 1 << 0,
    eGD_ScreenPosition  = 1 << 1,
    eGD_Normal          = 1 << 2,
    eGD_Tangent         = 1 << 3,
    eGD_Binormal        = 1 << 4,
    eGD_UV              = 1 << 6,
    eGD_UV2             = 1 << 7,
    eGeometryData_Count = 7
};

enum RenderableProperties
{
    eRP_Default = 0,
    eRP_DiffuseColor,
    eRP_DiffuseMap,
    eRP_NormalMap,
    eRP_SelfIlumMap,
    eRP_SpecularMap,
    eRP_DisplacementMap,
    eRP_TransparentMap,
    eRP_Roughness,
    eRP_Count
};

Begin_Enum_String(RenderableProperties)
{
    Enum_String_Id(eRP_Default, "default");
    Enum_String_Id(eRP_DiffuseColor, "diffuse_color");
    Enum_String_Id(eRP_DiffuseMap, "diffuse_map");
    Enum_String_Id(eRP_NormalMap, "normal_map");
    Enum_String_Id(eRP_SelfIlumMap, "self_ilum_map");
    Enum_String_Id(eRP_SpecularMap, "specular_map");
    Enum_String_Id(eRP_DisplacementMap, "displacement_map");
    Enum_String_Id(eRP_TransparentMap, "transparent_map");
}
End_Enum_String;

class CMaterial;
typedef std::shared_ptr< CMaterial > CMaterialSPtr;

class CSubMaterial;
typedef std::shared_ptr< CSubMaterial > CSubMaterialSPtr;

#endif
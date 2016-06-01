#pragma once
#ifndef _IRIS_GPH_
#define _IRIS_GPH_

#include "Types.h"

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
	eGD_Position		= 1 << 0,
	eGD_ScreenPosition	= 1 << 1,
	eGD_Normal			= 1 << 2,
	eGD_Tangent			= 1 << 3,
	eGD_Binormal		= 1 << 4,
	eGD_UV				= 1 << 6,
	eGD_UV2				= 1 << 7,
	eGeometryData_Count = 7
};

enum RenderableProperties
{
	eRP_Default = 0,
	eRP_Color,
	eRP_DiffuseMap,
	eRP_NormalMap,
	eRP_SelfIlumMap,
	eRP_SpecularMap,
	eRP_Count
};

class CMaterial;
typedef std::shared_ptr< CMaterial > CMaterialSPtr;

class CSubMaterial;
typedef std::shared_ptr< CSubMaterial > CSubMaterialSPtr;

#endif
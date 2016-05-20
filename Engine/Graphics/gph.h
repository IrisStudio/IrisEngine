#pragma once
#ifndef _IRIS_GPH_
#define _IRIS_GPH_

#include "Types.h"

enum TextureChanel
{
  eTC_Diffuse = 0,
  eTC_Normal,
  eTC_SelfIlum,
  eTC_Specular,
  eTC_Count
};

enum MeshResource
{
	eMR_Binary = 0,
	eMR_Obj,
	eMR_FBX,
	eMR_Count
};

class CMaterial;
typedef std::shared_ptr< CMaterial > CMaterialSPtr;

class CSubMaterial;
typedef std::shared_ptr< CSubMaterial > CSubMaterialSPtr;

#endif
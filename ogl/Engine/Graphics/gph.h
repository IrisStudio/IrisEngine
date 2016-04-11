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

class CMaterial;
typedef std::shared_ptr< CMaterial > CMaterialSPtr;

#endif
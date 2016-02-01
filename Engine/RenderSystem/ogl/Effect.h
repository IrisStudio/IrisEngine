#ifndef __EFFECT__
#define __EFFECT__

#include "Types.h"
#include <loki/SmartPtr.h>

#include "Shader.h"

class CEffect
{
public:
  CEffect(CShaderSPtr aVertexShader, CShaderSPtr aPixelShader);
  virtual ~CEffect();
  uint32 GetID() const;
private:
  uint32 mID;
};

inline uint32 CEffect::GetID() const { return mID; }

typedef Loki::SmartPtr<CEffect> CEffectSPtr;

#endif
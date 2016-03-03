#ifndef __EFFECT_LIBRARY__
#define __EFFECT_LIBRARY__

#include <Types.h>
#include <map>
#include "Shader.h"
#include "Effect.h"

class CEffectLibrary
{
public:
  CEffectLibrary();
  virtual ~CEffectLibrary();
  CEffectSPtr CreateEffect(const char* aEffectFile);
private:
  typedef std::map< uint32, CShaderSPtr > TMapShader;
  TMapShader mVertexShaderLibrary;
  TMapShader mPixelShaderLibrary;
};

#endif

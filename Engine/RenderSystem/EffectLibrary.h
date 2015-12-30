#ifndef __EFFECT_LIBRARY__
#define __EFFECT_LIBRARY__

#include <Types.h>
#include "RenderSystem.h"

class CEffectLibrary
{
public:
  CEffectLibrary();
  virtual ~CEffectLibrary();
  CEffectSPtr CreateEffect( const char* aEffectFile );
};

#endif

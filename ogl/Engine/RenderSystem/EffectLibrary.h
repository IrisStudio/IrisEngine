#ifndef __EFFECT_LIBRARY__
#define __EFFECT_LIBRARY__

#include "Types.h"
#include "Shader.h"
#include "Effect.h"
#include "Singleton.h"

class CEffectLibrary : public Singleton< CEffectLibrary >
{
    public:
        CEffectLibrary();
        virtual ~CEffectLibrary();
        CEffectSPtr CreateEffect(const char* aEffectFile);
        CEffectSPtr GetEffect( uint32 aEffectFlags );
    private:
        typedef std::map< uint32, CShaderSPtr > TMapShader;
        TMapShader mVertexShaderLibrary;
        TMapShader mPixelShaderLibrary;
};

#endif

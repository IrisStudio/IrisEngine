#ifndef __EFFECT_LIBRARY__
#define __EFFECT_LIBRARY__

#include "Types.h"
#include "Shader.h"
#include "Singleton.h"

class CEffect;

class CEffectLibrary : public Singleton< CEffectLibrary >
{
    public:
        CEffectLibrary();
        virtual ~CEffectLibrary();
        void Init();
        CEffect* CreateEffect(const char* aEffectFile);
        CEffect* GetEffect( uint32 aEffectFlags );
    private:
        typedef std::map< uint32, CShaderSPtr > TMapShader;
        typedef std::map< uint32, CEffect* >    TMapEffects;
        TMapShader mVertexShaderLibrary;
        TMapShader mPixelShaderLibrary;
        TMapEffects mEmbedded;
        CEffect* mScreenUV;
};

#endif

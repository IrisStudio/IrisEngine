#ifndef __EFFECT__
#define __EFFECT__

#include "Types.h"

#include "Shader.h"

class CEffect
{
    public:
        CEffect( CShaderSPtr aVertexShader, CShaderSPtr aPixelShader);
        virtual ~CEffect();
        void    Bind();
        uint32  GetID() const;
        void    BindMatrices(const float4x4& M, const float4x4& V, const float4x4& P);

        template <class T>
        void BindFragment(const T& in, const std::string& name);

        template <class T>
        void BindVertex(const T& in, const std::string& name);

    private:
        uint32 mID;
        CShaderSPtr mVertexShader;
        CShaderSPtr mFragmentShader;
};

inline uint32 CEffect::GetID() const
{
    return mID;
}

typedef std::shared_ptr< CEffect > CEffectSPtr;

#endif

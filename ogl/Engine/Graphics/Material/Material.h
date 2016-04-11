#pragma once
#ifndef _CMaterial_
#define _CMaterial_

#include "gph.h"

class CEffect;
class CTexture;

class CMaterial
{
    public:
        CMaterial();
        virtual ~CMaterial();
        void Apply();

        void SetDiffuseColor      (const float4& aColor);
        void SetTexture           (TextureChanel aType, CTexture* aTexture);
        
        const float4& GetDiffuseColor() const;
        CTexture*     GetTexture(TextureChanel aType) const;

    protected:
        CEffect*                mEffect;
        std::vector< CTexture*> mTextures;
        float4                  mColor;

    private:
        DISALLOW_COPY_AND_ASSIGN(CMaterial);
};

#endif
#pragma once
#ifndef _CSubMaterial_
#define _CSubMaterial_

#include "gph.h"
#include "rs.h"

class CEffect;
class CTexture;

class CSubMaterial
{
    public:
        CSubMaterial( uint32 aProperties );
        virtual ~CSubMaterial();
        void Apply();

        void SetDiffuseColor(const float4& aColor);
        void SetTexture(TextureChanel aType, CTextureSPtr aTexture);

        const float4& GetDiffuseColor() const;
        CTextureSPtr  GetTexture(TextureChanel aType) const;

    protected:
        CEffect*             mEffect;
        typedef std::vector< CTextureSPtr > TTextures;
        TTextures         mTextures;
        float4                  mColor;

    private:
        DISALLOW_COPY_AND_ASSIGN(CSubMaterial);
};

#endif
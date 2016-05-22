#pragma once
#ifndef _CSubMaterial_
#define _CSubMaterial_

#include "gph.h"
#include "rs.h"
#include "Named.h"

class CEffect;
class CTexture;

class CSubMaterial : public CNamed
{
    public:
        CSubMaterial();
        virtual ~CSubMaterial();
        void Apply();

        void SetRenderProperties(uint32 aRenderProperties);

    public:
        TTextures           mTextures;
        float3              mAmbientColor;
        float3              mSpecularColor;
        float3              mDiffuseColor;
        float3              mTransmittance;
        float3              mEmission;
        float               mShininess;
        float               mRoughness;
        float               mTransparency;

    private:
        DISALLOW_COPY_AND_ASSIGN(CSubMaterial);

        CEffect*             mEffect;
};

#endif
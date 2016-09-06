#pragma once
#ifndef _CSubMaterial_
#define _CSubMaterial_

#include "gph.h"
#include "rs.h"
#include "Named.h"

class CEffect;
class CTexture;
class CParameters;

class CSubMaterial : public CNamed
{
    public:
        CSubMaterial();
        virtual ~CSubMaterial();
        void Apply();
        void SetEffect( CEffect* aEffect );
        void SetRenderProperties(uint32 aRenderProperties);

    public:
        TTextures           mTextures;
		CParameters*		mParameters;

    private:
        DISALLOW_COPY_AND_ASSIGN(CSubMaterial);

        CEffect*             mEffect;
};

#endif
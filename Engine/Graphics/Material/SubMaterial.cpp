#include "SubMaterial.h"
#include "Effect.h"
#include "Texture.h"

#include "Camera\CameraManager.h"
#include "EffectLibrary.h"

#include <functional>

CSubMaterial::CSubMaterial()
    : CNamed()
    , mEffect( nullptr )
    , mDiffuseColor(float4(1.0f))
    , mAmbientColor(float4(1.0f))
    , mSpecularColor(float4(1.0f))
    , mTransmittance(float4(1.0f))
    , mShininess(1.0f)
    , mRoughness(1.0f)
    , mTransparency(1.0f)
{
    mTextures.resize(eTC_Count);
}

CSubMaterial::~CSubMaterial()
{
}

void CSubMaterial::Apply()
{
    CCamera* lCam = CCameraManager::Instance().GetCurrentCamera();
    float4x4 M, V, P;
    lCam->GetMatrices(P, V, M);
    mEffect->Bind();
    mEffect->BindMatrices(M, V, P);

    for each ( CTextureSPtr lTexture in mTextures )
    {
        if(lTexture)
        {
            lTexture->Bind();
        }
    }
}

void CSubMaterial::SetRenderProperties(uint32 aRenderProperties)
{
    mEffect = CEffectLibrary::Instance().GetEffect(aRenderProperties);
}
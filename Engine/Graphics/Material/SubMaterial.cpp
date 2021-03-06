#include "SubMaterial.h"
#include "Effect.h"
#include "Texture.h"

#include "Camera\CameraManager.h"
#include "EffectLibrary.h"

#include <functional>

CSubMaterial::CSubMaterial()
    : CNamed()
    , mEffect( nullptr )
    , mParameters( nullptr )
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

    for (uint32 i = 0; i < eTC_Count; ++i)
        if (mTextures[i])
        {
            mTextures[i]->Bind(i);
        }
}

void CSubMaterial::SetEffect(CEffect* aEffect)
{
    mEffect = aEffect;
}

void CSubMaterial::SetRenderProperties(uint32 aRenderProperties)
{
    mEffect = CEffectLibrary::Instance().GetEffect(aRenderProperties);
}
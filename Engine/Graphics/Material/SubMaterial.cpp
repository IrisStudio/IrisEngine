#include "SubMaterial.h"
#include "Effect.h"
#include "Texture.h"

#include "Camera\CameraManager.h"
#include "EffectLibrary.h"

#include <functional>

CSubMaterial::CSubMaterial( uint32 aProperties )
    : mEffect(CEffectLibrary::Instance().GetEffect(aProperties))
    , mColor( float4(1.0f) )
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

void CSubMaterial::SetDiffuseColor(const float4& color)
{
    mColor = color;
}

const float4& CSubMaterial::GetDiffuseColor() const
{
    return mColor;
}

void CSubMaterial::SetTexture(TextureChanel aType, CTextureSPtr aTexture)
{
    mTextures[aType] = aTexture;
}

CTextureSPtr CSubMaterial::GetTexture(TextureChanel aType) const
{
    return mTextures[aType];
}
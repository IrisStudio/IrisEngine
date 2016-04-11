#include "Material.h"
#include "Effect.h"
#include "Texture.h"

CMaterial::CMaterial()
    : mEffect(nullptr)
    , mColor( float4(1.0f) )
{
  mTextures.reserve(eTC_Count);
}

CMaterial::~CMaterial()
{
  mTextures.clear();
}

void CMaterial::Apply()
{
}

void CMaterial::SetDiffuseColor(const float4& color)
{
    mColor = color;
}

const float4& CMaterial::GetDiffuseColor() const
{
    return mColor;
}

void CMaterial::SetTexture(TextureChanel aType, CTexture* aTexture)
{
  mTextures[aType] = aTexture;
}

CTexture* CMaterial::GetTexture(TextureChanel aType) const
{
  return mTextures[aType];
}
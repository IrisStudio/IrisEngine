#include "Mesh.h"
#include "Effect.h"
#include "Camera\CameraManager.h"

CMesh::CMesh()
    : mGeometry( new CGeometry() )
    , mEffect(nullptr)
    , mColor( float4(1.0f) )
{
}

CMesh::~CMesh()
{
}

void CMesh::Render()
{
    CCameraSPtr lCam = CCameraManager::Instance().GetCurrentCamera();
    float4x4 M, V, P;
    lCam->GetMatrices(P, V, M);
    mEffect->Bind();
    mEffect->BindMatrices(M, V, P);
    mEffect->BindFragment(mColor, "in_color");
    mTex.Bind();
    mGeometry->Bind();
}

void CMesh::SetColor(const float4& color)
{
    mColor = color;
}

const float4& CMesh::GetColor() const
{
    return mColor;
}

#include "Mesh.h"

#include "Effect.h"
#include "EffectLibrary.h"
#include "io/Resource.h"
#include "Camera\CameraManager.h"

CMesh::CMesh()
    : mGeometry( new CGeometry() )
    , mColor( float4(1.0f) )
{
    iris::io::CResource vert("shaders/cube/cube.vert");
    const std::string lVtxShaderSrc(vert.GetFileContent());
    CShaderSPtr lVertexShader(new CShader());
    lVertexShader->Create(ShaderType::eST_Vertex, lVtxShaderSrc.c_str());

    iris::io::CResource frag("shaders/cube/cube.frag");
    const std::string lFragShaderSrc(frag.GetFileContent());
    CShaderSPtr lFragmentShader(new CShader());
    lFragmentShader->Create(ShaderType::eST_Fragment, lFragShaderSrc.c_str());

    mEffect = CEffectSPtr(new CEffect(lVertexShader, lFragmentShader));
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
    mGeometry->Bind();
}

void CMesh::SetColor(const float4& color)
{
    mColor = color;
}

float4 CMesh::GetColor() const
{
    return mColor;
}

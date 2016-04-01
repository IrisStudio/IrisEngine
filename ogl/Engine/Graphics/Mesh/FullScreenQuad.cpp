#include "FullScreenQuad.h"

#include "io/Resource.h"

CFullScreenQuad::CFullScreenQuad()
    : CMesh()
{
}


CFullScreenQuad::~CFullScreenQuad()
{
}

void CFullScreenQuad::Init( float aLenght, float aWidht, float aHeight )
{
    float vertices[] =
    {
        1.0f,  1.0f, /*UV*/ 0.0f, 0.0f,
        -1.0f, 1.0f, /*UV*/ 0.0f, 1.0f,
        1.0f, -1.0f, /*UV*/ 1.0f, 0.0f,
        -1.0f,-1.0f, /*UV*/ 1.0f, 1.0f,
    };

    uint32 indices[] =
    {
        2,1,3, // second triangle
        0,1,2, // first triangle
    };

    mGeometry->Create(eGD_ScreenPosition|eGD_UV, &vertices, &indices, 4, 6 );

    mTex.Create(eTT_2D, "hola");

    iris::io::CResource vert("shaders/first_triangle/ft.vert");
    const std::string lVtxShaderSrc(vert.GetFileContent());
    CShaderSPtr lVertexShader(new CShader());
    lVertexShader->Create(ShaderType::eST_Vertex, lVtxShaderSrc.c_str());

    iris::io::CResource frag("shaders/first_triangle/ft.frag");
    const std::string lFragShaderSrc(frag.GetFileContent());
    CShaderSPtr lFragmentShader(new CShader());
    lFragmentShader->Create(ShaderType::eST_Fragment, lFragShaderSrc.c_str());

    mEffect = CEffectSPtr(new CEffect(lVertexShader, lFragmentShader));
}
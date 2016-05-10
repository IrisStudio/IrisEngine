#include "FullScreenQuad.h"

#include "io/Resource.h"

#include "EffectLibrary.h"

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

    CGeometrySPtr lGeometry( new CGeometry() );

    lGeometry->Create(eGD_ScreenPosition | eGD_UV, &vertices, &indices, 4, 6 );
    mGeometry.push_back(lGeometry);
}
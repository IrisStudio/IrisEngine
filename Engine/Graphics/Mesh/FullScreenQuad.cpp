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
    float vertices[] = { -1, -1,  // bottom left corner
                         -1,  1, // top left corner
                         1,  1,  // top right corner
                         1, -1, // bottom right corner
                       };

    uint32 indices[] = { 0,1,2, // first triangle (bottom left - top left - top right)
                         0,2,3  // second triangle (bottom left - top right - bottom right)
                       };

    CGeometrySPtr lGeometry( new CGeometry() );
    lGeometry->Create(eGD_ScreenPosition, &vertices, &indices, 4, 6 );
    Resize(1);
    AddGeometry(0, lGeometry);
}